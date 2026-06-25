import QtQuick

Item {
    id: root

    width: 768
    height: 768

    property real compassAngle: 0

    Rectangle {
        id: background
        anchors.fill: parent
        color: "#181820"
        radius: width / 2
        border.width: 4
        border.color: "#404050"
    }

    Rectangle {
        id: compassPlaceholder

        width: parent.width * 0.82
        height: parent.height * 0.82
        anchors.centerIn: parent

        radius: width / 2
        color: "transparent"
        border.width: 8
        border.color: "#808090"

        rotation: root.compassAngle

        Behavior on rotation {
            NumberAnimation {
                duration: 80
                easing.type: Easing.Linear
            }
        }

        Text {
            anchors.centerIn: parent
            text: "N"
            color: "white"
            font.pixelSize: 64
            font.bold: true
        }

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 24
            text: "S"
            color: "white"
            font.pixelSize: 48
            font.bold: true
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 24
            text: "W"
            color: "white"
            font.pixelSize: 48
            font.bold: true
        }

        Text {
            anchors.verticalCenter: parent.verticalCenter
            anchors.right: parent.right
            anchors.rightMargin: 24
            text: "E"
            color: "white"
            font.pixelSize: 48
            font.bold: true
        }
    }

    Rectangle {
        id: cueArrow

        width: 18
        height: parent.height * 0.38
        radius: 8

        color: "#d8d8e8"

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: parent.height * 0.15
    }

    Text {
        id: angleText

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 44

        color: "#f0f0ff"
        font.pixelSize: 32
        font.bold: true

        text: Math.round(root.compassAngle) + "°"
    }

    Timer {
        id: animationTimer

        interval: 16
        running: true
        repeat: true

        onTriggered: {
            root.compassAngle = (root.compassAngle + 0.5) % 360
        }
    }
}