#include "TileManager.h"
#include <cmath>
#include "TileCoordinateUtility.h"
#include "qglobal.h"

TileManager::TileManager(TileView* view)
{
	tileView = view;
	loadedTileSet = new QSet<QString>();
	mapMarkerList = new QList<MapMarker>();
	currentTileType = STANDARD;

	// Connect TileManager with TileLoader
	QObject::connect
	(
		&tileLoaderManager,		SIGNAL(tileLoaded(Tile)),
        this,					SLOT(tileReady(Tile))
	);
	// Connect TileManager with View
	// Scene event
	QObject::connect
	(
		tileView,				SIGNAL(visibleSceneChanged(QRectF)),
        this,					SLOT(sceneChanged(QRectF))
	);
	// Zoom Up event
	QObject::connect
	(
		tileView,				SIGNAL(zoomUp()),
		this,					SLOT(zoomUp())
	);
	// Zoom Down event
	QObject::connect
	(
		tileView,				SIGNAL(zoomDown()),
		this,					SLOT(zoomDown())
	);
	// Load first tile
	fovChanged(85.0, -180.0, -85.0, 180, 0, true);
}

void TileManager::zoomUp()
{
	if (lastestZoomFactor > 0)
	{
		lastestZoomFactor--;
		tileView->clearScene();
		loadedTileSet->clear();
		fovChanged(lastestLatitude1, lastestLongitude1, lastestLatitude2, lastestLongitude2, lastestZoomFactor, true);
	}
	
	updateMarker();
	qDebug() << "ZoomUp " << lastestZoomFactor;
}

void TileManager::zoomDown()
{
	if (lastestZoomFactor < 18)
	{
		lastestZoomFactor++;
		tileView->clearScene();
		loadedTileSet->clear();
		fovChanged(lastestLatitude1, lastestLongitude1, lastestLatitude2, lastestLongitude2, lastestZoomFactor, true);
	}

	updateMarker();
	qDebug() << "ZoomDown " << lastestZoomFactor;
}

void TileManager::changeTileType(TileTypeEnum type)
{
	if (type != currentTileType)
	{
		currentTileType = type;
		tileView->clearScene();
		loadedTileSet->clear();
		fovChanged(lastestLatitude1, lastestLongitude1, lastestLatitude2, lastestLongitude2, lastestZoomFactor, true);
	}	
}

void TileManager::fovChanged(double lat1, double long1, double lat2, double long2, int zoom, bool center)
{
	lastestLatitude1 = lat1;
	lastestLongitude1 = long1;
	lastestLatitude2 = lat2;
	lastestLongitude2 = long2;
	lastestZoomFactor = zoom;

	int tileX1, tileX2, tileY1, tileY2;
	TileCoordinateUtility::convertGeoToTileInteger(lat1, long1, zoom, tileX1, tileY1);
	TileCoordinateUtility::convertGeoToTileInteger(lat2, long2, zoom, tileX2, tileY2);
	
	int x1 = qMin(tileX1, tileX2);
	int x2 = qMax(tileX1, tileX2);
	int y1 = qMin(tileY1, tileY2);
	int y2 = qMax(tileY1, tileY2);

	if(center == true)
	{
		double latCenter = lat1 + (lat2 - lat1) / 2.0;
		double longCenter = long1 + (long2 - long1) / 2.0;

		double xTile2, yTile2;
		TileCoordinateUtility::convertGeoToTileDouble(latCenter, longCenter, zoom, xTile2, yTile2);
		QPointF center = QPointF(xTile2 * 256.0, yTile2 * 256.0);

		qDebug() << "New Center Tiles: " << xTile2 << " " << yTile2;
		qDebug() << "New Center Scene: " << xTile2 * 256.0 << " " << yTile2 * 256.0;
		qDebug() << "New Center Deg : " << longCenter << " " << latCenter;

		tileView->centerScene(center);
	}

	for (int i = x1; i <= x2; i++)
	{
		for (int j = y1; j <= y2; j++)
		{
			QString str = QString("%1:%2:%3").arg(i).arg(j).arg(zoom);

			if (loadedTileSet->contains(str))
			{
				// Do nothing
			}
			else
			{
				// Insert value
				loadedTileSet->insert(str);
				// Load tile
				TileInfo info(currentTileType, i, j, zoom);
				tileLoaderManager.loadTile(info);
			}			
		}
	}
}

void TileManager::sceneChanged(QRectF rectangle)
{
	// Convert scene coordinates to tile coordinates
	// Keep floating-point precision
	double startX = rectangle.x() / 256.0;
	double endX = ((rectangle.x() + rectangle.width()) / 256.0);

	double startY = rectangle.y() / 256.0;
	double endY = ((rectangle.y() + rectangle.height()) / 256.0);

	double lat1, lat2, long1, long2;
	TileCoordinateUtility::convertTileDoubleToGeo(startX, startY, lastestZoomFactor, lat1, long1);
	TileCoordinateUtility::convertTileDoubleToGeo(endX, endY, lastestZoomFactor, lat2, long2);

	fovChanged(lat1, long1, lat2, long2, lastestZoomFactor, false);
}

void TileManager::tileReady(Tile tile)
{
	if (tile.getTileInfo().getTileType() == currentTileType)
	{
		if (tile.getTileInfo().getZoom() == lastestZoomFactor)
		{
			tileView->addTile(
				tile.getImage(), 
				tile.getTileInfo().getX(), 
				tile.getTileInfo().getY(), 
				256
				);
		}
		else
		{
			qDebug() << "Wrong zoom factor";
		}
	}
}

void TileManager::addMarker(MapMarker marker)
{
	if (!mapMarkerList->contains(marker))
	{
		mapMarkerList->append(marker);
	}
	updateMarker();
}

void TileManager::removeMarker(MapMarker marker)
{
	if (mapMarkerList->contains(marker))
	{
		mapMarkerList->removeOne(marker);
	}
	updateMarker();
}

void TileManager::editMarker(MapMarker marker)
{
	if (mapMarkerList->contains(marker))
	{
		int index = mapMarkerList->indexOf(marker);
		(*mapMarkerList)[index].latitude = marker.latitude;
		(*mapMarkerList)[index].longitude = marker.longitude;
	}
	updateMarker();
}

void TileManager::updateMarker()
{
	tileView->clearAllMarker();

	for (int i = 0; i < mapMarkerList->size(); i++)
	{
		MapMarker marker = mapMarkerList->at(i);

		double xCoord, yCoord;
		TileCoordinateUtility::convertGeoToTileDouble(marker.latitude, marker.longitude, lastestZoomFactor, xCoord, yCoord);

		tileView->addMarker(marker.id, xCoord * 256.0, yCoord * 256.0, marker.image);
	}
}