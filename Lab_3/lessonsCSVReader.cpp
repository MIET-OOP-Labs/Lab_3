#include "lessonsCSVReader.h"

lessonsCSVReader::lessonsCSVReader() {
}

vector<string> lessonsCSVReader::split(const string& str, char delim) {
    vector<string> tokens;
    if (!str.empty()) {
        size_t start = 0;
        size_t end = 0;
        do {
            end = str.find(delim, start);
            tokens.push_back(str.substr(start, (end - start)));
            start = end + 1;
        } while (end != string::npos);
    }

    return tokens;
}

lessonTypesEnum lessonsCSVReader::getLesson(string lessonStr){
    lessonTypesEnum lesson = none;
    if (!lessonStr.compare("Lection")) {
        lesson = Lection;
    } else if (!lessonStr.compare("Practice")) {
        lesson = Practice;
    } else if (!lessonStr.compare("Lab")) {
        lesson = Lab;
    } else if (!lessonStr.compare("Exam")) {
        lesson = Exam;
    }
    return lesson;
}

 //comparison function object for sorting records by classroom

vector<recordStruct> lessonsCSVReader::filterRecords(recordStruct filter){   //filter all records by filter struct. It will be also checked, if some parametr in filter isn't used
    vector<recordStruct> returnVec;
    for (recordStruct record : lessonsRecords) {
        bool subjectEqual = (!record.subjectName.compare(filter.subjectName)) || (!filter.subjectName.compare(" ")); //check if subjects are equal or subject name in filter is empty, which means this parametr isn't used
        bool lessonTypeEqual = (record.lessonType == filter.lessonType) || (!filter.lessonType);                //check if lesson types are equal or lesson type in filter is none (none in lessonTypesEnum = 0)
        bool classroomEqual = (record.classroom == filter.classroom) || (!filter.classroom);                    //check if classrooms are equal or classroom in filter is null
        if (subjectEqual && lessonTypeEqual && classroomEqual) {
            returnVec.push_back(record);
        }
    }
    return returnVec;
}

bool lessonsCSVReader::openFile(){
    file.open(filePath);
    if (!file.is_open()) {
        fileOpened = false;
        return fileOpened;
    }
    fileOpened = true;
    return fileOpened;
}


bool lessonsCSVReader::getRecord(vector<string> str, recordStruct *record){
    if (str.size() != 4) {
        return false;
    }
    record->num = stoi(str[0]);
    record->subjectName = str[1];
    record->lessonType = getLesson(str[2]);                 //function for filling record struct from string-line, taken from .csv file
    record->classroom = stoi(str[3]);
    return true;
}

string lessonsCSVReader::fillLessonsVector(){
    lessonsRecords.clear();
    if(!fileOpened){
        return "";
    }
    vector<string> row;                         //vector that stores splitted line from .csv file
    string line;
    while(getline(file, line)) {
        row.clear();
        row = split(line, ';');
        recordStruct currRecord;
        if (!getRecord(row, &currRecord)) {
            return line;
        }
        lessonsRecords.push_back(currRecord);
    }
    file.close();
    return "";
}

vector<recordStruct> lessonsCSVReader::getLessonsRecords() {
    return lessonsRecords;
}

void lessonsCSVReader::setNewLessonRecord(recordStruct newRecord) {
    lessonsRecords.push_back(newRecord);
}

//vector<recordStruct> lessonsCSVReader::sortLessonsVector() {
//    sort (lessonsRecords.begin(), lessonsRecords.end(), sortFunc);
//    return lessonsRecords;
//}
