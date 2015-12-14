#ifndef DOWNLOAD_TILE_REQUEST
#define DOWNLOAD_TILE_REQUEST

#include <QObject>
#include "TileInfo.h"

class DownloadTileRequest : public QObject
{
	public:
		DownloadTileRequest();
		DownloadTileRequest(TileInfo tileInfo);
		~DownloadTileRequest();

		TileInfo getTileInfo();
		void	 setTileInfo(TileInfo tileInfo);

		QString	 getRequestUrl();
		void	 setRequestUrl(QString url);

	private:
		TileInfo tileInfo;
		QString  requestUrl;
};

#endif
