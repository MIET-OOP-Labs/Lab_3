#ifndef LESSONSCSVREADER_H
#define LESSONSCSVREADER_H

#include <vector>
#include <fstream>
#include "lessonsCSV.h"

class lessonsCSVReader {
    vector<recordStruct> lessonsRecords;    //vector that stores all lesson records
    static bool sortFunc (recordStruct i,recordStruct j) { return (i.classroom < j.classroom);}
    bool getRecord(vector<string> str, recordStruct *record);
    ifstream file;
    bool fileOpened = false;

public:
    lessonsCSVReader();
    string filePath;
    vector<string> split(const string& str, char delim);
    vector<recordStruct> filterRecords(recordStruct filter);
    bool openFile();
    string fillLessonsVector();
    //string getLesson(lessonTypesEnum lesson);
    lessonTypesEnum getLesson(string lessonStr);
    vector<recordStruct> getLessonsRecords();
    void setNewLessonRecord(recordStruct newRecord);
};

#endif // LESSONSCSVREADER_H
