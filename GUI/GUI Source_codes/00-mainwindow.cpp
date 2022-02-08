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
#include<gvc.h>
#include<cdt.h>
#include<cgraph.h>
#include<QPixmap>
#include"dialog2.h"
#include"dialog3.h"


/*-------------------------------------- GLOBAL VARIABLES--------------------------------------*/
QString loaded_text,s;
vector<string> file_contents; // the is an extern variable used in all .cpp files
string error,detection_out,var_detection,in_s="",represent,global_string,xml_string;
vector<int>users_list;
vector<string> line3;
unsigned char zk,prevent_repr,prevent_compare;

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
    /*hide gui labels*/
    ui->label_4->hide();
    ui->pic_frame->hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}


/*-------------------------------------------------------------------------------------------------------------*/
/*------------------------------------------------OPEN BUTTON--------------------------------------------------*/
void MainWindow::on_actionOpen_triggered()
{   disable_effects();
    zk=1;
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
void MainWindow::disable_effects(){
    ui->pic_frame->hide();
    ui->label_4->hide();
}

/*-------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------FORMAT BUTTON-------------------------------------------------*/
void MainWindow::on_pushButton_clicked()
{   disable_effects();//disable the effects of graphics
    if(zk==1){
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
{   disable_effects();
    //Must get input from file:
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
{   disable_effects();
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
{       disable_effects();
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
{   disable_effects();
    if(zk==1){
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
{   disable_effects();
    if(zk==1){
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
/*-----------------------------------------------Minify--------------------------------------------------------*/
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

/*-------------------------------------------------------------------------------------------------------------*/
/*-----------------------------------------------REPRESENT GRAPH-----------------------------------------------*/

void MainWindow::on_pushButton_8_clicked()
{
    represent="";
    //clear output text
        ui->outputText->clear();
        if(zk==1){
        if(prevent_compare==0){
        //load the Qstring into a string
        QTextStream stream(&loaded_text);
        while (stream.readLineInto(&s)){
        represent.append(s.toStdString());
        prevent_repr=1;
        }

       Represent();
       }
       // string  dotLang="digraph main{node[shape =rect label=\"Read \n (x)\"]id1 node[shape =rect label=\"if\"] id2 {rank = same; id1; id2; } id1->id2}";
       //string  dotLang= "digraph G  {node[shape=record] 1[label=\"{ Ahmed | 2 | 3 }\"] 2[] 3[] 1->{3, 2} 2->{1} 3->{1} }";

       Agraph_t* G;
       GVC_t* gvc1;
       gvc1 = gvContext();
       char * y =&represent[0];
       G = agmemread(y);
       gvLayout (gvc1, G, "dot");
       gvRenderFilename(gvc1,G,"png","OUTPUT_FILES/visual_graph.png");
       gvFreeLayout(gvc1, G);
       agclose (G);
       gvFreeContext(gvc1);


       /*displaying png*/


       QPixmap map("OUTPUT_FILES/visual_graph.png");
       //adjusting width and height , and displaying the png
       int w = ui->pic_frame->width();
       int h = ui->pic_frame->height();

       ui->pic_frame->setPixmap(map.scaled(w,h,Qt::KeepAspectRatio, Qt::SmoothTransformation));
       ui->pic_frame->show();
       ui->label_4->show();
       //open backup image
       ifstream image;
       image.open("OUTPUT_FILES/visual_graph.png");




    }
    else{QMessageBox::warning(this,"Crash Alert","Please load a sample first to graphically represent");}

}

/*-------------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------- COMPARE USER --------------------------------------------------*/
void MainWindow::on_pushButton_9_clicked()
{    //load the Qstring into a string
    if(zk==1){
    if(prevent_repr==0){ // check if the string is already loaded
    QTextStream stream(&loaded_text);
    while (stream.readLineInto(&s)){
    represent.append(s.toStdString());
    prevent_compare=1;
    }

    Represent();

    }
    represent="";
    Dialog2 *dialog = new Dialog2(this);
    dialog->show();}

    else{QMessageBox::warning(this,"Crash Alert","Please load a sample first to compare users");}

}


void MainWindow::on_pushButton_10_clicked()
{   if(zk==1){
     QTextStream stream(&loaded_text);
     while (stream.readLineInto(&s)){
     xml_string.append(s.toStdString());
     }
    Dialog3 *dialog = new Dialog3(this);
    dialog->show();
    }
     else{QMessageBox::warning(this,"Crash Alert","Please load a sample first to post search a keyword");}
}

