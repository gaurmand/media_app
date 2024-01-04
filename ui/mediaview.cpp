#include <ui/mediaview.h>

#include <QShortcut>
#include <QKeySequence>
#include <QWheelEvent>

#include <algorithm>

namespace
{

constexpr int kSkipLength = 5000;   // ms

constexpr double kRatePerStep = 0.1;
constexpr double kMinRate = 0.25;
constexpr double kMaxRate = 3.0;
constexpr double kDefaultRate = 1.0;

constexpr int kVolumePerStep = 10;
constexpr int kMinVolume = 1;
constexpr int kMaxVolume = 150;
}


namespace ui
{

MediaView::MediaView(QWidget* parent) : QFrame(parent)
{
    player_.setWindow(winId());

    auto* pause = new QShortcut(Qt::Key_Space, this);
    connect(pause, &QShortcut::activated, this, &MediaView::pause);

    auto* forward = new QShortcut(Qt::Key_Right, this);
    connect(forward, &QShortcut::activated, this, &MediaView::skipForward);

    auto* back = new QShortcut(Qt::Key_Left, this);
    connect(back, &QShortcut::activated, this, &MediaView::skipBackward);

    auto* frame = new QShortcut(Qt::Key_E, this);
    connect(frame, &QShortcut::activated, this, &MediaView::nextFrame);

    auto* incRate = new QShortcut(Qt::Key_Up, this);
    connect(incRate, &QShortcut::activated, this, &MediaView::increaseRate);

    auto* decRate = new QShortcut(Qt::Key_Down, this);
    connect(decRate, &QShortcut::activated, this, &MediaView::decreaseRate);

    auto* defRate = new QShortcut(Qt::Key_Equal, this);
    connect(defRate, &QShortcut::activated, this, &MediaView::defaultRate);

    auto* mute = new QShortcut(Qt::Key_M, this);
    connect(mute, &QShortcut::activated, this, &MediaView::mute);
}

void MediaView::setMediaList(const vlc::MediaList& media_list)
{
    player_.setMediaList(media_list);
}

void MediaView::play()
{
    player_.play();
}

void MediaView::playAt(int idx)
{
    player_.playAt(idx);
}

void MediaView::stop()
{
    player_.stop();
}

void MediaView::pause()
{
    player_.pause();
}

void MediaView::skipForward()
{
    player_.setTime(std::min(player_.time() + kSkipLength, player_.length() - 1));
}

void MediaView::skipBackward()
{
    player_.setTime(std::max(player_.time() - kSkipLength, 0));
}

void MediaView::nextFrame()
{
    player_.nextFrame();
}

void MediaView::increaseRate()
{
    player_.setRate(std::min(player_.rate() + kRatePerStep, kMaxRate));
}

void MediaView::decreaseRate()
{
    player_.setRate(std::max(player_.rate() - kRatePerStep, kMinRate));
}

void MediaView::defaultRate()
{
    player_.setRate(kDefaultRate);
}

void MediaView::mute()
{
    if (muted_)
    {
        player_.setVolume(last_volume_);
        muted_ = false;
    }
    else
    {
        last_volume_ = player_.volume();
        player_.setVolume(kMinVolume);
        muted_ = true;
    }
}

void MediaView::mousePressEvent(QMouseEvent* event)
{
    setPositionFromMouseEvent(event);
}

void MediaView::mouseReleaseEvent(QMouseEvent* event)
{
    setPositionFromMouseEvent(event);
}

void MediaView::mouseMoveEvent(QMouseEvent* event)
{
    setPositionFromMouseEvent(event);
}

void MediaView::setPositionFromMouseEvent(QMouseEvent* event)
{
    const qreal x = event->position().x();
    const qreal pos = std::clamp(x / width(), 0.0, 1.0);
    player_.setPosition(pos);
}

void MediaView::wheelEvent(QWheelEvent* event)
{
    static const int kDeltasPerDegree = 8;  // 8 deltas = 1 degree
    static const int kDegreesPerStep = 15;  // 15 degrees = 1 step (most mice)

    const int degrees = event->angleDelta().y() / kDeltasPerDegree;
    const int steps = degrees / kDegreesPerStep;
    player_.setVolume(std::clamp(player_.volume() + steps * kVolumePerStep, kMinVolume, kMaxVolume));
}


} // namespace ui
