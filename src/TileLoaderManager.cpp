#include "TileLoaderManager.h"
#include <QDebug>

TileLoaderManager::TileLoaderManager()
{

	cacheRepository = QDir("C://TileCache");

	offlineTileLoader.setRepository(cacheRepository);
	//cachingEnabled = true;
	
	// Connect TileLoaderManager with OnlineTileLoader
	QObject::connect(
		&onlineTileLoader, 
		SIGNAL(onlineTileLoaded(Tile)),
		this, 
		SLOT(onlineTileReady(Tile))
	);

	// Connect TileLoaderManager with OnlineTileLoader
	QObject::connect(
		&offlineTileLoader, 
		SIGNAL(offlineTileLoaded(Tile)),
		this, 
		SLOT(offlineTileReady(Tile))
	);
}

TileLoaderManager::~TileLoaderManager()
{

}

void TileLoaderManager::enableCaching()
{
	cachingEnabled = true;
}

void TileLoaderManager::disableCaching()
{
	cachingEnabled = false;
}

void TileLoaderManager::loadTile(TileInfo info)
{
	if (cachingEnabled == true)
	{
		if(offlineTileLoader.isTileAvailable(info) == true)
		{
			offlineTileLoader.loadTile(info);
		}
		else
		{
			onlineTileLoader.loadTile(info);
		}
	}
	else
	{
		// Request tile loading from online loader
		onlineTileLoader.loadTile(info);
	}
}

void TileLoaderManager::offlineTileReady(Tile tile)
{
	emit tileLoaded(tile);
}

void TileLoaderManager::onlineTileReady(Tile tile)
{
	if (cachingEnabled && offlineTileLoader.isTileAvailable(tile.getTileInfo()) == false)
	{		
		// Ensure Root Directory exist, if not create it
		if(cacheRepository.exists() == false)
		{
			cacheRepository.mkdir(".");
		}

		QString tileTypeFolder = QString("TileType %1").arg(tile.getTileInfo().getTileType());
		QString zoomFolder = QString("ZoomLevel %1").arg(tile.getTileInfo().getZoom());

		QDir tileTypeDirectory(cacheRepository.absolutePath() + "//" + tileTypeFolder);
		
		// Ensure Tile Type Directory exist, if not create it
		if(tileTypeDirectory.exists() == false)
		{
			tileTypeDirectory.mkdir(".");
		}
		QDir zoomDirectory(cacheRepository.absolutePath() + "//" + tileTypeFolder + "//" + zoomFolder);

		// Ensure Zoom Directory Directory exist, if not create it
		if(zoomDirectory.exists() == false)
		{
			zoomDirectory.mkdir(".");
		}

		QString imageName = QString("%1x_%2y_%3z.png").arg(tile.getTileInfo().getX()).arg(tile.getTileInfo().getY()).arg(tile.getTileInfo().getZoom());

		QString imageFullPath = cacheRepository.absolutePath() + "//" + tileTypeFolder + "//" + zoomFolder + "/" + imageName;

		// Verify that same image doesn't exist
		if (!QFile(imageFullPath).exists())
		{
			tile.getImage().save(imageFullPath);
		}
	}

	emit tileLoaded(tile);
}