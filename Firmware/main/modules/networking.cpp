//
// Created by Alexandru Anastasiu on 2/7/23.
//

#include "networking.hpp"
#include "gps.hpp"


void wifiInitSoftAP() {
    nvs_flash_init();                                           // initialize nonvolatile flash
    esp_netif_init();                                           // initialize the network interface
    appInterconnect.iface = esp_netif_create_default_wifi_ap(); // and register it into the AppInterconnect

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();        // create a default parameter configuration
    esp_wifi_init(&cfg);                                 // initialize the Wi-Fi

    wifi_config_t wifiConfig =                                  // and set parameters
            {
            .ap = {
                    .ssid = "DR04",
                    .password = "UPBDriveFS",
                    .ssid_len = 5U,
                    .channel = 10U,
                    .authmode = WIFI_AUTH_WPA2_PSK,
                    .max_connection = 2U,                       // note: a maximum 2 clients are allowed at any time
            },
    };

    esp_wifi_set_mode(WIFI_MODE_AP);                      // set to softAP
    esp_wifi_set_config(WIFI_IF_AP, &wifiConfig); // and configure
    esp_wifi_start();                                           // then start

    xTaskCreate(tcpServerTask,
                "telnetListener",
                1500,
                (void *) AF_INET, // then, create the Telnet listener task.
                5,
                nullptr);
}

extern unsigned int rebootCounter;
extern unsigned int otaRebootAttemptCounter;

void tcpServerTask(void *pvParameters) {
    while(true)
    {
        char addrStr[128];
        int keepAlive = 1;
        int keepIdle = 5;
        int keepInterval = 5;
        int keepCount = 3;
        sockaddr_storage peerAddressStorage{};

        auto *peerAddress = (sockaddr_in *) &peerAddressStorage;
        peerAddress->sin_addr.s_addr = htonl(INADDR_ANY);
        peerAddress->sin_family = AF_INET;
        peerAddress->sin_port = htons(23);

        int listenSock = socket(AF_INET, SOCK_STREAM, 0);
        int opt = 1;
        setsockopt(listenSock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);
        //printf("Socket is up!\n");

        int err = bind(listenSock, (struct sockaddr *) &peerAddressStorage, sizeof(peerAddressStorage));
        if (err != 0)
            printf("Bind err: errno %d \n", errno);

        err = listen(listenSock, 1);
        if (err != 0)
            printf("Listen err: errno %d \n", errno);

        printf("Socket listening!\n");

        //while (true) {
        sockaddr_storage sourceAddr{}; // Large enough for both IPv4 or IPv6
        socklen_t addrLen = sizeof(sourceAddr);
        appInterconnect.sock = accept(listenSock, (struct sockaddr *) &sourceAddr, &addrLen);

        // Set tcp keepalive option
        setsockopt(appInterconnect.sock, SOL_SOCKET, SO_KEEPALIVE, &keepAlive, sizeof(int));
        setsockopt(appInterconnect.sock, IPPROTO_TCP, TCP_KEEPIDLE, &keepIdle, sizeof(int));
        setsockopt(appInterconnect.sock, IPPROTO_TCP, TCP_KEEPINTVL, &keepInterval, sizeof(int));
        setsockopt(appInterconnect.sock, IPPROTO_TCP, TCP_KEEPCNT, &keepCount, sizeof(int));

        if (sourceAddr.ss_family == PF_INET) {
            inet_ntoa_r(((struct sockaddr_in *) &sourceAddr)->sin_addr, addrStr, sizeof(addrStr) - 1);
        }
        appInterconnect.stdioRedirect = fdopen(appInterconnect.sock, "w");


        xTaskCreate(telnetREPL, "telnet_repl", 4096U, nullptr, tskIDLE_PRIORITY, nullptr);

        appInterconnect.socketConnected = true;

        rebootCounter = 0;
        otaRebootAttemptCounter = 0;

        shutdown(listenSock, SHUT_RDWR);
        close(listenSock);
        vTaskSuspend(nullptr);
    }

}


