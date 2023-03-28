#include <iostream>

using namespace std;

// Ʈ�� ��� ����ü
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// ��ũ�� ����Ʈ ��� ����ü
struct ListNode {
    TreeNode* node;
    ListNode* next;
    ListNode(TreeNode* n) {
        node = n;
        next = nullptr;
    }
};

// ��ũ�� ����Ʈ Ŭ����
class LinkedList {
private:
    ListNode* head;
public:
    LinkedList() {
        head = nullptr;
    }

    // ��带 ����Ʈ�� ���� �߰��ϴ� �Լ�
    void add(TreeNode* n) {
        ListNode* new_node = new ListNode(n);
        if (head == nullptr) {
            head = new_node;
        }
        else {
            ListNode* curr = head;
            while (curr->next != nullptr) {
                curr = curr->next;
            }
            curr->next = new_node;
        }
    }

    // ����Ʈ�� ù ��° ��带 ��ȯ�ϴ� �Լ�
    TreeNode* get_first() {
        if (head == nullptr) {
            return nullptr;
        }
        return head->node;
    }

    // ����Ʈ�� ù ��° ��带 �����ϴ� �Լ�
    void remove_first() {
        if (head != nullptr) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // ����Ʈ�� ��� �ִ��� Ȯ���ϴ� �Լ�
    bool is_empty() {
        return head == nullptr;
    }
};

// Ʈ�� Ŭ����
class Tree {
private:
    TreeNode* root;
public:
    Tree() {
        root = nullptr;
    }

    // Ʈ���� ��带 �߰��ϴ� �Լ�
    void add(int val) {
        TreeNode* new_node = new TreeNode(val);
        if (root == nullptr) {
            root = new_node;
        }
        else {
            LinkedList q;
            q.add(root);
            while (!q.is_empty()) {
                TreeNode* curr = q.get_first();
                q.remove_first();
                if (curr->left == nullptr) {
                    curr->left = new_node;
                    break;
                }
                else if (curr->right == nullptr) {
                    curr->right = new_node;
                    break;
                }
                else {
                    q.add(curr->left);
                    q.add(curr->right);
                }
            }
        }
    }

    // Ʈ���� ��ȸ�Ͽ� ���� ����ϴ� �Լ�
    void traverse(TreeNode* node) {
        if (node != nullptr) {
            traverse(node->left);
            cout << node->data << " ";
            traverse(node->right);
        }
    }

    // Ʈ���� ����ϴ� �Լ�
    void print() {
        traverse(root);
        cout << endl;
    }
};

int main() {
    Tree t;
    t.add(1);
    t.add(2);
    t.add(3);
    t.add(4);
    t.add(5);
    t.add(6);
    t.print(); // ���: 4 2 5 1 3 6
    return 0;
}
