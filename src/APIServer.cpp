#include "APIServer.h"

WebServer *ws;

void handlerRoot()
{
    ws->send(200, "text/plain", "Hello!");
}

void startSettingServer()
{
    ws = new WebServer();

    ws->on("/", handlerRoot);

    ws->begin();
}

void endSettingServer()
{
    ws->stop();
    delete(ws);
}