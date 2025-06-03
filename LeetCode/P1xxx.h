#pragma once
#include "Solution.h"
#include "DataParser.h"

class P1298 : Solution {
private:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        int n = status.size();
        queue<int> open;
        vector<int> visit(n, 0);    // 0表示没有盒子，1表示有盒子没钥匙，2表示已经打开盒子
        for (const int& initialBox : initialBoxes) {
            if (status[initialBox]) {
                open.push(initialBox);
            }
            else {
                visit[initialBox] = 1;
            }
        }
        int res = 0;
        while (!open.empty()) {
            int box = open.front();
            open.pop();
            visit[box] = 2;
            res += candies[box];
            for (const int& key : keys[box]) {
                status[key] = true;
                if (visit[key] == 1) {
                    visit[key] = 2;
                    open.push(key);
                }
            }
            for (const int& containedBox : containedBoxes[box]) {
                if (visit[containedBox] == 2) {
                    continue;
                }
                else if (status[containedBox]) {
                    open.push(containedBox);
                }
                else {
                    visit[containedBox] = 1;
                }
            }
        }
        return res;
    }
public:
    void run() {
        vector<int> status = DataParser::parseIntArray("[1,0,1,0]");
        vector<int> candies = DataParser::parseIntArray("[7,5,4,100]");
        vector<vector<int>> keys = DataParser::parseInt2DArray("[[],[],[1],[]]");
        vector<vector<int>> containedBoxes = DataParser::parseInt2DArray("[[1,2],[3],[],[]]");
        vector<int> initialBoxes = DataParser::parseIntArray("[0]");
        cout << maxCandies(status, candies, keys, containedBoxes, initialBoxes);
    }
};