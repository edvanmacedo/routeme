import QtQuick 1.0
import com.nokia.meego 1.0
import com.routeme.types 1.0

PageStackWindow {
    id: rootWindow

    property variant element: ""
    property string address: ""
    property string secondaryForeground: theme.inverted ? "#C8C8C8" : "#505050"

    function componentPush(filename) {
        var component = Qt.createComponent(filename)
        if (component.status === Component.Ready) {
            if (filename === "RouteMePage.qml" && rootWindow.address !== "") {
                pageStack.push(component, { messageText: rootWindow.address })
            } else {
                pageStack.push(component)
            }
        } else {
            console.log("Error when try to load component: "+filename)
        }
    }

    ToolBarLayout {
        id: rootToolbar

        ToolIcon {
            iconId: (screen.currentOrientation === Screen.Landscape)
                     ? "toolbar-back-landscape"  + (theme.inverted ? "" : "-white") : "toolbar-back"
            visible: (pageStack.depth !== 1)

            onClicked: {
                 pageStack.pop();
                 if (pageStack.depth === 1) theme.inverted = false;
             }
        }

        ToolIcon {
            id: sendLocation

            iconSource: "qrc:/qml/data/images/locationviamessage.png"
            visible: !(pageStack.depth !== 1)

            enabled: false
            anchors.right: zoomIn.left

            onClicked: {
                rootWindow.componentPush("RouteMePage.qml")
            }
        }

        ToolIcon {
            id: zoomIn

            iconSource: "qrc:/qml/data/images/zoomin.png"
            visible: !(pageStack.depth !== 1)

            anchors.right: zoomOut.left
            onClicked: {
                element.zoomLevel += 1
            }
        }

        ToolIcon {
            id: zoomOut

            iconSource: "qrc:/qml/data/images/zoomout.png"
            visible: !(pageStack.depth !== 1)

            anchors.right: about.left
            onClicked: {
                element.zoomLevel -= 1
            }
        }

        ToolIcon {
            id: about
            anchors.right: parent.right

            iconSource: "qrc:/qml/data/images/info.png"
            visible: !(pageStack.depth !== 1)

            onClicked: {
                rootWindow.componentPush("qrc:/qml/RouteMeAboutPage.qml")
            }
        }
    }

    Component.onCompleted: {
        var component = Qt.createComponent("MainWindow.qml")
        if (component.status === Component.Ready) {
            var page = component.createObject(pageStack)
            element = page
            pageStack.push(page)
        }
    }
}
