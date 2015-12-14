#ifndef OFFLINE_TILE_LOADER
#define OFFLINE_TILE_LOADER

#include "Tile.h"
#include <QDir>
#include <QFile>

class OfflineTileLoader : public QObject
{
	Q_OBJECT

	public:
		OfflineTileLoader();
		~OfflineTileLoader();

		QDir	getRepository();
		void	setRepository(QDir);

		void	loadTile(TileInfo info);
		bool	isTileAvailable(TileInfo info);
		
		// should move this to a utility class
		QString getFilenameFromInfo(TileInfo info, QDir directory);

	signals:
		void	offlineTileLoaded(Tile tile);

	private:
		QDir	cacheRepository;
};

#endif
