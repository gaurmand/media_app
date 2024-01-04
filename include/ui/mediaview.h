#ifndef UI_MEDIAVIEW_H
#define UI_MEDIAVIEW_H

#include <QFrame>

#include <vlcwrapper/mediaplayer.h>
#include <vlcwrapper/medialist.h>

namespace ui
{

class MediaView: public QFrame
{
public: 
    MediaView(QWidget* parent);

    void setMediaList(const vlc::MediaList& media_list);

    void play();
    void playAt(int idx);
    void stop();

public slots:
    void pause();

    void skipForward();
    void skipBackward();
    void nextFrame();

    void increaseRate();
    void decreaseRate();
    void defaultRate();

    void mute();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

    void setPositionFromMouseEvent(QMouseEvent* event);

private:
    vlc::MediaPlayer player_;

    bool muted_ = false;
    int last_volume_ = 0;
};

} // namespace ui

#endif