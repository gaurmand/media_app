#include <QApplication>

#include <ui/mainwindow.h>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);
   ui::MainWindow w;
   w.show();
   return a.exec();
}
