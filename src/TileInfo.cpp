#include "TileInfo.h"

TileInfo::TileInfo()
{
	this->tileType = STANDARD;
	this->x = 0;
	this->y = 0;
	this->zoom = 0;
}

TileInfo::TileInfo(TileTypeEnum type, int x, int y, int zoom)
{
	this->tileType = type;
	this->x = x;
	this->y = y;
	this->zoom = zoom;
}

TileTypeEnum TileInfo::getTileType()
{
	return tileType;
}

void	 TileInfo::setTileType(TileTypeEnum type)
{
	this->tileType = type;
}

int		 TileInfo::getX()
{
	return x;
}

void	 TileInfo::setX(int x)
{
	this->x = x;
}

int	     TileInfo::getY()
{
	return y;
}

void	 TileInfo::setY(int y)
{
	this->y = y;
}

int	     TileInfo::getZoom()
{
	return zoom;
}

void	 TileInfo::setZoom(int zoom)
{
	this->zoom = zoom;
}
