#ifndef WEBREQUESTHANDLER_H
#define WEBREQUESTHANDLER_H

#include "httpconnectionhandler.h"

class WebRequestHandler : public HttpRequestHandler
{
public:
    WebRequestHandler(QObject* parent=NULL);

    /** Destructor */
    virtual ~WebRequestHandler();

    virtual void service(HttpRequest& request, HttpResponse& response);
};

#endif // WEBREQUESTHANDLER_H
