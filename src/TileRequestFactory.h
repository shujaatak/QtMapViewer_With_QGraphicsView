#ifndef TILE_REQUEST_FACTORY
#define TILE_REQUEST_FACTORY

#include "DownloadTileRequest.h"

class TileRequestFactory
{
public:
	TileRequestFactory();
	~TileRequestFactory();

	DownloadTileRequest* createTileRequest(TileInfo info);

private:
	static const QString STANDARD_MAP_SERVER_A;
	static const QString STANDARD_MAP_SERVER_B;
	static const QString STANDARD_MAP_SERVER_C;

	static const QString CYCLE_MAP_SERVER_A;
	static const QString CYCLE_MAP_SERVER_B;
	static const QString CYCLE_MAP_SERVER_C;

	static const QString CYCLE_TRANSPORT_MAP_SERVER_A;
	static const QString CYCLE_TRANSPORT_MAP_SERVER_B;
	static const QString CYCLE_TRANSPORT_MAP_SERVER_C;

	int	standardMapServerIndex;
	int	cycleMapServerIndex;
	int	cycleTransportMapServerIndex;
};

#endif
