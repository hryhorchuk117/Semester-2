#include "sort.h"
#include "struct.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

vector<int> pr = setPriorities();

bool operator < (const Monster& lhs, const Monster& rhs) {
    return !comparing(lhs, rhs, pr);
}

int main() {
    vector<Monster> vec;
    ifstream in("lab_3b_demo.txt");
    int n = 0;
    in >> n;
    for (int i = 0; i < n; ++i) {
        Monster m;
        in >> m;
        vec.push_back(m);
    }
    sort(begin(vec), end(vec));
    for (auto& item : vec) {
        cout << item << endl;
    }
    return 0;
}
