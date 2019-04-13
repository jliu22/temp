/*
Let's say in a company, A joined at year1, left at year2, for example [2001, 2005].
B was in the company at [2003, 2007].
C was in the company [2006, 2008].
Count each year how many people in the company, return something like
[2001, 2003] 1
[2003, 2005] 2
[2005, 2006] 1
[2006, 2007] 2
[2007, 2008] 1

This was a question some big company asked me, I didn't get a good answer at that time.
When I looked back the 218 The Skyline Problem, I found out this one is quite simple.
We don't need get the maximum (skyline) as in the skyline problem, we just need count sum
assume all height is 1.
*/

#include <vector>
#include <utility>
#include <iostream>
#include <map>

using namespace std;

struct worker
{
    int st;
    int ed;
    int sum;
};

vector<worker> getWorkforce(vector<pair<int, int>> record)
{
    vector<worker> ret;
    multimap<int, int> mmap;

    if(record.empty()) return ret;

    for(auto r : record) {
        mmap.insert(make_pair(r.first, 1));
        mmap.insert(make_pair(r.second, -1));
    }

    int sum = 0;
    vector<pair<int, int>> yearsum;

    while(mmap.size()) {
        int year = mmap.begin()->first;
        while(year ==  mmap.begin()->first) {
            sum += mmap.begin()->second;
            mmap.erase(mmap.begin());
        }
        yearsum.push_back(make_pair(year, sum));
    }
    // convert to ret
    worker w;
    for(int i = 1; i < yearsum.size(); i++) {
        w.st = yearsum[i-1].first;
        w.ed = yearsum[i].first;
        w.sum = yearsum[i-1].second;
        ret.push_back(w);
    }
    return ret;
}

void print(vector<worker> w)
{
    for(auto i : w) {
        cout << "[" << i.st << ", " << i.ed << "] " << i.sum << endl;
    }
    cout << endl;
}

int main()
{
    // borrow skyline problem input for test
    vector<pair<int, int>> record = {{2,9},{3,7},{5,12},{15,20},{19,24}};
    vector<worker> w = getWorkforce(record);
    print(w);

    // use example in description
    vector<pair<int, int>> record2 = {{2001,2005},{2003, 2007},{2003,2007},{2006,2008}};
    w = getWorkforce(record2);
    print(w);

    return 0;
}


/*
How to build:
$ g++ -std=c++11 -o workforce workforce.cc

How to run:
$ ./workforce

Test result:
$ ./workforce 

[3, 5] 1
[5, 7] 2
[7, 9] 3
[9, 12] 2
[12, 15] 1
[15, 19] 0
[19, 20] 1
[20, 24] 2
[24, 32766] 1

[2001, 2003] 1
[2003, 2005] 3
[2005, 2006] 2
[2006, 2007] 3
[2007, 2008] 1

*/
