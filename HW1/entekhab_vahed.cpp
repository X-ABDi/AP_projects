#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct course 
{
    string course_name;
    string course_unit;
};

struct presented_course : course
{
    vector<string> prerequisites;
};

struct taken_course : course
{
    string grade;
};

int main()
{
    

}