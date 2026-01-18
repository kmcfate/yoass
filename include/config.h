#ifndef CONFIG_H
#define CONFIG_H

// WiFi Configuration
#define WIFI_SSID "YourSSID"
#define WIFI_PASSWORD "YourPassword"

// NTP Configuration
#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET_SEC 0
#define DAYLIGHT_OFFSET_SEC 0

// Audio Configuration
#define I2S_WS 15
#define I2S_SD 32
#define I2S_SCK 14
#define I2S_PORT I2S_NUM_0
#define I2S_SAMPLE_RATE 16000
#define I2S_SAMPLE_BITS 16
#define I2S_READ_LEN 1024

// Button Configuration
#define BUTTON_PIN 0
#define LED_PIN 2

// Storage Configuration
#define MAX_TASKS 50
#define MAX_NOTES 100
#define MAX_REMINDERS 50
#define TASK_FILE "/tasks.json"
#define NOTES_FILE "/notes.json"
#define REMINDERS_FILE "/reminders.json"

// Task Priority Levels
enum TaskPriority {
    LOW = 0,
    MEDIUM = 1,
    HIGH = 2,
    URGENT = 3
};

// Task Status
enum TaskStatus {
    TODO = 0,
    IN_PROGRESS = 1,
    COMPLETED = 2,
    CANCELLED = 3
};

#endif // CONFIG_H
