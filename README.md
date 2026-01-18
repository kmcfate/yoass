# Yoass - Your Only Assistant

An ESP32-based AI voice assistant designed specifically to help people with ADHD manage their daily lives. Yoass provides easy task tracking, scheduling, reminders, note-taking, and other essential features to make life more manageable and enjoyable.

## Features

### Core Functionality
- **Task Management**: Create, track, and manage tasks with priorities and due dates
- **Note Taking**: Quick and easy note-taking with tagging and search capabilities
- **Reminders**: Set one-time or recurring reminders to stay on track
- **Voice Feedback**: Audio confirmation and notification system
- **Persistent Storage**: All data saved to flash memory (SPIFFS)
- **WiFi Connectivity**: Time synchronization and future cloud integration
- **Real-time Monitoring**: Track tasks, notes, and reminders in real-time

### ADHD-Focused Features
- **Priority Levels**: Four priority levels (Low, Medium, High, Urgent) to help focus on what matters
- **Audio Feedback**: Immediate audio confirmation for actions to provide sensory reinforcement
- **Simple Interface**: Clean serial interface with numbered commands for easy navigation
- **Quick Capture**: Fast task and note creation to capture thoughts before they're forgotten
- **Smart Reminders**: Flexible reminder system with recurring options for routine tasks
- **Status Tracking**: Visual task status tracking (TODO, IN PROGRESS, COMPLETED, CANCELLED)

## Hardware Requirements

### Required Components
- ESP32 Development Board (ESP32-DevKitC or similar)
- I2S Audio Module (e.g., MAX98357A, UDA1334A)
- Speaker (4-8 ohm, 3W recommended)
- Micro USB cable for programming and power
- WiFi network for time synchronization

### Optional Components
- External button for voice activation
- LED indicators for visual feedback
- Microphone module for voice input (future feature)

### Pin Connections

Default pin configuration (can be changed in `include/config.h`):

```
I2S Audio:
- WS (Word Select/LRCLK): GPIO 15
- SD (Serial Data/DIN): GPIO 32
- SCK (Serial Clock/BCLK): GPIO 14

Controls:
- Button: GPIO 0 (Boot button)
- LED: GPIO 2 (Built-in LED)
```

## Software Requirements

- [PlatformIO IDE](https://platformio.org/) or Arduino IDE with ESP32 support
- USB drivers for your ESP32 board

## Installation

### 1. Clone the Repository

```bash
git clone https://github.com/kmcfate/yoass.git
cd yoass
```

### 2. Configure WiFi Settings

Edit `include/config.h` and update your WiFi credentials:

```cpp
#define WIFI_SSID "YourWiFiNetworkName"
#define WIFI_PASSWORD "YourWiFiPassword"
```

Also configure your timezone:

```cpp
#define GMT_OFFSET_SEC -18000  // For EST (adjust for your timezone)
#define DAYLIGHT_OFFSET_SEC 3600  // For daylight saving time
```

### 3. Install Dependencies

If using PlatformIO (recommended):

```bash
pio lib install
```

The following libraries will be automatically installed:
- ESP32-audioI2S
- ArduinoJson
- WiFiManager
- NTPClient
- Time

### 4. Upload to ESP32

Using PlatformIO:

```bash
pio run --target upload
```

Using Arduino IDE:
1. Open `src/main.cpp`
2. Select your ESP32 board from Tools > Board
3. Select the correct COM port
4. Click Upload

### 5. Monitor Serial Output

```bash
pio device monitor
```

Or use the Serial Monitor in Arduino IDE (115200 baud).

## Usage

### First Time Setup

1. Power on your ESP32
2. Wait for WiFi connection and time synchronization
3. The main menu will appear in the serial monitor

### Main Menu Commands

```
1. Add Task       - Create a new task with priority
2. List Tasks     - View all tasks with status
3. Complete Task  - Mark a task as completed
4. Add Note       - Create a quick note
5. List Notes     - View all saved notes
6. Search Notes   - Search notes by keyword
7. Add Reminder   - Set a timed reminder
8. List Reminders - View active reminders
9. Show Stats     - Display usage statistics
0. Help           - Show this menu
```

### Examples

#### Adding a Task

```
Command: 1
Title: Buy groceries
Description: Milk, eggs, bread, coffee
Priority: 2  (High)
```

#### Creating a Note

```
Command: 4
Title: Meeting notes
Content: Discussed project timeline and deliverables
Tags: work, meetings, important
```

#### Setting a Reminder

```
Command: 7
Title: Take medication
Message: Don't forget your evening medication
Trigger in seconds: 3600  (1 hour from now)
```

## Project Structure

```
yoass/
├── include/
│   ├── config.h              # Main configuration file
│   ├── task_manager.h        # Task management interface
│   ├── note_manager.h        # Note-taking interface
│   ├── reminder_manager.h    # Reminder system interface
│   └── audio_handler.h       # Audio output interface
├── src/
│   ├── main.cpp              # Main application entry point
│   ├── task_manager.cpp      # Task management implementation
│   ├── note_manager.cpp      # Note-taking implementation
│   ├── reminder_manager.cpp  # Reminder system implementation
│   └── audio_handler.cpp     # Audio output implementation
├── lib/                      # Custom libraries (if any)
├── test/                     # Unit tests
├── platformio.ini            # PlatformIO configuration
├── config.example            # Example configuration
└── README.md                 # This file
```

## Customization

### Adjusting Storage Limits

Edit `include/config.h`:

```cpp
#define MAX_TASKS 50      // Maximum number of tasks
#define MAX_NOTES 100     // Maximum number of notes
#define MAX_REMINDERS 50  // Maximum number of reminders
```

### Changing Audio Pins

Edit `include/config.h`:

```cpp
#define I2S_WS 15   // Word Select pin
#define I2S_SD 32   // Serial Data pin
#define I2S_SCK 14  // Serial Clock pin
```

### Modifying Audio Feedback

Edit `src/audio_handler.cpp` to customize tones and frequencies.

## Future Enhancements

- [ ] Voice recognition for hands-free operation
- [ ] Web interface for remote management
- [ ] Mobile app companion
- [ ] Cloud synchronization
- [ ] Habit tracking
- [ ] Focus timer (Pomodoro technique)
- [ ] Medication tracking
- [ ] Calendar integration
- [ ] Natural language processing for task creation
- [ ] Machine learning for task prioritization suggestions

## Troubleshooting

### WiFi Connection Issues

- Verify SSID and password in `config.h`
- Ensure WiFi network is 2.4GHz (ESP32 doesn't support 5GHz)
- Check if your network has MAC address filtering

### Audio Issues

- Verify I2S module connections
- Check power supply (some modules need 5V)
- Test with different pins if default pins conflict with your board
- Ensure speaker impedance matches module specifications

### Storage Issues

- If SPIFFS fails to mount, try reformatting: `SPIFFS.format()`
- Reduce MAX_TASKS, MAX_NOTES, or MAX_REMINDERS if memory is limited
- Check available SPIFFS space in partition table

### Serial Monitor Shows Garbage

- Verify baud rate is set to 115200
- Try pressing the ESP32 reset button
- Check USB cable and drivers

## Contributing

Contributions are welcome! Please feel free to submit issues and pull requests.

### Development Setup

1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Test thoroughly on hardware
5. Submit a pull request

## License

See the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Built with the ESP32 Arduino framework
- Uses ArduinoJson for efficient data serialization
- Inspired by the needs of the ADHD community

## Support

For questions, issues, or suggestions:
- Open an issue on GitHub
- Check existing issues for solutions
- Review the troubleshooting section

## Why Yoass?

ADHD can make everyday tasks feel overwhelming. Yoass is designed to be:
- **Simple**: No complex menus or confusing interfaces
- **Quick**: Capture thoughts and tasks instantly
- **Reliable**: Always available, no internet required for core features
- **Helpful**: Audio feedback provides immediate confirmation
- **Flexible**: Adapt the system to your needs

Stay organized, stay focused, and make your life easier with Yoass - Your Only Assistant!
