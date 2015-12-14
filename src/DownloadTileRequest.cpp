#include "DownloadTileRequest.h"

DownloadTileRequest::DownloadTileRequest()
{
}

DownloadTileRequest::DownloadTileRequest(TileInfo info)
{
    this->tileInfo = info;
}

DownloadTileRequest::~DownloadTileRequest()
{
}

TileInfo DownloadTileRequest::getTileInfo()
{
    return tileInfo;
}

void DownloadTileRequest::setTileInfo(TileInfo info)
{
	this->tileInfo = info;
}

QString	DownloadTileRequest::getRequestUrl()
{
	return requestUrl;
}

void DownloadTileRequest::setRequestUrl(QString url)
{
	this->requestUrl = url;
}
