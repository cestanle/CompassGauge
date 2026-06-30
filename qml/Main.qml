import QtQuick
import QtQuick.Window
import GaugeQML

Window {
    id: root

    visible: true
    visibility: Window.FullScreen
    title: "Gauge Cluster Prototype"

    color: "black"

    Item {
        id: designSurface

        width: 768
        height: 768
        anchors.centerIn: parent

        CompassGauge {
            id: compassGauge

            anchors.fill: parent

            compassFrame: cluster ? cluster.compassFrame : 0
            cueFrame: cluster ? cluster.cueFrame : 0
        }
    }
}
