#include "webrequesthandler.h"

WebRequestHandler::WebRequestHandler(QObject* parent)
    : HttpRequestHandler(parent) { }

WebRequestHandler::~WebRequestHandler() {}

void WebRequestHandler::service(HttpRequest &request, HttpResponse &response)
{
    // Get a request parameters
    QByteArray username=request.getParameter("username");

    // Set a response header
    response.setHeader("Content-Type", "text/html; charset=ISO-8859-1");

    // Generate the HTML document
    response.write("<html><body>");
    response.write("Hello ");
    response.write(username);
    response.write("</body></html>");
}
