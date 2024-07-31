#include <iostream>
#include <string>
#include <vector>

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

void getInput(vector<train> &trains, vector<request> &requests);

int main()
{
    vector<train> trains;
    vector<request> requests; 
    getInput(trains , requests);

    return 0;
}

void filling_trains (int trains_num ,vector<train> &trains) {
    int i{0};
    string line;
    
    for(i=0 ; i<trains_num ; i++) {
        getline (cin , line);
        train* T = new train;

    }
}

void getInput(vector<train> &trains, vector<request> &requests)
{
    int trains_num{0};
    int requests_num{0};

    cin >> trains_num >> requests_num;

    filling_trains (trains_num , trains);
}