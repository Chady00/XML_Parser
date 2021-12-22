#ifndef trees
#define trees
#include <iostream>
#include <vector>
using namespace std;
extern vector<string> line3; // this is an extern variable

class node{
    public:
    string tagname;
    vector<node*>childern;
    string tagdata;
    node* parent; 
    public:
    node(void);
    node(string name);
    node(string name,string data);
    friend class tree;
};
class tree{
    node*root;
    public:
    tree();
    node*get_root(void);
    vector<node*>get_children(node*n);
    void add_root(node*r);
    string get_tagdata(node*r);
    string get_name(node*r);
    node*add_node(string name);
    void add_data(node*n,string data);
    void add_child(node*parent,node*child);


};
void toJason();
#endif
