#include "esp_log.h"
#include "board.h"

static const char *TAG = "yoass";

void app_main(void)
{
    ESP_LOGI(TAG, "yoass starting");

    ESP_ERROR_CHECK(board_init());

    ESP_LOGI(TAG, "board ready — display %dx%d", BOARD_LCD_H_RES, BOARD_LCD_V_RES);

    /* Application code goes here */
}
