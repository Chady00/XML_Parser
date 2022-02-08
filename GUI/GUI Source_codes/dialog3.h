#ifndef DIALOG3_H
#define DIALOG3_H

#include <QDialog>
#include<mainwindow.h>
#include<string>
 extern string xml_string;
namespace Ui {
class Dialog3;
}
class Dialog3 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog3(QWidget *parent = nullptr);
    ~Dialog3();



private slots:
    void on_pushButton_clicked();


private:
    Ui::Dialog3 *ui;
};

bool search(string str, string pattern);
string remove_d_spaces(string str);
string post_search(string in_str, string keyword);

#endif // DIALOG3_H
