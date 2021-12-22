#ifndef CMP_FUNCTION_H_
#define CMP_FUNCTION_H_

/******** Headers *******/
#include<string>
#include<string.h>
#include<queue>
#include<iostream>
#include <fstream>
#include <vector>
using namespace std;

extern string in_s;//this is an extern variable

/******** Classes *******/

class Node
{
public:
    int freq;
    char data;
    string code; // the output code for each Node
    Node *left;
    Node *right;

public:
    Node(int freq, char data, Node *left, Node *right);
    Node(int freq, Node *left, Node *right);
};

class Compare // to be passed as the third parameter of priorety queue
{
public:
    bool operator()(Node *a, Node *b)
    {
        return (a->freq > b->freq); // least freq at the top to take large code
    }
};

/******** Function Prototypes *******/
void compress();
void decompress();
void save_to_file(void);
void seperate_codes(void);
void get_out_string(void);
void add_zeros(void);
void get_code(void);
void traverse(Node *ptr, string str);
void create_tree(void);
void storein_q(void);
void get_freqs();

#endif /*CMP_FUNCTION_H_ */
