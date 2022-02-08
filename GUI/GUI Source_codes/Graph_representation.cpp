
#include<Graph_representation.h>

vector<G_LinkedList *> users_vector;


/***** Functions Definition ******/

vector<G_LinkedList *> get_all_vectors(){
    return users_vector;
}

int Most_active(vector <G_LinkedList *> u ){
    int mostactive = 1;
    int count=0;
    int count2=0;

    for(unsigned int i=0; i<u.size();i++){
            Graph_Node *curr_head = u[i]->Myhead()->get_next();
            while (curr_head != NULL)
            {
               // cout<<curr_head->get_id()<<endl;
                count2++;
                curr_head = curr_head->get_next();
            }

        if(count<count2){count = count2; mostactive=u[i]->Myhead()->get_id();}
        count2=0;
    }
    cout<<mostactive<<endl;
    return mostactive;
}


int Has_more_Followers(vector <G_LinkedList *> u){
    int most_followed = 1;
    int arr[10000]={0};
    for(unsigned int i=0; i<u.size();i++){
            Graph_Node *curr_head = u[i]->Myhead()->get_next();
            while (curr_head != NULL)
            {   int current_val=curr_head->get_id();
                //increment the array at id position
                arr[current_val]+=1;
                curr_head = curr_head->get_next();
            }
    }
    int count=0;
    for(int i=0; i<10000;i++){
        if(arr[i]>=count){
            count=arr[i];
            most_followed=i;
        }
    }
    return most_followed;
}





string get_name(string str_in, int start_ind)
{
    string name = "";
    string open = "<name>";
    string close = "</name>";
    // int opening = in_str.find(tag, start_index);

    std::size_t found_open = str_in.find(open, start_ind) + 6;
    std::size_t found_close = str_in.find(close, start_ind);
    if (found_open != std::string::npos && found_close != std::string::npos)
    {

        // std::cout << "first 'name' found at: " << found_open << '\n';
        // std::cout << "first 'close name' found at: " << found_close << '\n';
        // std::cout << str_in.substr(found_open, found_close - found_open) << '\n';
        name = str_in.substr(found_open, found_close - found_open);
    }

    return name;
}






int get_followers(string str_in, int start_ind, G_LinkedList *user_list)
{
    int start_of_tag = 0;
    int end_of_tag = 0;
    int start_of_prev = 0;
    int end_of_prev = 0;
    string tag = "";
    string data_between = "";
    int index_in = start_ind;
    string curr_char;
    int len_in = str_in.length();
    string out_str = "";
    bool get_data = true;
    int end_of_user = 0;
    string follower_id = "";
    string follower_name="";

    while (get_data)
    {
        // cout << str_in << endl;
        curr_char = str_in[index_in];
        if (curr_char == "<")
        {
            start_of_prev = start_of_tag;
            end_of_prev = end_of_tag;
            start_of_tag = index_in;
            end_of_tag = str_in.find(">", start_of_tag);

            tag = str_in.substr(start_of_tag, end_of_tag + 1 - start_of_tag);
            if (tag == "</user>")
            {
                end_of_user = end_of_tag + 1;
                return end_of_user;
            }
            if (tag == "</id>")
            {
                follower_id = (index_in != 0) ? str_in.substr(end_of_prev + 1, start_of_tag - end_of_prev - 1) : "";
                // cout << "follower_id >>" << follower_id << endl;
                follower_name = get_name(str_in, end_of_tag);
                user_list->push_front(int(stoi(follower_id)), follower_name);
            }

            index_in = end_of_tag;
        }
        index_in++;

        if (index_in == len_in)
        {

            get_data = false;
        }
    }
    return index_in;
}














vector<G_LinkedList *> fill_graph_data(string xml_data)
{
    vector<G_LinkedList *> users_vector;

    int start_of_tag = 0;
    int end_of_tag = 0;
    int start_of_prev = 0;
    int end_of_prev = 0;
    string tag = "";
    string data_between = "";
    int index_in = 0;
    string curr_char;
    int len_in = xml_data.length();
    string out_str = "";
    bool get_data = true;
    int end_of_user = 0;
    string user_id = "";
    string user_name="";
    // int user_count = 0;

    while (get_data)
    {
        curr_char = xml_data[index_in];
        if (curr_char == "<")
        {
            start_of_prev = start_of_tag;
            end_of_prev = end_of_tag;
            start_of_tag = index_in;
            end_of_tag = xml_data.find(">", start_of_tag);

            tag = xml_data.substr(start_of_tag, end_of_tag + 1 - start_of_tag);
            if (tag == "</id>")
            {
                user_id = (index_in != 0) ? xml_data.substr(end_of_prev + 1, start_of_tag - end_of_prev - 1) : "";
                user_name = get_name(xml_data, index_in);
                // cout << "user_id >>" << user_id << endl;

                G_LinkedList *user_list = new G_LinkedList();
                users_vector.push_back(user_list);
                // // push the header in a vector

                end_of_user = get_followers(xml_data, end_of_tag + 1, user_list);
                user_list->push_front(int(stoi(user_id)), user_name);
                end_of_tag = end_of_user;
            }
            index_in = end_of_tag;
        }
        index_in++;

        if (index_in == len_in)
        {

            get_data = false;
        }
    }
    return users_vector;
}












































