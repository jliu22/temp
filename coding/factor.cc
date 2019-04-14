/**
find factorization of a number
for example: 6 has factorization 1*6, 2*3, these 6*1, 3*2 considered as duplicate
**/

#include <iostream>
#include <set>
#include <vector>

using namespace std;

void helper(int origin, 
    set<int> const& factors, int num, int multi, vector<int> path, vector<vector<int>>& rst)
{
    if(num < *factors.begin()) {
        return;
    }

    for(auto it = factors.begin(); it != factors.end(); ++it) {
        int item = *it;
        if(!path.empty() && item < path.back()) continue;        

        if(item * multi == origin) {
            path.push_back(item);
            rst.push_back(path);
            return;
        }
        path.push_back(item);
        helper(origin, factors, num/item, multi*item, path, rst);
        path.pop_back();
    }
}


int main()
{

    int number, temp = 1;

    cout << "Enter the number to determine its factors : " << endl;

    cin >> number;

    cout << "The factors of " << number << " are : " << endl;

    set<int> factors;
    while (temp <= number/2)
    {
        if (not(number % temp)) {
            cout << temp << " ";
            factors.insert(temp);
        }
        temp++;
    }
    cout << endl << endl << endl;

    vector<int> path;
    vector<vector<int>> rst;
    factors.erase(1);
    vector<int> t = {1, number};
    rst.push_back(t);
    helper(number, factors, number, 1, path, rst);
    for(auto i : rst) {
        for(auto j : i) {
          cout << j << " ";
        }
        cout << endl;
    }

    return 0;
}


/*
How to build:
$ g++ -std=c++11 factor.cc -o factor
How to run:
$ ./factor
Test result:

Enter the number to determine its factors : 
100
The factors of 100 are : 
1 2 4 5 10 20 25 50 


1 100 
2 2 5 5 
2 2 25 
2 5 10 
2 50 
4 5 5 
4 25 
5 20 
10 10 

*/
