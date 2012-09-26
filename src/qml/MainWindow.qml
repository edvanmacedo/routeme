import QtQuick 1.0
import com.routeme.types 1.0
import com.nokia.meego 1.0

Page {
    id: mainwindow

    property alias zoomLevel: map.zoomLevel

    tools: rootToolbar

    orientationLock: PageOrientation.LockPortrait

    RoutePositionInfo {
        id: positionInfo

        onCurrentCoordinateAvailable: {
            map.coordinate = currentCoordinate
            currentLocation.coordinate = currentCoordinate
            positionInfo.stopUpdates()

            searchManager.coordinate = currentCoordinate
            searchManager.searchPlace()
        }

        Component.onCompleted: {
            positionInfo.startUpdates()
        }
    }

    RouteSearchManager {
        id: searchManager

        onPlaceAvailable: {
            mainwindow.tools.children[1].enabled = true
            rootWindow.address = "Address: "
            rootWindow.address += "\n"
            rootWindow.address += "City: " + place.address.city
            rootWindow.address += "\n"
            rootWindow.address += "Street: " + place.address.street
            rootWindow.address += "\n"
            rootWindow.address += "Postcode: " + place.address.postcode
            rootWindow.address += "\n"
            rootWindow.address += "Lat: " + place.coordinate.latitude
            rootWindow.address += "\n"
            rootWindow.address += "Lon: " + place.coordinate.longitude
        }
    }

    RouteMap {
        id: map

        width: 480
        height: 864
        currentPixmapLocation: currentLocation
        visible: pageStack.busy ? false : true
        zoomLevel: 13

        onCurrentPixmapLocationClicked: {
            console.log("#### marker coordinate..... " + coordinate.latitude + " -- lon: " + coordinate.longitude);
        }
    }

    MouseArea {
        id: mousearea

        anchors.fill: map
        property bool mouseDown : false
        property int lastX : -1
        property int lastY : -1

        onPressed : {
            mouseDown = true
            lastX = mouse.x
            lastY = mouse.y
        }

        onReleased : {
            mouseDown = false
            lastX = -1
            lastY = -1
        }
        onPositionChanged: {
            if (mouseDown) {
                var dx = mouse.x - lastX
                var dy = mouse.y - lastY
                map.pan(-dx, -dy)
                lastX = mouse.x
                lastY = mouse.y
            }
        }
        onDoubleClicked: {
            map.coordinate = map.screenPositionToCoordinate(Qt.point(mouse.x, mouse.y))
            map.zoomLevel += 1
        }
    }

    RoutePixmap {
        id: currentLocation

        source: ":/qml/data/images/direction0.png"
    }

    RoutePixmap {
        id: balloon

        source: ":/qml/data/images/ballon.png"
    }
}
