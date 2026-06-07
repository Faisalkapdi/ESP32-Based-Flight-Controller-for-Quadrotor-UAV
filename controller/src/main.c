#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

#include "uart.h"

static GPS_Data current_gps;

// ================= MAIN =================
void app_main(void)
{
    char buffer[128];

    // Start GPS UART
    GPS_UART_Init(UART_NUM_2, 9600);

    while (1) {
        int len = GPS_UART_ReadLine(buffer, sizeof(buffer));

        if (len > 0 && strstr(buffer, "$GPRMC")) {
            GPS_Parse_GPRMC(buffer, &current_gps);

            printf("Lat: %.6f | Lon: %.6f | Spd: %.2f km/h | Fix: %s\n",
                   current_gps.latitude,
                   current_gps.longitude,
                   current_gps.speed_kmph,
                   current_gps.fix ? "Valid" : "No Fix");

                }

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}