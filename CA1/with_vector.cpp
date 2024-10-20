#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

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

struct category
{
    string name;
    vector<sub_category> sub_categories;
    int total_expense;
};

void run();

int main()
{
    run();
}

void identifyRequest(vector<category *> &categories, stringstream &line_to_parse);
void free(vector<category *> &categories);

void run()
{
    std::vector<category *> categories;
    std::string line;
    stringstream line_to_parse;
    while (getline(std::cin, line))
    {
        line_to_parse = stringstream();
        line_to_parse << line;
        identifyRequest(categories, line_to_parse);
    }
    free(categories);
}

void free(vector<category *> &categories)
{
    for (auto i : categories)
    {
        delete i;
    }
}

void newCategory(vector<category *> &categories, stringstream &line_to_parse);
void addExpense(vector<category *> &categories, stringstream &line_to_parse);
void removeExpense(vector<category *> &categories, stringstream &line_to_parse);
void report(vector<category *> &categories, stringstream &line_to_parse);

void identifyRequest(vector<category *> &categories, stringstream &line_to_parse)
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

void newCategory(vector<category *> &categories, stringstream &line_to_parse)
{
    category *new_category = new category;
    line_to_parse >> new_category->name;
    new_category->total_expense = 0;
    string sub_category_name;
    while (line_to_parse >> sub_category_name)
    {
        sub_category new_sub_category;
        new_sub_category.name = sub_category_name;
        new_sub_category.total_expense = 0;
        new_category->sub_categories.push_back(new_sub_category);
    }
    categories.push_back(new_category);
}

void parseCatSubcatName(string *directory, string *cat_name);
void aboutExpenses(vector<category *> &categories, stringstream &line_to_parse, int type);

void addExpense(vector<category *> &categories, stringstream &line_to_parse)
{
    aboutExpenses(categories, line_to_parse, ADD);
}

void removeExpense(vector<category *> &categories, stringstream &line_to_parse)
{
    aboutExpenses(categories, line_to_parse, REMOVE);
}

void parseCatSubcatName(string *directory, string *cat_name)
{
    size_t pos = (*directory).find('/');
    *cat_name = (*directory).substr(0, pos);
    (*directory) = (*directory).substr(pos + 1);
}

void aboutExpenses(vector<category *> &categories, stringstream &line_to_parse, int type)
{
    string directory;
    string cat_name;
    line_to_parse >> directory;
    parseCatSubcatName(&directory, &cat_name);

    vector<category *>::iterator cat_it;
    for (cat_it = categories.begin(); cat_it != categories.end(); cat_it++)
    {
        if ((*cat_it)->name == cat_name)
        {
            size_t sub_cat_size{(*cat_it)->sub_categories.size()};
            for (int i = 0; i < sub_cat_size; i++)
            {
                if ((*cat_it)->sub_categories[i].name == directory)
                {
                    if (type == ADD)
                    {
                        int new_expense;
                        line_to_parse >> new_expense;
                        (*cat_it)->sub_categories[i].expenses.push_back(new_expense);
                        (*cat_it)->sub_categories[i].total_expense += new_expense;
                        (*cat_it)->total_expense += new_expense;
                    }
                    else if (type == REMOVE)
                    {
                        (*cat_it)->sub_categories[i].total_expense -= (*cat_it)->sub_categories[i].expenses.back();
                        (*cat_it)->total_expense -= (*cat_it)->sub_categories[i].expenses.back();
                        (*cat_it)->sub_categories[i].expenses.pop_back();
                    }
                }
            }
        }
    }
}

void sortingVectors(vector<category *> &categories);

void report(vector<category *> &categories, stringstream &line_to_parse)
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

    // cout << "threshold: " << Threshold << endl;

    if (categories.begin() == categories.end())
    {
        cout << endl;
    }

    vector<category *>::iterator cat_it;

    for (cat_it = categories.begin(); cat_it != categories.end(); cat_it++)
    {
        cout << "Category: " << (*cat_it)->name << endl;
        cout << "Total expenses: " << (*cat_it)->total_expense << endl;
        cout << "Subcategories expenses:" << endl;

        for (int i = 0; i < (*cat_it)->sub_categories.size(); i++)
        {
            if((*cat_it)->sub_categories[i].total_expense >= Threshold)
            {
                cout << "    - " << (*cat_it)->sub_categories[i].name << ": " << (*cat_it)->sub_categories[i].total_expense << endl;
            }
        }
        if (cat_it == categories.end() - 1)
        {
            cout << "**********" << endl;
        }
        else
        {
            cout << "----------" << endl;
        }
    }
}

void sortingVectors(vector<category *> &categories)
{
    for (int i = 0; i < categories.size(); i++)
    {
        sort(categories[i]->sub_categories.begin(), categories[i]->sub_categories.end());
    }
    sort(categories.begin(), categories.end(), [](category *cat1,category *cat2){return cat1->name < cat2->name;});
}

