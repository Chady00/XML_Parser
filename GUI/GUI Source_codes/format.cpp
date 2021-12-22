#include"mainwindow.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include<vector>
#include <stack>
#include<string>
#include<format.h>

using namespace std;
/*-----------------------------------------GLOBAL VARIABLES-----------------------------------*/
int data_start=0;
/*--------------------------------------------------------------------------------------------*/


void adjust_ident(string *ptr,int a,int data_start){
   string ident;
// cout<<"data_start "<<data_start<<"  a"<<a<<endl;
 if(data_start>0){
     (*ptr).erase(0,data_start);
 }

    for(int i=0;i<a;i++){
        ident += " ";
    }
    (*ptr).insert(0,ident);


}
int get_start(string *line){
     int data_start=0;
     if((*line)[0]==' '){
`
    data_start = (*line).find_first_not_of(" ");
    }
    else {data_start=0;}
    return data_start;
}

void format()
{
    //clear the file
    std::ofstream ofs;
    ofs.open("OUTPUT_FILES/format_output.xml", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    int checker=0;

//adjust the first line:
 data_start=get_start(&file_contents[0]);
 adjust_ident(&file_contents[0],0,data_start);

for(unsigned int i=0;i<file_contents.size()-1;i++){
   // line_len=file_contents[i].size()-1;

    /*if first character not '<' AKA: text--> next line shift back: checker-=4
      else if the line initially openTag and noClosedTag at the end of the same line-->  ident_shift the next line
      else if line closed tag and next line open.. or previous line was text --> dont shift next line
    */

    //each cycle extract last_space occurence in case data was shifted
    data_start= get_start(&file_contents[i+1]);

    //check if there is a prolog
    //check if there is a prolog or a comment
       if(file_contents[i][checker+1]=='?'||file_contents[i][checker+1]=='!'){
           adjust_ident(&file_contents[i+1],checker,data_start);
       }

    //body text
    else if(file_contents[i][checker]!='<'){
        checker-=4;
        if( file_contents[i+1].substr(data_start,2)!="</")checker+=4;
        adjust_ident(&file_contents[i+1],checker,data_start);
        }
    //open but no closed
    else if(file_contents[i][checker]=='<' && file_contents[i].find("</") == std::string::npos){
        checker+=4;
        adjust_ident(&file_contents[i+1],checker,data_start);
    }
    // open closed , and next closed
    else if(file_contents[i][checker]=='<' && file_contents[i].find("</") != std::string::npos && file_contents[i+1].substr(data_start,2)=="</"){
        checker-=4;
        adjust_ident(&file_contents[i+1],checker,data_start);
    }
    //closing , next closing
    else if(file_contents[i].substr(checker,2)=="</" && file_contents[i+1].substr(data_start,2)=="</"){
        checker-=4;
        adjust_ident(&file_contents[i+1],checker,data_start);
    }
    //closing then open
     else if(file_contents[i][checker]!='<'||(file_contents[i].find("</") != std::string::npos && file_contents[i+1][data_start]=='<') ){

         adjust_ident(&file_contents[i+1],checker,data_start); }

}


    // Output to the file
    std::ofstream file("OUTPUT_FILES/format_output.xml"); int i=0;
    for(std::string line : file_contents){
        //cout<<file_contents[i];
        i++;
    file <<line<<endl;
    }
 file.close();
}

/**************************** Some of the implementation is in mainwindow.cpp *****************************************/

