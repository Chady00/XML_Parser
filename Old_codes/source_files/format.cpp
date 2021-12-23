/*============================================================================
// Name        : xml_format.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================*/

#include "XML_format.h"

/*-----------------------------------------GLOBAL VARIABLES-----------------------------------*/
int data_start=0;
/*--------------------------------------------------------------------------------------------*/
/*---Prints the xml line by line---*/
void print_vect(vector<string> vect){
for(int i =0; i<vect.size();i++){
    cout<<vect[i]<<endl;
}
}

/*---Adjusts the identation of a file given the dataStart index---*/
void adjust_ident(string *ptr,int a,int data_start){
   string ident;
 if(data_start>0){
     (*ptr).erase(0,data_start);
 }

    for(int i=0;i<a;i++){
        ident += " ";
    }
    (*ptr).insert(0,ident);
    
    
}

/*---Gets the starting index of a line given a pointer to string---*/
int get_start(string *line){
     int data_start=0;
     if((*line)[0]==' '){

    data_start = (*line).find_first_not_of(" ");
    }
    else {data_start=0;}
    return data_start;
}

/*---LoadFile, Processes each line, and format at it according to poisition---*/
void format(){
    vector <string> file_contents;
     ifstream infile("XML.xml");
     string line;
     int beg,end,closend,temp;
     bool skip=false;
     
   for( std::string line; getline( infile, line ); )
{   
    //check if line is empty or all white spaces
      if(line.find_first_not_of(' ') != std::string::npos){
            /*
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

            else{*/file_contents.push_back(line);//}
        }
}

int checker=0;

//adjust the first line:(each line adjusts the one that follows)
 data_start=get_start(&file_contents[0]);
 adjust_ident(&file_contents[0],0,data_start);

for(int i=0;i<file_contents.size()-1;i++){
   // line_len=file_contents[i].size()-1;

    /*if first character not '<' AKA: text--> next line shift back: checker-=4
      else if the line initially openTag and noClosedTag at the end of the same line-->  ident_shift the next line 
      else if line closed tag and next line open.. or previous line was text --> dont shift next line
    */

    //each cycle extract last_space occurence in case data was shifted (Starting index of data)
    data_start= get_start(&file_contents[i+1]);
    
    //check if there is a prolog or a comment
    if(file_contents[i][checker+1]=='?'||file_contents[i][checker+1]=='!'){
        adjust_ident(&file_contents[i+1],checker,data_start);
    }
    
    //body text 
    else if(file_contents[i][checker]!='<'){
        checker-=4;
        adjust_ident(&file_contents[i+1],checker,data_start); 
        }
    //open but no closed or open then closed
    else if(file_contents[i][checker]=='<' && file_contents[i].find("</") == std::string::npos){
        if( file_contents[i+1].substr(data_start,2)!="</")checker+=4;
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
    //closing then open or open then
     else if((file_contents[i].find("</") != std::string::npos && file_contents[i+1][data_start]=='<') ){
       
         adjust_ident(&file_contents[i+1],checker,data_start); }
    
}
// Output to the file
std::ofstream file("format_output.xml");
 for(std::string line: file_contents){
file <<line<<endl;
 }
 file.close();
 
/*clear the file output
std::ofstream ofs;
ofs.open("format_output.xml", std::ofstream::out | std::ofstream::trunc);
ofs.close();
*/
print_vect(file_contents);
//ofstream file2("format_output.xml");
//file2.close();
}

int main()
{  format();
   return 0;
}
