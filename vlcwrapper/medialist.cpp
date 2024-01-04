#include <vlcwrapper/medialist.h>

#include <vlcwrapper/instance.h>

#include <stdexcept>
 #include <QDebug>

namespace vlc
{

Media::Media(const std::string& media_path): media_path_(media_path)
{
    m_ = libvlc_media_new_path(Instance::get(), media_path.data());

    if (!m_)
    {
        throw std::runtime_error("Media could not be created");
    }
}

Media::Media(const Media& other): 
    media_path_(other.media_path_), 
    m_(libvlc_media_duplicate(other.m_))
{
}

void Media::operator=(const Media& other)
{
    media_path_ = other.media_path_;

    libvlc_media_release(m_);
    m_ = libvlc_media_duplicate(other.m_);
}

Media::~Media()
{
    libvlc_media_release(m_);
}




MediaList::MediaList()
{
    ml_ = libvlc_media_list_new(Instance::get());
}

MediaList::~MediaList()
{
    libvlc_media_list_release(ml_);
}

void MediaList::add(const std::string& media_path)
{
    media_vec.emplace_back(media_path);

    libvlc_media_list_lock(ml_);
    libvlc_media_list_add_media(ml_, media_vec.back().data());
    libvlc_media_list_unlock(ml_);
}

void MediaList::clear()
{
    media_vec.clear();

    libvlc_media_list_release(ml_);
    ml_ = libvlc_media_list_new(Instance::get());
}

int MediaList::count() const
{
    return media_vec.size();
}

Media MediaList::at(const int idx) const
{
    return media_vec.at(idx);
}


} // namespace vlc
