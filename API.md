# API Reference

## TaskManager Class

Manages tasks with priorities, due dates, and reminders.

### Methods

#### `TaskManager()`
Constructor. Initializes the task manager.

```cpp
TaskManager taskManager;
```

#### `bool addTask(const String& title, const String& description, TaskPriority priority, unsigned long dueDate = 0)`
Add a new task to the system.

**Parameters:**
- `title`: Task title (String)
- `description`: Task description (String)
- `priority`: Task priority (LOW, MEDIUM, HIGH, URGENT)
- `dueDate`: Due date in milliseconds since boot (optional)

**Returns:** `true` if successful, `false` otherwise

**Example:**
```cpp
taskManager.addTask("Buy groceries", "Milk, eggs, bread", HIGH, millis() + 86400000);
```

#### `bool updateTask(const String& id, TaskStatus status)`
Update task status.

**Parameters:**
- `id`: Task ID (String)
- `status`: New status (TODO, IN_PROGRESS, COMPLETED, CANCELLED)

**Returns:** `true` if successful, `false` otherwise

**Example:**
```cpp
taskManager.updateTask("12345678901234", COMPLETED);
```

#### `bool deleteTask(const String& id)`
Delete a task.

**Parameters:**
- `id`: Task ID (String)

**Returns:** `true` if successful, `false` otherwise

#### `bool setReminder(const String& id, unsigned long reminderTime)`
Set a reminder for a task.

**Parameters:**
- `id`: Task ID (String)
- `reminderTime`: Trigger time in milliseconds since boot

**Returns:** `true` if successful, `false` otherwise

#### `Task* getTask(const String& id)`
Get a specific task by ID.

**Parameters:**
- `id`: Task ID (String)

**Returns:** Pointer to Task object or `nullptr` if not found

#### `int getTaskCount()`
Get total number of tasks.

**Returns:** Number of tasks (int)

#### `Task* getAllTasks()`
Get all tasks.

**Returns:** Pointer to array of Task objects

#### `Task* getTasksByStatus(TaskStatus status, int& count)`
Get tasks filtered by status.

**Parameters:**
- `status`: Status to filter by
- `count`: Reference to store result count

**Returns:** Pointer to array of filtered Task objects

#### `Task* getTasksByPriority(TaskPriority priority, int& count)`
Get tasks filtered by priority.

**Parameters:**
- `priority`: Priority to filter by
- `count`: Reference to store result count

**Returns:** Pointer to array of filtered Task objects

#### `bool saveTasks()`
Save tasks to persistent storage.

**Returns:** `true` if successful, `false` otherwise

#### `bool loadTasks()`
Load tasks from persistent storage.

**Returns:** `true` if successful, `false` otherwise

#### `void checkReminders(unsigned long currentTime)`
Check and trigger task reminders.

**Parameters:**
- `currentTime`: Current time in milliseconds

### Task Structure

```cpp
struct Task {
    String id;                  // Unique identifier
    String title;               // Task title
    String description;         // Task description
    TaskPriority priority;      // Priority level
    TaskStatus status;          // Current status
    unsigned long dueDate;      // Due date (milliseconds)
    unsigned long createdAt;    // Creation time
    unsigned long completedAt;  // Completion time
    bool hasReminder;           // Has reminder flag
    unsigned long reminderTime; // Reminder trigger time
};
```

### Enums

```cpp
enum TaskPriority {
    LOW = 0,
    MEDIUM = 1,
    HIGH = 2,
    URGENT = 3
};

enum TaskStatus {
    TODO = 0,
    IN_PROGRESS = 1,
    COMPLETED = 2,
    CANCELLED = 3
};
```

---

## NoteManager Class

Manages notes with tagging and search capabilities.

### Methods

#### `NoteManager()`
Constructor. Initializes the note manager.

#### `bool addNote(const String& title, const String& content, const String& tags = "")`
Add a new note.

**Parameters:**
- `title`: Note title (String)
- `content`: Note content (String)
- `tags`: Comma-separated tags (String, optional)

**Returns:** `true` if successful, `false` otherwise

**Example:**
```cpp
noteManager.addNote("Meeting Notes", "Discussed Q1 goals", "work,meetings");
```

#### `bool updateNote(const String& id, const String& title, const String& content, const String& tags = "")`
Update an existing note.

**Parameters:**
- `id`: Note ID (String)
- `title`: New title (String)
- `content`: New content (String)
- `tags`: New tags (String, optional)

**Returns:** `true` if successful, `false` otherwise

#### `bool deleteNote(const String& id)`
Delete a note.

**Parameters:**
- `id`: Note ID (String)

**Returns:** `true` if successful, `false` otherwise

#### `Note* getNote(const String& id)`
Get a specific note by ID.

**Parameters:**
- `id`: Note ID (String)

**Returns:** Pointer to Note object or `nullptr` if not found

#### `int getNoteCount()`
Get total number of notes.

**Returns:** Number of notes (int)

#### `Note* getAllNotes()`
Get all notes.

**Returns:** Pointer to array of Note objects

#### `Note* searchNotes(const String& query, int& count)`
Search notes by keyword.

**Parameters:**
- `query`: Search query (String)
- `count`: Reference to store result count

**Returns:** Pointer to array of matching Note objects

**Example:**
```cpp
int resultCount;
Note* results = noteManager.searchNotes("meeting", resultCount);
```

#### `bool saveNotes()`
Save notes to persistent storage.

**Returns:** `true` if successful, `false` otherwise

#### `bool loadNotes()`
Load notes from persistent storage.

**Returns:** `true` if successful, `false` otherwise

### Note Structure

```cpp
struct Note {
    String id;                  // Unique identifier
    String title;               // Note title
    String content;             // Note content
    unsigned long createdAt;    // Creation time
    unsigned long modifiedAt;   // Last modification time
    String tags;                // Comma-separated tags
};
```

---

## ReminderManager Class

Manages one-time and recurring reminders.

### Methods

#### `ReminderManager()`
Constructor. Initializes the reminder manager.

#### `bool addReminder(const String& title, const String& message, unsigned long triggerTime, bool recurring = false, unsigned long recurInterval = 0)`
Add a new reminder.

**Parameters:**
- `title`: Reminder title (String)
- `message`: Reminder message (String)
- `triggerTime`: Trigger time in milliseconds
- `recurring`: Whether reminder recurs (bool, optional)
- `recurInterval`: Recurrence interval in seconds (unsigned long, optional)

**Returns:** `true` if successful, `false` otherwise

**Example:**
```cpp
// One-time reminder in 1 hour
reminderManager.addReminder("Take medication", "Evening dose", millis() + 3600000);

// Recurring reminder every 24 hours
reminderManager.addReminder("Daily review", "Review tasks", millis() + 3600000, true, 86400);
```

#### `bool deleteReminder(const String& id)`
Delete a reminder.

**Parameters:**
- `id`: Reminder ID (String)

**Returns:** `true` if successful, `false` otherwise

#### `bool enableReminder(const String& id, bool enable)`
Enable or disable a reminder.

**Parameters:**
- `id`: Reminder ID (String)
- `enable`: Enable state (bool)

**Returns:** `true` if successful, `false` otherwise

#### `Reminder* getReminder(const String& id)`
Get a specific reminder by ID.

**Parameters:**
- `id`: Reminder ID (String)

**Returns:** Pointer to Reminder object or `nullptr` if not found

#### `int getReminderCount()`
Get total number of reminders.

**Returns:** Number of reminders (int)

#### `Reminder* getAllReminders()`
Get all reminders.

**Returns:** Pointer to array of Reminder objects

#### `bool saveReminders()`
Save reminders to persistent storage.

**Returns:** `true` if successful, `false` otherwise

#### `bool loadReminders()`
Load reminders from persistent storage.

**Returns:** `true` if successful, `false` otherwise

#### `void checkReminders(unsigned long currentTime)`
Check and trigger reminders.

**Parameters:**
- `currentTime`: Current time in milliseconds

### Reminder Structure

```cpp
struct Reminder {
    String id;                   // Unique identifier
    String title;                // Reminder title
    String message;              // Reminder message
    unsigned long triggerTime;   // Trigger time
    bool recurring;              // Recurring flag
    unsigned long recurInterval; // Recurrence interval (seconds)
    bool enabled;                // Enabled flag
    unsigned long createdAt;     // Creation time
};
```

---

## AudioHandler Class

Manages audio output and feedback.

### Methods

#### `AudioHandler()`
Constructor. Initializes the audio handler.

#### `bool init()`
Initialize the audio system.

**Returns:** `true` if successful, `false` otherwise

**Example:**
```cpp
AudioHandler audioHandler;
if (audioHandler.init()) {
    Serial.println("Audio ready");
}
```

#### `bool startRecording()`
Start audio recording (reserved for future use).

**Returns:** `true` if successful, `false` otherwise

#### `bool stopRecording()`
Stop audio recording (reserved for future use).

**Returns:** `true` if successful, `false` otherwise

#### `size_t readAudio(uint8_t* buffer, size_t length)`
Read audio data (reserved for future use).

**Parameters:**
- `buffer`: Buffer to store audio data
- `length`: Buffer length

**Returns:** Number of bytes read

#### `bool playTone(int frequency, int duration)`
Play a tone at specified frequency.

**Parameters:**
- `frequency`: Frequency in Hz (int)
- `duration`: Duration in milliseconds (int)

**Returns:** `true` if successful, `false` otherwise

**Example:**
```cpp
audioHandler.playTone(1000, 200); // 1kHz for 200ms
```

#### `void playNotification()`
Play notification sound (two-tone beep).

**Example:**
```cpp
audioHandler.playNotification();
```

#### `void playConfirmation()`
Play confirmation sound (ascending three-tone).

**Example:**
```cpp
audioHandler.playConfirmation();
```

#### `void playError()`
Play error sound (two low beeps).

**Example:**
```cpp
audioHandler.playError();
```

---

## Configuration Constants

Defined in `include/config.h`:

### WiFi Configuration
```cpp
#define WIFI_SSID "YourSSID"
#define WIFI_PASSWORD "YourPassword"
```

### Time Configuration
```cpp
#define NTP_SERVER "pool.ntp.org"
#define GMT_OFFSET_SEC 0
#define DAYLIGHT_OFFSET_SEC 0
```

### I2S Audio Configuration
```cpp
#define I2S_WS 15
#define I2S_SD 32
#define I2S_SCK 14
#define I2S_PORT I2S_NUM_0
#define I2S_SAMPLE_RATE 16000
#define I2S_SAMPLE_BITS 16
```

### Storage Limits
```cpp
#define MAX_TASKS 50
#define MAX_NOTES 100
#define MAX_REMINDERS 50
```

### File Paths
```cpp
#define TASK_FILE "/tasks.json"
#define NOTES_FILE "/notes.json"
#define REMINDERS_FILE "/reminders.json"
```
