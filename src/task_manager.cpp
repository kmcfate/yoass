#include "task_manager.h"
#include <SPIFFS.h>

TaskManager::TaskManager() : taskCount(0) {
    for (int i = 0; i < MAX_TASKS; i++) {
        tasks[i].id = "";
    }
}

String TaskManager::generateId() {
    return String(millis()) + String(random(1000, 9999));
}

bool TaskManager::addTask(const String& title, const String& description, TaskPriority priority, unsigned long dueDate) {
    if (taskCount >= MAX_TASKS) {
        return false;
    }
    
    Task newTask;
    newTask.id = generateId();
    newTask.title = title;
    newTask.description = description;
    newTask.priority = priority;
    newTask.status = TODO;
    newTask.dueDate = dueDate;
    newTask.createdAt = millis();
    newTask.completedAt = 0;
    newTask.hasReminder = false;
    newTask.reminderTime = 0;
    
    tasks[taskCount++] = newTask;
    return saveTasks();
}

bool TaskManager::updateTask(const String& id, TaskStatus status) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id) {
            tasks[i].status = status;
            if (status == COMPLETED) {
                tasks[i].completedAt = millis();
            }
            return saveTasks();
        }
    }
    return false;
}

bool TaskManager::deleteTask(const String& id) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id) {
            // Shift tasks down
            for (int j = i; j < taskCount - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            taskCount--;
            tasks[taskCount].id = "";
            return saveTasks();
        }
    }
    return false;
}

bool TaskManager::setReminder(const String& id, unsigned long reminderTime) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id) {
            tasks[i].hasReminder = true;
            tasks[i].reminderTime = reminderTime;
            return saveTasks();
        }
    }
    return false;
}

Task* TaskManager::getTask(const String& id) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == id) {
            return &tasks[i];
        }
    }
    return nullptr;
}

int TaskManager::getTaskCount() {
    return taskCount;
}

Task* TaskManager::getAllTasks() {
    return tasks;
}

Task* TaskManager::getTasksByStatus(TaskStatus status, int& count) {
    count = 0;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].status == status) {
            filteredTasks[count++] = tasks[i];
        }
    }
    return filteredTasks;
}

Task* TaskManager::getTasksByPriority(TaskPriority priority, int& count) {
    count = 0;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].priority == priority) {
            filteredTasks[count++] = tasks[i];
        }
    }
    return filteredTasks;
}

bool TaskManager::saveTasks() {
    if (!SPIFFS.begin(true)) {
        return false;
    }
    
    File file = SPIFFS.open(TASK_FILE, FILE_WRITE);
    if (!file) {
        return false;
    }
    
    DynamicJsonDocument doc(8192);
    JsonArray tasksArray = doc.createNestedArray("tasks");
    
    for (int i = 0; i < taskCount; i++) {
        JsonObject taskObj = tasksArray.createNestedObject();
        taskObj["id"] = tasks[i].id;
        taskObj["title"] = tasks[i].title;
        taskObj["description"] = tasks[i].description;
        taskObj["priority"] = tasks[i].priority;
        taskObj["status"] = tasks[i].status;
        taskObj["dueDate"] = tasks[i].dueDate;
        taskObj["createdAt"] = tasks[i].createdAt;
        taskObj["completedAt"] = tasks[i].completedAt;
        taskObj["hasReminder"] = tasks[i].hasReminder;
        taskObj["reminderTime"] = tasks[i].reminderTime;
    }
    
    serializeJson(doc, file);
    file.close();
    return true;
}

bool TaskManager::loadTasks() {
    if (!SPIFFS.begin(true)) {
        return false;
    }
    
    if (!SPIFFS.exists(TASK_FILE)) {
        return true; // No file yet, that's ok
    }
    
    File file = SPIFFS.open(TASK_FILE, FILE_READ);
    if (!file) {
        return false;
    }
    
    DynamicJsonDocument doc(8192);
    DeserializationError error = deserializeJson(doc, file);
    file.close();
    
    if (error) {
        return false;
    }
    
    JsonArray tasksArray = doc["tasks"];
    taskCount = 0;
    
    for (JsonObject taskObj : tasksArray) {
        if (taskCount >= MAX_TASKS) break;
        
        tasks[taskCount].id = taskObj["id"].as<String>();
        tasks[taskCount].title = taskObj["title"].as<String>();
        tasks[taskCount].description = taskObj["description"].as<String>();
        tasks[taskCount].priority = (TaskPriority)taskObj["priority"].as<int>();
        tasks[taskCount].status = (TaskStatus)taskObj["status"].as<int>();
        tasks[taskCount].dueDate = taskObj["dueDate"].as<unsigned long>();
        tasks[taskCount].createdAt = taskObj["createdAt"].as<unsigned long>();
        tasks[taskCount].completedAt = taskObj["completedAt"].as<unsigned long>();
        tasks[taskCount].hasReminder = taskObj["hasReminder"].as<bool>();
        tasks[taskCount].reminderTime = taskObj["reminderTime"].as<unsigned long>();
        taskCount++;
    }
    
    return true;
}

void TaskManager::checkReminders(unsigned long currentTime) {
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].hasReminder && tasks[i].status != COMPLETED && tasks[i].status != CANCELLED) {
            if (currentTime >= tasks[i].reminderTime) {
                Serial.println("REMINDER: " + tasks[i].title);
                // Disable reminder after triggering
                tasks[i].hasReminder = false;
                saveTasks();
            }
        }
    }
}
