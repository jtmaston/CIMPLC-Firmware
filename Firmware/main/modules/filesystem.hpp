//
// Created by Alexandru Anastasiu on 2/7/23.
//

#ifndef SERIALTEST_FILESYSTEM_HPP
#define SERIALTEST_FILESYSTEM_HPP

#include <init/commonComponents.hpp>
#include <esp_vfs_fat.h>
#include <sdmmc_cmd.h>

extern Transport appInterconnect;

int testFileSystem(int x, char**y);
int initFileSystem();
int listDir(int x, char**y);
int touch(int x, char**y);
int cat(int x, char**y);

#endif //SERIALTEST_FILESYSTEM_HPP
