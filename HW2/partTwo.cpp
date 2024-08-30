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
// void printSubDirectory(vector<input *> &data, vector<input *>::iterator main_iterator);
void free(vector<input *> &data);

int main()
{
    vector<input *> data;
    int depth{getInput(data)};
    cout << "before process data" << endl;
    // for (int i = 0; i < data.size(); i++)
    // {
    //     cout << data[i]->line << endl;
    // }
    processData(data);
    cout << "after process data" << endl;
    // for (int i = 0; i < data.size(); i++)
    // {
    //     cout << data[i]->children_count << endl;
    // }
    cout << endl;
    // for (int i = 0; i < data.size(); i++)
    // {
    //     cout << data[i]->depth << endl;
    // }
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
        data.push_back(new_input);
    }

    return depth;
}

void processData(vector<input *> &data)
{
    cout << "inside process data" << endl;
    for (int i = 0; i < data.size(); i++)
    {
        for (int j = i + 1; j < data.size(); j++)
        {
            if (data[i]->line == data[j]->father_line)
            {
                data[i]->children_count++;
            }
        }
    }

    for (int i = 0; i < data.size(); i++)
    {
        if (data[i]->line == 1)
        {
            // cout << "if" << endl;
            // cout << i << " " << data[i]->line << " ";
            data[i]->depth == 1;
            // cout << data[i]->depth << endl;
        }
        else
        {
            for (int j = 0; j < i; j++)
            {
                if (data[i]->father_line == data[j]->line)
                {
                    // cout << "else" << endl;
                    // cout << i << " " << data[i]->line << " ";
                    data[i]->depth = data[j]->depth + 1;
                    // cout << data[i]->depth << endl;
                }
            }
        }
    }
}

void printSubLine(vector<input *> &data, int index, int sub_index)
{
    // cout << "print subline" << endl;
    // cout << "\n sub_index: " << sub_index << "  data[index]->depth: " << data[index]->depth << endl;
    if (sub_index == data[index]->depth)
    {
        cout << "|__";
        return;
    }
    else
    {
        // cout << "print subline in else section" << endl;
        if (data[sub_index]->children_count > 0)
        {
            // cout << "children count: " << data[sub_index]->children_count << endl;
            cout << "|  " ;
        }
        else
        {
            cout << "   ";
        }
        printSubLine(data, index, sub_index + 1);
    }
}

void printDirectory(vector<input *> &data, int depth, int index)
{
    // cout << "print directory" << endl;
    if (index == data.size())
    {
        return;
    }
    else
    {
        // cout << "print directory in else section" << endl;
        int sub_index{0};
        printSubLine(data, index, sub_index);
        cout << data[index]->name << endl;
        for (int i = 0; i < data.size(); i++)
        {
            if (data[index]->father_line == data[i]->line)
            {
                data[i]->children_count--;
            }
        }
        printDirectory(data, depth, index + 1);
    }
}

void free(vector<input *> &data)
{
    for (auto i : data)
    {
        delete i;
    }
}