#include "mainwindow.h"
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
#include <QPalette>
#include<QVector>
#include<QTextEdit>
/*-------------------------------------- GLOBAL VARIABLES--------------------------------------*/
QString loaded_text,s;
vector<string> file_contents; // the is an extern variable used in all .cpp files
string error,detection_out,var_detection,in_s="";
vector<string> line3;
unsigned char zk;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //make the the outputText ReadOnly
    ui->outputText->setReadOnly(true);
    ui->inputText->setReadOnly(true);
    setFixedSize(this->geometry().width(),this->geometry().height());
    QCoreApplication::setApplicationName("your title");
    setWindowTitle("XML_EDITOR");

}

MainWindow::~MainWindow()
{
    delete ui;
}


/*-------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------OPEN BUTTON--------------------------------------------------*/
void MainWindow::on_actionOpen_triggered()
{   zk=1;
    ui->label_3->setVisible(false);
    QString select ="All files(*.*);;XML files(*.xml)";
    QString myfile =QFileDialog::getOpenFileName(this,"Select an XML file","Desktop:\\",select); //create an object
    QFile file(myfile);
    /*display the File on TextEditor
           constraint: if the file is not readonly, or a file containing text : display warrning message*/
    // if(!file.open(QFile::NotOpen)){}
    if(!file.open(QFile:: ReadOnly | QFile::Text )){
        QMessageBox::warning(this,"Warning","Could not Load file or\n Wrong format");
        ui->outputText->clear();
        ui->label_3->setVisible(true);
        zk=0;
    }
    QTextStream in(&file);
    loaded_text= in.readAll();
    //now display it on the pre-made textEditor
    ui->inputText->setPlainText(loaded_text);



}
/*-------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------FORMAT BUTTON-------------------------------------------------*/
void MainWindow::on_pushButton_clicked()
{   if(zk==1){
    int data_start=0,closend=0,end=0,temp=0;
    QTextStream stream(&loaded_text);
    //Must get input from file:

    while (stream.readLineInto(&s)){
        string line=s.toStdString();
        //check if line is empty or all white spaces
        //check if line is empty or all white spaces
        if(line.find_first_not_of(' ') != std::string::npos){
            // if not empty line, check for concatenation of tags and separate them making each in a new line
            data_start=get_start(&line);

            if(line.find("<",data_start) != std::string::npos){

                // there are more open tags on the same line
                while(line.find("<",data_start) != std::string::npos ){
                    // signifies where the first bracket stops
                    closend=line.find_first_of(">",data_start);
                    //get the closing bracket of that open tag and push it in a new line
                    //check if there is a closing tag
                    temp=line.find_first_of("<",closend)+1;
                    if(line.find("</",data_start)!=std::string::npos && line[temp]=='/' ){

                        end=line.find_first_of(">",temp);
                        file_contents.push_back(line.substr(data_start,end+1));
                    }
                    else{end=line.find_first_of(">",data_start+1);
                        file_contents.push_back(line.substr(data_start,end-data_start+1));}

                    data_start=end+1;

                }
            }

            else{file_contents.push_back(line);}
        }
    }
    format();
    QFile file("OUTPUT_FILES/format_output.xml");
    file.open(QFile::ReadOnly | QFile::Text);
    ui->outputText->setPlainText(file.readAll());
    //clear the vector for the next cycle
    file_contents.clear();
    file.close();
}
    else {QMessageBox::warning(this,"Crash Alert","Please load a sample first to format");}

}
/*-------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------COMPRESS BUTTON-------------------------------------------------*/

void MainWindow::on_pushButton_4_clicked()
{   //Must get input from file:
    if(zk==1){
    //clear the output window
        ui->outputText->clear();

        QTextStream stream(&loaded_text);
        while (stream.readLineInto(&s)){
        in_s.append(s.toStdString());
    }

    compress();
    QFile file("OUTPUT_FILES/compression_output.xml");
    file.open(QFile::ReadOnly | QFile::Text);
    ui->outputText->setPlainText(file.readAll());

    //clear the string
    in_s="";
    file.close();
}
    else {QMessageBox::warning(this,"Crash Alert","Please load a sample first to compress");}

}

/*-------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------DECOMPRESS BUTTON------------------------------------------------*/

void MainWindow::on_pushButton_5_clicked()
{
 if(zk==1){
    decompress();
    QFile file("OUTPUT_FILES/decompression_output.xml");
    file.open(QFile::ReadOnly | QFile::Text);
    ui->outputText->setPlainText(file.readAll());
   //clear the string
    in_s="";
    file.close();}
 else {QMessageBox::warning(this,"Crash Alert","Please load a sample first to decompress");}

}

/*-------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------TO_JASON()-------------------------------------------------------*/
void MainWindow::on_pushButton_3_clicked()
{
        if(zk==1){
       QTextStream stream(&loaded_text);
        while (stream.readLineInto(&s)){
        string line2=s.toStdString();
        line3.push_back(line2);
        }

    toJason();
    QFile file("OUTPUT_FILES/toJson_output.json");
    file.open(QFile::ReadOnly | QFile::Text);
    ui->outputText->setPlainText(file.readAll());
   // line3.clear();
}
        else {QMessageBox::warning(this,"Crash Alert","Please load a sample first to convert to JSON");}

}

/*-------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------Correct_Errors---------------------------------------------------*/
void MainWindow::on_pushButton_2_clicked()
{   if(zk==1){
    //clear the output window
    ui->outputText->clear();

    QTextStream stream(&loaded_text);

    while (stream.readLineInto(&s)){
        error.append(s.toStdString());
        error.append("\n");
    }
    correct();
    error="";
    QFile file("OUTPUT_FILES/Consistency_output.xml");
    file.open(QFile::ReadOnly | QFile::Text);
    ui->outputText->setPlainText(file.readAll());
    detection_out="";
    var_detection="";}
    else {QMessageBox::warning(this,"Crash Alert","Please load a sample first to correct errors");}

}
/*-------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------Detect_Errors----------------------------------------------------*/

void MainWindow::on_pushButton_7_clicked()
{   if(zk==1){
    //clear the output window
    ui->outputText->clear();


    QTextStream stream(&loaded_text);
    while (stream.readLineInto(&s)){
        error.append(s.toStdString());
        error.append("\n");
    }
    correct();
    error="";
    QString displayer=QString::fromStdString(detection_out);
    ui->outputText->setPlainText(displayer);
    //clear variables
    detection_out="";
    var_detection="";}
    else {QMessageBox::warning(this,"Crash Alert","Please load a sample first to detect errors");}


}
/*-------------------------------------------------------------------------------------------------------------*/
/*--------------------------------------------Minify----------------------------------------------------*/
void MainWindow::on_pushButton_6_clicked()
{   if(zk==1){
    //clear the file
    std::ofstream ofs;
    ofs.open("OUTPUT_FILES/minify_output.xml", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    QTextStream stream(&loaded_text);
    string minif;
    ofstream out_file;
    out_file.open("OUTPUT_FILES/minify_output.xml");
    while (stream.readLineInto(&s)){
        int i = 0;
        minif = s.toStdString();
        while (minif[i] == ' ') // to remove the spaces in the begin of the line
            i++;
        minif.erase(minif.begin(), minif.begin() + i);
        out_file << minif;
    }
    out_file.close();

    QFile file("OUTPUT_FILES/minify_output.xml");
    file.open(QFile::ReadOnly | QFile::Text);
    ui->outputText->setPlainText(file.readAll());
    //clear the string
    in_s="";}
      else {QMessageBox::warning(this,"Crash Alert","Please load a sample first to minify");}
    }




void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}
