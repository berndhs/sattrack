
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
                dbif.getImages(15);
            }
        }
    }

    Rectangle {
        id: bigRect;
        anchors.fill: parent;
        objectName: "bigRect";
//        color: "lightyellow";
        Text {
            id: imgLabel;
            objectName: "imgLabel";
            width: theImage.width;
            height: 40;
            anchors.left: topRow.right;
            anchors.top: bigRect.top;
            z: bigRect.z+2;
            font.pixelSize: 15;
            text: (theImage.visible ? theImage.source : "no image")
                + "\n" + dbif.currentRemark + "\t" + dbif.currentStamp;
        }
        Row {
            id: topRow;
            objectName: "topRow";
            opacity: 0.8;
            anchors {
                top: bigRect.top;
                left: bigRect.left;
            }
            height: imgLabel.height;
            z: theImage.z+1;
            Button {
                id: exitButton
                objectName: "exitButton";
                width: bigWindow.width/6;
                height: 40;
                text: "Done";
                font.family: "DejaVu Serif";
                onReleased: {
                    console.log("Button Pressed. Entered text: " + exitButton.text);
                    dbif.doQuit();
                }
                background: Rectangle {
                    radius: height/2;
                    color: "lightyellow";
                    border.width: 2;
                    border.color: "yellow";
                }
            }

        }

        Column {
            id: leftButtons;
            visible: theImage.visible;
            anchors {
                left: bigRect.left;
                top: imgLabel.bottom;
                topMargin: 20;
            }
            z: theImage.z+1;
            Button {
                id: backButton;
                height: font.pixelSize*2;
                width: 40;
                opacity: 0.6;
                text: "<";
                font.bold: true;
                onReleased: {
                    console.log("Back Button");
                    dbif.goBack();
                    theImage.source = "image://satpics/" + dbif.nextIdent + "/" + dbif.currentPic;
                }
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 40
                    color: backButton.down ? "#d6d6d6" : "#f6f6f6"
                    border.color: "#26287a"
                    border.width: 3
                    radius: 4
                }
            }
            Button {
                id: fwdButton;
                height: font.pixelSize*2;
                width: 40;
                opacity: 0.6;
                text: ">";
                font.bold: true;
                onReleased: {
                    console.log("Forward Button");
                    dbif.goForward();
                    theImage.source = "image://satpics/" +  dbif.nextIdent + "/" + dbif.currentPic;
                }
                background: Rectangle {
                    implicitWidth: 100
                    implicitHeight: 40
                    color: fwdButton.down ? "#d6d6d6" : "#f6f6f6"
                    border.color: "#26287a"
                    border.width: 3
                    radius: 4
                }
            }
        }


        Image {
            id: theImage;
            objectName: "theImage";
            visible: false;
            anchors {
                left: bigRect.left;
                top: imgLabel.bottom;
            }
            width: bigRect.width;
            height: bigRect.height - imgLabel.height;
            source: "qrc:pics/nopic.jpg"
            property string remark: "don't know";
            z: bigRect.z+1;
        }

        ListView {
            id: theList;
            objectName: "theList";
            visible: true;
            height: bigRect.height;
            width: bigRect.width/2;
            z: theImage.z+1;
            anchors.left: bigRect.left;
            anchors.top:  bigRect.top;
            anchors.topMargin: 100;
            model: dbif.imageModel;
            delegate: Button {
                id: listItem;
                width: identText.width + 50;
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
                    dbif.doCenter(ident,picname,stamp);
                }
            }
        }

//        Page1 {
//            id: subPage;
//            objectName: "subPage";
//            z: bigRect.z+10;
//            anchors {
//                right: bigRect.right;
//                verticalCenter: bigRect.verticalCenter;
//            }

//            outsidedate: dbif.date;
//            numImages: dbif.numImages;
//            Timer {
//                id: getDate;
//                interval: 200;
//                repeat: true;
//                running: true;
//                onTriggered: {
//                    subPage.outsidedate = dbif.date;
//                }
//            }
//        }
        Component.onCompleted: {
            dbif.doConnect();
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
