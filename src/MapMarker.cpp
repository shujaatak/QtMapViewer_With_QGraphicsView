#include "MapMarker.h"

MapMarker::MapMarker()
{

}

MapMarker::~MapMarker()
{

}

bool MapMarker::operator ==(const MapMarker & m) const
{
    return(m.id == this->id);
}
