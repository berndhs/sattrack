import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle {
    id: page1Box;
    width: 300;
    height: 300;
    color: "lightgreen";
    property alias outsidedate: closeButton.text;
    property int numImages: -1;
    onOutsidedateChanged: {
        console.log("date changed to ",outsidedate);
    }

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
