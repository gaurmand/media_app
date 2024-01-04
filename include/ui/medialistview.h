#ifndef UI_MEDIALISTVIEW_H
#define UI_MEDIALISTVIEW_H

#include <QListWidget>

#include <vlcwrapper/medialist.h>

namespace ui
{

class MediaListView: public QListWidget
{
public: 
    MediaListView(QWidget* parent);

    void build(const vlc::MediaList& media_list);
};

} // namespace ui

#endif