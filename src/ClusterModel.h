#pragma once

#include <QObject>

class ClusterModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int compassFrame READ compassFrame WRITE setCompassFrame NOTIFY compassFrameChanged)
    Q_PROPERTY(int cueFrame READ cueFrame WRITE setCueFrame NOTIFY cueFrameChanged)

public:
    explicit ClusterModel(QObject *parent = nullptr);

    int compassFrame() const;
    int cueFrame() const;

public slots:
    void setCompassFrame(int frame);
    void setCueFrame(int frame);

    signals:
        void compassFrameChanged();
        void cueFrameChanged();

private:
    int normalizeFrame(int frame) const;

    int m_compassFrame = 0;
    int m_cueFrame = 0;
    static constexpr int FrameCount = 360;
};