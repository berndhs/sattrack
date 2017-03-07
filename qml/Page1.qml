
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

Rectangle {
    id: page1Box;
    width: 300;
    height: 300;
    color: "lightgreen";
    property alias outsidedate: closeButton.text;
    property int numImages: -1;

    Text {
        id: numText;
        text: page1Box.numImages;
        anchors.horizontalCenter: closeButton.horizontalCenter;
        anchors.bottom: closeButton.top;
        anchors.bottomMargin: 10;
    }

    Button {
        id: closeButton;
        anchors.centerIn: page1Box;
        text: page1Box.outsidedate;
        onClicked: {
            console.log("Button Pressed. Entered text: " + closeButton.text);
            Qt.quit();
        }
    }

}
