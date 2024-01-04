#include <vlcwrapper/mediaplayer.h>
#include <vlcwrapper/instance.h>

namespace vlc
{

MediaPlayer::MediaPlayer()
{
    mlp_ = libvlc_media_list_player_new(Instance::get());
    mp_  = libvlc_media_list_player_get_media_player(mlp_);
}

MediaPlayer::~MediaPlayer()
{
    libvlc_media_list_player_release(mlp_);
}

void MediaPlayer::setWindow(const int windowId)
{
    libvlc_media_player_set_xwindow(mp_, windowId);
}

void MediaPlayer::setMediaList(const MediaList& media_list)
{
    libvlc_media_list_player_set_media_list(mlp_, media_list.data());
}

void MediaPlayer::setPlaybackMode(const PlaybackMode mode)
{
    libvlc_playback_mode_t vlc_mode = libvlc_playback_mode_default;
    switch (mode)
    {
        case PlaybackMode::Loop:
            vlc_mode = libvlc_playback_mode_loop;
            break;
        case PlaybackMode::Repeat:
            vlc_mode = libvlc_playback_mode_repeat;
            break;
        case PlaybackMode::Default:
        default:
            break;
    }
    libvlc_media_list_player_set_playback_mode(mlp_, vlc_mode);
}

void MediaPlayer::next()
{
    libvlc_media_list_player_next(mlp_);
}

void MediaPlayer::previous()
{
    libvlc_media_list_player_previous(mlp_);
}

bool MediaPlayer::isPlaying() const
{
    return libvlc_media_list_player_is_playing(mlp_);
}

void MediaPlayer::play()
{
    libvlc_media_list_player_play(mlp_);
}

void MediaPlayer::playAt(int idx)
{
    libvlc_media_list_player_play_item_at_index(mlp_, idx);
}

void MediaPlayer::pause()
{
    libvlc_media_list_player_pause(mlp_);
}

void MediaPlayer::stop()
{
    libvlc_media_list_player_stop(mlp_);
}

void MediaPlayer::nextFrame()
{
    libvlc_media_player_next_frame(mp_);
}

State MediaPlayer::state() const
{
    const libvlc_state_t vlc_state = libvlc_media_list_player_get_state(mlp_);
    switch (vlc_state)
    {
        case libvlc_Opening:
            return State::Opening;
        case libvlc_Playing:
            return State::Playing;
        case libvlc_Paused:
            return State::Paused;
        case libvlc_Stopped:
            return State::Stopped;
        case libvlc_Ended:
            return State::Ended;
        case libvlc_Error:
            return State::Error;
        case libvlc_NothingSpecial:
        default:
            return State::None;
    }
}

std::pair<int, int> MediaPlayer::size() const
{
    unsigned int px = 0;
    unsigned int py = 0;
    const int res = libvlc_video_get_size(mp_, 0, &px, &py);
    if (res != 1)
    {
        return {px, py};
    }
    else
    {
        return {0, 0};
    }
}

int MediaPlayer::length() const
{
    return libvlc_media_player_get_length(mp_);
}

int MediaPlayer::time() const
{
    return libvlc_media_player_get_time(mp_);
}

void MediaPlayer::setTime(const int time)
{
    libvlc_media_player_set_time(mp_, time);
}

double MediaPlayer::position() const
{
    return libvlc_media_player_get_position(mp_);
}

void MediaPlayer::setPosition(const double pos)
{
    libvlc_media_player_set_position(mp_, pos);
}

double MediaPlayer::rate() const
{
    return libvlc_media_player_get_rate(mp_);
}

void MediaPlayer::setRate(const double rate)
{
    libvlc_media_player_set_rate(mp_, rate);
}

int MediaPlayer::volume() const
{
    return libvlc_audio_get_volume(mp_);
}

void MediaPlayer::setVolume(const int vol)
{
    libvlc_audio_set_volume(mp_, vol);
}

} // namespace vlc
