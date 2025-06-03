#pragma once
#include "Solution.h"
#include "DataParser.h"

class P0135 : Solution {
private:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        vector<int> minArr(n, 1);
        for (int i = 1; i < n; ++i) {
            if (ratings[i] > ratings[i - 1]) {
                minArr[i] = minArr[i - 1] + 1;
            }
        }
        for (int i = n - 2; i >= 0; --i) {
            if (ratings[i] > ratings[i + 1]) {
                minArr[i] = max(minArr[i], minArr[i + 1] + 1);
            }
        }
        int res = 0;
        for (const int& num : minArr) {
            res += num;
        }
        return res;
    }
public:
    void run() {
        vector<int> ratings = DataParser::parseIntArray("[1,3,4,5,2]");
        cout << candy(ratings);
    }
};

class P0909 : Solution {
private:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size();
        vector<int> boards(n * n + 1);
        bool dir = true;
        for (int i = n - 1, k = 1; i >= 0; --i) {
            if (dir) {
                for (int j = 0; j < n; ++j, ++k) {
                    boards[k] = board[i][j];
                }
                dir = false;
            }
            else {
                for (int j = n - 1; j >= 0; --j, ++k) {
                    boards[k] = board[i][j];
                }
                dir = true;
            }
        }
        vector<bool> visit(n * n + 1, false);
        queue<int> que;
        que.push(1);
        visit[1] = true;
        int times = 0;
        while (!que.empty()) {
            int queSize = que.size();
            for (int i = 0; i < queSize; ++i) {
                int cur = que.front();
                que.pop();
                if (cur >= n * n) {
                    return times;
                }
                for (int step = 1; step <= 6; ++step) {
                    int nxt = cur + step;
                    nxt = min(nxt, n * n);
                    if ((boards[nxt] != -1) && !visit[boards[nxt]]) {
                        visit[boards[nxt]] = true;
                        que.push(boards[nxt]);
                    }
                    else if (!visit[nxt] && boards[nxt] == -1) {
                        visit[nxt] = true;
                        que.push(nxt);
                    }
                }
            }
            ++times;
        }
        return -1;
    }

public:
    void run() {
        vector<vector<int>> board = DataParser::parseInt2DArray("[[-1,-1,-1,46,47,-1,-1,-1],[51,-1,-1,63,-1,31,21,-1],[-1,-1,26,-1,-1,38,-1,-1],[-1,-1,11,-1,14,23,56,57],[11,-1,-1,-1,49,36,-1,48],[-1,-1,-1,33,56,-1,57,21],[-1,-1,-1,-1,-1,-1,2,-1],[-1,-1,-1,8,3,-1,6,56]]");
        cout << snakesAndLadders(board);
    }
};