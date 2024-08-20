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

void getInput(vector<presented_course *> &presented_courses, vector<taken_course *> &taken_courses, vector<presented_course *> &requests);
vector<string> processInput(vector<presented_course *> &presented_courses, vector<taken_course *> &taken_courses, vector<presented_course *> &requests);
void monitorOutput(vector<string> &response);
void free(vector<presented_course *> &presented_courses, vector<taken_course *> &taken_courses, vector<presented_course *> &requests);

int main()
{
    vector<presented_course *> presented_courses;
    vector<taken_course *> taken_courses;
    vector<presented_course *> requests;
    vector<string> response;

    getInput(presented_courses, taken_courses, requests);
    response = processInput(presented_courses, taken_courses, requests);
    monitorOutput(response);
    // DEBUG
    int i{0};int vec_size = requests.size();
    // for (i = 0; i < vec_size; i++)
    // {
    //     cout << requests[i] << endl;
    // }
    free(presented_courses, taken_courses, requests);
    return 0;
}

//+++++++GETTING INPUT++++++++

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

void fillingRequests(vector<presented_course *> &requests)
{
    int i{0};
    int req_num;
    cin >> req_num;
    cin.ignore();

    for (i = 0; i < req_num; i++)
    {
        presented_course *request_crs = new presented_course;
        cin >> request_crs->course_name;
        requests.push_back(request_crs);
    }
}

void getInput(vector<presented_course *> &presented_courses, vector<taken_course *> &taken_courses, vector<presented_course *> &requests)
{
    fillingPresentedCrs(presented_courses);
    fillingTakenCrs(taken_courses);
    fillingRequests(requests);
}

//++++PROCESSING INPUT++++++++++

float caculateAvrage(vector<taken_course *> &taken_courses)
{
    int vec_size{taken_courses.size()};
    int i{0};
    float weighted_sum{0};
    int unit_sum{0};

    for (i = 0; i < vec_size; i++)
    {
        weighted_sum += stoi(taken_courses[i]->course_unit) * stof(taken_courses[i]->grade);
        unit_sum += stoi(taken_courses[i]->course_unit);
    }

    return weighted_sum / unit_sum;
}

int maxUnit(float average)
{
    int max_unit_val{0};
    if (average < 12)
    {
        max_unit_val = 14;
    }
    else if (average >= 12 && average < 17)
    {
        max_unit_val = 20;
    }
    else
    {
        max_unit_val = 24;
    }
    return max_unit_val;
}

bool isPresented(vector<presented_course *> &presented_courses, vector<presented_course *> &requests)
{
    int count{0};
    for (auto i : requests)
    {
        count = 0;
        for (auto j : presented_courses)
        {
            if (i->course_name == j->course_name)
            {
                i->course_unit = j->course_unit;
                i->prerequisites = j->prerequisites;
                count++;
            }
        }
        if (count == 0)
        {
            return false;
        }
    }
    return true;
}

int totalRequestedUnits(vector<presented_course *> &requests)
{
    int unit_sum{0};
    for (auto i : requests)
    {
        unit_sum += stoi(i->course_unit);
    }
    return unit_sum;
}

bool requestTakenBefore(vector<presented_course *> &requests, vector<taken_course *> &taken_courses)
{
    for (auto i : requests)
    {
        for (auto j : taken_courses)
        {
            if (i->course_name == j->course_name)
            {
                return true;
            }
        }
    }
    return false;
}

bool prerequisityMeet(vector<presented_course *> &requests, vector<presented_course *> &presented_courses, vector<taken_course *> taken_courses)
{
    int count{0};
    for (auto i : requests)
    {
        for (auto j : i->prerequisites)
        {
            count = 0;
            for (auto k : taken_courses)
            {
                if (j == k->course_name)
                {
                    count++;
                }
            }
            if(count == 0)
            {
                return false;
            }
        }
    }
    return true;
}

vector<string> processInput(vector<presented_course *> &presented_courses, vector<taken_course *> &taken_courses, vector<presented_course *> &requests)
{
    vector<string> response;
    bool is_presented{isPresented(presented_courses, requests)};
    if (!is_presented)
    {
        response.push_back("Course Not Offered!");
    }

    int total_req_unit{totalRequestedUnits(requests)};
    int min_unit_val{12};
    float average{caculateAvrage(taken_courses)};
    int max_unit_val{maxUnit(average)};
    if (total_req_unit >= max_unit_val)
    {
        response.push_back("Maximum Units Validation Failed!");
    }
    if (total_req_unit <= min_unit_val)
    {
        response.push_back("Minimum Units Validation Failed!");
    }

    bool request_taken_before{requestTakenBefore(requests, taken_courses)};
    if (request_taken_before)
    {
        response.push_back("Course Already Taken!");
    }

    bool prerequisity_meet{prerequisityMeet(requests, presented_courses, taken_courses)};
    if (is_presented && !prerequisity_meet)
    {
        response.push_back("Prerequisites Not Met!");
    }

    return response;
}

//+++++MONITORING OUTPUT++++++++

void monitorOutput (vector<string> &response)
{
    if (response.size() == 0)
    {
        cout << "Ok!" << endl;
    }
    else
    {
        for (auto i : response)
        {
            cout << i << endl;
        }
    }
}

//++++FREE+++++

void free(vector<presented_course *> &presented_courses, vector<taken_course *> &taken_courses, vector<presented_course *> &requests)
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

    vector_size = requests.size();
    for (i = 0; i<vector_size; i++)
    {
        delete requests[i];
    }
}
