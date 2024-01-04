#ifndef VLC_MEDIALIST_H
#define VLC_MEDIALIST_H

#include <vlc/vlc.h>

#include <vector>
#include <memory>
#include <string>

namespace vlc
{

class MediaList;

class Media
{
public:
    Media() {}
    Media(const std::string& media_path);
    ~Media();

    Media(const Media&);
    void operator=(const Media&);

    std::string path() const { return media_path_; }
    libvlc_media_t* data() const { return m_; }

private:
    std::string media_path_;
    libvlc_media_t* m_ = nullptr;
};

class MediaList {
public:
    MediaList();
    ~MediaList();

    void add(const std::string& media_path);
    void clear();

    int count() const;
    Media at(const int idx) const;

    MediaList(const MediaList&) = delete;
    void operator=(const MediaList&) = delete;

    libvlc_media_list_t* data() const { return ml_; }

private:
    libvlc_media_list_t* ml_ = nullptr;
    std::vector<Media> media_vec;
};

} // namespace ui

#endif