#include <iostream>

using namespace std;

// 트리 노드 구조체
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

// 링크드 리스트 노드 구조체
struct ListNode {
    TreeNode* node;
    ListNode* next;
    ListNode(TreeNode* n) {
        node = n;
        next = nullptr;
    }
};

// 링크드 리스트 클래스
class LinkedList {
private:
    ListNode* head;
public:
    LinkedList() {
        head = nullptr;
    }

    // 노드를 리스트의 끝에 추가하는 함수
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

    // 리스트의 첫 번째 노드를 반환하는 함수
    TreeNode* get_first() {
        if (head == nullptr) {
            return nullptr;
        }
        return head->node;
    }

    // 리스트의 첫 번째 노드를 제거하는 함수
    void remove_first() {
        if (head != nullptr) {
            ListNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // 리스트가 비어 있는지 확인하는 함수
    bool is_empty() {
        return head == nullptr;
    }
};

// 트리 클래스
class Tree {
private:
    TreeNode* root;
public:
    Tree() {
        root = nullptr;
    }

    // 트리에 노드를 추가하는 함수
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

    // 트리를 순회하여 값을 출력하는 함수
    void traverse(TreeNode* node) {
        if (node != nullptr) {
            traverse(node->left);
            cout << node->data << " ";
            traverse(node->right);
        }
    }

    // 트리를 출력하는 함수
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
    t.print(); // 결과: 4 2 5 1 3 6
    return 0;
}
