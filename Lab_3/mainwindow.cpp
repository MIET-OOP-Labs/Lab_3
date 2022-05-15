#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::findLesson() {
    QString logStr = "You entered: ";
    QString userRequest = ui->editSearch->text();
    ui->textOut->append(logStr.append(userRequest) + "\n");

    recordStruct filter;
    char subjectName_c[16];
    char lessonType_c[16];
    char *userRequest_c = new char[userRequest.length() + 1];
    strcpy(userRequest_c, userRequest.toStdString().c_str());
    sscanf(userRequest_c, "%[^;];%[^;];%d", subjectName_c, lessonType_c, &filter.classroom);
    delete[] userRequest_c;
    filter.lessonType = myCSV_fileRead.getLesson(lessonType_c);
    filter.subjectName = subjectName_c;

    printLessonsRecords(myCSV_fileRead.filterRecords(filter));
}

void MainWindow::printLessonsRecords(vector<recordStruct> lessonRecords){
    for (recordStruct record : lessonRecords) {            //function for printing all records in recordStruct vector
        QString outStr;
        outStr.sprintf("%-2d %-15s %-10s %-5d", record.num, record.subjectName.c_str(), ToString(record.lessonType).c_str(), record.classroom);
        ui->textOut->append(outStr);
    }
}

void MainWindow::on_chooseFile_clicked() {
    myCSV_fileRead.filePath = QFileDialog::getOpenFileName(this, "Open a .csv file", QDir::currentPath()).toStdString();
    if (!myCSV_fileRead.openFile()){
        QMessageBox::information(this,"Failed to open file ",QString::fromStdString(myCSV_fileRead.filePath));
        return;
    }
    QMessageBox::information(this,"Opened file ", QString::fromStdString(myCSV_fileRead.filePath));
    string fillReturnVal = myCSV_fileRead.fillLessonsVector();
    if (fillReturnVal.length()){
        fillReturnVal.insert(0, "Error in line");
        ui->textOut->append(QString::fromStdString(fillReturnVal));
        return;
    }

    printLessonsRecords(myCSV_fileRead.getLessonsRecords());
}

void MainWindow::addLesson() {
    recordStruct newRecord;
    newRecord.subjectName = ui->lineSubject->text().toStdString();
    newRecord.lessonType = static_cast<lessonTypesEnum>(ui->comboType->currentIndex() + 1);
    newRecord.classroom = ui->lineClassroom->text().toInt();
    newRecord.num = myCSV_fileRead.getLessonsRecords()[myCSV_fileRead.getLessonsRecords().size() - 1].num + 1;

    myCSV_fileRead.setNewLessonRecord(newRecord);
    if(!myCSV_fileWrite.writeNewRecordInFile(newRecord, myCSV_fileRead.filePath)){
        ui->textOut->append("Failed to open file");
        return;
    }
    QString outStr;
    outStr.sprintf("Added new record: %-2d %-15s %-10s %-5d\n", newRecord.num, newRecord.subjectName.c_str(), ToString(newRecord.lessonType).c_str(), newRecord.classroom);
    ui->textOut->append(outStr);
}
