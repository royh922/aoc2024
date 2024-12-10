#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

int check(pair<int, int> item, vector<int>& spaces) {
    int cnt = item.first;
    int index = item.second;
    for(int i = 0; i < spaces.size() && i+1 < index; i++){
        if(spaces[i] >= cnt){
            spaces.insert(spaces.begin() + index, cnt + spaces[index-1]);
            spaces.erase(spaces.begin() + index - 1);
            return i+1;
        }
    }
    return -1;
}

int main() {
    ifstream input("data.txt");
    string line;
    vector<pair<int, int>> nums;
    vector<int> spaces;
    while (getline(input, line)) {
        for (int i = 0; i < line.size(); i++) {
            char c = line[i];
            if(i % 2 == 0) nums.push_back({c - '0', i / 2});
            else spaces.push_back(c - '0');
        }
    }

    // vector<int> times = vector<int>(spaces.size(), 0);

    bool found = true;

    while(found){
        for(int i = 0; i < nums.size(); i++){
            printf("%d:%d ", nums[i].first, nums[i].second);
        }
        cout << endl;

        for(int i = 0; i < spaces.size(); i++){
            printf("%d ", spaces[i]);
        }
        cout << endl;
        found = false;
        for(int i = nums.size()-1; i >= 0; i--){
            int res = check(nums[i], spaces);
            if(res != -1){
                found = true;
                pair<int, int> temp = nums[i];
                nums.erase(nums.begin() + i);
                nums.insert(nums.begin() + res, temp);
                spaces.insert(spaces.begin() + res-1, 0);
                spaces.erase(spaces.end()-1);
                break;
            }
        }
    }

    int index = 0;

    long long cnt = 0;

    for(int i = 0; i < nums.size(); i++){
        for(int j = 0; j < nums[i].first; j++){
            cnt += index * nums[i].second;
            index++;
        }
        index+=spaces[i];
    }

    cout << cnt << endl;

    

    return 0;
}
