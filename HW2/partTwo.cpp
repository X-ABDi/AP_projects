#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct input
{
    string name;
    int line;
    int father_line;
    int children_count;
    int depth;
};

int getInput(vector<input *> &data);
void processData(vector<input *> &data);
void printDirectory(vector<input *> &data, int depth, int index);
void free(vector<input *> &data);

int main()
{
    vector<input *> data;
    int depth{getInput(data)};

    processData(data);

    // DEBUG
    // for (int i = 0; i < data.size(); i++)
    // {
    //     cout << "children count: " << data[i]->children_count << "  father line: " << data[i]->father_line << endl;
    // }
    // cout << endl;
    // for (int i = 0; i < data.size(); i++)
    // {
    //     cout << data[i]->depth << endl;
    // }
    // DEBUG

    int index{0};
    printDirectory(data, depth, index);
    free(data);
}

int getInput(vector<input *> &data)
{
    int depth{0};
    int line_count;
    cin >> line_count >> depth;
    cin.ignore();

    string line;
    stringstream line_stream;
    int i{0};
    for (i = 0; i < line_count; i++)
    {
        getline(cin, line);
        line_stream = stringstream();
        line_stream << line;
        input *new_input = new input;

        new_input->children_count = 0;
        new_input->line = i + 1;
        line_stream >> new_input->name >> new_input->father_line;
        new_input->father_line = new_input->father_line;
        data.push_back(new_input);
    }

    return depth;
}

void processData(vector<input *> &data)
{
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = i + 1; j < data.size(); j++)
        {
            if (data[i]->line == data[j]->father_line)
            {
                data[i]->children_count = data[i]->children_count + 1;
            }
        }
    }

    for (int i = 0; i < data.size(); i++)
    {
        if (data[i]->father_line == 0)
        {
            data[i]->depth = 1;
        }
        else
        {
            for (int j = 0; j < i; j++)
            {
                if (data[i]->father_line == data[j]->line)
                {
                    data[i]->depth = data[j]->depth + 1;
                }
            }
        }
    }
}

void printLine(vector<input *> &data, int index, int sub_index, int standard_depth)
{
    int depth;
    if ((sub_index >= index && index != 0))
    {
        // cout << "sub_index >= index,, index != 0" << endl;
        return;
    }
    if (sub_index == index - 1)
    {
        // cout << "sub_index == index - 1" << endl;
        return;
    }
    
    // if (data[sub_index]->depth == 1)
    // {
    //     cout << "data[sub_index]->depth == 1" << endl;
    //     return;
    // }
    else if (data[sub_index]->depth >= standard_depth || data[sub_index]->depth > data[index]->depth)
    {
        printLine(data, index, sub_index + 1, standard_depth);
    }
    else
    {
        depth = data[sub_index]->depth;
        while (depth == data[sub_index + 1]->depth && sub_index < index) // && data[sub_index]->children_count == 0
        {
            ++sub_index;
        }
        // printLine(data, index, sub_index, standard_depth);
        if (sub_index == index || sub_index == index - 1) // depth == data[sub_index]->depth &&
        {
            return;
        }
        else if (depth != data[sub_index + 1]->depth && sub_index < index && data[sub_index]->children_count > 0)
        {
            cout << "|  ";
            printLine(data, index, sub_index + 1, standard_depth);
        }
        else if (depth != data[sub_index + 1]->depth && sub_index < index && data[sub_index]->children_count == 0)
        {
            cout << "   ";
            printLine(data, index, sub_index + 1, standard_depth);
        }
        // else if (depth != data[sub_index + 1]->depth && sub_index == index)
        // {
        //     cout << "   ";
        //     return;
        // }
    }
}

void printDirectory(vector<input *> &data, int standard_depth, int index)
{
    if (index == data.size())
    {
        return;
    }
    else
    {
        if (data[index]->depth >= standard_depth)
        {
            printDirectory(data, standard_depth, index + 1);
        }
        else
        {
            int sub_index{0};
        // cout << data[index]->depth << endl;
            if (data[index]->depth != 1)
            {
                cout << "   ";
                sub_index = sub_index + 1;
            }
            printLine(data, index, sub_index, standard_depth);
            cout << "|__" << data[index]->name << endl;
            for (int i = 0; i < index; i++)
            {
                if (data[index]->father_line == data[i]->line && data[i]->children_count > 0)
                {
                    data[i]->children_count = data[i]->children_count - 1;
                    break;
                }
            }
            printDirectory(data, standard_depth, index + 1);
        }
    }
}

void free(vector<input *> &data)
{
    for (auto i : data)
    {
        delete i;
    }
}