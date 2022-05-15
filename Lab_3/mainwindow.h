#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "lessonsCSVReader.h"
#include "lessonsCSVwriter.h"

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void findLesson();
    void addLesson();
private slots:
    void on_chooseFile_clicked();

private:
    Ui::MainWindow *ui;

    lessonsCSVReader myCSV_fileRead;
    lessonsCSVWriter myCSV_fileWrite;
    void printLessonsRecords(vector<recordStruct> lessonRecords);
};
#endif // MAINWINDOW_H
