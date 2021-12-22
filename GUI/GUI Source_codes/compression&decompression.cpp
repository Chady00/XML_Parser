#include "comp.h"
/********************** Glopal Variables*********************/
unsigned long long freqs[1000] = {0};
char cs[200] = {0}; // just repeated characters
long long in_size = 0;
long long size2 = 0;
priority_queue<Node *, vector<Node *>, Compare> priority_q;
Node *tree_root;
string global_code = "",temp2; // coded string
string character_codes[10000]={""};
unsigned char codes[10000]={' '}; // to store seperate bytes
long long codes_size = 0;   // bytes
long long zeros = 0;
string decoded_string = "";


/********************** Function Definitions *********************/
Node::Node(int freq, char data, Node *left, Node *right)
{
    this->freq = freq;
    this->data = data;
    this->left = left;
    this->right = right;
}
Node::Node(int freq, Node *left, Node *right)
{
    this->freq = freq;
    this->left = left;
    this->right = right;
}

// 1
void get_freqs()
{
   // string in_lines[1000];
   /* ifstream in_file(file_name);
    int i = 0;
    while (getline(in_file, in_lines[i]))
    {
        in_s = in_s + in_lines[i];
        i++;
    }
    */

    in_size = in_s.size();
    cout << in_size << endl;

    char c;
    int j = 0;
    for (long i = 0; i < in_s.size(); i++)
    {
        c = in_s[i]; // <

        if (freqs[c] == 0)
        { // just in case it is first time
            cs[j] = in_s[i];
            j++;
        }

        freqs[c]++;
    }
    size2 = j + 1;
    // check
    //  for (size_t i = 0; i < 200; i++)
    //  {
    //      cout << freqs[i] << "\n";
    //  }
    //  for (size_t i = 0; i < 200; i++)
    //  {
    //      cout << cs[i] << "\n";
    //  }
}
// 2
void storein_q(void)
{
    char c;
    for (int i = 0; i < size2; i++)
    {
        c = cs[i]; // character
        Node *temp = new Node(freqs[c], cs[i], NULL, NULL);
        priority_q.push(temp);
    }
    // check
    // for (int i = 0; i < size2; i++)
    // {
    //     Node *c = priority_q.top();
    //     priority_q.pop();
    //     cout << c->data << freqs[c->data] << endl;
    // }
}
// 3
void create_tree(void)
{
    int q_size = priority_q.size();
    // cout << q_size << "\n";
    while (q_size-- != 1)
    {
        /*get the least 2 freqs*/
        Node *left = priority_q.top();
        // cout << left->data << "\n";
        priority_q.pop();
        Node *right = priority_q.top();
        // cout << right->data << "\n";
        priority_q.pop();
        /*new freq*/
        int new_freq = left->freq + right->freq;

        Node *new_Node = new Node(new_freq, left, right);

        /*put  the new Node at the top*/
        priority_q.push(new_Node);
    }
    tree_root = priority_q.top();
}
// 4
void traverse(Node *ptr, string str)
{

    if (ptr->left == NULL && ptr->right == NULL)
    {
        ptr->code = str;                  // store the code
        character_codes[ptr->data] = str; // depend on the character it is have its code

        // cout << ptr->data << " " << ptr->code << "\n";
    }
    else
    {
        traverse(ptr->left, str + "0");

        traverse(ptr->right, str + "1");
    }

    // for (std::size_t i = 0; i < (ptr->code).size(); ++i)
    // {
    //     cout << stoi(ptr->code) << endl;
    // }
}
// 5
void get_code(void)
{
    get_freqs();
    storein_q();
    create_tree();
    traverse(tree_root, "");
    // cout << global_code << endl;

}

void add_zeros(void) /* needded zeros to make the string have an 8 bytes characters*/
{
    long size_code = global_code.size();
    int size_rem = size_code % 8;
    zeros = 8 - size_rem; // needded zeros to make the string have an 8 bytes characters
                          //  cout << "reeeeem " << size_rem << endl;
    for (size_t i = 0; i < zeros && size_rem != 0; i++)
    {
        // cout << "d5lllllllllllllll" << endl;
        global_code = global_code + '0';
    }

}
// the output file will be characters each of one byte

void get_out_string(void)
{
    for (size_t i = 0; i < in_size; i++)
    {
        global_code = global_code + character_codes[in_s[i]];
    }
   temp2 =global_code;

   // cout << global_code;
}

void seperate_codes(void)
{
    // cout << global_code << endl;
    add_zeros();
    // cout << global_code << endl;
    long size_code = global_code.size(); // size become divisible by 8

    for (size_t i = 0; i < (size_code); i += 8) // 0
    {
        string temp = "";
        for (size_t j = i; j < i + 8; j++) // 0-> 7
        {
            temp = temp + global_code[j];
            // cout << temp << endl;
        }
        // cout << temp << endl;
        codes[codes_size] = (char)stoi(temp);

        //  cout << codes[codes_size] << endl;
        codes_size++;
    }
}

void save_to_file(void)
{   //clear the file
    std::ofstream ofs;
    ofs.open("OUTPUT_FILES/compression_output.xml", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    ofstream out_file;
    out_file.open("OUTPUT_FILES/compression_output.xml");
    for (size_t i = 0; i < codes_size; i++)
    {
        out_file << codes[i];
    }


    out_file.close();
}
void decompress(void)
{
    node temp = tree_root;
    for (size_t i = 0; i < temp2.size(); i++) /*get the decoded string from the tree*/
    {
        if (temp2[i] == '0')
            temp = temp->left;
        else
            temp = temp->right;

        if (temp->left == nullptr && temp->right == nullptr)
        {
            decoded_string += temp->data;
            temp = tree_root;
        }
    }

    std::ofstream ofs;
    ofs.open("decompressed_output2.xml", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    ofstream out_file;

    out_file.open("decompressed_output2.xml");
    int flag = 0; // a flag fo case of string
    for (size_t i = 0; i < decoded_string.size(); i++)
    {
        flag = (decoded_string[i] >= 45 && decoded_string[i] < 122 && decoded_string[i + 1] == ' ' && !(decoded_string[i + 2] >= 45 && decoded_string[i + 1] < 122));

        if (flag  (decoded_string[i] == '>' && decoded_string[i + 1] == '<')  (decoded_string[i] == '>' && decoded_string[i + 1] == ' '))
        {
            out_file << decoded_string[i];
            out_file << endl; // new line
            flag = 0;
        }
        else
        {
            out_file << decoded_string[i];
        }
    }
    out_file.close();
    temp2 = "";
    // cout << decoded_string << endl;
}

void compress()
{  // reset variables
    in_size = 0;
    zeros = 0;
    decoded_string = "";
    codes_size = 0;
    size2 = 0;
    global_code = "";
    std::fill_n(cs, 200, 0);
    std::fill_n(freqs, 1000, 0);
    std::fill_n(character_codes, 10000, "");
    std::fill_n(codes, 10000, 0);
   // in_s = "";

    for (size_t i = 0; i < priority_q.size(); i++)
    {
        priority_q.pop();
    }
    //
    get_code();
    get_out_string(); // store in global_code
    seperate_codes();
    save_to_file();
}

