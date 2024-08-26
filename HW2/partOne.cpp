#include <iostream>
#include <cmath>

using namespace std;

int processInput(long num);

int main()
{
    long num{0};
    cin >> num;
    long out_put{processInput(num)};
    cout << out_put << endl;

    return 0;
}

int calculateDigits(long num)
{
    int digit{0};
    while (num != 0)
    {
        num = num / 10;
        digit++;
    }
    return digit;
}

long makeNumByOnes(int digit)
{
    long new_num{0};
    while (digit != 0)
    {
        new_num += 1 * pow(10, digit - 1);
        digit--;
    }
    return new_num;
}

int processInput(long num)
{
    cout << "in process input" << endl;
    if (num == 0)
    {
        return 0;
    }
    else
    {
        int digit{calculateDigits(num)};
        long num_made_by_one{makeNumByOnes(digit)};
        long diff{abs(num_made_by_one - num)};

        return digit + processInput(diff);
    }
}
