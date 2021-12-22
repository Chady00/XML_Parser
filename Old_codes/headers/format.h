/*============================================================================
// Name        : xml_format.h
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================*/
#ifndef XML_FORMAT_H_
#define XML_FORMAT_H_

/**************************** HEADER *****************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include<vector>
#include <stack>
#include<string>
using namespace std;


/********************** FUNCTION PROTOTYPES *********************/
void print_vect(vector<string> vect);
void adjust_ident(string *ptr,int a,int data_start);
int get_start(string *line);
void format();


#endif /* MINIFY_FUNCTION_H_ */
