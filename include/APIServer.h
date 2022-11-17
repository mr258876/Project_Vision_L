#ifndef _APISERVER_H_
#define _APISERVER_H_

#include <WebServer.h>
#include "rtos_externs.h"

void startAPIServer();
void endAPIServer();

void APILoop(void* parameter);

#endif