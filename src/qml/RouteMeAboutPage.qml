import QtQuick 1.0
import com.nokia.meego 1.0

Page {
    id: about

    tools: rootToolbar
    orientationLock: PageOrientation.LockPortrait

    Text {
        id: header
        text: "About"
        font.family: "Nokia Pure Text"
        font.pixelSize: 26

        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Column {
        anchors.top: header.bottom
        anchors.topMargin: 40

        spacing: 20

        Text {
            id: version
            text: "Version: 1.0"
            font.family: "Nokia Pure Text"
            font.pixelSize: 20

            anchors.left: parent.left
            anchors.leftMargin: 10
        }

        Text {
            id: devel
            text: "Development by: INdT"
            font.family: "Nokia Pure Text"
            font.pixelSize: 20

            anchors.left: parent.left
            anchors.leftMargin: 10
        }

        Text {
            id: description
            width: 465
            text: "Route Me application, send your current coordinate by sms and get a route directly for you."
            wrapMode: Text.WordWrap
            font.family: "Nokia Pure Text"
            font.pixelSize: 20

            anchors.left: parent.left
            anchors.leftMargin: 10
        }
    }
}
