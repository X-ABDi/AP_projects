#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct train {

    string name;
    string source;
    string destination;
    string time;
    string remaining_capacity;
};
struct request {
    string source;
    string destination;
    string first_time_possible;
    string traveller_count;
} ;

void getInput(vector<train*> &trains, vector<request*> &requests);
// void processInput(vector<train*> &trains, vector<request*> &requests,vector<train*> &available_trains);
// void monitorOutput(vector<train*> &available_trains);

int main()
{
    vector<train*> trains;
    vector<request*> requests; 
    vector<train*> available_trains;
    cout << "before getinput" << endl;
    getInput(trains , requests);

    // processInput(trains, requests, available_trains);
    // monitorOutput(available_trains);
    

    return 0;
}

void fillingTrains (int trains_num ,vector<train*> &trains) {
    int i{0};
    string line;
    stringstream in_line;
    cout << "inside filling train" << endl;
    for(i=0 ; i<trains_num ; i++) {
        getline (cin , line);
        in_line << line;
        train* T = new train;
        in_line >> T->name >> T->source >> T->destination >> T->time >> T->remaining_capacity;
        trains.push_back(T);
    }
    cout << "it should print the vector of trains!!" << endl;
    for(i=0 ; i<trains_num ; i++) {
        cout << trains[i]->name << endl;
    }
}

void fillingRequests (int requests_num, vector<request*> &requests){
    int i{0};
    string line;
    stringstream in_line;
    for(i=0 ; i<requests_num ; i++) {
        getline (cin , line);
        in_line << line;
        request* R = new request;
        in_line >> R->source >> R->destination >> R->first_time_possible >> R->traveller_count;
        requests.push_back(R);
    }

    for(i=0 ; i<requests_num ; i++) {
        cout << requests[i]->source << endl;
    }
}

void getInput(vector<train*> &trains, vector<request*> &requests)
{
    int trains_num{0};
    int requests_num{0};
    cout << "inside getinput" << endl;
    cin >> trains_num >> requests_num;
    cout << "before filling stuff" << endl;
    fillingTrains (trains_num , trains);
    fillingRequests (requests_num, requests);
}

// void processInput(vector<train> &trains, vector<request> &requests,vector<train> &available_trains) {

// }

// void monitorOutput(vector<train> &available_trains){
 
// }