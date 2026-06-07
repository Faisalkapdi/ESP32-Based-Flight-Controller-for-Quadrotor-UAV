#ifndef GPS_UART_H
#define GPS_UART_H

#include <stdbool.h>

typedef struct {
    double latitude;
    double longitude;
    double speed_kmph;
    bool   fix;
} GPS_Data;

/* Initialize UART (platform-specific implementation in .c) */
void GPS_UART_Init(int uart_num, int baudrate);

/* Read raw NMEA data from UART */
int GPS_UART_ReadLine(char *buffer, int maxlen);

/* Parse GPRMC sentence */
void GPS_Parse_GPRMC(char *nmea, GPS_Data *out);

#endif