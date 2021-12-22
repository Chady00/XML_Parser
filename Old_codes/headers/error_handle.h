#ifndef ERROR_HANDLE_H
#define ERROR_HANDLE_H
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <stack>
#include <streambuf>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

string get_indent(int stack_level);

bool comp_tags(string open_tag, string close_tag);
string remove_extra(string str);
bool tag_in_stack(string tag, stack<string> stack);
string close_tag(string open_tag);
void PrintStack(stack<string> s);
string check_const(string in_str);

#endif // ERROR_HANDLE_H
