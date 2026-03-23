idf_component_register(
    SRCS
        "esp32_c6_amoled_1_8.c"
        "esp32_s3_amoled_1_8.c"
    INCLUDE_DIRS "include"
    REQUIRES
        driver
        esp_lcd
        esp_lcd_touch
        esp_lvgl_port
        esp_timer
        log
)
