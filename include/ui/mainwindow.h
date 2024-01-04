#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QMainWindow>

#include <vlcwrapper/medialist.h>

#include <vector>

class QDockWidget;

namespace ui
{

class MediaView;
class MediaListView;

class MainWindow: public QMainWindow{
public: 
    MainWindow(QWidget* parent = nullptr);

public slots:
    void openDirectory();
    void playMedia(int idx);

private:
    void addDock(QWidget* widget, Qt::DockWidgetArea area, const QString& title);

private:
    MediaView* mv_ = nullptr;
    MediaListView* mlv_ = nullptr;

    std::vector<QDockWidget*> docks_;

    vlc::MediaList media_list_;
};


} // namespace ui

#endif