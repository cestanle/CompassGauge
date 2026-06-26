import QtQuick

Item {
    id: root

    property string basePath: "../assets/compass"
    property string sheetPrefix: "sprite_sheet"

    property int frameWidth: 768
    property int frameHeight: 768

    property int columns: 10
    property int rows: 9
    property int frameCount: 360

    property real angle: 0

    readonly property int framesPerSheet: columns * rows

    readonly property int frameIndex: {
        var f = Math.floor(root.angle) % root.frameCount
        if (f < 0)
            f += root.frameCount
        return f
    }

    readonly property int sheetIndex: Math.floor(frameIndex / framesPerSheet)
    readonly property int localFrame: frameIndex % framesPerSheet

    readonly property int sourceColumn: localFrame % columns
    readonly property int sourceRow: Math.floor(localFrame / columns)

    readonly property int sourceX: sourceColumn * frameWidth
    readonly property int sourceY: sourceRow * frameHeight

    readonly property string sheetSource:
        root.basePath + "/" + root.sheetPrefix + "_" + sheetIndex + ".png"

    width: frameWidth
    height: frameHeight
    clip: true

    Image {
        id: sheetImage

        source: root.sheetSource

        x: -root.sourceX
        y: -root.sourceY

        width: root.frameWidth * root.columns
        height: root.frameHeight * root.rows

        fillMode: Image.Stretch
        smooth: false
        mipmap: false
        cache: true
        asynchronous: false

        onStatusChanged: {
            if (status === Image.Error) {
                console.log("Failed to load sprite sheet:", source)
            }
        }
    }
}