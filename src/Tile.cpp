#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(TileInfo info, QImage image)
{
	this->tileInfo = info;
	this->tileImage = image;
}

Tile::~Tile()
{

}

TileInfo Tile::getTileInfo()
{
	return tileInfo;
}

void Tile::setTileInfo(TileInfo tileInfo)
{
	this->tileInfo = tileInfo;
}

QImage Tile::getImage()
{
	return tileImage;
}

void Tile::setImage(QImage image)
{
	this->tileImage = image;
}
