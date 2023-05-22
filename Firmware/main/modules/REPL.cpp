//
// Created by Alexandru Anastasiu on 2/7/23.
//

#include "REPL.hpp"
#include "modules/twai.hpp"
#include <esp_timer.h>

esp_console_repl_t *repl = nullptr;

int stats(int x, char **y) {
    printf("Task Name\tStatus\tPrio\tHWM\tTask\tAffinity\n");
    char stats_buffer[1024];
    vTaskList(stats_buffer);
    printf("%s\n", stats_buffer);
    vTaskGetRunTimeStats(stats_buffer);
    printf("%s\n", stats_buffer);
    return 0;
}

static void topTask(void *pvParameters) {
    stdout = appInterconnect.stdioRedirect;
    char statsBuffer[512];
    while (true) {
        linenoiseClearScreen();
        vTaskGetRunTimeStats(statsBuffer);
        printf("%s\n", statsBuffer);
        fflush(stdout);
        vTaskDelay(500 / PORT_TICK_PERIOD_MS);
    }
}

int top(int x, char **y) {
    xTaskCreate(topTask, "top", 2048, nullptr, tskIDLE_PRIORITY, nullptr);
    return 0;
}

int fuckFunction(int x, char **y) {
    printf("Fuck you!\n");
    return 0;
}

int clearConsole(int x, char **y) {
    linenoiseClearScreen();
    return 0;
}

int rebootCCU(int x, char **y) {
    esp_restart();
    return 0;
}

void registerNewCommand(const char *commandName, const char *hint, const char *helpText,
                        esp_console_cmd_func_t workerFunction, void *arguments) {
    esp_console_cmd_t worker;
    worker.command = commandName;
    worker.hint = hint;
    worker.help = helpText;
    worker.argtable = arguments;
    worker.func = (esp_console_cmd_func_t) workerFunction;

    esp_console_cmd_register(&worker);
}

int killTop(int x, char **y) {
    vTaskDelete(xTaskGetHandle("top"));
    appInterconnect.debugPrintGPS = false;
    printf("CCU > ");
    fflush(stdout);
    return 0;
}

int memTest(int x, char **y)
{
    printf("Minimum: %d\n", xPortGetMinimumEverFreeHeapSize());
    printf("Free now: %d\n", xPortGetFreeHeapSize());
    fflush(stdout);
    return 0;
}

int setGPSDebug(int x, char **y)
{
    linenoiseClearScreen();
    appInterconnect.debugPrintGPS = true;
    return true;
}

int uptime(int x, char **y)
{
    int seconds = esp_timer_get_time() / 1e6;
    if ( seconds < 60 )
        printf("Up %d seconds\n", (int)seconds);
    else
    {
        int minutes = seconds / 60;
        if(minutes < 60)
        {
            printf("Up %d minutes %d seconds\n", (int) minutes, (int)(seconds - (minutes * 60)));
        }else
        {
            int hours = minutes / 60;
            printf("Up %d hours %d minutes %d seconds\n",hours,minutes - (hours * 60), seconds - (minutes * 60));
        }
    }
    fflush(stdout);
    return true;
}

bool initializeREPL() {
    stdout = appInterconnect.stdioRedirect;

    esp_console_config_t a = ESP_CONSOLE_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_console_register_help_command());
    esp_console_init(&a);

    registerNewCommand("clear", "",
                       "This command clears the screen", clearConsole);
    registerNewCommand("reboot", "",
                       "Reboots the central compute unit", rebootCCU);
    registerNewCommand("stats", "",
                       "Displays system statistics", stats);
    registerNewCommand("top", "",
                       "Displays CPU usage real-time", top);
    registerNewCommand("testSD", "",
                       "Displays CPU usage real-time", testFileSystem);
    registerNewCommand("memstat", "",
                       "Displays lowest amount of free memory available to date", memTest);

    registerNewCommand("ls", "",
                       "Lists files inside the directory specified", listDir);
    registerNewCommand("touch", "filename",
                       "Creates the specified file", touch);
    registerNewCommand("gpsDebug", "filename",
                       "Creates the specified file", setGPSDebug);
    registerNewCommand("uptime", "",
                       "Displays time since boot", uptime);
    registerNewCommand("cat", "filename",
                       "Lists contents of file", cat);
    registerNewCommand("twai", "",
                       "Print shit from the TWAI", createTWAITask);

    return true;
}

void telnetREPL(void *pvParameters) {
    stdout = appInterconnect.stdioRedirect;

    char command[100];
    int ret;
    printf("%s", banner);

    esp_app_desc_t runningAppInfo;
    if (esp_ota_get_partition_description(esp_ota_get_running_partition(), &runningAppInfo) == ESP_OK) {
        printf("CCU fw ver %s\n", runningAppInfo.version);
        printf("Active partition: %s\n", esp_ota_get_running_partition()->label);
    }

    fflush(stdout);
    recv(appInterconnect.sock, command, sizeof(command), 0);

    TaskHandle_t h = nullptr;
    while (true) {
        printf("CCU > ");
        fflush(stdout);
        memset(command, 0, sizeof command);

        int flag = recv(appInterconnect.sock, command, sizeof(command), 0);
        if (flag == 0) {
            h = xTaskGetHandle("top");
            if (h != nullptr)
                vTaskDelete(h);


            shutdown(appInterconnect.sock, SHUT_RDWR);
            close(appInterconnect.sock);
            auto h = xTaskGetHandle("telnetListener");
            if (h == nullptr)
                esp_restart();

            vTaskResume(h);
            vTaskDelete(nullptr);
        } else if (flag < 0) {
            continue;
        }

        if (command[0] == 'q') {
            h = xTaskGetHandle("top");
            if (h != nullptr)
                vTaskDelete(h);
            appInterconnect.debugPrintGPS = false;
            linenoiseClearScreen();

            continue;
        }


        command[strlen(command) - 2] = 0;
        if (esp_console_run(command, &ret) == ESP_ERR_NOT_FOUND)
            printf("Command %s not found\n", command);
        vTaskDelay(1);
    }

    vTaskDelete(nullptr);

}