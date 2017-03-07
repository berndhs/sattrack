
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
        ListView {
            id: theList;
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
                    dbif.doRaise(index,ident,picname);
                }
            }
        }

        Page1 {
            id: subPage;
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
                    console.log("Button Pressed. Entered text: " + exitButton.text);
                    dbif.doQuit();
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
