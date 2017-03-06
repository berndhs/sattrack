import QtQuick 2.7
import QtQuick.Controls 2.0

Rectangle {
    id: page1Box;
    width: 300;
    height: 300;
    color: "lightgreen";
    property string outsidedate: "?";
    Button {
        id: closeButton;
        text: page1Box.outsidedate;
        onClicked: {
            console.log("Button Pressed. Entered text: " + closeButton.text);
            Qt.quit();
        }
    }

}
