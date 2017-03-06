import QtQuick 2.7
import QtQuick.Controls 2.0
import com.berndhs 1.0

ApplicationWindow {
    id: bigWindow;
    visible: true
    width: 640
    height: 480
    DBIf {
        id: dbif;
    }

    Rectangle {
        id: bigRect;
        anchors.fill: parent;
        color: "lightyellow";

        Page1 {
            id: subPage;
            anchors.centerIn:parent
            outsidedate: dbif.date;
            numImages: dbif.numImages;
            Timer {
                id: getDate;
                interval: 200;
                repeat: true;
                running: true;
                onTriggered: {
//                    console.log("ticked ",getDate,dbif.date);
                    subPage.outsidedate = dbif.date;
                }
            }
        }
        Component.onCompleted: {
            dbif.doConnect();
        }
        Row {
            id: bottomRow;
            anchors {
                bottom: bigRect.bottom;
                horizontalCenter: bigRect.horizontalCenter;
            }
            Button {
                id: exitButton
                width: bigWindow.width/6;
                height: 40;
                text: "Done";
                onReleased: {
                    Qt.quit();
                }
            }
            Button {
                id: runButton;
                width: exitButton.width;
                height: exitButton.height;
                text: "Run";
                onReleased: {
                    dbif.getImages();
                }
            }

        }
    }

    //    footer: TabBar {
    //        id: tabBar
    //        currentIndex: swipeView.currentIndex
    //        TabButton {
    //            text: qsTr("First")
    //        }
    //        TabButton {
    //            text: qsTr("Second")
    //        }
    //    }
}
