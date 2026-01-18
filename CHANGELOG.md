# Changelog

All notable changes to Yoass will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [1.0.0] - 2026-01-18

### Added

#### Core Features
- Complete ESP32 project structure with PlatformIO support
- Task management system with priorities and status tracking
- Note-taking functionality with tagging and search
- Reminder system with one-time and recurring options
- Audio feedback system using I2S interface
- Persistent storage using SPIFFS filesystem
- WiFi connectivity with automatic connection
- NTP time synchronization
- Serial command interface

#### Task Management
- Create tasks with title, description, and priority levels (Low, Medium, High, Urgent)
- Task status tracking (TODO, In Progress, Completed, Cancelled)
- Due date support
- Task reminders
- Task completion tracking with timestamps
- Filter tasks by status and priority
- Persistent storage of tasks

#### Note Taking
- Quick note creation with title and content
- Tag support for organization
- Search functionality across title, content, and tags
- Update and delete notes
- Persistent storage of notes
- Timestamp tracking (created and modified)

#### Reminders
- Create one-time reminders
- Create recurring reminders with custom intervals
- Enable/disable reminders
- Automatic triggering based on system time
- Persistent storage of reminders

#### Audio System
- I2S audio output support
- Configurable audio pins
- Notification sound (two-tone)
- Confirmation sound (three-tone ascending)
- Error sound (two low tones)
- Custom tone generation

#### Hardware Support
- ESP32 DevKit support
- I2S audio module integration (MAX98357A, UDA1334A)
- Button input handling with debouncing
- LED status indicator
- Configurable GPIO pins

#### Documentation
- Comprehensive README with setup instructions
- Hardware setup guide with wiring diagrams
- API reference documentation
- Contributing guidelines
- Configuration examples
- Troubleshooting guide

#### Configuration
- WiFi credentials configuration
- Timezone configuration
- Hardware pin configuration
- Storage limits configuration
- Example configuration file

### Technical Details
- Arduino framework for ESP32
- JSON-based data serialization
- SPIFFS filesystem for persistent storage
- I2S driver for audio output
- NTP client for time synchronization
- WiFi manager integration ready

### Known Limitations
- Maximum 50 tasks (configurable)
- Maximum 100 notes (configurable)
- Maximum 50 reminders (configurable)
- No voice input yet (planned for future)
- No web interface yet (planned for future)
- Serial interface only (no display support yet)

## [Unreleased]

### Planned Features
- Voice recognition for hands-free operation
- Web interface for remote access
- Mobile app companion
- Cloud synchronization
- Habit tracking
- Focus timer (Pomodoro technique)
- Medication tracking
- Calendar integration
- Natural language processing
- ML-based task prioritization

### Under Consideration
- OLED display support
- Battery operation optimization
- Bluetooth connectivity
- Smart home integration
- Multiple user profiles
- Data export/import
- Backup and restore functionality

---

## Version History

### Version Numbering

- **Major version** (X.0.0): Significant changes, possible breaking changes
- **Minor version** (0.X.0): New features, backward compatible
- **Patch version** (0.0.X): Bug fixes, minor improvements

### Support

- Current stable version: 1.0.0
- Minimum ESP32 Arduino core: 2.0.0
- Minimum PlatformIO: 6.0.0

---

[1.0.0]: https://github.com/kmcfate/yoass/releases/tag/v1.0.0
[Unreleased]: https://github.com/kmcfate/yoass/compare/v1.0.0...HEAD
