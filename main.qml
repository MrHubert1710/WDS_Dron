import QtQuick 2.0
import QtQuick.Window 2.0
import QtLocation 5.6
import QtPositioning 5.6

Item {
    width: 2000
    height: 2000

    visible: true

    Plugin {
        id: mapPlugin
        name: "esri"
    }
    Map {
        id: mapa
        anchors.fill: parent
        plugin: mapPlugin
        center: QtPositioning.coordinate(51.109885, 17.059713)
        zoomLevel: 15

        MapPolyline{
            id: pl
            line.width: 3
            line.color: 'blue'

        }

    }
    function addPoint(){
            var point = pathController.geopath.coordinateAt(pathController.geopath.size()-1)

            var lon = point.longitude;
            var lat = point.latitude;
            mapa.center=QtPositioning.coordinate(lat, lon);
            return point;
        }
        Connections{
            target: pathController
            onGeopathChanged: pl.addCoordinate(addPoint())
        }

        Component.onCompleted: pl.addCoordinate(addPoint())
}
