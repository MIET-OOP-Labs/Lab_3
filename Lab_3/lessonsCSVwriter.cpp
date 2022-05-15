#include "lessonsCSVwriter.h"

lessonsCSVWriter::lessonsCSVWriter() {
}

bool lessonsCSVWriter::writeNewRecordInFile(recordStruct newRecord, string filePath){
    ofstream writeFile;

     writeFile.open(filePath, fstream::app);
    if (!writeFile.is_open()) {
        return false;
    }

    char buff[64] = "";
    sprintf(buff, "%d;%s;%s;%d", newRecord.num, newRecord.subjectName.c_str(), ToString(newRecord.lessonType).c_str(), newRecord.classroom);
    string foo = string(buff);
    writeFile  << endl << foo << endl;       // Write to the file

    writeFile.close();
    return true;
}
