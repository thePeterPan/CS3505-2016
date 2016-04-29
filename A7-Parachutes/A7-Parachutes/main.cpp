#include "mainwindow.h"
#include "windowcontroller.h"
#include <QApplication>

// Application internals
#include "networking.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString configFile = ":/A7-Parachutes.ini";
    Networking *client = new Networking(configFile, &app);
    // If the connection closes:
    QObject::connect(client, &Networking::socketClosed, &app, &QCoreApplication::quit);

    WindowController controller(client);

    return app.exec();
}
