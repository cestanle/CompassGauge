#include "SerialInput.h"

#include <QDebug>
#include <QStringList>

SerialInput::SerialInput(ClusterModel *cluster, QObject *parent)
    : QObject(parent),
      m_cluster(cluster)
{
    connect(
        &m_serial,
        &QSerialPort::readyRead,
        this,
        &SerialInput::handleReadyRead
    );
}

bool SerialInput::open(const QString& portName, qint32 baudRate)
{
    m_serial.setPortName(portName);
    m_serial.setBaudRate(baudRate);
    m_serial.setDataBits(QSerialPort::Data8);
    m_serial.setParity(QSerialPort::NoParity);
    m_serial.setStopBits(QSerialPort::OneStop);
    m_serial.setFlowControl(QSerialPort::NoFlowControl);

    if (!m_serial.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open serial port:"
                   << portName
                   << m_serial.errorString();
        return false;
    }

    qDebug() << "Opened serial port:" << portName << "baud:" << baudRate;
    return true;
}

void SerialInput::handleReadyRead()
{
    m_buffer.append(m_serial.readAll());

    while (true) {
        int newlineIndex = m_buffer.indexOf('\n');

        if (newlineIndex < 0)
            break;

        QByteArray line = m_buffer.left(newlineIndex).trimmed();
        m_buffer.remove(0, newlineIndex + 1);

        if (!line.isEmpty()) {
            processLine(line);
        }
    }
}

void SerialInput::processLine(const QByteArray& line)
{
    // Expected:
    // ADC,1234,2048

    QList<QByteArray> parts = line.split(',');

    if (parts.size() != 3) {
        qWarning() << "Bad serial line:" << line;
        return;
    }

    if (parts[0] != "ADC") {
        qWarning() << "Unknown packet:" << line;
        return;
    }

    bool ok0 = false;
    bool ok1 = false;

    int adc0 = parts[1].toInt(&ok0);
    int adc1 = parts[2].toInt(&ok1);

    if (!ok0 || !ok1) {
        qWarning() << "Bad ADC values:" << line;
        return;
    }

    adc0 = qBound(0, adc0, 4095);
    adc1 = qBound(0, adc1, 4095);

    static constexpr int AdcMax = 4095;

    static constexpr int CompassTurnsScale = 50;
    static constexpr int CueTurnsScale     = 50;

    int compassFrame = (adc0 * 360 * CompassTurnsScale / AdcMax) % 360;
    int cueFrame = (adc1 * 360 * CueTurnsScale / AdcMax) % 360;

    m_cluster->setCompassFrame(compassFrame);
    m_cluster->setCueFrame(cueFrame);

    qDebug() << "ADC:" << adc0 << adc1
             << "frames:" << compassFrame << cueFrame;
}