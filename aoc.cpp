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

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

// void populate(vector<vector<char>>& grid, vector<vector<char>>& newGrid, vector<pair<int, int>>& nodes) {
//     for (int i = 0; i < nodes.size() - 1; i++) {
//         for (int j = i + 1; j < nodes.size(); j++) {
//             pair<int, int> A = nodes[i];
//             pair<int, int> B = nodes[j];
//             int x_dist = (B.first - A.first);
//             int y_dist = (B.second - A.second);
//             int xA = A.first;
//             int yA = A.second;
//             int xB = B.first;
//             int yB = B.second;

//             if (xA - x_dist >= 0 && xA - x_dist < grid[0].size() && yA - y_dist >= 0 && yA - y_dist < grid.size()) {
//                 newGrid[xA - x_dist][yA - y_dist] = '#';
//             }
//             if (xB + x_dist >= 0 && xB + x_dist < grid[0].size() && yB + y_dist >= 0 && yB + y_dist < grid.size()) {
//                 newGrid[xB + x_dist][yB + y_dist] = '#';
//             }
//         }
//     }
// }

void populate2(vector<vector<char>>& grid, vector<vector<char>>& newGrid, vector<pair<int, int>>& nodes) {
    for (int i = 0; i < nodes.size() - 1; i++) {
        for (int j = i + 1; j < nodes.size(); j++) {
            pair<int, int> A = nodes[i];
            pair<int, int> B = nodes[j];
            int x_dist = (B.first - A.first);
            int y_dist = (B.second - A.second);
            int common = gcd(abs(x_dist), abs(y_dist));
            x_dist /= common;
            y_dist /= common;
            int xA = A.first;
            int yA = A.second;
            int xB = B.first;
            int yB = B.second;

            int newX = xA;
            int newY = yA;
            while (newX >= 0 && newX < grid[0].size() && newY >= 0 && newY < grid.size()) {
                newGrid[newX][newY] = '#';
                newX -= x_dist;
                newY -= y_dist;
            }
            newX = xB;
            newY = yB;
            while (newX >= 0 && newX < grid[0].size() && newY >= 0 && newY < grid.size()) {
                newGrid[newX][newY] = '#';
                newX += x_dist;
                newY += y_dist;
            }

            // newX = xA + x_dist;
            // newY = yA + y_dist;
            // while (newX >= 0 && newX < grid[0].size() && newY >= 0 && newY < grid.size()) {
            //     newGrid[newX][newY] = '#';
            //     newX += x_dist;
            //     newY += y_dist;
            // }
        }
    }
}

int main() {
    ifstream input("data.txt");
    string line;
    vector<vector<char>> grid;
    while (getline(input, line)) {
        // Populate grid
        vector<char> row;
        for (char c : line) {
            row.push_back(c);
        }
        grid.push_back(row);
    }

    map<char, vector<pair<int, int>>> nodes;

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            if (isalnum(grid[i][j])) {
                nodes[grid[i][j]].push_back({i, j});
            }
        }
    }

    vector<vector<char>> newGrid = grid;

    // Populate newGrid with '.'s
    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid[i].size(); j++) {
            newGrid[i][j] = '.';
        }
    }

    for (auto& [key, value] : nodes) {
        populate2(grid, newGrid, value);
    }

    int cnt = 0;
    for (int i = 0; i < newGrid.size(); i++) {
        for (int j = 0; j < newGrid[i].size(); j++) {
            if (newGrid[i][j] == '#') {
                cnt++;
            }
        }
    }

    cout << cnt << endl;

    return 0;
}
