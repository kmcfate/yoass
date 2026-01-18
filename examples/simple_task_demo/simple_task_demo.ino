/**
 * Simple Task Demo
 * 
 * This example demonstrates basic task management functionality.
 * It creates a few tasks, lists them, and completes one.
 * 
 * Hardware Required:
 * - ESP32 board
 * - I2S audio module (optional, but recommended for feedback)
 * - Speaker connected to I2S module
 * 
 * See HARDWARE.md for wiring details.
 */

#include <Arduino.h>
#include <SPIFFS.h>
#include "task_manager.h"
#include "audio_handler.h"

TaskManager taskManager;
AudioHandler audioHandler;

void setup() {
    Serial.begin(115200);
    delay(1000);
    
    Serial.println("\n=== Yoass Simple Task Demo ===\n");
    
    // Initialize SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("Failed to mount SPIFFS!");
        return;
    }
    
    // Initialize audio for feedback
    audioHandler.init();
    audioHandler.playConfirmation();
    
    // Load any existing tasks
    taskManager.loadTasks();
    
    Serial.println("Creating demo tasks...\n");
    
    // Add some example tasks
    taskManager.addTask("Buy groceries", "Milk, eggs, bread, coffee", HIGH);
    taskManager.addTask("Call dentist", "Schedule checkup appointment", URGENT);
    taskManager.addTask("Exercise", "30 minutes cardio", MEDIUM);
    taskManager.addTask("Read book", "Chapter 5 of current book", LOW);
    
    audioHandler.playConfirmation();
    
    // List all tasks
    Serial.println("=== Task List ===\n");
    int count = taskManager.getTaskCount();
    Task* tasks = taskManager.getAllTasks();
    
    const char* priorityStr[] = {"Low", "Medium", "High", "Urgent"};
    const char* statusStr[] = {"TODO", "In Progress", "Completed", "Cancelled"};
    
    for (int i = 0; i < count; i++) {
        Serial.print(i + 1);
        Serial.print(". ");
        Serial.println(tasks[i].title);
        Serial.print("   Description: ");
        Serial.println(tasks[i].description);
        Serial.print("   Priority: ");
        Serial.println(priorityStr[tasks[i].priority]);
        Serial.print("   Status: ");
        Serial.println(statusStr[tasks[i].status]);
        Serial.println();
    }
    
    // Complete the first task
    delay(2000);
    Serial.println("Completing first task...\n");
    taskManager.updateTask(tasks[0].id, COMPLETED);
    audioHandler.playConfirmation();
    
    // Show statistics
    delay(1000);
    Serial.println("=== Statistics ===");
    Serial.print("Total tasks: ");
    Serial.println(taskManager.getTaskCount());
    
    int todoCount = 0;
    taskManager.getTasksByStatus(TODO, todoCount);
    Serial.print("TODO: ");
    Serial.println(todoCount);
    
    int completedCount = 0;
    taskManager.getTasksByStatus(COMPLETED, completedCount);
    Serial.print("Completed: ");
    Serial.println(completedCount);
    
    int highPriorityCount = 0;
    taskManager.getTasksByPriority(HIGH, highPriorityCount);
    Serial.print("High priority: ");
    Serial.println(highPriorityCount);
    
    int urgentCount = 0;
    taskManager.getTasksByPriority(URGENT, urgentCount);
    Serial.print("Urgent: ");
    Serial.println(urgentCount);
    
    Serial.println("\nDemo complete! Tasks are saved to SPIFFS.");
    Serial.println("Reset the board to see tasks persist across reboots.");
}

void loop() {
    // Nothing to do in loop for this simple demo
    delay(1000);
}
