#include "dialog2.h"
#include "ui_dialog2.h"
#include<Graph_representation.h>
#include<mainwindow.h>
#include<QMessageBox>

extern string global_string;

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
    setWindowTitle("Compare Users' Followers");
}

Dialog2::~Dialog2()
{
    delete ui;
}


// user_list --> all ids

void Dialog2::on_pushButton_clicked()
{

    //check if both users exist and the comparison is valid

    bool user1=false; // not found yet
    bool user2=false; // not found yet
    QString user_text1 = ui->textEdit->toPlainText();
    QString user_text2 = ui->textEdit_2->toPlainText();
    string u1 = user_text1.toStdString();
    string u2 = user_text2.toStdString();


int found1;
int found2;

    for(unsigned int i=0; i<users_list.size();i++){

        if(u1 == to_string(users_list[i]) ){user1=true; found1=i;}
        else if(u2==to_string(users_list[i]) ){user2=true; found2=i;}

    }


    if(user1 && user2){
       // start comparison
     vector<G_LinkedList *> all_users= get_all_vectors(); // function to allow to access linked list in different cpp file

     Graph_Node *head_a = all_users[found1]->Myhead()->get_next(); // pointer to first user linkedlist selected by gui
     Graph_Node *head_b = all_users[found2]->Myhead()->get_next();
     int a_val,b_val=0;
     global_string.append("Mutual Followers are :");
     //// if ever found :::::::::  global_string.append("user ") then append user index as string;
        while(head_a!=NULL){
            a_val=head_a->get_id();
             while(head_b!=NULL){
             b_val=head_b->get_id();
             if(a_val==b_val){
             global_string.append("user: ");
             global_string.append(" of ID: ");

             global_string.append(to_string(a_val));
             global_string.append(" ");
             }
             head_b=head_b->get_next();
             }
        head_b=all_users[found2]->Myhead()->get_next();
        head_a=head_a->get_next();
        }
        if(global_string=="Mutual Followers are :"){global_string=" "; global_string.append("There are no mutual Followers");}

       ui->textEdit_4->setPlainText(QString::fromStdString(global_string));
       global_string="";
    }
    else{QMessageBox::warning(this,"Crash Alert","The user you have entered does not exist");}


}

