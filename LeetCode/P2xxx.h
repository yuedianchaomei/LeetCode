#pragma once
#include "Solution.h"
#include "DataParser.h"

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