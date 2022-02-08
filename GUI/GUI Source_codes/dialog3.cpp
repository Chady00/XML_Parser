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

