#pragma once
#include "Solution.h"
#include "DataParser.h"
#include <chrono>

class P2359 : Solution {
private:
    void dfs(int node, vector<int>& dis, vector<vector<int>>& children, int k) {
        if (dis[node] != -1) {
            return;
        }
        dis[node] = k;
        for (const auto& child : children[node]) {
            dfs(child, dis, children, k + 1);
        }
    }
    int closestMeetingNode(vector<int>& edges, int node1, int node2) {
        int n = edges.size();
        vector<vector<int>> children(n);
        for (int i = 0; i < n; ++i) {
            if (edges[i] != -1) {
                children[i].emplace_back(edges[i]);
            }
        }
        vector<int> dis1(n, -1);
        dfs(node1, dis1, children, 0);
        vector<int> dis2(n, -1);
        dfs(node2, dis2, children, 0);
        int minValue = INT_MAX;
        int minNode = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (dis1[i] != -1 && dis2[i] != -1) {
                dis1[i] = max(dis1[i], dis2[i]);
                if (dis1[i] < minValue) {
                    minValue = dis1[i];
                    minNode = i;
                }
            }
        }
        if (minNode == INT_MAX) {
            return -1;
        }
        return minNode;
    }
public:
    void run() {
        vector<int> edges = DataParser::parseIntArray("[2,2,3,-1]");
        int node1 = 0;
        int node2 = 1;
        int res = closestMeetingNode(edges, node1, node2);
        cout << res;
    }
};

class P2929 : Solution {
private:
    long long distributeCandiesF1Enum(int n, int limit) {
        long long ans = 0;
        for (int i = 0; i <= min(limit, n); i++) {
            if (n - i > 2 * limit) {
                continue;
            }
            ans += min(n - i, limit) - max(0, n - i - limit) + 1;
        }
        return ans;
    }

    long long distributeCandiesF2InExclusion(int n, int limit) {
        auto cal = [](int x) {
            return x < 0 ? 0LL : static_cast<long long>(x + 2) * (x + 1) / 2;
            };
        return cal(n)
            - 3 * cal(n - (limit + 1))
            + 3 * cal(n - 2 * (limit + 1))
            - cal(n - 3 * (limit + 1));
    }

public:
    void run() {
        int n = 964126, limit = 465261;
        
        auto start1 = chrono::high_resolution_clock::now();
        cout << distributeCandiesF1Enum(n, limit) << endl;
        auto end1 = chrono::high_resolution_clock::now();
        auto duration1 = chrono::duration_cast<chrono::milliseconds>(end1 - start1);
        cout << "Ã¶¾ÙºÄÊ±£º" << duration1.count() << "ms" << endl;

        auto start2 = chrono::high_resolution_clock::now();
        cout << distributeCandiesF2InExclusion(n, limit) << endl;
        auto end2 = chrono::high_resolution_clock::now();
        auto duration2 = chrono::duration_cast<chrono::milliseconds>(end2 - start2);
        cout << "ÈÝ³âºÄÊ±£º" << duration2.count() << "ms" << endl;
    }
};