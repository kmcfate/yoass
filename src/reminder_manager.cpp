#include "reminder_manager.h"
#include <SPIFFS.h>

ReminderManager::ReminderManager() : reminderCount(0) {
    for (int i = 0; i < MAX_REMINDERS; i++) {
        reminders[i].id = "";
    }
}

String ReminderManager::generateId() {
    return String(millis()) + String(random(1000, 9999));
}

bool ReminderManager::addReminder(const String& title, const String& message, unsigned long triggerTime, bool recurring, unsigned long recurInterval) {
    if (reminderCount >= MAX_REMINDERS) {
        return false;
    }
    
    Reminder newReminder;
    newReminder.id = generateId();
    newReminder.title = title;
    newReminder.message = message;
    newReminder.triggerTime = triggerTime;
    newReminder.recurring = recurring;
    newReminder.recurInterval = recurInterval;
    newReminder.enabled = true;
    newReminder.createdAt = millis();
    
    reminders[reminderCount++] = newReminder;
    return saveReminders();
}

bool ReminderManager::deleteReminder(const String& id) {
    for (int i = 0; i < reminderCount; i++) {
        if (reminders[i].id == id) {
            // Shift reminders down
            for (int j = i; j < reminderCount - 1; j++) {
                reminders[j] = reminders[j + 1];
            }
            reminderCount--;
            reminders[reminderCount].id = "";
            return saveReminders();
        }
    }
    return false;
}

bool ReminderManager::enableReminder(const String& id, bool enable) {
    for (int i = 0; i < reminderCount; i++) {
        if (reminders[i].id == id) {
            reminders[i].enabled = enable;
            return saveReminders();
        }
    }
    return false;
}

Reminder* ReminderManager::getReminder(const String& id) {
    for (int i = 0; i < reminderCount; i++) {
        if (reminders[i].id == id) {
            return &reminders[i];
        }
    }
    return nullptr;
}

int ReminderManager::getReminderCount() {
    return reminderCount;
}

Reminder* ReminderManager::getAllReminders() {
    return reminders;
}

bool ReminderManager::saveReminders() {
    if (!SPIFFS.begin(true)) {
        return false;
    }
    
    File file = SPIFFS.open(REMINDERS_FILE, FILE_WRITE);
    if (!file) {
        return false;
    }
    
    DynamicJsonDocument doc(8192);
    JsonArray remindersArray = doc.createNestedArray("reminders");
    
    for (int i = 0; i < reminderCount; i++) {
        JsonObject reminderObj = remindersArray.createNestedObject();
        reminderObj["id"] = reminders[i].id;
        reminderObj["title"] = reminders[i].title;
        reminderObj["message"] = reminders[i].message;
        reminderObj["triggerTime"] = reminders[i].triggerTime;
        reminderObj["recurring"] = reminders[i].recurring;
        reminderObj["recurInterval"] = reminders[i].recurInterval;
        reminderObj["enabled"] = reminders[i].enabled;
        reminderObj["createdAt"] = reminders[i].createdAt;
    }
    
    serializeJson(doc, file);
    file.close();
    return true;
}

bool ReminderManager::loadReminders() {
    if (!SPIFFS.begin(true)) {
        return false;
    }
    
    if (!SPIFFS.exists(REMINDERS_FILE)) {
        return true; // No file yet, that's ok
    }
    
    File file = SPIFFS.open(REMINDERS_FILE, FILE_READ);
    if (!file) {
        return false;
    }
    
    DynamicJsonDocument doc(8192);
    DeserializationError error = deserializeJson(doc, file);
    file.close();
    
    if (error) {
        return false;
    }
    
    JsonArray remindersArray = doc["reminders"];
    reminderCount = 0;
    
    for (JsonObject reminderObj : remindersArray) {
        if (reminderCount >= MAX_REMINDERS) break;
        
        reminders[reminderCount].id = reminderObj["id"].as<String>();
        reminders[reminderCount].title = reminderObj["title"].as<String>();
        reminders[reminderCount].message = reminderObj["message"].as<String>();
        reminders[reminderCount].triggerTime = reminderObj["triggerTime"].as<unsigned long>();
        reminders[reminderCount].recurring = reminderObj["recurring"].as<bool>();
        reminders[reminderCount].recurInterval = reminderObj["recurInterval"].as<unsigned long>();
        reminders[reminderCount].enabled = reminderObj["enabled"].as<bool>();
        reminders[reminderCount].createdAt = reminderObj["createdAt"].as<unsigned long>();
        reminderCount++;
    }
    
    return true;
}

void ReminderManager::checkReminders(unsigned long currentTime) {
    for (int i = 0; i < reminderCount; i++) {
        if (reminders[i].enabled && currentTime >= reminders[i].triggerTime) {
            Serial.println("REMINDER: " + reminders[i].title);
            Serial.println(reminders[i].message);
            
            if (reminders[i].recurring && reminders[i].recurInterval > 0) {
                // Update trigger time for next occurrence
                // Convert recurInterval from seconds to milliseconds safely
                unsigned long intervalMs = reminders[i].recurInterval * 1000UL;
                reminders[i].triggerTime = currentTime + intervalMs;
                saveReminders();
            } else {
                // Disable one-time reminder
                reminders[i].enabled = false;
                saveReminders();
            }
        }
    }
}
