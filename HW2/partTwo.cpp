#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct input
{
    int line;
    string name;
    int father_line;
    int children_count;
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
    processData(data);
    cout << "after process data" << endl;
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
        for (int j = i+1; j < data.size(); j++)
        {
            if (data[i]->line == data[j]->father_line)
            {
                data[i]->children_count++;
            }
        }
    }
}

void printSubLine(vector<input *> &data, int index, int sub_index)
{

    if (sub_index == data[index]->father_line)
    {
        // cout << "when sub line should return" << endl;
        cout << "|__";
        return;
    }
    else
    {
        // cout << "in every sub line else" << endl;
        if (data[sub_index]->children_count != 0)
        {
            cout << "|  ";
            data[sub_index]->children_count--;
        }
        else
        {
            cout << "   ";
        }
        // cout << "sub_index: " << sub_index << endl;
        printSubLine(data, index, sub_index+1);
    }
}

void printDirectory(vector<input *> &data, int depth, int index)
{
    if (index == data.size())
    {
        // cout << "last return in print directory" << endl;
        return;
    }
    else
    {
        // cout << "in print directory. index: " << index << "and before sub line" << endl;
        int sub_index{0};
        printSubLine(data, index, sub_index);
        cout << data[index]->name << endl;
        printDirectory(data, depth, index+1);
    }
}

void free(vector<input *> &data)
{
    for (auto i : data)
    {
        delete i;
    }
}