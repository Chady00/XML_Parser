#include <error_handle.h>

using namespace std;

// getting the line indentation based on stack level
string get_indent(int stack_level)
{
    string indent(stack_level * 4, ' ');
    return indent;
}

// comparing the open and close tags
bool comp_tags(string open_tag, string close_tag)
{
    return (open_tag.substr(1, open_tag.length() - 1) == close_tag.substr(2, close_tag.length() - 2));
}

// removes new lines and extra spaces
string remove_extra(string str)
{

    // size_t found = str.find_first_not_of("\n \t");
    // if (found != string::npos)
    // {
    //     return str.substr(found, str.size() - found);
    // }
    // return "";
    string new_str = "";
    string t = "";
    for (auto &&i : str)
    {
        if (i != ' ' && i != '\n' && i != '\t')
        {
            t = string(1, i);
            new_str.append(t);
        }
    }
    return new_str;
}

// checks if the closed tag has a matching open tag in the stack
bool tag_in_stack(string tag, stack<string> stack)
{
    while (!stack.empty())
    {
        if (comp_tags(stack.top(), tag))
        {
            return true;
        }

        stack.pop();
    }
    return false;
}

// to close an open tag
string close_tag(string open_tag)
{
    return "</" + open_tag.substr(1, open_tag.size() - 1);
}

// for debugging >>> prints the stack recursively
void PrintStack(stack<string> s)
{
    if (s.empty())
        return;
    string x = s.top();
    s.pop();
    PrintStack(s);
    cout << x << " ";
    s.push(x);
}

string check_const(string in_str)
{
    // variables
    stack<string> my_stack;
    int error_num = 0;
    int len_in = in_str.length();
    string out_str = "";
    bool get_data = true;
    int index_in = 0;
    string curr_char;

    int start_of_tag = 0;
    int end_of_tag = 0;
    int start_of_prev = 0;
    int end_of_prev = 0;
    // string prev_tag = "";
    string tag = "";
    string data_between = "";
    string data_between_modified = "";

    // main loop
    while (get_data)
    {
        curr_char = in_str[index_in];
        // search for tags and append them to out_str based on several conditions
        if (curr_char == "<")
        {

            start_of_prev = start_of_tag;
            end_of_prev = end_of_tag;
            // prev_tag = in_str.substr(start_of_prev, end_of_prev + 1);
            start_of_tag = index_in;
            end_of_tag = in_str.find(">", start_of_tag);

            data_between = (index_in != 0) ? in_str.substr(end_of_prev + 1, start_of_tag - end_of_prev - 1) : "";
            data_between_modified = remove_extra(data_between);
            tag = in_str.substr(start_of_tag, end_of_tag + 1 - start_of_tag);

            // condition of the tag found
            // 1 >>> if tag is open and no data before
            if (tag[1] != '/' && data_between_modified == "")
            {
                if (!my_stack.empty() && tag == my_stack.top()) // open tag equals the stack top >>> (non closed error)
                {
                    my_stack.pop();
                    my_stack.push(tag);
                    error_num++;
                    // cout << "error:\t" << error_num << "\t non existing closed tag for  " << my_stack.top() << endl; // for error tracing
                    var_detection = "error:\t" + to_string(error_num) + "\t non existing closed tag for  " + my_stack.top() + "\n"; // adding the error line to detection output
                    detection_out.append(var_detection);

                    out_str.append("\n");
                    out_str.append(get_indent(my_stack.size() - 1));
                    out_str.append(close_tag(my_stack.top()));
                    out_str.append("\n");
                    out_str.append(get_indent(my_stack.size() - 1));
                    out_str.append(tag);
                }
                else
                {
                    out_str.append(data_between);
                    out_str.append(tag);
                    my_stack.push(tag);
                }
            }
            // 2 >>> if tag is open and data before
            else if (tag[1] != '/' && data_between_modified != "")
            {
                error_num++;
                // cout << "error:\t" << error_num << "\t non existing closed tag: " << my_stack.top() << data_between_modified << endl; // for error tracing
                var_detection = "error:\t" + to_string(error_num) + "\t non existing closed tag for  " + my_stack.top() + data_between_modified + "\n"; // adding the error line to detection output
                detection_out.append(var_detection);

                out_str.append(data_between.substr(0, data_between.length() - get_indent(my_stack.size() - 1).length() - 1));
                out_str.append(close_tag(my_stack.top()));
                out_str.append("\n");
                out_str.append(get_indent(my_stack.size() - 1));
                // out_str.append(data_between);
                out_str.append(tag);
                my_stack.pop();
                my_stack.push(tag);
            }
            
            
            
            // 3 >>> if tag is close but the stack is empty >>> delete the tag
            else if (tag[1] == '/' && my_stack.empty())
            {
                error_num++;
                var_detection = "error:\t" + to_string(error_num) + "\t closed tag for unopened tag:  " + tag + "\n"; // adding the error line to detection output
                detection_out.append(var_detection);
                //cout << "error:\t" << error_num << "\t closed tag for unopened tag:  " << tag << endl; // for error tracing
                out_str.append(data_between);
            }
            

            // 4 >>> if tag is close and matches the open tag
            else if (tag[1] == '/' && comp_tags(my_stack.top(), tag))
            {
                my_stack.pop();
                out_str.append(data_between);
                out_str.append(tag);
            }

            // 5 >>> if tag is close and does not match the open tag but matches open tag on lower level
            else if (tag[1] == '/' && tag_in_stack(tag, my_stack))
            {
                int level_of_stack = my_stack.size() - 1;
                out_str.append(data_between_modified);
                while (!comp_tags(my_stack.top(), tag))
                {
                    error_num++;
                    // cout << "error:\t" << error_num << "\t non existing closed tag for  " << my_stack.top() << endl; // for error tracing
                    var_detection = "error:\t" + to_string(error_num) + "\t non existing closed tag for  " + my_stack.top() + "\n"; // adding the error line to detection output
                    detection_out.append(var_detection);

                    out_str.append("\n");                       // add new line
                    out_str.append(get_indent(level_of_stack)); // indent the next line properly
                    out_str.append(close_tag(my_stack.top()));
                    my_stack.pop();
                    level_of_stack--;
                }
                // out_str.append(data_between);
                out_str.append("\n");
                out_str.append(get_indent(level_of_stack));
                out_str.append(tag);
                my_stack.pop();
            }

            // 6  >>> close tag &&does not match the open tag nor open tags on lower levels >> (correct the closed tag)
            else if (tag[1] == '/' && !(tag_in_stack(tag, my_stack)))
            {
                error_num++;
                //  cout << "error:\t" << error_num << "\t badly closed tag for  " << my_stack.top() << endl; // for error tracing
                var_detection = "error:\t" + to_string(error_num) + "\t badly closed tag for  " + my_stack.top() + "\n"; // adding the error line to detection output
                detection_out.append(var_detection);

                out_str.append(data_between);
                out_str.append(close_tag(my_stack.top()));
                my_stack.pop();
            }

            // for stack tracing
            // cout << (my_stack.size());
            // PrintStack(my_stack);
            // cout << ("\n");
            index_in = end_of_tag + 1;
        }
        else
        {
            index_in++;
        }
        if (index_in == len_in)
        {

            get_data = false;
        }
    }
    // 7 >>> when the stack is not empty in the end
    while (!my_stack.empty())
    {
        error_num++;
        // cout << "error:\t" << error_num << "\t non existing closed tag for  " << my_stack.top() << endl; // for error tracing
        var_detection = "error:\t" + to_string(error_num) + "\t non existing closed tag for  " + my_stack.top() + "\n"; // adding the error line to detection output
        detection_out.append(var_detection);

        out_str.append("\n");
        out_str.append(get_indent(my_stack.size() - 1));
        out_str.append(close_tag(my_stack.top()));
        my_stack.pop();
    }

    if (error_num == 0)
    {    detection_out.append("\t  \tNO ERRORS WERE FOUND IN YOUR FILE \n");
        //cout << "NO ERRORS WERE FOUND IN YOUR FILE" << endl;
    }
    return out_str;
}

void correct()
{
    // clear the file
    std::ofstream ofs;
    ofs.open("OUTPUT_FILES/Consistency_output.xml", std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    ofstream out_file("OUTPUT_FILES/Consistency_output.xml");

    out_file << check_const(error);
}
