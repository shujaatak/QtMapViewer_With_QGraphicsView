#ifndef TILE_MANAGER
#define TILE_MANAGER

#include <QObject>
#include <QImage>
#include <QPoint>
#include <QList>
#include "TileView.h"
#include "Tile.h"
#include "TileLoaderManager.h"
#include "MapMarker.h"

class TileManager : public QObject
{
	Q_OBJECT

	public:
		TileManager(TileView* view);

	public slots:
		void zoomUp();
		void zoomDown();
		void fovChanged(double lat1, double long1, double lat2, double long2, int zoom, bool center);
		void sceneChanged(QRectF rectangle);
		void changeTileType(TileTypeEnum type);

		void addMarker(MapMarker marker);
		void removeMarker(MapMarker marker);
		void editMarker(MapMarker marker);
		void updateMarker();

	private slots:
		void tileReady(Tile tile);

	signals:
		void clearScene();

	private:
		TileLoaderManager tileLoaderManager;
		TileTypeEnum currentTileType;
		QSet<QString>* loadedTileSet;
		QList<MapMarker>* mapMarkerList;
		
		TileView* tileView;

		float	lastestLatitude1;
		float	lastestLongitude1;
		float	lastestLatitude2;
		float	lastestLongitude2;
		int		lastestZoomFactor;
};

#endif
