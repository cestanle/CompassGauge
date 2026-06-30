#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCoreApplication>
#include <QQmlContext>
#include <QUrl>
#include <QDebug>
#include <QFileInfo>
#include <QTimer>
#include "SerialInput.h"
#include "ClusterModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QString assetDir =
    QCoreApplication::applicationDirPath() + "/assets";

    // Yocto/runtime install location
    if (!QFileInfo(assetDir + "/background/0000.png").exists()) {
        assetDir = "/usr/share/gauge-cluster/assets";
    }

    const QString assetRoot =
    QUrl::fromLocalFile(assetDir).toString();

    qDebug() << "assetDir:" << assetDir;
    qDebug() << "assetRoot:" << assetRoot;
    qDebug() << "background exists:"
             << QFileInfo(assetDir + "/background/0000.png").exists();

    ClusterModel cluster;

    SerialInput serialInput(&cluster);

    // On Raspberry Pi / CM5:
    serialInput.open("/dev/serial0", 115200);

    /*
        Temporary C++ simulation.

        Later this gets replaced by STM32 serial input:
            Pot 1 -> compassFrame
            Pot 2 -> cueFrame

    QTimer simulationTimer;
    QObject::connect(&simulationTimer, &QTimer::timeout, [&cluster]() {
        cluster.setCompassFrame(cluster.compassFrame() + 1);
        cluster.setCueFrame(cluster.cueFrame() + 2);
    });
    simulationTimer.start(16);
    */
    engine.rootContext()->setContextProperty("assetRoot", assetRoot);
    engine.rootContext()->setContextProperty("cluster", &cluster);

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection
    );

    engine.loadFromModule("GaugeQML", "Main");

    return app.exec();
}
