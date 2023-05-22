//
// Created by Alexandru Anastasiu on 2/7/23.
//

#ifndef SERIALTEST_REPL_HPP
#define SERIALTEST_REPL_HPP

#include "init/commonComponents.hpp"
#include <esp_console.h>
#include <esp_app_desc.h>
#include <esp_ota_ops.h>
#include <lwip/sockets.h>

#define REPLCOMM(x)int x (int a, char** b)

#include "modules/filesystem.hpp"
extern Transport appInterconnect;
bool initializeREPL();

void telnetREPL(void *pvParameters);

void registerNewCommand(const char *commandName, const char *hint, const char *helpText,
                        esp_console_cmd_func_t workerFunction, void *arguments = nullptr);


REPLCOMM(fuckFunction);

REPLCOMM(clearConsole);

REPLCOMM(rebootCCU);

REPLCOMM(stats);
//    REPLCOMM(startParser);
REPLCOMM(top);
REPLCOMM(killTop);


#endif //SERIALTEST_REPL_HPP
