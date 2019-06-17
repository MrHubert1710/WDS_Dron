#include "pathcontroller.h"


void PathController::addPoint(double lat, double lon)
{
        mGeoPath.addCoordinate(QGeoCoordinate(lat, lon));
        if(mGeoPath.size()>1)
            mGeoPath.removeCoordinate(0);
        emit geopathChanged();
}
void PathController::setGeopath(const QGeoPath &geoPath) {
   if (geoPath == mGeoPath)
      return;
   mGeoPath = geoPath;
   emit geopathChanged();
}
