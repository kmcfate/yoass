#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "config.h"

struct Task {
    String id;
    String title;
    String description;
    TaskPriority priority;
    TaskStatus status;
    unsigned long dueDate;
    unsigned long createdAt;
    unsigned long completedAt;
    bool hasReminder;
    unsigned long reminderTime;
};

class TaskManager {
private:
    Task tasks[MAX_TASKS];
    int taskCount;
    String generateId();

public:
    TaskManager();
    bool addTask(const String& title, const String& description, TaskPriority priority, unsigned long dueDate = 0);
    bool updateTask(const String& id, TaskStatus status);
    bool deleteTask(const String& id);
    bool setReminder(const String& id, unsigned long reminderTime);
    Task* getTask(const String& id);
    int getTaskCount();
    Task* getAllTasks();
    Task* getTasksByStatus(TaskStatus status, int& count);
    Task* getTasksByPriority(TaskPriority priority, int& count);
    bool saveTasks();
    bool loadTasks();
    void checkReminders(unsigned long currentTime);
};

#endif // TASK_MANAGER_H
