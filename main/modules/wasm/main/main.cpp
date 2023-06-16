#include <stdio.h>
#include <string.h>
#include <wasm3.h>
#include <m3_function.h>
#include <hal/gpio_types.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wasm.hpp"
#include <m3_env.h>

#define NATIVE_STACK_SIZE   (32*1024)
#define WASM_STACK_SLOTS    1024
#define WASM_MEMORY_LIMIT   2048 * 5                        // apparently, WASM needed more memory, which was causing
// the crash
extern "C" {

static const char* TAG = "main";

const char * filename= "../WasmPrograms/target.wasm";

gpio_num_t iPorts[] = {GPIO_NUM_36, GPIO_NUM_39, GPIO_NUM_34, GPIO_NUM_35, GPIO_NUM_32, GPIO_NUM_33, GPIO_NUM_25,
                       GPIO_NUM_26, GPIO_NUM_27, GPIO_NUM_14, GPIO_NUM_12, GPIO_NUM_13};
gpio_num_t oPorts[] = {GPIO_NUM_0, GPIO_NUM_10, GPIO_NUM_11};

m3ApiRawFunction(m3_IO_getpin){
        m3ApiReturnType(uint32_t)
        m3ApiGetArg(uint32_t, pinNumber)
        uint32_t pinStat = gpio_get_level(iPorts[pinNumber]);
        m3ApiReturn(pinStat)
}

m3ApiRawFunction(m3_IO_setpin){
        m3ApiGetArg(uint32_t, pinNumber)
        m3ApiGetArg(uint32_t, stat)
        gpio_set_level(oPorts[pinNumber], stat);
        m3ApiSuccess()
}

//m3ApiRawFunction(m3_IO_print){
//    printf("Inside wasm program");
//    fflush(stdout);
//    m3ApiSuccess()
//}

M3Result linkESP(IM3Runtime rt){
    IM3Module module = rt->modules;
    m3_LinkRawFunction(module, "IO", "getpin", "i(i)", &m3_IO_getpin);
    m3_LinkRawFunction(module, "IO", "setpin", "v(ii)", &m3_IO_setpin);
//    m3_LinkRawFunction(module, "IO", "print", "v", &m3_IO_print);
    return m3Err_none;
}


void wasm_task(void *pvParameters)
{
    M3Result result = m3Err_none;

    IM3Environment env = m3_NewEnvironment ();
    if (!env) printf("NewEnvironment failed");

    IM3Runtime runtime = m3_NewRuntime (env, WASM_STACK_SLOTS, NULL);
    if (!runtime) printf("NewRuntime failed");

#ifdef WASM_MEMORY_LIMIT
    runtime->memoryLimit = WASM_MEMORY_LIMIT;
#endif

//    int size = 0;
//    unsigned char *target = get_target_program(filename, &size);
//    printf("%d", size);
//    fflush(stdout);

    IM3Module module;
    result = m3_ParseModule (env, &module, target_wasm, target_wasm_len);
    if(result) printf("Problem parsing module");
    result = m3_LoadModule (runtime, module);
    if (result) printf("Problem loading module");

    result = linkESP(runtime);
    if(result) printf("Problem linking ESP");

    IM3Function f;
    result = m3_FindFunction (&f, runtime, "run");
    if (result) printf("Problem finding function");

    printf("Loading Web Ass...");
    fflush(stdout);
    result = m3_CallV(f);

    printf("After function call");
    fflush(stdout);

    if (result) {
        M3ErrorInfo info;
        m3_GetErrorInfo (runtime, &info);
        printf("Error: ");
//        Serial.print(result);
//        Serial.print(" (");
//        Serial.print(info.message);
//        Serial.println(")");
        if (info.file && strlen(info.file) && info.line) {
            printf("aici");
//            Serial.print("At ");
//            Serial.print(info.file);
//            Serial.print(":");
//            Serial.println(info.line);
        }
    }

    vTaskDelete(nullptr);                               // make sure to delete the task on exit, otherwise the dreaded
}                                                       // "guru meditation error" will pop up

void app_main() {
    printf("In app main");
    fflush(stdout);
    xTaskCreate(                                        // app_main should be called only for initialization,
            wasm_task,                              // as such it is limited in stack size
            "Wasm Task"                         ,   // bigger stack sizes require other tasks to be used
            NATIVE_STACK_SIZE,
            NULL,
            tskIDLE_PRIORITY,
            NULL
    );
    printf("Done task creating");
    fflush(stdout);

}