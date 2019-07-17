// 1. use dependency map to find lib depends on what libs
// 2. use reverse dependency map to find lib is depended by what libs
// 3. need detect dependency cycle
// 4. need divide between explicit and implicit install/remove
// 5. maintain a list of installed libs by installation order
#include <algorithm> // for std::remove
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>

using namespace std;

// key: lib name, value: installation status
//                       0 - not installed
//                       1 - explicit installed
//                       2 - implicit installed
unordered_map<string, int> status;

// key: lib name, value: key lib depends on what libs
unordered_map<string, vector<string>> depends;

// key: lib name, value: what libs depends on key lib
unordered_map<string, vector<string>> reverse_depends;

// installed libs, use vector to track installation order
vector<string> installedlibs;

// check if there's cycle in dependency, A depends on B, B depends on A
// use Depth First Search to find if a lib was visited before
// input lib and deplibs are from cin
// search current dependency map to detect cycle
bool isCycle(string const& lib,
    vector<string> const& deplibs,
    unordered_map<string, bool>& resolved,
    unordered_map<string, bool>& visited)
{
    // resolved means this lib has been checked before
    if(resolved[lib]) return false;
    visited[lib] = true;
    for(auto const& item : deplibs) {
        // see you again
        if(visited[item]) {
            // only print message at end of Depth First Search
            cout << lib << " depends on " << item << ", ignoring command" << endl;
            return true;
        }
        if(isCycle(item, depends[item], resolved, visited)) return true;
    }
    resolved[lib] = true;
    visited[lib] = false;
    return false;
}

// check if a lib is needed by other installed lib when do REMOVE
bool needed(string const& lib)
{
    // if any of the libs who depends on input lib is installed,
    // then the input lib is needed, cannot be removed
    for(auto const& item : reverse_depends[lib]) {
        // no matter explicit or implicit installed
        if(status[item]) return true;
    }
    return false;
}

// install lib
// isExplicit: whether explicit install or not
void install(string const& lib, bool isExplicit)
{
    // if not installed
    if(!status[lib]) {
        // implicit install depend on libs
        for(auto const& item : depends[lib]) {
            install(item, false);
        }
        cout << "Installing " << lib << endl;
        status[lib] = isExplicit ? 1 : 2;
        // add to installed libs for LIST
        installedlibs.push_back(lib);
    } else if (isExplicit){
        cout << lib << " is already installed" << endl;
    }
}

// remove lib
// isExplicit: whether explicit remove or not
void remove(string const& lib, bool isExplicit)
{
    if(isExplicit && status[lib]==0) {
        cout << lib << " is not installed" << endl;
    } else if(isExplicit && needed(lib)) {
        cout << lib << " is still needed" << endl;
    } else if(!needed(lib) && (isExplicit || status[lib]==2)) {
        status[lib] = 0; // reset status to not installed
        // remove from installed list
        installedlibs.erase(
            std::remove(installedlibs.begin(), installedlibs.end(), lib),
            installedlibs.end());

        cout << "Removing " << lib << endl;
        // implicit remove depends on libs
        for(auto const& item : depends[lib]) {
            remove(item, false);
        }
    }
}

// add lib and depends on libs into dependency maps
// check if there's dependency cycle, then ignore this line of DEPEND command
void add_depend(string const& lib,
    vector<string> const& dependlibs)
{
    unordered_map<string, bool> resolved, visited;
    if(isCycle(lib, dependlibs, resolved, visited)) {
        return;
    }
    // if no dependency cycle, put into dependency maps
    for(auto const& item : dependlibs) {
        depends[lib].push_back(item);
        reverse_depends[item].push_back(lib);
    }
}

int main() {
    string line, cmd;
    string lib, dependlib;
    bool firstline = true;
    while(getline(cin, line), line != "END") {
        if(firstline) {
            // skip the first line of test case number
            firstline = false;
            continue;
        }
        cout << line << endl;
        stringstream ss(line);
        ss >> cmd;
        if(cmd == "LIST") {
            for(auto const& item : installedlibs) {
                cout << item << endl;
            }
        } else if(cmd == "DEPEND") {
            ss >> lib;
            vector<string> dependlibs;
            while(ss >> dependlib) {
                dependlibs.push_back(dependlib);
            }
            add_depend(lib, dependlibs);
        } else if(cmd == "INSTALL") {
            ss >> lib;
            install(lib, true);
        } else if(cmd == "REMOVE") {
            ss >> lib;
            remove(lib, true);
        } else {
            cout << "Invalid command" << endl;
        }
    }
    cout << "END" << endl;
    
    return 0;
}

