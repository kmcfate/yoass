#include "note_manager.h"
#include <SPIFFS.h>

NoteManager::NoteManager() : noteCount(0) {
    for (int i = 0; i < MAX_NOTES; i++) {
        notes[i].id = "";
    }
}

String NoteManager::generateId() {
    return String(millis()) + String(random(1000, 9999));
}

bool NoteManager::addNote(const String& title, const String& content, const String& tags) {
    if (noteCount >= MAX_NOTES) {
        return false;
    }
    
    Note newNote;
    newNote.id = generateId();
    newNote.title = title;
    newNote.content = content;
    newNote.tags = tags;
    newNote.createdAt = millis();
    newNote.modifiedAt = millis();
    
    notes[noteCount++] = newNote;
    return saveNotes();
}

bool NoteManager::updateNote(const String& id, const String& title, const String& content, const String& tags) {
    for (int i = 0; i < noteCount; i++) {
        if (notes[i].id == id) {
            notes[i].title = title;
            notes[i].content = content;
            notes[i].tags = tags;
            notes[i].modifiedAt = millis();
            return saveNotes();
        }
    }
    return false;
}

bool NoteManager::deleteNote(const String& id) {
    for (int i = 0; i < noteCount; i++) {
        if (notes[i].id == id) {
            // Shift notes down
            for (int j = i; j < noteCount - 1; j++) {
                notes[j] = notes[j + 1];
            }
            noteCount--;
            notes[noteCount].id = "";
            return saveNotes();
        }
    }
    return false;
}

Note* NoteManager::getNote(const String& id) {
    for (int i = 0; i < noteCount; i++) {
        if (notes[i].id == id) {
            return &notes[i];
        }
    }
    return nullptr;
}

int NoteManager::getNoteCount() {
    return noteCount;
}

Note* NoteManager::getAllNotes() {
    return notes;
}

Note* NoteManager::searchNotes(const String& query, int& count) {
    count = 0;
    String queryLower = query;
    queryLower.toLowerCase();
    
    for (int i = 0; i < noteCount; i++) {
        String titleLower = notes[i].title;
        titleLower.toLowerCase();
        String contentLower = notes[i].content;
        contentLower.toLowerCase();
        String tagsLower = notes[i].tags;
        tagsLower.toLowerCase();
        
        if (titleLower.indexOf(queryLower) >= 0 || 
            contentLower.indexOf(queryLower) >= 0 || 
            tagsLower.indexOf(queryLower) >= 0) {
            searchResults[count++] = notes[i];
        }
    }
    return searchResults;
}

bool NoteManager::saveNotes() {
    if (!SPIFFS.begin(true)) {
        return false;
    }
    
    File file = SPIFFS.open(NOTES_FILE, FILE_WRITE);
    if (!file) {
        return false;
    }
    
    DynamicJsonDocument doc(16384);
    JsonArray notesArray = doc.createNestedArray("notes");
    
    for (int i = 0; i < noteCount; i++) {
        JsonObject noteObj = notesArray.createNestedObject();
        noteObj["id"] = notes[i].id;
        noteObj["title"] = notes[i].title;
        noteObj["content"] = notes[i].content;
        noteObj["tags"] = notes[i].tags;
        noteObj["createdAt"] = notes[i].createdAt;
        noteObj["modifiedAt"] = notes[i].modifiedAt;
    }
    
    serializeJson(doc, file);
    file.close();
    return true;
}

bool NoteManager::loadNotes() {
    if (!SPIFFS.begin(true)) {
        return false;
    }
    
    if (!SPIFFS.exists(NOTES_FILE)) {
        return true; // No file yet, that's ok
    }
    
    File file = SPIFFS.open(NOTES_FILE, FILE_READ);
    if (!file) {
        return false;
    }
    
    DynamicJsonDocument doc(16384);
    DeserializationError error = deserializeJson(doc, file);
    file.close();
    
    if (error) {
        return false;
    }
    
    JsonArray notesArray = doc["notes"];
    noteCount = 0;
    
    for (JsonObject noteObj : notesArray) {
        if (noteCount >= MAX_NOTES) break;
        
        notes[noteCount].id = noteObj["id"].as<String>();
        notes[noteCount].title = noteObj["title"].as<String>();
        notes[noteCount].content = noteObj["content"].as<String>();
        notes[noteCount].tags = noteObj["tags"].as<String>();
        notes[noteCount].createdAt = noteObj["createdAt"].as<unsigned long>();
        notes[noteCount].modifiedAt = noteObj["modifiedAt"].as<unsigned long>();
        noteCount++;
    }
    
    return true;
}
