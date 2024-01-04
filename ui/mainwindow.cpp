#include <ui/mainwindow.h>

#include <ui/mediaview.h>
#include <ui/medialistview.h>

#include <QDockWidget>
#include <QFileDialog>
#include <QDir>
#include <QShortcut>
#include <QFileInfo>

namespace ui
{

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent)
{
    setWindowTitle(tr("media_app"));

    mv_ = new MediaView(this);
    setCentralWidget(mv_);

    mlv_ = new MediaListView(this);
    mlv_->build(media_list_);
    addDock(mlv_, Qt::RightDockWidgetArea, tr("Media List"));

    connect(mlv_, &MediaListView::currentRowChanged, this, &MainWindow::playMedia);

    auto* open = new QShortcut(QKeySequence::Open, this);
    connect(open, &QShortcut::activated, this, &MainWindow::openDirectory);

    setMinimumSize(QSize(600, 400));
    showMaximized();
}

void MainWindow::addDock(QWidget* widget, Qt::DockWidgetArea area, const QString& title)
{
    auto* dock = new QDockWidget(title, this);
    dock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    dock->setWidget(widget);
    addDockWidget(area, dock);
    docks_.push_back(dock);
}

void MainWindow::openDirectory()
{
    static const QString kDefaultDir = "/home";
    const QString dir_path = QFileDialog::getExistingDirectory(
        this, tr("Open Direcory"), kDefaultDir);

    static const QStringList name_filters = {"*.wmv", "*.avi", "*.flv", "*.mov", "*.mp4", "*.ogg", "*.mp3", "*.flac"};
    const QDir dir(dir_path);
    const QFileInfoList files = dir.entryInfoList(name_filters, QDir::Files);

    if (files.isEmpty())
    {
        return;
    }

    mv_->stop();

    media_list_.clear();
    for (const auto& file_info: files)
    {
        media_list_.add(file_info.filePath().toStdString());
    }
    mv_->setMediaList(media_list_);
    mlv_->build(media_list_);
}

void MainWindow::playMedia(int idx)
{
    if (idx < 0 || idx >= media_list_.count())
    {
        return;
    }
    mv_->playAt(idx);
}

} // namespace ui
