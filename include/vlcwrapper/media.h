#ifndef VLC_MEDIALIST_H
#define VLC_MEDIALIST_H

#include <vlc/vlc.h>

#include <QString>

#include <vector>
#include <memory>

namespace vlc
{

class MediaList;

class Media
{
public:
    Media() {}
    Media(const QString& media_path);
    ~Media();

    Media(const Media&);
    void operator=(const Media&);

    QString path() const { return media_path_; }

    friend class MediaList;
    friend class MediaPlayer;

private:
    QString media_path_;
    libvlc_media_t* m_ = nullptr;
};

} // namespace ui

#endif