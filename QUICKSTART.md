# Quick Start Guide

Get your Yoass assistant up and running in 15 minutes!

## Prerequisites

✅ ESP32 development board  
✅ I2S audio module (MAX98357A or similar)  
✅ Speaker (4-8Ω, 3W)  
✅ Micro USB cable  
✅ PlatformIO IDE or Arduino IDE  

## 5-Step Setup

### Step 1: Hardware Assembly (5 minutes)

Connect your components:

```
ESP32 GPIO 15  →  I2S Module LRC (Word Select)
ESP32 GPIO 32  →  I2S Module DIN (Data In)
ESP32 GPIO 14  →  I2S Module BCLK (Bit Clock)
ESP32 3.3V     →  I2S Module VIN
ESP32 GND      →  I2S Module GND
                  Speaker → I2S Module terminals
```

See [HARDWARE.md](HARDWARE.md) for detailed wiring diagrams.

### Step 2: Install Software (3 minutes)

**Option A: PlatformIO (Recommended)**
1. Install [VS Code](https://code.visualstudio.com/)
2. Install PlatformIO extension
3. Done!

**Option B: Arduino IDE**
1. Install [Arduino IDE](https://www.arduino.cc/en/software)
2. Add ESP32 board support:
   - File → Preferences
   - Add to Additional Board URLs: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Tools → Board → Boards Manager
   - Search "ESP32" and install

### Step 3: Configure WiFi (2 minutes)

Edit `include/config.h`:

```cpp
#define WIFI_SSID "YourWiFiName"
#define WIFI_PASSWORD "YourPassword"

// Optional: Set your timezone
#define GMT_OFFSET_SEC -18000  // EST = -18000, PST = -28800, etc.
```

### Step 4: Upload Firmware (3 minutes)

**PlatformIO:**
1. Open project folder in VS Code
2. Click "Upload" button (→) in bottom toolbar
3. Wait for upload to complete

**Arduino IDE:**
1. Open `src/main.cpp`
2. Tools → Board → ESP32 Dev Module
3. Tools → Port → Select your COM port
4. Click Upload button

### Step 5: Test (2 minutes)

1. Open Serial Monitor (115200 baud)
2. Press ESP32 reset button
3. Watch for:
   - "YOASS - Your Only Assistant"
   - WiFi connection message
   - Confirmation beep from speaker
   - Main menu

## Your First Tasks

### Add a Task
```
Command: 1
Title: Test Yoass
Description: My first task
Priority: 2
```

### Add a Note
```
Command: 4
Title: Shopping list
Content: Milk, bread, coffee
Tags: shopping
```

### Set a Reminder
```
Command: 7
Title: Test reminder
Message: This is a test
Trigger in seconds: 60
```

Wait 60 seconds and watch for the reminder!

## Troubleshooting

### "WiFi connection failed"
- Check SSID and password
- Ensure 2.4GHz network (not 5GHz)
- Move closer to router

### "No sound from speaker"
- Check all wire connections
- Verify speaker polarity
- Test with different speaker

### "Upload failed"
- Check USB cable connection
- Try different USB port
- Press and hold BOOT button during upload

### "Serial Monitor shows gibberish"
- Set baud rate to 115200
- Press ESP32 reset button
- Check USB drivers

## Next Steps

📖 Read the full [README.md](README.md) for detailed features  
🔧 Check [HARDWARE.md](HARDWARE.md) for advanced wiring  
💻 Review [API.md](API.md) for programming reference  
🤝 See [CONTRIBUTING.md](CONTRIBUTING.md) to contribute  

## Quick Reference

### Serial Commands
- `1` - Add Task
- `2` - List Tasks  
- `3` - Complete Task
- `4` - Add Note
- `5` - List Notes
- `6` - Search Notes
- `7` - Add Reminder
- `8` - List Reminders
- `9` - Show Stats
- `0` - Help

### Audio Feedback
- 🎵 Three ascending beeps = Confirmation
- 🎵 Two quick beeps = Notification
- 🎵 Two low beeps = Error

## Need Help?

- 📧 Open an issue on GitHub
- 📖 Check the troubleshooting section
- 💬 Ask in discussions

## Success! 🎉

You now have a working ADHD assistant!

Start by adding your daily tasks and setting reminders for important activities. The more you use it, the more helpful it becomes.

**Pro Tips for ADHD:**
- Add tasks immediately when you think of them
- Use HIGH/URGENT priorities for time-sensitive items
- Set reminders for medication and routines
- Tag notes for easy searching later
- Check your tasks list every morning

Happy organizing! 📝✨
