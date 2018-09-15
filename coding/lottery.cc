/*
Winning Ticket!

Your favorite uncle, Morty, is crazy about the lottery and even crazier about how he picks his “lucky” numbers. And even though his “never fail” strategy has yet to succeed, Uncle Morty doesn't let that get him down.

Every week he searches through the Sunday newspaper to find a string of digits that might be potential lottery picks. But this week the newspaper has moved to a new electronic format, and instead of a comfortable pile of papers, Uncle Morty receives a text file with the stories.

Help your Uncle find his lotto picks. Given a large series of number strings, return each that might be suitable for a lottery ticket pick. Note that a valid lottery ticket must have 7 unique numbers between 1 and 59, digits must be used in order, and every digit must be used exactly once.

For example, given the following strings:

[ "569815571556", “4938532894754”, “1234567”, “472844278465445”]

Your function should return:

4938532894754 -> 49 38 53 28 9 47 54
1234567 -> 1 2 3 4 5 6 7
*/

#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

const int SEG = 7;

bool isvalid(std::string const& s){
    if(s.empty() || s.size()>2 || (s.size()>1 && s[0]=='0')) return false;
 
    int sum=0;      
    for(int i=0;i<s.size();i++){      
        sum*=10;    
        sum+=s[i]-'0';      
    }    
    return sum>=1&&sum<=59;     
}

void helper(string& s, int start, int count, string path, unordered_set<string>& visited, vector<string>& rst){
    if(count > SEG-1)return;
    if(count == SEG-1 && isvalid(s.substr(start)) && !visited.count(s.substr(start))){
        path.append(s.substr(start));
        rst.push_back(path);
        return;
    }

    for(int i = start; i < s.size() && (i-start)<2; i++){
        string cur = s.substr(start, i-start+1);
        if(isvalid(cur)){
            if(visited.count(cur)) continue;
            visited.insert(cur);
            helper(s, i+1, count+1, path + cur + " ", visited, rst);
            visited.erase(cur);
        }
    }
}

vector<string> restoreNumber(string& s) {
    vector<string> rst;
    unordered_set<string> visited;
    if(s.size() < SEG) return rst;//empty
    string path = "";
    helper(s, 0, 0, path, visited, rst);
    return rst;
}

int main()
{
    vector<string> nums{"569815571556", "4938532894754", "1234567", "472844278465445"};
    vector<string> rst;

    for(int i = 0; i < nums.size(); i++) {
        rst.clear();
        rst = restoreNumber(nums[i]);
        for(int j = 0; j < rst.size(); j++) {
            cout << nums[i] << " -> " << rst[j] << endl;
        }
    }

    return 0;
}



/*
How to build:
$ g++ -std=c++11 -o lottery lottery.cc


How to run:
$ ./lottery

Test result:
$ ./lottery 
4938532894754 -> 49 38 53 28 9 47 54
1234567 -> 1 2 3 4 5 6 7
*/
