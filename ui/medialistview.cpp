#include <ui/medialistview.h>

#include <QFileInfo>

namespace ui
{

constexpr int kFilePathRole = Qt::UserRole + 1;

MediaListView::MediaListView(QWidget* parent): QListWidget(parent)
{

}

void MediaListView::build(const vlc::MediaList& media_list)
{
    clear();

    for (int i = 0; i < media_list.count(); ++i)
    {
        const QString filePath = QString::fromStdString(media_list.at(i).path());
        const QString fileName = QFileInfo(filePath).fileName();

        auto* item = new QListWidgetItem;
        item->setText(fileName);
        item->setData(kFilePathRole, filePath);

        addItem(item);
    }
}

}