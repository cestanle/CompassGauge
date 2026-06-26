import QtQuick
import QtQuick.Window
import GaugeQML

Window {
    id: root

    width: 768
    height: 768
    visible: true
    title: "Gauge Cluster Prototype"

    color: "black"

    CompassGauge {
        id: compassGauge

        anchors.centerIn: parent
        width: 768
        height: 768

        compassFrame: cluster ? cluster.compassFrame : 0
        cueFrame: cluster ? cluster.cueFrame : 0
    }
}