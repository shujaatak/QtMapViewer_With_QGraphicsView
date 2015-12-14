#ifndef TILE
#define TILE

#include <QImage>
#include "TileInfo.h"

class Tile
{
	public:
		Tile();
		Tile(TileInfo info, QImage image);
		~Tile();

		TileInfo getTileInfo();
		void	 setTileInfo(TileInfo tileInfo);	
		QImage	 getImage();
		void	 setImage(QImage image);

	private:
		TileInfo tileInfo;
		QImage	 tileImage;
};

#endif
