#ifndef LESSONSCSV_H
#define LESSONSCSV_H

#include <string>

using namespace std;

typedef enum lessonTypesEnum {none, Lection, Practice, Lab, Exam};  //enumeration of types of lessons

typedef struct {
    int num;
    string subjectName;
    lessonTypesEnum lessonType; //structure that stores info about each record of lessons
    int classroom;
} recordStruct;

inline string ToString(lessonTypesEnum lesson){       //functions to convert enum type of lessons to string and vice-versa
    switch (lesson) {
    case Lection:   return "Lection";
    case Practice:   return "Practice";
    case Lab:   return "Lab";
    case Exam:   return "Exam";
    default: return "None";
    }
}

#endif // LESSONSCSV_H
