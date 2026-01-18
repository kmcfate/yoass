# Simple Task Demo

This example demonstrates the basic task management features of Yoass.

## What It Does

1. Initializes the task manager
2. Creates 4 sample tasks with different priorities
3. Lists all tasks with their details
4. Completes the first task
5. Shows statistics about tasks

## Running the Example

### Arduino IDE
1. Copy this folder to your Arduino sketches directory
2. Open `simple_task_demo.ino`
3. Make sure you have the main Yoass project files in your include path
4. Upload to your ESP32

### PlatformIO
This example uses the same structure as the main project, so you can:
1. Replace `src/main.cpp` with this example temporarily
2. Build and upload as normal
3. Restore the original `main.cpp` when done

## Expected Output

```
=== Yoass Simple Task Demo ===

Creating demo tasks...

=== Task List ===

1. Buy groceries
   Description: Milk, eggs, bread, coffee
   Priority: High
   Status: TODO

2. Call dentist
   Description: Schedule checkup appointment
   Priority: Urgent
   Status: TODO

3. Exercise
   Description: 30 minutes cardio
   Priority: Medium
   Status: TODO

4. Read book
   Description: Chapter 5 of current book
   Priority: Low
   Status: TODO

Completing first task...

=== Statistics ===
Total tasks: 4
TODO: 3
Completed: 1
High priority: 1
Urgent: 1

Demo complete! Tasks are saved to SPIFFS.
Reset the board to see tasks persist across reboots.
```

## Learning Points

This example shows:
- How to initialize managers
- How to create tasks with different priorities
- How to retrieve and list tasks
- How to update task status
- How to filter tasks by status and priority
- How data persists in SPIFFS

## Next Steps

Try modifying the example to:
- Add tasks with due dates
- Set reminders on tasks
- Delete completed tasks
- Search for specific tasks
- Add your own custom functionality
