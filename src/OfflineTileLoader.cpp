#include "OfflineTileLoader.h"	
#include <QDebug>

OfflineTileLoader::OfflineTileLoader()
{

}

OfflineTileLoader::~OfflineTileLoader()
{

}

QDir OfflineTileLoader::getRepository()
{
	return cacheRepository;
}

void OfflineTileLoader::setRepository(QDir directory)
{
	this->cacheRepository = directory;
}

void OfflineTileLoader::loadTile(TileInfo info)
{
	if (isTileAvailable(info))
	{
		QString filename = getFilenameFromInfo(info, cacheRepository);
		QImage image(filename);

		Tile tile(info, image);

		emit offlineTileLoaded(tile);
	}
}

bool OfflineTileLoader::isTileAvailable(TileInfo info)
{
	if (cacheRepository.exists())
	{
		QFile file(getFilenameFromInfo(info, cacheRepository));
		return file.exists();
	} 
	else
	{
		return false;
	}	
}

QString OfflineTileLoader::getFilenameFromInfo(TileInfo info, QDir directory)
{
	QString tileTypeFolder = QString("TileType %1").arg(info.getTileType());
	QString zoomFolder = QString("ZoomLevel %1").arg(info.getZoom());
	QString imageName = QString("%1x_%2y_%3z.png").arg(info.getX()).arg(info.getY()).arg(info.getZoom());

	QString fileName = directory.absolutePath() + "//" + tileTypeFolder + "//" + zoomFolder + "//" + imageName;
	return fileName;
}