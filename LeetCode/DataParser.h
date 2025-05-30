#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <queue>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// 链表节点定义
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// 二叉树节点定义
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 工具类：解析各种数据结构
class DataParser {
public:
    // 解析整数
    static int parseInt(const std::string& input) {
        try {
            return json::parse(input).get<int>();
        }
        catch (const json::exception& e) {
            std::cerr << "整数解析错误: " << e.what() << std::endl;
            return 0;
        }
    }

    // 解析字符串
    static std::string parseString(const std::string& input) {
        try {
            return json::parse(input).get<std::string>();
        }
        catch (const json::exception& e) {
            std::cerr << "字符串解析错误: " << e.what() << std::endl;
            return "";
        }
    }

    // 解析整数数组
    static std::vector<int> parseIntArray(const std::string& input) {
        try {
            return json::parse(input).get<std::vector<int>>();
        }
        catch (const json::exception& e) {
            std::cerr << "整数数组解析错误: " << e.what() << std::endl;
            return {};
        }
    }

    // 解析二维整数数组
    static std::vector<std::vector<int>> parseInt2DArray(const std::string& input) {
        try {
            return json::parse(input).get<std::vector<std::vector<int>>>();
        }
        catch (const json::exception& e) {
            std::cerr << "二维整数数组解析错误: " << e.what() << std::endl;
            return {};
        }
    }

    // 解析字符串数组
    static std::vector<std::string> parseStringArray(const std::string& input) {
        try {
            return json::parse(input).get<std::vector<std::string>>();
        }
        catch (const json::exception& e) {
            std::cerr << "字符串数组解析错误: " << e.what() << std::endl;
            return {};
        }
    }

    // 解析链表
    static ListNode* parseLinkedList(const std::string& input) {
        try {
            auto arr = json::parse(input).get<std::vector<int>>();
            if (arr.empty()) return nullptr;

            ListNode dummy(0);
            ListNode* curr = &dummy;
            for (int val : arr) {
                curr->next = new ListNode(val);
                curr = curr->next;
            }
            return dummy.next;
        }
        catch (const json::exception& e) {
            std::cerr << "链表解析错误: " << e.what() << std::endl;
            return nullptr;
        }
    }

    // 解析二叉树
    static TreeNode* parseBinaryTree(const std::string& input) {
        try {
            auto arr = json::parse(input);
            if (arr.empty() || arr[0].is_null()) return nullptr;

            TreeNode* root = new TreeNode(arr[0].get<int>());
            std::queue<TreeNode*> q;
            q.push(root);

            int i = 1;
            while (!q.empty() && i < arr.size()) {
                TreeNode* node = q.front();
                q.pop();

                // 左子节点
                if (i < arr.size() && !arr[i].is_null()) {
                    node->left = new TreeNode(arr[i].get<int>());
                    q.push(node->left);
                }
                i++;

                // 右子节点
                if (i < arr.size() && !arr[i].is_null()) {
                    node->right = new TreeNode(arr[i].get<int>());
                    q.push(node->right);
                }
                i++;
            }

            return root;
        }
        catch (const json::exception& e) {
            std::cerr << "二叉树解析错误: " << e.what() << std::endl;
            return nullptr;
        }
    }

    // 辅助函数：释放链表内存
    static void freeLinkedList(ListNode* head) {
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // 辅助函数：释放二叉树内存
    static void freeBinaryTree(TreeNode* root) {
        if (!root) return;
        freeBinaryTree(root->left);
        freeBinaryTree(root->right);
        delete root;
    }
};