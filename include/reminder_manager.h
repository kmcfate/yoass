#ifndef REMINDER_MANAGER_H
#define REMINDER_MANAGER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "config.h"

struct Reminder {
    String id;
    String title;
    String message;
    unsigned long triggerTime;
    bool recurring;
    unsigned long recurInterval; // in seconds
    bool enabled;
    unsigned long createdAt;
};

class ReminderManager {
private:
    Reminder reminders[MAX_REMINDERS];
    int reminderCount;
    String generateId();

public:
    ReminderManager();
    bool addReminder(const String& title, const String& message, unsigned long triggerTime, bool recurring = false, unsigned long recurInterval = 0);
    bool deleteReminder(const String& id);
    bool enableReminder(const String& id, bool enable);
    Reminder* getReminder(const String& id);
    int getReminderCount();
    Reminder* getAllReminders();
    bool saveReminders();
    bool loadReminders();
    void checkReminders(unsigned long currentTime);
};

#endif // REMINDER_MANAGER_H
