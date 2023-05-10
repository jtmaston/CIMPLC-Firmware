//
// Created by Alexandru Anastasiu on 2/7/23.
//
#include "gps.hpp"




int gpgga(int x, char **y) {
    float discardf;
    char discardc;
    int discardd;
    float alt;

    sscanf(y[1], "%f,%f,%c,%f,%c,%d,%d,%f,%f",
           &discardf, &discardf, &discardc, &discardf, &discardc, &discardd, &discardd, &discardf, &alt);

    appInterconnect.gpsData.altitude = alt;
    return 0;
}

int gpgsa(int x, char **y) {
    return 0;
}

int gpgsv(int x, char **y)
{
    int msgCount, msgNum, inView;
    sscanf(y[1], "%d,%d,%d", &msgCount, &msgNum, &inView);
    appInterconnect.gpsData.satellitesInView = inView;

    fflush(stdout);
    return 0;
}

int gprmc(int x, char **y) {
    float utc;
    char status;
    float latitude;
    char nS;
    float longitude;
    char eV;
    float kn;
    float course;
    int date;

    sscanf(y[1], "%f,%c,%f,%c,%f,%c,%f,%f,%d", &utc, &status, &latitude, &nS, &longitude, &eV, &kn, &course, &date);

    if(status == 'A' )
    {
        appInterconnect.gpsData.utcTime = utc;
        appInterconnect.gpsData.latitude = (nS == 'N') ? latitude : -latitude;
        appInterconnect.gpsData.longitude = (eV == 'E') ? longitude : -longitude;
        appInterconnect.gpsData.date = date;
        appInterconnect.gpsData.groundSpeed = kn * 1.852f;
        appInterconnect.gpsData.heading = course;
    }


    // negative long => vest


    return 0;
}

int gpvtg(int x, char **y) {


    float discardF;
    int discardI;
    char discardC;


    sscanf(y[1], "%f,%c,%f,%c,%f,%c,%f", &discardF, &discardC, &discardF, &discardC, &discardF, &discardC,
           &appInterconnect.gpsData.groundSpeed);
    return 0;
}

static void gpsParser(void *pvParameters) {


    uart_flush_input(GPS_SERIAL);
    uart_flush(GPS_SERIAL);

    registerNewCommand("$GPGGA",
                       "UTC,LAT,N/S,LONG,E/W,FIX,SATS USED,HTOP,MSL ALT,UNIT,GEOIDAL SEP,UNIT,AGE",
                       "Global Positioning System Fixed Data",
                       &gpgga);
    registerNewCommand("$GPGSA",
                       "MODE1,MODE2,SATUSED_1 ... SATUSED_12,PDOP,HDOP",
                       "GNSS DOP and Active Satellites",
                       &gpgsa);
    registerNewCommand("$GPGSV",
                       "MSGS,MSG NUM,SAT IN VIEW,SAT ID,ELEVATION,AZIMUTH,SNR,...,SATID,ELEVATION,AZIMUTH,SNR",
                       "GNSS Satellites in View",
                       &gpgsv);
    registerNewCommand("$GPRMC",
                       "UTC,STATUS,LAT,N/S,LONG,E/W,SPEED,COURSE,DATE,MAG VAR_VAL, VAR_DIR,MODE",
                       "Recommended Minimum Navigation Information",
                       &gprmc);
    registerNewCommand("$GPVTG",
                       "COURSE,REFERENCE,SPEED_KN,UNIT_KN,SPEED_KM,UNIT_KM,MODE",
                       "Course and speed information relative to the ground",
                       &gpvtg);

    char data[100] = { 0 };
    int p = 0; int ret;

    while (true) {
        char b = 0;
        int len = uart_read_bytes(GPS_SERIAL, &b, sizeof (char), 20 / portTICK_PERIOD_MS);
        if(len > 0)
        {
            if(b == '\n')
            {
                data[p - 1] = 0;
                if ( appInterconnect.debugPrintGPS )
                {
                    stdout = appInterconnect.stdioRedirect;
                    printf("%s\n", data);
                    fflush(stdout);
                }
                p = 0;
                for(int i = 0 ; i < 7;i++)
                    if(data[i] == ',')
                        data[i] = ' ';
                esp_console_run(data, &ret);
            }
            else
            {
                data[p++] = b;
            }
        }
    }
}


int startParser() {
    xTaskCreate(gpsParser, "GPS_Parser", 4096U, nullptr, tskIDLE_PRIORITY, nullptr);
    return 0;
}