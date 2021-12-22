#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include<vector>
#include <stack>
#include<string>
using namespace std;

#include <QFileDialog> //Provide a header for the Q-file Dialog
#include <QMessageBox>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QFile>
#include <QPalette>
#include<QVector>
//include format ,comp , tree, error_handle
#include <format.h>
#include<comp.h>
#include<tree.h>
#include<error_handle.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern vector<string> file_contents; // the is an extern variable used in all .cpp files


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:



    void on_pushButton_clicked();

    void on_actionOpen_triggered();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
