#include "ClusterModel.h"

ClusterModel::ClusterModel(QObject *parent)
    : QObject(parent)
{
}

int ClusterModel::compassFrame() const
{
    return m_compassFrame;
}

int ClusterModel::cueFrame() const
{
    return m_cueFrame;
}

void ClusterModel::setCompassFrame(int frame)
{
    frame = normalizeFrame(frame);

    if (m_compassFrame == frame)
        return;

    m_compassFrame = frame;
    emit compassFrameChanged();
}

void ClusterModel::setCueFrame(int frame)
{
    frame = normalizeFrame(frame);

    if (m_cueFrame == frame)
        return;

    m_cueFrame = frame;
    emit cueFrameChanged();
}

int ClusterModel::normalizeFrame(int frame) const
{
    frame %= FrameCount;

    if (frame < 0)
        frame += FrameCount;

    return frame;
}
