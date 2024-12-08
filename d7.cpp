#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

bool dfs(long long target, vector<int>& v, int i, long long sum) {
    if (i == v.size()) {
        if (sum == target) {
            return true;
        }
        return false;
    }
    if (sum > target) {
        return false;
    }

    // Calculate the number of digits of v[i], edge case 1, 100, 1000, 10000, ...
    double n = log10(v[i]);
    if(n == (int) n) n = n + 1;
    else n = ceil(n);
    
    return dfs(target, v, i + 1, sum + v[i]) || dfs(target, v, i + 1, sum * v[i]) ||
           dfs(target, v, i + 1, sum * (long long)pow(10, n) + (long long)v[i]);
}

int main() {
    ifstream input("data.txt");
    string line;
    long long sum = 0;
    while (getline(input, line)) {
        long long target = 0;
        // Split by ':'
        int i = 0;
        while (line[i] != ':') {
            i++;
        }
        target = stoll(line.substr(0, i));

        // Split by ','
        i += 2;
        vector<int> v;
        while (i < line.size()) {
            int j = i;
            while (j < line.size() && line[j] != ' ') {
                j++;
            }
            v.push_back(stoi(line.substr(i, j - i)));
            i = j + 1;
        }

        if (dfs(target, v, 1, v[0])) {
            sum += target;
        }
    }

    cout << sum << endl;

    return 0;
}