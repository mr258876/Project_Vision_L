#include "APIServer.h"

WebServer *ws;

void handleRoot()
{
    ws->send(200, "text/plain", "Web server running!");
}

void _startAPIServer()
{
    ws = new WebServer();

    ws->on("/", HTTP_GET, handleRoot);

    ws->begin();
}

void _endAPIServer()
{
    ws->stop();
    delete (ws);
}

void startAPIServer()
{
    _startAPIServer();

    xTaskCreatePinnedToCore(APILoop,        //任务函数
                            "APILoop",      //任务名称
                            3072,           //任务堆栈大小
                            NULL,           //任务参数
                            1,              //任务优先级
                            &APILoopHandle, //任务句柄
                            0);             //执行任务核心
}

void endAPIServer()
{
    vTaskDelete(APILoopHandle);

    _endAPIServer();
}

void APILoop(void *parameter)
{
    while (1)
    {
        ws->handleClient();
    }
}