import QtQuick
import QtQuick.Window
import GaugeCluster

Window {
    id: root

    width: 768
    height: 768
    visible: true
    title: "Gauge Cluster Prototype"

    color: "#101014"

    CompassGauge {
        id: compassGauge
        anchors.centerIn: parent
        width: 768
        height: 768
    }
}