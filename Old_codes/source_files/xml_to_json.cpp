#include<fstream>
#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include"tree.h"
using namespace std;
vector <string> line3;
node::node()
{
    parent=NULL;
}
node::node(string name,string data)
{

    tagname=name;
    tagdata=data;
    parent=NULL;

}
node::node(string name)
{
    tagname=name;
    //cout<<"from class"<<tagname<<endl;
    parent=NULL;
}
tree::tree(void)
{
    root=NULL;
}

node* tree::get_root(void)
{
    return root;
}
vector<node*> tree::get_children(node*n)
{
    return n->childern;
}
void tree::add_root(node *n)
{
    root=n;
}
string tree::get_tagdata(node*n)
{
    return n->tagdata;
}
string tree::get_name(node*n)
{
    return n->tagname;
}
node* tree::add_node(string name )
{

    node* s=new node(name);
    return s;

}
void tree::add_data(node*n,string data)
{
    n->tagdata+=data;
}
void tree::add_child(node*parent,node*child)
{
    parent->childern.push_back(child);
    child->parent = parent;
}
/*function to put all xml lines in a string vector*/
void get_xml()
{
    string line;
    ifstream input;
    input.open("tiral.xml");
    while(getline(input,line)){
        line3.push_back(line);
                
    }
}

ofstream output;
/*function to edit the xml file to make it easier to put in tree*/
void xml_editor()
{

    string new_string;
    int beg,end;
    ofstream my_output;
    string my_string;
    my_output.open("tiral_min.xml");
    for(unsigned int i=0;i<line3.size()-1;i++)
    {   my_string=line3[i];
        int u = (my_string).find_first_not_of(" ");

       if(u>0){
       my_string.erase(0,u);
 }
        for(int i=0 ; i < my_string.length(); i++)
        {
            if(my_string[0]=='<'&& (my_string[1]=='!'||my_string[1]=='?')){
                continue;
            }

            if(my_string[i]=='<')
            {
                beg=i;
                for(i;i<my_string.length();i++){
                    if(my_string[i]=='>'){
                        end=i;
                        break;
                    }
                }

            }
            else
            {

                beg=i;
                for(i;i<my_string.length();i++){
                    if(my_string[i]=='<'){
                        end=i-1;
                        i--;
                        break;
                    }
                    else{
                        end=i;
                    }
                }
            }
            new_string=my_string.substr(beg,(end-beg+1));
            if(new_string[0]!=' '){
                my_output << new_string << endl;
            }



        }
    }
    my_output.close();
}
int i=0;
/*function to create the tree*/
void create_tree(tree& my_tree)
{

    string tag;
    string temp;
    vector<node*>nodes;
    stack<int>level;
    string my_string;
    ifstream input;
    input.open("tiral_min.xml");
    //cout<<line3.size();
     while(getline(input,my_string))
    {

        if(my_string[0]=='<'&& my_string[1]!='/')
        {
            tag=my_string.substr(1,my_string.length()-2);
            nodes.push_back(my_tree.add_node(tag));
            if(level.size()==0)
            {
                //cout<<"i added root"<<endl;
                my_tree.add_root(nodes[nodes.size()-1]);
            }

            else
            {
                //cout<<"child added"<<endl;
                my_tree.add_child(nodes[level.top()], nodes[nodes.size() - 1]);

            }
            //cout<<"stack increased"<<endl;
            level.push(nodes.size() - 1);
        }
        else if(my_string[0]=='<'&&my_string[1]=='/')
        {
            //cout<<"pop happened"<<endl;
            level.pop();
        }
        else if(my_string[0]!='<')
        {
            //cout<<"data added"<<endl;
            if(my_string[0]!=' '){
            temp=my_string;
            my_tree.add_data(nodes[level.top()], temp);
            //cout<<"data is  "<<my_tree.get_tagdata(nodes[tags.top()])<<endl;
            }
        }


    }
    input.close();

}
/*function to convert the tree to json*/
void print_node(node*root,int& new_space,int node_type,int rr_indicator,int rr_max,int once,string s)
{

    if(once==1)
    {
        output << "{"<<endl;
        once++;
    }
    if(node_type==1)
    {
        if(rr_indicator<=1 || rr_max<=1)
        {
            output << "\n";
            for(int k=0;k<new_space;k++){
                output << s;
            }

            output<<"\""<<root->tagname<<"\":";
        }
        if(rr_indicator==1 && rr_max>1)
        {

            output<<"[";
            new_space++;
        }
        if(root->childern.size())
        {
            if(rr_max>1)
            {
                output << "\n";
                for(int k=0;k<new_space;k++){
                    output << s;
                }
            }

            output<<"{";
            new_space++;
        }
    }

    if(root->tagdata.size()&&!(root->childern.size()))
    {
        if(rr_max>1)
        {
            new_space++;
        }
        output << "\n";
        for(int k=0;k<new_space;k++){
            output << s;
            }
        if(node_type==0 )
        {
            output<<"\""<<root->tagname<<"\": ";
        }

        output<<"\""<<root->tagdata<<"\"";

    }
    if(root->childern.size())
    {

        int chil_size=root->childern.size();
        int new_type=0;
        int my_repeat=1;
        for(int i=0; i<chil_size; i++)
        {
            if(my_repeat)
            {
                int repeat=1;
                int j=0;
                while(j+1<chil_size &&root->childern[j]->tagname==root->childern[j+1]->tagname )
                {
                    repeat++;
                    j++;
                }
                rr_max=repeat;
                //cout<<rr_max;
                rr_indicator=1;
                my_repeat=0;
            }
            if( root->childern[i]->childern.size() || rr_max >1)
            {
                new_type=1;
            }
            else
            {
                new_type=0;
            }
            print_node(root->childern[i],new_space,new_type,rr_indicator,rr_max,3,s);
            if(rr_max>1 && rr_indicator<=rr_max)
            {
                rr_indicator++;
            }
            if(new_type==1)
            {
                new_space--;
                if( root->childern[i]->childern.size())
                {
                    output << "\n";
                    for(int k=0;k<new_space;k++){
                        output <<s;
                    }
                    output<<"}";
                }
            }
            if(rr_indicator>1 && rr_indicator>rr_max)
            {
                rr_indicator=1;
                rr_max=1;
                new_space--;
                output << "\n";
                for(int k=0;k<new_space;k++){
                    output <<s;
                }
                output<<"]";
                my_repeat=1;
            }
            if(i!=root->childern.size()-1)
            {
                output<<",";
            }
        }
    }

}
