
///****************************************************************
// * This file is distributed under the following license:
// *
// * Copyright (C) 2017, Bernd Stramm
// *
// *  This program is free software; you can redistribute it and/or
// *  modify it under the terms of the GNU General Public License
// *  as published by the Free Software Foundation; either version 2
// *  of the License, or (at your option) any later version.
// *
// *  This program is distributed in the hope that it will be useful,
// *  but WITHOUT ANY WARRANTY; without even the implied warranty of
// *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// *  GNU General Public License for more details.
// *
// *  You should have received a copy of the GNU General Public License
// *  along with this program; if not, write to the Free Software
// *  Foundation, Inc., 51 Franklin Street, Fifth Floor,
// *  Boston, MA  02110-1301, USA.
// ****************************************************************/


import QtQuick 2.7
import QtQuick.Controls 2.0
import com.berndhs 1.0

ApplicationWindow {
    id: bigWindow;
    objectName: "bigWindow";
    visible: true
    width: 640
    height: 480
    Item {
        id: fakeItem;
        objectName: "fakeItem";
        DBIF {
            id: dbif;
            objectName: "QMLDbif";
            Component.onCompleted: {
                console.log("we have dbif at",dbif);
                dbif.doConnect();
                dbif.getImages();
            }
        }
    }

    Rectangle {
        id: bigRect;
        anchors.fill: parent;
        objectName: "bigRect";
        color: "lightyellow";
        Text {
            id: imgLabel;
            objectName: "imgLabel";
            width: theImage.width;
            height: 19;
            anchors.left: bigRect.left;
            anchors.top: bigRect.top;
            z: bigRect.z+2;
            font.pixelSize: 15;
            text: "?";
        }

        Image {
            id: theImage;
            objectName: "theImage";
            visible: false;
            anchors {
                left: bigRect.left;
                verticalCenter: bigRect.verticalCenter;
            }
            width: 200;
            height: 300;
            source: "qrc:pics/nopic.jpg"
            z: bigRect.z+1;
        }

        ListView {
            id: theList;
            objectName: "theList";
            visible: true;
            height: bigRect.height;
            width: bigRect.width/2;
            z: bigRect.z+1;
            anchors {
                left: bigRect.left;
                verticalCenter: bigRect.verticalCenter;
            }
            model: dbif.imageModel;
            delegate: Button {
                id: listItem;
                width: 200;
                height: 20;
                Text {
                    id: identText;
                    font.pixelSize: 15;
                    text: index + " of "+theList.count+" "+ ident + "_" + picname;
                }
                onReleased: {
                    console.log("they want " ,identText.text);
                    theList.visible = false;
                    theImage.visible = true;
                    theImage.source = "image://satpics/" + ident + "/" + picname;
                    imgLabel.text = theImage.source;
                }
            }
        }

        Page1 {
            id: subPage;
            objectName: "subPage";
            z: bigRect.z+10;
            anchors {
                right: bigRect.right;
                verticalCenter: bigRect.verticalCenter;
            }

            outsidedate: dbif.date;
            numImages: dbif.numImages;
            Timer {
                id: getDate;
                interval: 200;
                repeat: true;
                running: true;
                onTriggered: {
                    subPage.outsidedate = dbif.date;
                }
            }
        }
        Component.onCompleted: {
            dbif.doConnect();
        }
        Row {
            id: bottomRow;
            objectName: "bottomRow";
            anchors {
                bottom: bigRect.bottom;
                horizontalCenter: bigRect.horizontalCenter;
            }
            Button {
                id: exitButton
                objectName: "exitButton";
                width: bigWindow.width/6;
                height: 40;
                text: "Done";
                onReleased: {
                    console.log("Button Pressed. Entered text: " + exitButton.text);
                    dbif.doQuit();
                    Qt.quit();
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
