#include <iostream>
#include <queue>
using namespace std;

class RedBlackTree {
    struct Node {
        int data;
        bool color; // 0 - ������, 1 - �������
        Node* parent;
        Node* left;
        Node* right;

        // �����������
        Node(int value) : data(value), color(1), parent(nullptr), left(nullptr), right(nullptr) {}
    };

    // ������
    Node* root; 

    // ��������������� �������: ����� ��������
    void rotateLeft(Node*& node)
    {
        Node* child = node->right;
        node->right = child->left;
        if (node->right != nullptr)
            node->right->parent = node;
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;
        child->left = node;
        node->parent = child;
    }

    // ��������������� �������: ������ ��������
    void rotateRight(Node*& node)
    {
        Node* child = node->left;
        node->left = child->right;
        if (node->left != nullptr)
            node->left->parent = node;
        child->parent = node->parent;
        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;
        child->right = node;
        node->parent = child;
    }

    // ��������������� �������: ���������� ������������ � ������ ��� �������
    void fixInsert(Node*& node)
    {
        Node* parent = nullptr;
        Node* grandparent = nullptr;
        while (node != root && node->color
            && node->parent->color) {
            parent = node->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left) {
                Node* uncle = grandparent->right;
                if (uncle != nullptr
                    && uncle->color) {
                    grandparent->color = 1;
                    parent->color = 0;
                    uncle->color = 0;
                    node = grandparent;
                }
                else {
                    if (node == parent->right) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
            else {
                Node* uncle = grandparent->left;
                if (uncle != nullptr
                    && uncle->color) {
                    grandparent->color = 1;
                    parent->color = 0;
                    uncle->color = 0;
                    node = grandparent;
                }
                else {
                    if (node == parent->left) {
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }
                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }
        root->color = 0;
    }

    // ��������������� �������: �������� ��� ������������� ������
    void inOrderTraversalHelper(Node* root) {

        if (!root) return;

        // ������� ������� ����� ���������
        inOrderTraversalHelper(root->left);

        // �������� ������� ����
        cout << root->data << " ";

        // ����� ������� ������ ���������
        inOrderTraversalHelper(root->right);
    }

    // ��������������� �������: �������� ��� ������ � ������
    void levelOrderTraversalHelper(Node* root) {
        if (root == nullptr) {
            return;
        }

        // ������� ��� �������� ����� �� ������� ������
        queue<Node*> q;

        // �������� ������ � �������
        q.push(root);

        while (!q.empty()) {
            // ��������� ���� �� �������
            Node* current = q.front();
            q.pop();

            // ������������ ������� ����
            cout << current->data << " ";

            // ��������� ����� ��������� � �������
            if (current->left != nullptr) {
                q.push(current->left);
            }

            // ��������� ������ ��������� � �������
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }

    // ��������������� �������: �������� ��� ���������� ����� �������
    int sumOfLeavesHelper(Node* root) {
        if (root == nullptr) {
            return 0; // ���� ���� ������, ���������� 0
        }

        // ���� ���� �������� ������
        if (root->left == nullptr && root->right == nullptr) {
            return root->data;
        }

        // ���������� ��������� ������ � ����� � ������ �����������
        return sumOfLeavesHelper(root->left) + sumOfLeavesHelper(root->right);
    }

    //  ��������������� �������: �������� ��� �������� ����� �������� ����� � �� ����������
    void calculateSumAndCount(Node* root, int& sum, int& count) {
        if (root == nullptr) {
            return;
        }

        // ��������� �������� �������� ���� � �����
        sum += root->data;

        // ����������� ������� �����
        count++;

        // ���������� ������� ����� � ������ ���������
        calculateSumAndCount(root->left, sum, count);
        calculateSumAndCount(root->right, sum, count);
    }

    // ��������������� �������: �������� ��� ���������� �������� ���������������
    double findAverageHelper(Node* root) {
        if (root == nullptr) {
            return 0.0; // ���� ������ ������, ������� ����� 0
        }

        int sum = 0;
        int count = 0;

        // ��������� ����� � ���������� �����
        calculateSumAndCount(root, sum, count);

        // ���������� ������� ��������������
        return static_cast<double>(sum) / count;
    }

    // ��������������� �������: �������� ��� ������ ������-������� ������
    void printHelper(Node* root, string indent, bool last)
    {
        if (root != nullptr) {
            cout << indent;
            if (last) {
                cout << "R----";
                indent += "   ";
            }
            else {
                cout << "L----";
                indent += "|  ";
            }
            string sColor
                = (root->color) ? "�������" : "������";
            cout << root->data << "(" << sColor << ")"
                << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

    

public:
    // �����������
    RedBlackTree() : root(nullptr) {}

    // ����� �������
    void insert(int key)
    {
        Node* node = new Node(key);
        Node* parent = nullptr;
        Node* current = root;
        while (current != nullptr) {
            parent = current;
            if (node->data < current->data)
                current = current->left;
            else
                current = current->right;
        }
        node->parent = parent;
        if (parent == nullptr)
            root = node;
        else if (node->data < parent->data)
            parent->left = node;
        else
            parent->right = node;
        fixInsert(node);
    }

    // ����� ������������� ������
    void inOrderTraversal() {
        if (root == nullptr) {
            cout << "������ �����." << endl;
        }
        else {
            cout << "������������ ����� ������: ";
            inOrderTraversalHelper(root);
            cout << endl;
        }
        
    }
    
    // ����� ������ � ������
    void levelOrderTraversal() {
        if (root == nullptr) {
            cout << "������ �����." << endl;
        }
        else {
            cout << "����� ������ � ������: ";
            levelOrderTraversalHelper(root);
            cout << endl;
        }
    }
    
    // ����� ������ ����� �������
    void sumOfLeaves() {
        if (root == nullptr) {
            cout << "������ �����." << endl;
        }
        else {
            cout << "����� ������� ����� ";
            cout << sumOfLeavesHelper(root);
            cout << endl;
        }
    }

    // ����� ������ �������� �����. ����� 
    void findAverage() {
        if (root == nullptr) {
            cout << "������ �����." << endl;
        }
        else {
            cout << "������� �������������� ���� ����� ����� ";
            cout << findAverageHelper(root);
            cout << endl;
        }
    }

    // ����� ������ ������
    void printTree()
    {
        if (root == nullptr)
            cout << "������ �����." << endl;
        else {
            cout << "������:" << endl;
            printHelper(root, "", true);
        }
    }
};

// ������� ��� ����������������� ����
void menu() {
    RedBlackTree tree; // ������� ��������� ������-������� ������
    int choice;

    // ����� ������ ������ ���� ���
    cout << "=== ���� ������ � ������-������ ������� ===\n";
    cout << "1. �������� ����\n";
    cout << "2. ������������ �����\n";
    cout << "3. ����� � ������\n";
    cout << "4. ������� ����� �������\n";
    cout << "5. ����� ������� �������������� �����\n";
    cout << "6. ������� ������\n";
    cout << "0. �����\n";

    do {
        cout << "\n> ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            cout << "������� �������� ��� ����������: ";
            cin >> value;
            tree.insert(value);
            cout << "���� � ��������� " << value << " ��������." << endl;
            break;
        }
        case 2: {
            tree.inOrderTraversal();
            break;
        }
        case 3: {
            tree.levelOrderTraversal();
            break;
        }
        case 4: {
            tree.sumOfLeaves();
            break;
        }
        case 5: {
            tree.findAverage();
            break;
        }
        case 6: {
            tree.printTree();
            break;
        }
        case 0: {
            cout << "����� �� ���������." << endl;
            break;
        }
        default: {
            cout << "�������� �����. ���������� �����." << endl;
        }
        }
    } while (choice != 0);
}

int main()
{
    setlocale(LC_ALL, "Russian");
    menu();
    return 0;
}
