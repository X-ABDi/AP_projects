#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>

#define NEW_CATEGORY "new_category"
#define ADD_EXPENSE "add_expense"
#define REMOVE_EXPENSE "remove_expense"
#define REPORT "report"
#define ADD 1
#define REMOVE 2

using namespace std;

struct sub_category
{
    std::string name;
    std::vector<int> expenses;
    int total_expense;

    bool operator<(const sub_category &sub_cat)
    {
        if (this->total_expense == sub_cat.total_expense)
        {
            return this->name < sub_cat.name;
        }
        return this->total_expense > sub_cat.total_expense;
    }
};

void run();

int main()
{
    run();
}

void identifyRequest(map <string, vector<sub_category>> &categories, stringstream &line_to_parse);

void run()
{
    map <string, vector<sub_category>> categories;
    std::string line;
    stringstream line_to_parse;
    while (getline(std::cin, line))
    {
        line_to_parse = stringstream();
        line_to_parse << line;
        identifyRequest(categories, line_to_parse);
    }
}

void newCategory(map <string, vector<sub_category>> &categories, stringstream &line_to_parse);
void addExpense(map <string, vector<sub_category>> &categories, stringstream &line_to_parse);
void removeExpense(map <string, vector<sub_category>> &categories, stringstream &line_to_parse);
void report(map <string, vector<sub_category>> &categories, stringstream &line_to_parse);

void identifyRequest(map <string, vector<sub_category>> &categories, stringstream &line_to_parse)
{
    string type_of_request;
    line_to_parse >> type_of_request;
    if (type_of_request == NEW_CATEGORY)
    {
        newCategory(categories, line_to_parse);
    }
    else if (type_of_request == ADD_EXPENSE)
    {
        addExpense(categories, line_to_parse);
    }
    else if (type_of_request == REMOVE_EXPENSE)
    {
        removeExpense(categories, line_to_parse);
    }
    else if (type_of_request == REPORT)
    {
        report(categories, line_to_parse);
    }
}

void newCategory(map <string, vector<sub_category>> &categories, stringstream &line_to_parse)
{
    string category_name;
    line_to_parse >> category_name;
    categories[category_name];

    string sub_category_name;
    while (line_to_parse >> sub_category_name)
    {
        sub_category new_sub_category;
        new_sub_category.name = sub_category_name;
        new_sub_category.total_expense = 0;
        categories[category_name].push_back(new_sub_category);
    }
}

void parseCatSubcatName(string *directory, string *cat_name);
void aboutExpenses(map <string, vector<sub_category>> &categories, stringstream &line_to_parse, int type);

void addExpense(map <string, vector<sub_category>> &categories, stringstream &line_to_parse)
{
    aboutExpenses(categories, line_to_parse, ADD);
}

void removeExpense(map <string, vector<sub_category>> &categories, stringstream &line_to_parse)
{
    aboutExpenses(categories, line_to_parse, REMOVE);
}

void parseCatSubcatName(string *directory, string *cat_name)
{
    size_t pos = (*directory).find('/');
    *cat_name = (*directory).substr(0, pos);
    (*directory) = (*directory).substr(pos + 1);
}

void aboutExpenses(map <string, vector<sub_category>> &categories, stringstream &line_to_parse, int type)
{
    string sub_cat_name;
    string cat_name;
    line_to_parse >> sub_cat_name;
    parseCatSubcatName(&sub_cat_name, &cat_name);
    vector<sub_category>::iterator sub_cat_it;
    for (sub_cat_it = categories[cat_name].begin(); sub_cat_it != categories[cat_name].end(); sub_cat_it++)
    {
        if (sub_cat_it->name == sub_cat_name)
        {
            if (type == ADD)
            {
                int new_expense{0};
                line_to_parse >> new_expense;
                sub_cat_it->expenses.push_back(new_expense);
                sub_cat_it->total_expense += new_expense;
            }
            else if (type == REMOVE)
            {
                if (sub_cat_it->expenses.size() != 0)
                {
                    sub_cat_it->total_expense -= sub_cat_it->expenses.back();
                    sub_cat_it->expenses.pop_back();
                }
            }
        }
    }
}

void sortingVectors(map <string, vector<sub_category>> &categories);
int totalExpense(vector<sub_category> expenses);

void report(map <string, vector<sub_category>> &categories, stringstream &line_to_parse)
{
    sortingVectors(categories);
    string threshold{""};
    int Threshold;
    line_to_parse >> threshold;
    if (threshold == "")
    {
        Threshold = 0;
    }
    else
    {
        Threshold = stoi(threshold);
    }

    if (categories.begin() == categories.end())
    {
        cout << endl;
    }

    map <string, vector<sub_category>>::iterator cat_it;

    for (cat_it = categories.begin(); cat_it != categories.end(); cat_it++)
    {
        cout << "Category: " << cat_it->first << endl;
        cout << "Total expenses: " << totalExpense(cat_it->second) << endl;
        cout << "Subcategories expenses:" << endl;

        for (int i = 0; i < cat_it->second.size(); i++)
        {
            if(cat_it->second[i].total_expense >= Threshold)
            {
                cout << "    - " << cat_it->second[i].name << ": " << cat_it->second[i].total_expense << endl;
            }
        }
        if (cat_it == categories.end()--)
        {
            cout << "**********" << endl;
        }
        else
        {
            cout << "----------" << endl;
        }
    }
}

void sortingVectors(map <string, vector<sub_category>> &categories)
{
    map <string, vector<sub_category>> :: iterator map_it;
    for (map_it = categories.begin(); map_it != categories.end(); map_it++)
    {
        sort(map_it->second.begin(), map_it->second.end());
    }
}

int totalExpense(vector<sub_category> expenses)
{
    int total_expense{0};
    vector<sub_category> :: iterator it;
    for (it = expenses.begin(); it != expenses.end(); it++)
    {
        total_expense += it->total_expense;
    }
    return total_expense;
}


