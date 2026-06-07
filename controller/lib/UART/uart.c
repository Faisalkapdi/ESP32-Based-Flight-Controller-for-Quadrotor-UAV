#include "uart.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* ------------------ UART INIT (Platform dependent) ------------------ */
/* Example for ESP32 (ESP-IDF). Modify for your MCU. */

#include "driver/uart.h"
#include "driver/gpio.h"

#define GPS_RX_PIN 16
#define GPS_TX_PIN 17

void GPS_UART_Init(int uart_num, int baudrate)
{
    uart_config_t config = {
        .baud_rate = baudrate,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };

    uart_param_config(uart_num, &config);
    uart_set_pin(uart_num, GPS_TX_PIN, GPS_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    uart_driver_install(uart_num, 2048, 0, 0, NULL, 0);
}

/* ------------------ READ ONE LINE FROM UART ------------------ */
int GPS_UART_ReadLine(char *buffer, int maxlen)
{
    int idx = 0;
    uint8_t c;

    while (uart_read_bytes(UART_NUM_2, &c, 1, 10 / portTICK_PERIOD_MS) > 0) {
        if (c == '\n') {
            buffer[idx] = '\0';
            return idx;
        }
        if (idx < maxlen - 1) {
            buffer[idx++] = c;
        }
    }
    return 0; // No complete line
}

/* ------------------ PARSE GPRMC ------------------ */
void GPS_Parse_GPRMC(char *nmea, GPS_Data *out)
{
    char *token;
    int index = 0;

    /* Default values */
    out->fix = false;
    out->latitude = 0.0;
    out->longitude = 0.0;
    out->speed_kmph = 0.0;

    token = strtok(nmea, ",");

    while (token != NULL && index <= 8) {
        // loop 0 to 6 
        switch (index) {

        case 2: // A/V GPS FIX
            out->fix = (token[0] == 'A');
            break;

        case 3: { // LATITUDE ddmm.mmmm
            double raw = atof(token);
            int deg = (int)(raw / 100);
            double minutes = raw - (deg * 100);
            out->latitude = deg + minutes / 60.0;
            break;
        }

        case 4: // N/S
            if (token[0] == 'S') out->latitude *= -1;
            break;

        case 5: { // LONGITUDE dddmm.mmmm
            double raw = atof(token);
            int deg = (int)(raw / 100);
            double minutes = raw - (deg * 100);
            out->longitude = deg + minutes / 60.0;
            break;
        }

        case 6: // E/W
            if (token[0] == 'W') out->longitude *= -1;
            break;

        case 7: { // Speed in knots
            double knots = atof(token);
            out->speed_kmph = knots * 1.852;
            break;
        }
        }

        token = strtok(NULL, ",");
        index++;
    }
}