#include "TileRequestFactory.h"

const QString TileRequestFactory::STANDARD_MAP_SERVER_A = "http://a.tile.openstreetmap.org/%1/%2/%3.png";
const QString TileRequestFactory::STANDARD_MAP_SERVER_B = "http://b.tile.openstreetmap.org/%1/%2/%3.png";
const QString TileRequestFactory::STANDARD_MAP_SERVER_C = "http://c.tile.openstreetmap.org/%1/%2/%3.png";

const QString TileRequestFactory::CYCLE_MAP_SERVER_A = "http://a.tile.opencyclemap.org/cycle/%1/%2/%3.png";
const QString TileRequestFactory::CYCLE_MAP_SERVER_B = "http://b.tile.opencyclemap.org/cycle/%1/%2/%3.png";
const QString TileRequestFactory::CYCLE_MAP_SERVER_C = "http://c.tile.opencyclemap.org/cycle/%1/%2/%3.png";

const QString TileRequestFactory::CYCLE_TRANSPORT_MAP_SERVER_A = "http://a.tile2.opencyclemap.org/transport/%1/%2/%3.png";
const QString TileRequestFactory::CYCLE_TRANSPORT_MAP_SERVER_B = "http://b.tile2.opencyclemap.org/transport/%1/%2/%3.png";
const QString TileRequestFactory::CYCLE_TRANSPORT_MAP_SERVER_C = "http://c.tile2.opencyclemap.org/transport/%1/%2/%3.png";

TileRequestFactory::TileRequestFactory()
{

}

TileRequestFactory::~TileRequestFactory()
{

}

DownloadTileRequest* TileRequestFactory::createTileRequest(TileInfo info)
{	
	// Tile fetching url
	QString urlString;

	TileTypeEnum type = info.getTileType();

	switch(type)
	{
		case STANDARD:
			if (standardMapServerIndex % 3 == 0)
			{
				urlString = STANDARD_MAP_SERVER_A;
			}
			else if (standardMapServerIndex % 3 == 1)
			{
				urlString = STANDARD_MAP_SERVER_B;
			}
			else 
			{
				urlString = STANDARD_MAP_SERVER_C;
			}
			standardMapServerIndex++;
			break;
		case CYCLE:
			if (cycleMapServerIndex % 3 == 0)
			{
				urlString = CYCLE_MAP_SERVER_A;
			}
			else if (cycleMapServerIndex % 3 == 1)
			{
				urlString = CYCLE_MAP_SERVER_B;
			}
			else 
			{
				urlString = CYCLE_MAP_SERVER_C;
			}
			cycleMapServerIndex++;
			break;
		case CYCLE_TRANSPORT:
			if (cycleTransportMapServerIndex % 3 == 0)
			{
				urlString = CYCLE_TRANSPORT_MAP_SERVER_A;
			}
			else if (cycleTransportMapServerIndex % 3 == 1)
			{
				urlString = CYCLE_TRANSPORT_MAP_SERVER_B;
			}
			else 
			{
				urlString = CYCLE_TRANSPORT_MAP_SERVER_C;
			}
			cycleTransportMapServerIndex++;
			break;
		default:
			break;
	}

	urlString = urlString.arg(info.getZoom()).arg(info.getX()).arg(info.getY());

	DownloadTileRequest* request = new DownloadTileRequest(info);
	request->setRequestUrl(urlString);

	// Return created request
	return request;
}