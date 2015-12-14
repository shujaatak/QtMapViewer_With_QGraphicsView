#ifndef TILE_LOADER_MANAGER
#define TILE_LOADER_MANAGER

#include "OnlineTileLoader.h"
#include "OfflineTileLoader.h"

#include "Tile.h"
#include "TileInfo.h"

class TileLoaderManager : public QObject
{
	Q_OBJECT

	public:
		TileLoaderManager();
		~TileLoaderManager();

		void enableCaching();
		void disableCaching();
		void loadTile(TileInfo info);

	private slots:
		void offlineTileReady(Tile tile);
		void onlineTileReady(Tile tile);

	private:
		OnlineTileLoader	onlineTileLoader;
		OfflineTileLoader	offlineTileLoader;
		bool				cachingEnabled;
		QDir				cacheRepository;

	signals:
		void tileLoaded(Tile tile);
};

#endif
