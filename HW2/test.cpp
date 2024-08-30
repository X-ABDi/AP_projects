#include <iostream>
#include <vector>

using namespace std;

struct input
{
    string name;
};

int main()
{
    vector<input *> test_vec;
    input in1;
    in1.name = "fati";
    input in2;
    in2.name = "mati";
    test_vec.push_back(&in1);
    test_vec.push_back(&in2);

    vector<input *>::iterator it;
    it = test_vec.begin()+1;
    *it->name;
}