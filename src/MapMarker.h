#ifndef MAP_MARKER
#define MAP_MARKER

#include <QImage>

class MapMarker
{
public:
	MapMarker();
	~MapMarker();

public:
	QImage image;
	int id;
	double latitude;
	double longitude;
	
bool operator ==(const MapMarker & m) const;
};

#endif
