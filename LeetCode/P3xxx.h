#pragma once
#include "Solution.h"
#include "DataParser.h"

class P3373 : Solution {
private:
    int dfsFind(int node, int parent, const vector<vector<int>>& children, int k) {
        int res = 0;
        if (k % 2 == 0) {
            res = 1;
        }
        for (const auto& child : children[node]) {
            if (child == parent) {
                continue;
            }
            int addNum = dfsFind(child, node, children, k + 1);
            res += addNum;
        }
        return res;
    }
    void dfsRender(int node, int parent, const vector<vector<int>>& children, int k, vector<int>& res) {
        if (k % 2 == 0) {
            res[node] = res[0];
        }
        else {
            res[node] = children.size() - res[0];
        }
        for (const auto& child : children[node]) {
            if (child == parent) {
                continue;
            }
            dfsRender(child, node, children, k + 1, res);
        }
    }
    vector<int> build(const vector<vector<int>>& edges) {
        int n = edges.size() + 1;
        vector<vector<int>> children(n);
        for (const auto& edge : edges) {
            children[edge[0]].emplace_back(edge[1]);
            children[edge[1]].emplace_back(edge[0]);
        }
        vector<int> res(n);
        res[0] = dfsFind(0, -1, children, 0);
        dfsRender(0, -1, children, 0, res);
        return res;
    }
    vector<int> maxTargetNodes(vector<vector<int>>& edges1, vector<vector<int>>& edges2) {
        int n = edges1.size() + 1, m = edges2.size() + 1;
        vector<int> count1 = build(edges1);
        vector<int> count2 = build(edges2);
        int maxCount2 = *(max_element(count2.begin(), count2.end()));
        vector<int> res(n);
        for (int i = 0; i < n; ++i) {
            res[i] = count1[i] + maxCount2;
        }
        return res;
    }
public:
    void run() {
        vector<vector<int>> edges1 = DataParser::parseInt2DArray("[[0,1],[0,2],[2,3],[2,4]]");
        vector<vector<int>> edges2 = DataParser::parseInt2DArray("[[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]");
        vector<int> res = maxTargetNodes(edges1, edges2);
        int n = res.size();
        cout << "[";
        int i = 0;
        for (; i < n - 1; ++i) {
            cout << res[i] << ",";
        }
        cout << res[i] << "]";
    }
};