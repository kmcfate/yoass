# Contributing to Yoass

Thank you for your interest in contributing to Yoass! This document provides guidelines and instructions for contributing.

## Code of Conduct

- Be respectful and inclusive
- Focus on constructive feedback
- Help create a welcoming environment for all contributors
- Remember that this project aims to help people with ADHD

## How to Contribute

### Reporting Bugs

1. Check if the bug has already been reported in Issues
2. Create a new issue with:
   - Clear, descriptive title
   - Steps to reproduce
   - Expected vs actual behavior
   - Hardware setup details
   - Software versions
   - Serial monitor output (if applicable)

### Suggesting Features

1. Check existing issues for similar suggestions
2. Create a new issue with:
   - Clear description of the feature
   - Use case and benefits
   - Any implementation ideas
   - How it helps people with ADHD

### Pull Requests

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Make your changes
4. Test thoroughly on actual ESP32 hardware
5. Commit with clear messages (`git commit -m 'Add amazing feature'`)
6. Push to your branch (`git push origin feature/amazing-feature`)
7. Open a Pull Request

## Development Guidelines

### Code Style

- Use consistent indentation (4 spaces)
- Follow existing code structure
- Add comments for complex logic
- Use meaningful variable and function names
- Keep functions focused and concise

### Example

```cpp
// Good
bool TaskManager::addTask(const String& title, const String& description, TaskPriority priority) {
    if (taskCount >= MAX_TASKS) {
        return false;
    }
    // Implementation...
}

// Avoid
bool TaskManager::a(String t, String d, int p) {
    // Implementation...
}
```

### Hardware Testing

All changes that affect hardware functionality must be tested on:
- ESP32 DevKit (minimum)
- With I2S audio module
- With WiFi connection

### Documentation

- Update README.md for user-facing changes
- Update API.md for API changes
- Add comments for complex algorithms
- Update HARDWARE.md for hardware changes
- Include examples in documentation

### Commit Messages

Use clear, descriptive commit messages:

```
Good:
- Add recurring reminder functionality
- Fix task deletion bug in TaskManager
- Update WiFi connection error handling
- Improve audio feedback for task completion

Avoid:
- Fixed stuff
- Update
- Changes
- WIP
```

## Testing Checklist

Before submitting a PR, verify:

- [ ] Code compiles without errors
- [ ] Code compiles without warnings
- [ ] Tested on physical ESP32 hardware
- [ ] All existing features still work
- [ ] New features work as expected
- [ ] Documentation updated
- [ ] No memory leaks
- [ ] Serial output is clean and informative
- [ ] Audio feedback works correctly
- [ ] WiFi connection stable
- [ ] Data persists across reboots

## Areas for Contribution

### High Priority
- Voice recognition integration
- Web interface development
- Mobile app companion
- Improved error handling
- Performance optimization

### Medium Priority
- Additional audio feedback options
- More reminder types
- Task scheduling algorithms
- Better WiFi management
- Power optimization

### Low Priority
- UI improvements
- Code refactoring
- Documentation enhancements
- Example projects
- Tutorial videos

## ADHD-Focused Design Principles

When contributing, keep these principles in mind:

1. **Simplicity**: Keep interfaces simple and intuitive
2. **Speed**: Enable quick capture of thoughts and tasks
3. **Feedback**: Provide immediate sensory feedback
4. **Flexibility**: Allow customization for different needs
5. **Reliability**: Ensure consistent, predictable behavior
6. **Forgiveness**: Make it easy to undo or correct mistakes

## Questions?

- Open an issue for questions
- Tag with "question" label
- Be specific about what you need help with

## License

By contributing, you agree that your contributions will be licensed under the same license as the project.

## Recognition

All contributors will be acknowledged in the project documentation.

Thank you for helping make Yoass better! 🎉
