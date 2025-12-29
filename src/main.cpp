#include <QtWidgets>
#include "MainWindow.h"

int main(int argc, char** argv){
    QCoreApplication::setOrganizationName("MyOrg");
    QCoreApplication::setApplicationName("MyWeatherApp");
    QApplication app(argc, argv);
    MainWindow main_window;
    main_window.show();
    return app.exec();
}