#ifndef TILE_INFO
#define TILE_INFO

#include "TileTypeEnum.h"

class TileInfo
{
	public:
		TileInfo();
        TileInfo(TileTypeEnum type, int x, int y, int zoom);
	
        TileTypeEnum getTileType();
        void	 setTileType(TileTypeEnum type);
		int		 getX();
		void	 setX(int x);	
		int	     getY();
		void	 setY(int y);
		int	     getZoom();
		void	 setZoom(int zoom);
	
	private:
        TileTypeEnum	tileType;
		int			x;
		int			y;
		int			zoom;
};

#endif
