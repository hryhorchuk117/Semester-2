#include <iostream>
#include <stack>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <utility>

using namespace std;

int GetElem(stack<int> stack, int n) {
    for (int i = 0; i < n; ++i) {
        stack.pop();
    }
    return stack.top();
}

int Erase(stack<int>& stack, int n) {
    std::stack<int> top_n;
    for (int i = 0; i < n + 1; ++i) {
        int curr = stack.top();
        top_n.push(curr);
        stack.pop();
    }
    int res = top_n.top();
    top_n.pop();

    for (int i = 0; i < n ; ++i) {
        int curr = top_n.top();
        stack.push(curr);
        top_n.pop();
    }

    return res;
}

void Print(stack<int> stack) {
    while(!stack.empty()) {
        cout << stack.top() << " ";
        stack.pop();
    }
    cout << endl;
}

template <class T>
T Read(ifstream& demo, bool interactive, T& t) {
    if (interactive) {
        cin >> t;
        return t;
    }
    demo >> t;
    return t;
}

void SkipSpaces(stringstream& ss) {
    while (ss.peek() == ' ') {
        ss.ignore();
    }
}

void AddOperation(map<string, string>& operations, bool interactive, ifstream& demo) {
    //Enter name of the operation
    string name;
    if (interactive) {
        getline(cin, name);
    } else {
        getline(demo, name);
    }
   //Enter the definition of the operation
    string def;
    if (interactive) {
        getline(cin, def);
    } else {
        getline(demo, def);
    }

    operations[name] = def;
}

pair<int, int> Top2(stack<int>& stack) {
    pair<int, int> p;
    p.second = stack.top();
    stack.pop();
    p.first = stack.top();
    stack.pop();
    return  p;
}

void Operation(map<string, string> operations,
        stack<int>& stack, stringstream& in) {
    int number;
    string operation;
    while(in) {
        if (in.peek() >= '0' && in.peek() <= '9') {
            in >> number;
            SkipSpaces(in);
            stack.push(number);
        } else {

            in >> operation;
            SkipSpaces(in);
            if (operation == "+") {
                pair<int, int> top = Top2(stack);
                stack.push(top.first + top.second);
            }

            else if (operation == "-") {
                pair<int, int> top = Top2(stack);
                stack.push(top.first - top.second);
            }

            else if (operation == "*") {
                pair<int, int> top = Top2(stack);
                stack.push(top.first * top.second);
            }

            else if (operation == "/") {
                pair<int, int> top = Top2(stack);
                stack.push(top.first / top.second);
            }

            else if (operation == "MOD") {
                pair<int, int> top = Top2(stack);
                stack.push(top.first % top.second);
            }

            else {
                for (const auto& [key, value] : operations) {
                    if (key == operation) {
                        stringstream ss{value};
                        Operation(operations, stack, ss);
                    }
                }
            }
        }
    }
}

int main() {
    std::stack<int> stack;
    map<string, string> operations;
    string curr_operation{};
    bool interactive = true;
    ifstream demo(".../lab_2b_24.txt");

    string type{};
    cin >> type;
    if (type == "Demo") {
        interactive = false;
    }

    while (true) {
        //cout << "OK" << endl;
        string s;
        if (interactive) {
            getline(cin, s);
        } else {
            getline(demo, s);
        }
        //cout << s << endl;
        stringstream in{s};
        SkipSpaces(in);
        if (in.peek() >= '0' && in.peek() <= '9') {
            Operation(operations, stack, in);
        }

        else {
            string command;
            in >> command;
            if (command == "Stop") {
                return 0;
            }

            if (command == "New_operation") {
                AddOperation(operations, interactive, demo);
            }

            if (command == "PICK") {
                int n = Read(demo, interactive, n);
                int elem = GetElem(stack, n);
                stack.push(elem);
            }

            if (command == "ROLL") {
                int n = Read(demo, interactive, n);
                int elem = Erase(stack, n);
                stack.push(elem);
            }

            if (command == ".") {
                Print(stack);
            }
        }


    }
}






