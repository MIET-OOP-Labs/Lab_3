#ifndef LESSONSCSVWRITER_H
#define LESSONSCSVWRITER_H

#include "lessonsCSV.h"
#include <fstream>

class lessonsCSVWriter {
public:
    lessonsCSVWriter();
    bool writeNewRecordInFile(recordStruct newRecord, string filePath);
};

#endif // LESSONSCSVWRITER_H
