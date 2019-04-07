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
        sum += mmap.begin()->second;
        yearsum.push_back(make_pair(mmap.begin()->first, sum));
        mmap.erase(mmap.begin());
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
    vector<pair<int, int>> record2 = {{2001,2005},{2003,2007},{2006,2008}};
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
[2, 3] 1
[3, 5] 2
[5, 7] 3
[7, 9] 2
[9, 12] 1
[12, 15] 0
[15, 19] 1
[19, 20] 2
[20, 24] 1

[2001, 2003] 1
[2003, 2005] 2
[2005, 2006] 1
[2006, 2007] 2
[2007, 2008] 1

*/
