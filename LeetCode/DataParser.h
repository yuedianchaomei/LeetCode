#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <queue>
#include <sstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

// ����ڵ㶨��
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// �������ڵ㶨��
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// �����ࣺ�����������ݽṹ
class DataParser {
public:
    // ��������
    static int parseInt(const std::string& input) {
        try {
            return json::parse(input).get<int>();
        }
        catch (const json::exception& e) {
            std::cerr << "������������: " << e.what() << std::endl;
            return 0;
        }
    }

    // �����ַ���
    static std::string parseString(const std::string& input) {
        try {
            return json::parse(input).get<std::string>();
        }
        catch (const json::exception& e) {
            std::cerr << "�ַ�����������: " << e.what() << std::endl;
            return "";
        }
    }

    // ������������
    static std::vector<int> parseIntArray(const std::string& input) {
        try {
            return json::parse(input).get<std::vector<int>>();
        }
        catch (const json::exception& e) {
            std::cerr << "���������������: " << e.what() << std::endl;
            return {};
        }
    }

    // ������ά��������
    static std::vector<std::vector<int>> parseInt2DArray(const std::string& input) {
        try {
            return json::parse(input).get<std::vector<std::vector<int>>>();
        }
        catch (const json::exception& e) {
            std::cerr << "��ά���������������: " << e.what() << std::endl;
            return {};
        }
    }

    // �����ַ�������
    static std::vector<std::string> parseStringArray(const std::string& input) {
        try {
            return json::parse(input).get<std::vector<std::string>>();
        }
        catch (const json::exception& e) {
            std::cerr << "�ַ��������������: " << e.what() << std::endl;
            return {};
        }
    }

    // ��������
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
            std::cerr << "�����������: " << e.what() << std::endl;
            return nullptr;
        }
    }

    // ����������
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

                // ���ӽڵ�
                if (i < arr.size() && !arr[i].is_null()) {
                    node->left = new TreeNode(arr[i].get<int>());
                    q.push(node->left);
                }
                i++;

                // ���ӽڵ�
                if (i < arr.size() && !arr[i].is_null()) {
                    node->right = new TreeNode(arr[i].get<int>());
                    q.push(node->right);
                }
                i++;
            }

            return root;
        }
        catch (const json::exception& e) {
            std::cerr << "��������������: " << e.what() << std::endl;
            return nullptr;
        }
    }

    // �����������ͷ������ڴ�
    static void freeLinkedList(ListNode* head) {
        while (head) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // �����������ͷŶ������ڴ�
    static void freeBinaryTree(TreeNode* root) {
        if (!root) return;
        freeBinaryTree(root->left);
        freeBinaryTree(root->right);
        delete root;
    }
};