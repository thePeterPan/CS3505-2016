/**
  @file
  @author Stefan Frings
*/

#include <QCoreApplication>
#include <QDir>
#include "httplistener.h"
#include "requestmapper.h"


/**
  Entry point of the program.
*/
int main(int argc, char *argv[])
{
    QCoreApplication app(argc,argv);

    app.setApplicationName("webServer");
    app.setOrganizationName("The Lost Boys & Wendy");

    // Find the configuration file
    QString configFileName=":/webServer.ini";

    // Configure and start the TCP listener
    QSettings* listenerSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    listenerSettings->beginGroup("listener");
    new HttpListener(listenerSettings,new RequestMapper(&app),&app);

    qWarning("Application has started");

    app.exec();

    qWarning("Application has stopped");
}
