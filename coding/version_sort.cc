/*
    definition: 
        Sem-ver is defined as a software versioning structure, where given a version number MAJOR.MINOR.PATCH, increment the:
        MAJOR version when you make incompatible API changes,
        MINOR version when you add functionality in a backwards-compatible manner, and
        PATCH version when you make backwards-compatible bug fixes.
        Additional labels for pre-release and build metadata are available as extensions to the MAJOR.MINOR.PATCH format.
        1.0.0-alpha, 1.0.0-alpha.1, 1.0.0-0.3.7, 1.0.0-x.7.z.92
        
        precedence:
        1.0.0-alpha < 1.0.0-alpha.1 < 1.0.0-alpha.beta < 1.0.0-beta < 1.0.0-beta.2 < 1.0.0-beta.11 < 1.0.0-rc.1 < 1.0.0
        

    question:
        How do you sort sem-ver values (1.1.1 vs 1.2.1 etc)

    sample input:    
        1.2.3
        4.11.6
        4.2.0
        1.5.19
        1.5.5
        4.1.3
        2.3.1
        10.5.5
        11.3.0
*/

#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool compare(std::string const& str1, std::string const& str2);

// for version string after -
bool comparesub(std::string const& str1, std::string const& str2)
{
    int len1 = str1.length(), len2 = str2.length();
    int i1 = 0, i2 = 0, num1 = 0, num2 = 0;
    string part1, part2;
    // whether identifier is number, default true
    bool bNum1 = true, bNum2 = true;
    
    // if one sub is empty
    if(len1 == 0 || len2 == 0) {
        return len1 > len2;
    }

    while(i1 < len1 || i2 < len2) {
        while(i1 < len1 && str1[i1] != '.') {
            if(!isdigit(str1[i1])) {
                bNum1 = false;
            } else {
                num1 = num1*10 + (str1[i1] - '0');
            }
            part1 += str1[i1];
            i1++;
        }
        
        while(i2 < len2 && str2[i2] != '.') {
            if(!isdigit(str2[i2])) {
                bNum2 = false;
            } else {
                num2 = num2*10 + (str2[i2] - '0');
            }
            part2 += str2[i2];
            i2++;
        }

        if(bNum1 && bNum2) {
            if(num1 > num2) return false;
            else if(num1 < num2) return true;
        } else {
            // one is string, the other is number
            if(bNum1 && !bNum2) return true;
            if(!bNum1 && bNum2) return false;
            // both string
            if (part1 != part2) return part1 < part2;
        }
        
        i1++;
        i2++;
        num1 = 0;
        num2 = 0;
        part1 = "";
        part2 = "";
        bNum1 = true;
        bNum2 = true;
    }
    return true;
}

bool compare_enhance(std::string const& str1, std::string const& str2)
{
    string pre1 = str1, pre2 = str2;
    string sub1, sub2;
    int pos1 = str1.find('-');
    bool has_sub1 = (pos1 != -1);
    if(has_sub1) {
        pre1 = str1.substr(0, pos1);
        sub1 = str1.substr(pos1+1);
    }

    int pos2 = str2.find('-');
    bool has_sub2 = (pos2 != -1);
    if(has_sub2) {
        pre2 = str2.substr(0, pos2);
        sub2 = str2.substr(pos2+1);
    }
    
    // both input don't have -
    if(!has_sub1 && !has_sub2) {
        return compare(str1, str2);
    } else {
        /* this piece code used as example for better understanding the logic
           because in comparesub() line 62-65 can do samething for only one has -
           so I replace with below line 151-156
        */
        /*
        // only one of the input have -
        if((has_sub1 && !has_sub2) || (!has_sub1 && has_sub2)) {
            if(pre1 == pre2) return sub1.length() > sub2.length();
            else return compare(pre1, pre2);
        }
        // both have -
        if(compare(pre1, pre2)) {
            if(pre1 == pre2) return comparesub(sub1, sub2);
            else return true;
        } else 
            return false;
        */
        if(pre1 == pre2) {
            // compare(pre1, pre2) will return true
            return comparesub(sub1, sub2);
        } else {
            return compare(pre1, pre2);
        }
    }

    return true;
}

bool compare(std::string const& str1, std::string const& str2)
{
    int len1 = str1.length(), len2 = str2.length();
    int i1 = 0, i2 = 0, num1 = 0, num2 = 0;
    
    while(i1 < len1 || i2 < len2) {
        
        // go throgh str1
        while(i1 < len1 && str1[i1] != '.') {
            num1 = num1*10 + (str1[i1] - '0');
            i1++;
        }
        
        // go through str2
        while(i2 < len2 && str2[i2] != '.') {
            num2 = num2*10 + (str2[i2] - '0');
            i2++;
        }
        
        if(num1 > num2) return false;
        else if(num1 < num2) return true;
        
        i1++;
        i2++;
        num1 = 0;
        num2 = 0;
    }
    
    return true;
}

void print(vector<std::string> const& input)
{
    for(auto &item : input) {
        cout << item << endl;
    }
    cout << endl;
}

int main()
{
    vector<std::string> input = {
        "1.1.0",
        "1.0.0",
        "1.2.3",
        "4.11",
        "4.11.6",
        "4.2.0",
        "1.5.19",
        "1.5.5",
        "4.1.3",
        "2.3.1",
        "10.5.5",
        "11.3.0"
    };
    
    vector<std::string> input2 = {
        "1.0.0",
        "1.0.0-beta.11",
        "1.0.0-alpha",
        "1.0.0-beta.2",
        "0.1.0",
        "1.2.0",
        "1.0.0-alpha.1",
        "1.0.0-rc.1",
        "1.1.0",
        "1.0.0-alpha.beta",
        "1.0.0-beta",
        "1.1.0-beta.2",
        "1.0.0-beta.10",
        "1.1.0-beta"
    };
    
    //print(input);
    sort(input.begin(), input.end(), compare);
    print(input);
    
    //print(input2);
    sort(input2.begin(), input2.end(), compare_enhance);
    print(input2);
}



/*
How to build:
$ g++ -std=c++11 version_sort.cc -o version_sort

How to run:
$ ./version_sort

Test result:
1.0.0
1.1.0
1.2.3
1.5.5
1.5.19
10.5.5
2.3.1
4.1.3
4.2.0
4.11
4.11.6
11.3.0

0.1.0
1.0.0-alpha
1.0.0-alpha.1
1.0.0-beta
1.0.0-alpha.beta
1.0.0-beta.2
1.1.0
1.0.0-beta.10
1.0.0-beta.11
1.0.0-rc.1
1.0.0
1.1.0-beta
1.1.0-beta.2
1.2.0
*/
