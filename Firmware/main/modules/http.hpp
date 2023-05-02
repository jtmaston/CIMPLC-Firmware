//
// Created by Alexandru Anastasiu on 2/7/23.
//

#ifndef SERIALTEST_HTTP_HPP
#define SERIALTEST_HTTP_HPP

#include <init/commonComponents.hpp>
#include <esp_ota_ops.h>
#include <esp_app_desc.h>
#include <esp_image_format.h>
#include <lwip/sockets.h>
#include <cmath>
extern Transport appInterconnect;
httpd_handle_t setupHTTPServer();

#endif //SERIALTEST_HTTP_HPP
