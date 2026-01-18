#ifndef NOTE_MANAGER_H
#define NOTE_MANAGER_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "config.h"

struct Note {
    String id;
    String title;
    String content;
    unsigned long createdAt;
    unsigned long modifiedAt;
    String tags;
};

class NoteManager {
private:
    Note notes[MAX_NOTES];
    int noteCount;
    String generateId();

public:
    NoteManager();
    bool addNote(const String& title, const String& content, const String& tags = "");
    bool updateNote(const String& id, const String& title, const String& content, const String& tags = "");
    bool deleteNote(const String& id);
    Note* getNote(const String& id);
    int getNoteCount();
    Note* getAllNotes();
    Note* searchNotes(const String& query, int& count);
    bool saveNotes();
    bool loadNotes();
};

#endif // NOTE_MANAGER_H
