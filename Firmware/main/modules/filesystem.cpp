//
// Created by Alexandru Anastasiu on 2/7/23.
//

#include "filesystem.hpp"

inline void trap()
{
    printf("Trap!\n");
    fflush(stdout);
}
#include "driver/gpio.h"

int testFileSystem(int x, char**y)
{
    printf("FS init...\n");
    fflush(stdout);

    gpio_reset_pin(GPIO_NUM_4);
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_INPUT);
    if(!gpio_get_level(GPIO_NUM_4)) { printf("No SD card detected!\n");fflush(stdout); return 1; }

    esp_vfs_fat_sdmmc_mount_config_t sdConfig =
            {
                    .format_if_mount_failed = false,
                    .max_files = 1,
                    .allocation_unit_size = 16 * 1024
            };


    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    spi_bus_config_t SPIBusConfig =
            {
                    .mosi_io_num = GPIO_NUM_23,
                    .miso_io_num = GPIO_NUM_19,
                    .sclk_io_num = GPIO_NUM_18,
                    .quadwp_io_num = -1,
                    .quadhd_io_num = -1,
                    .max_transfer_sz = 4000,
            };



    if(!appInterconnect.spiHasBeenInit) {
        auto flag = spi_bus_initialize(static_cast<spi_host_device_t>(host.slot), &SPIBusConfig, SDSPI_DEFAULT_DMA);
        if (flag) {
            printf("Could not initialize the bus!\n");
            fflush(stdout);
            return 1;
        }
        appInterconnect.spiHasBeenInit = true;
    }

    sdspi_device_config_t slotConfig = SDSPI_DEVICE_CONFIG_DEFAULT();
    slotConfig.gpio_cs = GPIO_NUM_5;
    slotConfig.host_id = static_cast<spi_host_device_t>(host.slot);

    mount:
    printf("Attempting to mount fs: "); fflush(stdout);
    auto flag = esp_vfs_fat_sdspi_mount("/storage", &host, &slotConfig, &sdConfig, &appInterconnect.card);
    if ( flag == ESP_FAIL )
    {
        printf("\nFailed to init fs! Would you like to reformat it and try again? (y/n): ");
        fflush(stdout);
        char option;
        scanf("%c", &option);
        if(option == 'y' || option == 'Y'){
            sdConfig.format_if_mount_failed = true;
            goto mount;
        }
        return 1;
    }else if ( flag != ESP_OK)
    {
        printf("\nFailed to communicate with SD card!\n");
        fflush(stdout);
        return 1;
    }

    printf("OK!\n");

    printf("Unmounting and cleaning up...\n");
    fflush(stdout);

    esp_vfs_fat_sdcard_unmount("/storage", appInterconnect.card);
    spi_bus_free(static_cast<spi_host_device_t>(host.slot));
    appInterconnect.spiHasBeenInit = false;

    return 0;
}

#include <filesystem>

int initFileSystem()
{
    gpio_reset_pin(GPIO_NUM_4);
    gpio_set_direction(GPIO_NUM_4, GPIO_MODE_INPUT);
    if(!gpio_get_level(GPIO_NUM_4)) { return 1; }
    // Initialize pins ^


    esp_vfs_fat_sdmmc_mount_config_t sdConfig =
            {
                    .format_if_mount_failed = false,
                    .max_files = 1,
                    .allocation_unit_size = 16 * 1024,
            };

    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    spi_bus_config_t SPIBusConfig =
            {
                    .mosi_io_num = GPIO_NUM_23,
                    .miso_io_num = GPIO_NUM_19,
                    .sclk_io_num = GPIO_NUM_18,
                    .quadwp_io_num = -1,
                    .quadhd_io_num = -1,
                    .max_transfer_sz = 4000,
            };
    if(!appInterconnect.spiHasBeenInit) {
        auto flag = spi_bus_initialize(static_cast<spi_host_device_t>(host.slot), &SPIBusConfig, SDSPI_DEFAULT_DMA);
        if (flag) {
            return 1;
        }
        appInterconnect.spiHasBeenInit = true;
    }
    sdspi_device_config_t slotConfig = SDSPI_DEVICE_CONFIG_DEFAULT();
    slotConfig.gpio_cs = GPIO_NUM_5;
    slotConfig.host_id = static_cast<spi_host_device_t>(host.slot);
    auto flag = esp_vfs_fat_sdspi_mount("/storage", &host, &slotConfig, &sdConfig, &appInterconnect.card);
    if ( flag != ESP_OK)
    {
        return 1;
    }
    trap();
    appInterconnect.logfile = fopen("/storage/log.txt", "w+");
    fclose(appInterconnect.logfile);

    return 0;
}
#include <dirent.h>

int listDir(int x, char**y)
{
    DIR* d;
    dirent *dir;
    d = opendir("/storage/");
    if(d)
    {
        while((dir = readdir(d)) != nullptr)
        {
            printf("%s\n", dir->d_name);
        }
        closedir(d);
    }

    return 0;
}

int cat(int x, char**y)
{
    char dest[100] = "/storage/";
    strcat(dest, y[1]);
    FILE* file = fopen(dest, "r");
    char c;
    do{
        fscanf(file, "%c", &c);
        printf("%c", c);
    }while(c != EOF);
    return 0;
}

int touch(int x, char**y)
{
    char dest[100] = "/storage/";
    strcat(dest, y[1]);
    fclose(fopen(dest, "w+"));
    return 0;
}
