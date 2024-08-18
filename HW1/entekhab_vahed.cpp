#include <iostream>
#include <string>
#include <sstream>
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

void getInput(vector<presented_course *> &presented_courses, vector<taken_course *> &taken_courses, vector<string> &requests);
vector<string> processInput(vector<presented_course *> &presented_courses, vector<taken_course *> &taken_courses, vector<string> &requests);
void monitorOutput(vector<string> &response);
void free(vector<presented_course *> &presented_courses, vector<taken_course *> &taken_courses);

int main()
{
    vector<presented_course *> presented_courses;
    vector<taken_course *> taken_courses;
    vector<string> requests;
    vector<string> response;

    getInput(presented_courses, taken_courses, requests);
    // response = processInput(presented_courses, taken_courses, requests);
    // monitorOutput(response);
    // DEBUG
    int i{0};
    // for (i = 0; i < presented_courses.size(); i++)
    // {
    //     cout << presented_courses[i]->course_name << " " << presented_courses[i]->course_unit << endl;
    //     int vector_size = presented_courses[i]->prerequisites.size();
    //     for (int j = 0; j < vector_size; j++)
    //     {
    //         cout << presented_courses[i]->prerequisites[j] << endl;
    //     }
    //     cout << '\n'
    //          << endl;
    // }

    // cout << taken_courses.size() << endl;
    // for (i = 0; i < taken_courses.size(); i++)
    // {
    //     cout << taken_courses[i]->course_name << " " << taken_courses[i]->course_unit << " " << taken_courses[i]->grade << endl;
    // }

    // int vec_size = requests.size();
    // for (i = 0; i < vec_size; i++)
    // {
    //     cout << requests[i] << endl;
    // }

    return 0;
}

void fillingPresentedCrs(vector<presented_course *> &presented_courses)
{
    int i{0};
    int pres_crs_num;
    string line;
    stringstream line_stream;

    cin >> pres_crs_num;
    // cout << pres_crs_num << endl;
    cin.ignore();
    for (i = 0; i < pres_crs_num; i++)
    {
        getline(cin, line);
        line_stream = stringstream();
        line_stream << line;
        presented_course *pc = new presented_course;
        line_stream >> pc->course_name;
        line_stream >> pc->course_unit;
        line_stream.ignore();

        string prerequisity;
        while (getline(line_stream, prerequisity, ','))
        {
            pc->prerequisites.push_back(prerequisity);
        }

        presented_courses.push_back(pc);
    }
}

void fillingTakenCrs(vector<taken_course *> &taken_courses)
{
    int i{0};
    int taken_crs_num;
    string line;
    stringstream line_stream;

    cin >> taken_crs_num;
    // cout << taken_crs_num << endl;
    cin.ignore();
    for (i = 0; i < taken_crs_num; i++)
    {
        getline(cin, line);
        line_stream = stringstream();
        line_stream << line;
        taken_course *tc = new taken_course;

        line_stream >> tc->course_name;
        line_stream >> tc->course_unit;
        line_stream >> tc->grade;

        taken_courses.push_back(tc);
    }
}

void fillingRequests(vector<string> &requests)
{
    int i{0};
    string request_crs;
    int req_num;
    cin >> req_num;
    cin.ignore();

    for (i = 0; i < req_num; i++)
    {
        cin >> request_crs;
        requests.push_back(request_crs);
    }
}

void getInput(vector<presented_course *> &presented_courses, vector<taken_course *> &taken_courses, vector<string> &requests)
{
    fillingPresentedCrs(presented_courses);
    fillingTakenCrs(taken_courses);
    fillingRequests(requests);
}

void free(vector<presented_course *> &presented_courses, vector<taken_course *> &taken_courses)
{
    int i;
    int j;
    int vector_size{presented_courses.size()};
    for (i = 0; i < vector_size; i++)
    {
        delete presented_courses[i];
    }

    vector_size = taken_courses.size();
    for (i = 0; i < vector_size; i++)
    {
        delete taken_courses[i];
    }
}
