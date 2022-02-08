#ifndef GRAPH_REPRESENTATION_H
#define GRAPH_REPRESENTATION_H
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;


/***** Classes ******/
class Graph_Node
{
private:
    int id;
    string name;
    Graph_Node *next;

public:
    Graph_Node(int d, string name)
    {
        this->id = d;
        this->next = NULL;
        this->name=name;
    }
    int get_id()
    {
        return this->id;
    }
    string get_name()
    {
        return this->name;
    }
    Graph_Node *get_next()
    {
        return this->next;
    }
    friend class G_LinkedList;
};

class G_LinkedList
{
private:
    Graph_Node *head;

public:
    G_LinkedList()
    {
        head = NULL;
    }
    // function to return head
    Graph_Node *Myhead()
    {
        return this->head;
    }
    // function to add a new Graph_Node to the list
    void push_front(int d,string name)
    {
        Graph_Node *new_Graph_Node = new Graph_Node(d,name);
        new_Graph_Node->next = head;
        head = new_Graph_Node;
    }
    // function to get length of the linked list
    int length()
    {
        Graph_Node *my_Graph_Node = head;
        int count = 0;
        while (my_Graph_Node != NULL)
        {
            count++;
            my_Graph_Node = my_Graph_Node->next;
        }
        return count;
    }
    void printG_LinkedList(Graph_Node *head)
    {
        if (head == NULL)
        {
            return;
        }
        cout << head->id << " ";
        printG_LinkedList(head->next);
    }
    void print()
    {
        printG_LinkedList(head);
    }
};

extern string represent; // extern variable
extern vector<int>users_list;


void get_users_list();
int Most_active(vector <G_LinkedList *> u );
int Has_more_Followers(vector <G_LinkedList *> u);
vector<G_LinkedList *> get_all_vectors();
#endif // GRAPH_REPRESENTATION_H
