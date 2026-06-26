#pragma once

#include <QObject>
#include <QSerialPort>
#include <QByteArray>

#include "ClusterModel.h"

class SerialInput : public QObject
{
    Q_OBJECT

public:
    explicit SerialInput(ClusterModel *cluster, QObject *parent = nullptr);

    bool open(const QString& portName, qint32 baudRate);

private slots:
    void handleReadyRead();

private:
    void processLine(const QByteArray& line);

    ClusterModel *m_cluster = nullptr;
    QSerialPort m_serial;
    QByteArray m_buffer;
};
