#include "dialog3.h"
#include "ui_dialog3.h"
#include<string>
#include<Graph_representation.h>
#include<mainwindow.h>

Dialog3::Dialog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3)
{
    ui->setupUi(this);
}

Dialog3::~Dialog3()
{
    delete ui;
}

bool search(string str, string pattern)
{
    int i = 0;
    int j = 0;
    int n = str.length();
    int m = pattern.length();
    while (i < n && j < m)
    {
        if (str[i] == pattern[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == m)
    {
        return true;
    }
    else
    {
        return false;
    }
}

string remove_d_spaces(string str)
{
    string new_str = "";
    for (unsigned int i = 0; i < str.length(); i++)
    {
        if (str.substr(i, 2) != "  ")
        {
            new_str += str[i];
        }
    }
    return new_str;
}


string post_search(string in_str, string keyword)
{
    string out_str = "";

    int start_of_tag = 0;
    int end_of_tag = 0;
    //int start_of_prev = 0;
    int end_of_prev = 0;

    string tag = "";
    int index_in = 0;
    string curr_char;
    int len_in = in_str.length();
    bool get_data = true;
    string user_id = "";
    string curr_post;
    bool search_result = false;
    int result_num = 0;
    while (get_data)
    {
        curr_char = in_str[index_in];
        if (curr_char == "<")
        {
           // start_of_prev = start_of_tag;
            end_of_prev = end_of_tag;
            start_of_tag = index_in;
            end_of_tag = in_str.find(">", start_of_tag);

            tag = in_str.substr(start_of_tag, end_of_tag + 1 - start_of_tag);

            if (tag == "</body>")
            {
                curr_post = in_str.substr(end_of_prev + 1, start_of_tag - end_of_prev - 1);
                search_result = search(curr_post, keyword);
                out_str.append(search_result ? to_string(++result_num)+"\n" : "");
                out_str.append(search_result ? remove_d_spaces(curr_post) + "\n" : "");
            }
            index_in = end_of_tag;
        }
        index_in++;

        if (index_in == len_in)
        {

            get_data = false;
        }
    }
    return out_str;
}



void Dialog3::on_pushButton_clicked()
{    QString user_text1 = ui->textEdit_2->toPlainText();
     string keyword =user_text1.toStdString();
     string output ="";
     output.append("found keyword in \n");
     output.append(post_search(xml_string, keyword));

    if (output =="found keyword in \n" ){output="No matching words were found.";}

     QString done =  QString::fromStdString(output);

     ui->textEdit->setPlainText(done);
     output="";

}

