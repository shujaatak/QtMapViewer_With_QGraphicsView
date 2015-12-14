#ifndef ONLINE_TILE_LOADER
#define ONLINE_TILE_LOADER

#include <QObject>
#include <QNetworkAccessManager>

#include "Tile.h"
#include "TileRequestFactory.h"


class OnlineTileLoader : public QObject
{
	Q_OBJECT

	public:
		OnlineTileLoader();
		~OnlineTileLoader();
		void loadTile(TileInfo info);

	private:
		QNetworkAccessManager*	networkAccesManager;
		TileRequestFactory		tileRequestFactory;
        QString                 requestUserAgent;

	private slots:
		void networkReplyReady(QNetworkReply* reply);

	signals:
		void onlineTileLoaded(Tile tile);
};

#endif
