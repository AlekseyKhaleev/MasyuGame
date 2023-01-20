#include <QApplication>
#include <QPainter>
#include "MainWidget.h"

#include <QLabel>


using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setOverrideCursor(Qt::BlankCursor);

    MainWidget mainWindow;
    mainWindow.showFullScreen();


    return app.exec();

}
