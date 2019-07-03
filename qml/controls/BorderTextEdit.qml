import QtQuick 2.0


Rectangle {
    property string textValue
    signal textChanged(string text)
    border.color: "grey"

    Flickable {
        id: flick
        width: parent.width - 10
        height: parent.height;
        clip: true

        function ensureVisible(r) {
            if (contentX >= r.x)
                contentX = r.x;
            else if (contentX+width <= r.x+r.width)
                contentX = r.x+r.width-width;

            if (contentY >= r.y)
                contentY = r.y;
            else if (contentY+height <= r.y+r.height)
                contentY = r.y+r.height-height;
        }

        TextEdit {
            id: message
            text: textValue
            width: parent.width
            height: parent.height
            onCursorRectangleChanged: flick.ensureVisible(cursorRectangle)
            selectByMouse: true
            onTextChanged: {
                //textChanged(message.text)
            }
        }
    }
}
