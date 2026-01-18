#include <Arduino.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include "config.h"
#include "task_manager.h"
#include "note_manager.h"
#include "reminder_manager.h"
#include "audio_handler.h"

// Global managers
TaskManager taskManager;
NoteManager noteManager;
ReminderManager reminderManager;
AudioHandler audioHandler;

// WiFi and time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_SERVER, GMT_OFFSET_SEC, 60000);

// Button handling
bool buttonPressed = false;
unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 50;

void setupWiFi() {
    Serial.println("Connecting to WiFi...");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20) {
        delay(500);
        Serial.print(".");
        attempts++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        digitalWrite(LED_PIN, HIGH);
    } else {
        Serial.println("\nWiFi connection failed!");
    }
}

void setupButton() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    pinMode(LED_PIN, OUTPUT);
}

void handleButton() {
    static bool lastButtonState = HIGH;
    bool currentButtonState = digitalRead(BUTTON_PIN);
    
    if (currentButtonState != lastButtonState) {
        unsigned long currentTime = millis();
        if ((currentTime - lastButtonPress) > debounceDelay) {
            if (currentButtonState == LOW) {
                buttonPressed = true;
                Serial.println("Button pressed!");
                audioHandler.playConfirmation();
            }
            lastButtonPress = currentTime;
        }
    }
    lastButtonState = currentButtonState;
}

void printMenu() {
    Serial.println("\n===== YOASS - Your Only Assistant =====");
    Serial.println("1. Add Task");
    Serial.println("2. List Tasks");
    Serial.println("3. Complete Task");
    Serial.println("4. Add Note");
    Serial.println("5. List Notes");
    Serial.println("6. Search Notes");
    Serial.println("7. Add Reminder");
    Serial.println("8. List Reminders");
    Serial.println("9. Show Stats");
    Serial.println("0. Help");
    Serial.println("======================================");
    Serial.print("Enter command: ");
}

void handleSerialCommands() {
    if (Serial.available() > 0) {
        String command = Serial.readStringUntil('\n');
        command.trim();
        
        if (command == "1") {
            Serial.println("\nAdd Task");
            Serial.print("Title: ");
            while (!Serial.available()) delay(10);
            String title = Serial.readStringUntil('\n');
            title.trim();
            
            Serial.print("Description: ");
            while (!Serial.available()) delay(10);
            String description = Serial.readStringUntil('\n');
            description.trim();
            
            Serial.print("Priority (0=Low, 1=Medium, 2=High, 3=Urgent): ");
            while (!Serial.available()) delay(10);
            int priority = Serial.parseInt();
            Serial.readStringUntil('\n'); // Clear buffer
            
            if (taskManager.addTask(title, description, (TaskPriority)priority)) {
                Serial.println("Task added successfully!");
                audioHandler.playConfirmation();
            } else {
                Serial.println("Failed to add task!");
                audioHandler.playError();
            }
        }
        else if (command == "2") {
            Serial.println("\n=== Task List ===");
            int count = taskManager.getTaskCount();
            if (count == 0) {
                Serial.println("No tasks found.");
            } else {
                Task* tasks = taskManager.getAllTasks();
                for (int i = 0; i < count; i++) {
                    Serial.print(i + 1);
                    Serial.print(". ");
                    Serial.print(tasks[i].title);
                    Serial.print(" - ");
                    const char* statusStr[] = {"TODO", "IN PROGRESS", "COMPLETED", "CANCELLED"};
                    Serial.print(statusStr[tasks[i].status]);
                    Serial.print(" (Priority: ");
                    const char* priorityStr[] = {"Low", "Medium", "High", "Urgent"};
                    Serial.print(priorityStr[tasks[i].priority]);
                    Serial.println(")");
                }
            }
        }
        else if (command == "3") {
            Serial.println("\nComplete Task");
            Serial.print("Enter task number: ");
            while (!Serial.available()) delay(10);
            int taskNum = Serial.parseInt();
            Serial.readStringUntil('\n');
            
            Task* tasks = taskManager.getAllTasks();
            int count = taskManager.getTaskCount();
            if (taskNum > 0 && taskNum <= count) {
                if (taskManager.updateTask(tasks[taskNum - 1].id, COMPLETED)) {
                    Serial.println("Task completed!");
                    audioHandler.playConfirmation();
                } else {
                    Serial.println("Failed to complete task!");
                    audioHandler.playError();
                }
            } else {
                Serial.println("Invalid task number!");
                audioHandler.playError();
            }
        }
        else if (command == "4") {
            Serial.println("\nAdd Note");
            Serial.print("Title: ");
            while (!Serial.available()) delay(10);
            String title = Serial.readStringUntil('\n');
            title.trim();
            
            Serial.print("Content: ");
            while (!Serial.available()) delay(10);
            String content = Serial.readStringUntil('\n');
            content.trim();
            
            Serial.print("Tags (comma-separated): ");
            while (!Serial.available()) delay(10);
            String tags = Serial.readStringUntil('\n');
            tags.trim();
            
            if (noteManager.addNote(title, content, tags)) {
                Serial.println("Note added successfully!");
                audioHandler.playConfirmation();
            } else {
                Serial.println("Failed to add note!");
                audioHandler.playError();
            }
        }
        else if (command == "5") {
            Serial.println("\n=== Notes List ===");
            int count = noteManager.getNoteCount();
            if (count == 0) {
                Serial.println("No notes found.");
            } else {
                Note* notes = noteManager.getAllNotes();
                for (int i = 0; i < count; i++) {
                    Serial.print(i + 1);
                    Serial.print(". ");
                    Serial.println(notes[i].title);
                    Serial.print("   ");
                    Serial.println(notes[i].content);
                    if (notes[i].tags.length() > 0) {
                        Serial.print("   Tags: ");
                        Serial.println(notes[i].tags);
                    }
                    Serial.println();
                }
            }
        }
        else if (command == "6") {
            Serial.println("\nSearch Notes");
            Serial.print("Search query: ");
            while (!Serial.available()) delay(10);
            String query = Serial.readStringUntil('\n');
            query.trim();
            
            int count = 0;
            Note* results = noteManager.searchNotes(query, count);
            Serial.print("Found ");
            Serial.print(count);
            Serial.println(" results:");
            for (int i = 0; i < count; i++) {
                Serial.print(i + 1);
                Serial.print(". ");
                Serial.println(results[i].title);
            }
        }
        else if (command == "7") {
            Serial.println("\nAdd Reminder");
            Serial.print("Title: ");
            while (!Serial.available()) delay(10);
            String title = Serial.readStringUntil('\n');
            title.trim();
            
            Serial.print("Message: ");
            while (!Serial.available()) delay(10);
            String message = Serial.readStringUntil('\n');
            message.trim();
            
            Serial.print("Trigger in seconds: ");
            while (!Serial.available()) delay(10);
            unsigned long seconds = Serial.parseInt();
            Serial.readStringUntil('\n');
            
            // Prevent overflow: calculate safe maximum
            const unsigned long MAX_SECONDS = ULONG_MAX / 1000UL;  // ~4294967 seconds (49 days)
            
            if (seconds > MAX_SECONDS) {
                Serial.print("Time too large! Maximum is ");
                Serial.print(MAX_SECONDS);
                Serial.println(" seconds (49 days)");
                audioHandler.playError();
            } else {
                // Safe multiplication since we checked bounds
                unsigned long offsetMs = seconds * 1000UL;
                unsigned long currentMillis = millis();
                
                // Check for overflow when adding offset to current time
                if (offsetMs > ULONG_MAX - currentMillis) {
                    Serial.println("Reminder time would overflow system time!");
                    audioHandler.playError();
                } else {
                    unsigned long triggerTime = currentMillis + offsetMs;
                    if (reminderManager.addReminder(title, message, triggerTime)) {
                        Serial.println("Reminder added successfully!");
                        audioHandler.playConfirmation();
                    } else {
                        Serial.println("Failed to add reminder!");
                        audioHandler.playError();
                    }
                }
            }
        }
        else if (command == "8") {
            Serial.println("\n=== Reminders List ===");
            int count = reminderManager.getReminderCount();
            if (count == 0) {
                Serial.println("No reminders found.");
            } else {
                Reminder* reminders = reminderManager.getAllReminders();
                for (int i = 0; i < count; i++) {
                    Serial.print(i + 1);
                    Serial.print(". ");
                    Serial.print(reminders[i].title);
                    Serial.print(" - ");
                    Serial.println(reminders[i].enabled ? "Enabled" : "Disabled");
                }
            }
        }
        else if (command == "9") {
            Serial.println("\n=== Statistics ===");
            Serial.print("Total Tasks: ");
            Serial.println(taskManager.getTaskCount());
            
            int todoCount = 0;
            taskManager.getTasksByStatus(TODO, todoCount);
            Serial.print("TODO Tasks: ");
            Serial.println(todoCount);
            
            int completedCount = 0;
            taskManager.getTasksByStatus(COMPLETED, completedCount);
            Serial.print("Completed Tasks: ");
            Serial.println(completedCount);
            
            Serial.print("Total Notes: ");
            Serial.println(noteManager.getNoteCount());
            
            Serial.print("Active Reminders: ");
            Serial.println(reminderManager.getReminderCount());
        }
        else if (command == "0") {
            printMenu();
        }
        else {
            Serial.println("Unknown command. Type '0' for help.");
        }
    }
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n\n===================================");
    Serial.println("   YOASS - Your Only Assistant");
    Serial.println("   ADHD Management System");
    Serial.println("===================================\n");
    
    // Initialize SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("Failed to mount SPIFFS!");
        return;
    }
    Serial.println("SPIFFS mounted successfully");
    
    // Setup hardware
    setupButton();
    
    // Initialize audio
    if (audioHandler.init()) {
        Serial.println("Audio system initialized");
        audioHandler.playConfirmation();
    } else {
        Serial.println("Failed to initialize audio system");
    }
    
    // Connect to WiFi
    setupWiFi();
    
    // Initialize NTP client
    if (WiFi.status() == WL_CONNECTED) {
        timeClient.begin();
        timeClient.update();
        Serial.println("Time synchronized");
    }
    
    // Load existing data
    Serial.println("Loading existing data...");
    taskManager.loadTasks();
    noteManager.loadNotes();
    reminderManager.loadReminders();
    
    Serial.print("Loaded: ");
    Serial.print(taskManager.getTaskCount());
    Serial.print(" tasks, ");
    Serial.print(noteManager.getNoteCount());
    Serial.print(" notes, ");
    Serial.print(reminderManager.getReminderCount());
    Serial.println(" reminders");
    
    printMenu();
}

void loop() {
    // Handle button
    handleButton();
    
    // Handle serial commands
    handleSerialCommands();
    
    // Update time
    if (WiFi.status() == WL_CONNECTED) {
        timeClient.update();
    }
    
    // Check reminders
    unsigned long currentTime = millis();
    taskManager.checkReminders(currentTime);
    reminderManager.checkReminders(currentTime);
    
    delay(100);
}
