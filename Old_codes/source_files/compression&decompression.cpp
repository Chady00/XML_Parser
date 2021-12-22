
#include "cmp.h"

/********************** Glopal Variables*********************/
unsigned long long freqs[1000] = {0};
char cs[200] = {0}; // just repeated characters
string in_s = "";
long long in_size = 0;
long long size2 = 0;

priority_queue<node *, vector<node *>, Compare> priority_q;  // tree -> priority 

node *tree_root;
string global_code = ""; // coded string
string character_codes[10000] = {""};
unsigned char codes[10000] = {0}; // to store seperate bytes
long long codes_size = 0;         // bytes
long long zeros = 0;
string decoded_string = "";
string temp2 = "";

/********************** Function Deffinations *********************/
node::node(int freq, char data, node *left, node *right)
{
    this->freq = freq;
    this->data = data;
    this->left = left;
    this->right = right;
}

node::node(int freq, node *left, node *right)
{
    this->freq = freq;
    this->left = left;
    this->right = right;
}

// 1
void get_freqs(string file_name)
{
    string in_lines[1000];
    ifstream in_file(file_name);
    int i = 0;
    while (getline(in_file, in_lines[i]))
    {
        in_s = in_s + in_lines[i];
        i++;
    }

    in_size = in_s.size();
    // cout << in_size << endl;

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
        node *temp = new node(freqs[c], cs[i], NULL, NULL);
        priority_q.push(temp);
    }
    // check
    // for (int i = 0; i < size2; i++)
    // {
    //     node *c = priority_q.top();
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
        node *left = priority_q.top();
        // cout << left->data << "\n";
        priority_q.pop();
        node *right = priority_q.top();
        // cout << right->data << "\n";
        priority_q.pop();
        /*new freq*/
        int new_freq = left->freq + right->freq;

        node *new_node = new node(new_freq, left, right);

        /*put  the new node at the top*/
        priority_q.push(new_node);
    }
    tree_root = priority_q.top();
}
// 4
void traverse(node *ptr, string str)
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
    get_freqs("../sample.xml");
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
    temp2 = global_code;
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
{
    std::ofstream ofs;
    ofs.open("compression_outpu2t.xml", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    ofstream out_file;
    out_file.open("compression_outpu2t.xml");
    for (size_t i = 0; i < codes_size; i++)
    {
        out_file << codes[i];
    }
    std::fill_n(codes, 10000, 0);
}



void compress(void)
{
    // reset variables
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
    in_s = "";
    for (size_t i = 0; i < priority_q.size(); i++)
    {
        priority_q.pop();
    }

    get_code();
    get_out_string(); // store in global_code
    seperate_codes();
    save_to_file();

}

int main()
{

    compress();
    compress();
    compress();
    compress();
    compress();
    decompress();
    decompress();
    decompress();
    // compress();
    compress();

    return 0;
}

