#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct train
{

    string name;
    string source;
    string destination;
    string time;
    string remaining_capacity;
};
struct request
{
    string source;
    string destination;
    string first_time_possible;
    string traveller_count;
};

void getInput(vector<train *> &trains, vector<request *> &requests);
void processInput(vector<train *> &trains, vector<request *> &requests, vector<vector<train *>> &available_trains);
void monitorOutput(vector<vector<train *>> &available_trains, vector<request *> &requests);
void freeVectors(vector<train *> &trains, vector<request *> &requests, vector<vector<train *>> &available_trains);

int main()
{
    vector<train *> trains;
    vector<request *> requests;
    vector<vector<train *>> available_trains;

    getInput(trains, requests);

    processInput(trains, requests, available_trains);
    monitorOutput(available_trains, requests);
    freeVectors(trains, requests, available_trains);

    return 0;
}

void fillingTrains(int trains_num, vector<train *> &trains)
{
    int i{0};
    string line;
    stringstream in_line;
    cin.ignore();
    for (i = 0; i < trains_num; i++)
    {
        getline(cin, line);

        in_line = stringstream();
        in_line << line;
        train *T = new train;
        in_line >> T->name >> T->source >> T->destination >> T->time >> T->remaining_capacity;
        trains.push_back(T);
    }
}

void fillingRequests(int requests_num, vector<request *> &requests)
{
    int i{0};
    string line;
    stringstream in_line;
    for (i = 0; i < requests_num; i++)
    {
        getline(cin, line);
        in_line = stringstream();
        in_line << line;
        request *R = new request;
        in_line >> R->source >> R->destination >> R->first_time_possible >> R->traveller_count;
        requests.push_back(R);
    }
}

void getInput(vector<train *> &trains, vector<request *> &requests)
{
    int trains_num{0};
    int requests_num{0};
    cin >> trains_num >> requests_num;
    fillingTrains(trains_num, trains);
    fillingRequests(requests_num, requests);
}

bool checkTime(request *user_request, train *poss_train)
{
    string req_hour, train_hour;
    string req_min, train_min;
    req_hour = user_request->first_time_possible.substr(0, 2);
    req_min = user_request->first_time_possible.substr(3, 2);
    train_hour = poss_train->time.substr(0, 2);
    train_min = poss_train->time.substr(3, 2);

    if (req_hour < train_hour)
    {
        return true;
    }
    else if (req_hour == train_hour)
    {
        if (req_min <= train_min)
        {
            return true;
        }
        else
            return false;
    }
    else
        return false;
}

bool checkCapacity(request *user_request, train *poss_train)
{
    if (stoi(user_request->traveller_count) <= stoi(poss_train->remaining_capacity))
    {
        return true;
    }
    else
        return false;
}

void processInput(vector<train *> &trains, vector<request *> &requests, vector<vector<train *>> &available_trains)
{
    for (request *i : requests)
    {
        vector<train *> same_des_trains;
        for (train *j : trains)
        {
            if (i->source == j->source)
            {
                if (i->destination == j->destination)
                {
                    if (checkTime(i, j))
                    {
                        if (checkCapacity(i, j))
                        {
                            train *T = new train;
                            T->source = j->source;
                            T->destination = j->destination;
                            T->name = j->name;
                            T->time = j->time;
                            T->remaining_capacity = j->remaining_capacity;
                            j->remaining_capacity = to_string(stoi(j->remaining_capacity) - stoi(i->traveller_count));
                            same_des_trains.push_back(T);
                        }
                    }
                }
            }
        }
        available_trains.push_back(same_des_trains);
    }
}

void monitorOutput(vector<vector<train *>> &available_trains, vector<request *> &requests)
{
    for (auto i : available_trains)
    {
        for (auto j : i)
        {
            cout << j->name << endl;
        }
        if (i != available_trains.back())
        {
            cout << "----------" << endl;
        }
    }
}
void freeVectors(vector<train *> &trains, vector<request *> &requests, vector<vector<train *>> &available_trains)
{
    for (auto i : trains)
    {
        delete i;
    }

    for (auto i : requests)
    {
        delete i;
    }

    for (auto i : available_trains)
    {
        for (auto j : i)
        {
            delete j;
        }
    }
}