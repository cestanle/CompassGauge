import QtQuick


Item {
    id: root

    width: 768
    height: 768
    focus: true

    property int compassFrame: 0
    property int cueFrame: 0

    readonly property int frameCount: 360

    Image {
        id: backgroundImage

        anchors.fill: parent

        source: assetRoot + "/background/0000.png"

        fillMode: Image.Stretch
        smooth: true
        cache: true

        onStatusChanged: {
            if (status === Image.Error) {
                console.log("Failed to load background:", source)
            }
        }
    }

    SpriteLayer {
        id: compassRing

        anchors.centerIn: parent

        width: parent.width
        height: parent.height

        basePath: assetRoot + "/compass"
        sheetPrefix: "sprite_sheet"

        frameWidth: 768
        frameHeight: 768

        columns: 10
        rows: 9
        frameCount: root.frameCount

        angle: root.compassFrame
    }

    SpriteLayer {
        id: cueArrow

        anchors.centerIn: parent

        width: parent.width
        height: parent.height

        basePath: assetRoot + "/cue"
        sheetPrefix: "cue_sheet"

        frameWidth: 768
        frameHeight: 768

        columns: 10
        rows: 9
        frameCount: root.frameCount

        angle: root.cueFrame
    }

    Text {
        id: angleText

        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 30

        color: "#ffffff"
        font.pixelSize: 28
        font.bold: true

        text: "Ring " + root.compassFrame + "°   Cue " + root.cueFrame + "°"
    }

    Text {
        id: helpText

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.margins: 16

        color: "#aaaaaa"
        font.pixelSize: 16

        text: "C++ ClusterModel driving QML"
    }
}