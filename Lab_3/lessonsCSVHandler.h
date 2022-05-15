#ifndef LESSONSCSVHANDLER_H
#define LESSONSCSVHANDLER_H

#include "lessonsCSVReader.h"
#include "lessonsCSVwriter.h"


typedef enum lessonTypesEnum {none, Lection, Practice, Lab, Exam};  //enumeration of types of lessons

typedef struct {
    int num;
    string subjectName;
    lessonTypesEnum lessonType; //structure that stores info about each record of lessons
    int classroom;
} recordStruct;

class lessonsCVSHandler: protected fileCSVReader, protected fileCSVWriter {
public:
    lessonsCVSHandler();
};

#endif // LESSONSCSVHANDLER_H
