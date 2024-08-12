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
void processInput(vector<train *> &trains, vector<request *> &requests, vector<train *> &available_trains);
void monitorOutput(vector<train *> &available_trains, vector<request *> &requests);
void freeVectors(vector<train *> &trains, vector<request *> &requests, vector<train *> &available_trains);

int main()
{
    vector<train *> trains;
    vector<request *> requests;
    vector<train *> available_trains;
    // cout << "before getinput" << endl;
    getInput(trains, requests);

    // for (train* i : trains) {
    //     cout << i->name << endl;
    // }
    // for (request* i : requests) {
    //     cout << i->source << endl;
    // }

    processInput(trains, requests, available_trains);
    monitorOutput(available_trains, requests);
    freeVectors(trains, requests, available_trains);

    return 0;
}

void fillingTrains(int trains_num, vector<train *> &trains)
{
    int i{0};
    int count{0}; // DEBUGGING
    string line;
    stringstream in_line;
    // cin.clear();
    // getline(cin , line);
    // cout << line << endl;
    cin.ignore();
    // cout << "inside filling train" << endl; //DEBUGGING
    // cout << "trains_num: " << trains_num << endl;
    for (i = 0; i < trains_num; i++)
    {
        getline(cin, line);

        // cout << line << " " << count << endl; //DEBUGGING
        in_line = stringstream();
        in_line << line;
        train *T = new train;
        in_line >> T->name >> T->source >> T->destination >> T->time >> T->remaining_capacity;
        // cout << T->name << endl;
        // cout << T->source << endl;
        // cout << T->destination << endl;
        // cout << T->time << endl;
        // cout << T->remaining_capacity << endl;
        // cout << "-----------------" << endl;
        trains.push_back(T);
        count++;
    }
    // cout << "it should print the vector of trains!!" << endl;
    // for(i=0 ; i<trains_num ; i++) {
    //     cout << trains[i]->name << endl;
    // }
}

void fillingRequests(int requests_num, vector<request *> &requests)
{
    int i{0};
    string line;
    stringstream in_line;
    // getline(cin,line);
    for (i = 0; i < requests_num; i++)
    {
        getline(cin, line);
        in_line = stringstream();
        in_line << line;
        request *R = new request;
        in_line >> R->source >> R->destination >> R->first_time_possible >> R->traveller_count;
        requests.push_back(R);
    }

    // for(i=0 ; i<requests_num ; i++) {
    //     cout << requests[i]->source << endl;
    // }
}

void getInput(vector<train *> &trains, vector<request *> &requests)
{
    int trains_num{0};
    int requests_num{0};
    // cout << "inside getinput" << endl;
    cin >> trains_num >> requests_num;
    // cout << trains_num << " " << requests_num << endl;
    // cout << "before filling stuff" << endl;

    fillingTrains(trains_num, trains);
    fillingRequests(requests_num, requests);

    // for (train* i : trains) {
    //     cout << i->name << endl;
    // }
    // for (request* i : requests) {
    //     cout << i->source << endl;
    // }
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

void processInput(vector<train *> &trains, vector<request *> &requests, vector<train *> &available_trains)
{
    for (request *i : requests)
    {
        // cout << i->source << " " << i->destination << " " << i->first_time_possible << " " << i->traveller_count << endl;
        for (train *j : trains)
        {
            // cout << j->name << " " << j->source << " " << j->destination << " " << j->time << " " << j->remaining_capacity << endl;
            if (i->source == j->source)
            {
                // cout << "sources match" << endl;
                if (i->destination == j->destination)
                {
                    // cout << "destination match" << endl;
                    if (checkTime(i, j))
                    {
                        // cout << "time match" << endl;
                        if (checkCapacity(i, j))
                        {
                            // cout << "capacity available" << endl;
                            train *T = new train;
                            T->source = j->source;
                            T->destination = j->destination;
                            T->name = j->name;
                            T->time = j->time;
                            T->remaining_capacity = j->remaining_capacity;
                            j->remaining_capacity = to_string(stoi(j->remaining_capacity) - stoi(i->traveller_count));
                            available_trains.push_back(T);
                        }
                    }
                }
            }
        }
    }
}

void monitorOutput(vector<train *> &available_trains, vector<request *> &requests)
{
    // for(train* i : available_trains) {
    //     cout << i->name << " " << i->time << " " << i->remaining_capacity << endl;
    // }
    vector<train *>::iterator i;
    i = available_trains.begin();
    for (request *j : requests)
    {
        while (i != available_trains.end())
        {
            if (j->source == (*i)->source && j->destination == (*i)->destination)
            {
                cout << (*i)->name << " " << (*i)->time << " " << (*i)->remaining_capacity << endl;
                i++;
            }
            else
                break;
        }
        cout << "----------" << endl;
    }
}

void freeVectors(vector<train *> &trains, vector<request *> &requests, vector<train *> &available_trains)
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
        delete i;
    }
}