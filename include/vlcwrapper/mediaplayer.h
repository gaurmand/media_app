#ifndef VLC_MEDIAPLAYER_H
#define VLC_MEDIAPLAYER_H

#include <vlc/vlc.h>

#include <vlcwrapper/medialist.h>

#include <utility>


namespace vlc
{

enum class PlaybackMode
{
    Default,
    Loop,
    Repeat
};

enum class State
{
    None,
    Opening,
    Playing,
    Paused,
    Stopped,
    Ended,
    Error
};

class MediaPlayer {
public:

public:
    MediaPlayer();
    ~MediaPlayer();
    MediaPlayer(const MediaPlayer&) = delete;
    void operator=(const MediaPlayer&) = delete;

    void setWindow(const int windowId);

    void setMediaList(const MediaList& media_list);
    void setPlaybackMode(const PlaybackMode mode);
    void next();
    void previous();

    bool isPlaying() const;
    void play();
    void playAt(int idx);
    void pause();   // i.e. toggle pause/play
    void stop();

    void nextFrame();

    State state() const;
    std::pair<int, int> size() const;

    int length() const; // ms
    int time() const; // ms
    void setTime(const int time);

    double position() const; // 0.0 - 1.0
    void setPosition(const double pos);

    double rate() const;
    void setRate(const double rate);

    int volume() const; // 1 - 100
    void setVolume(const int vol);

private:
    libvlc_media_list_player_t* mlp_ = nullptr;
    libvlc_media_player_t* mp_       = nullptr;
};

} // namespace ui

#endif