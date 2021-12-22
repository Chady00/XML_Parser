#ifndef CMP_FUNCTION_H_
#define CMP_FUNCTION_H_

/********************** Headers *********************/
//#include <bits/stdc++.h>
#include <iostream> 
#include <string>
#include <queue>
#include <fstream>
#include <vector>
using namespace std;



/********************** Classes *********************/

class node
{
public:
    int freq;
    char data = ' ';
    string code; // the output code for each node
    node *left;
    node *right;

public:
    node(int freq, char data, node *left, node *right);
    node(int freq, node *left, node *right);
};

class Compare // to be passed as the third parameter of priorety queue
{
public:
    /*impelemnting the comprator*/
    bool operator()(node *a, node *b /*the top */) // to make it min heap 
    {
        return (a->freq > b->freq); // least freq at the top to take large code
    } // if true put it as a node else it will sift up and be the new top 
};

#endif /*CMP_FUNCTION_H_ */
