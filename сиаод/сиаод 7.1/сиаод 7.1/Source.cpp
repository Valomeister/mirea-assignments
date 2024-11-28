#include <iostream>
#include <queue>
using namespace std;

class RedBlackTree {
    struct Node {
        int data;
        bool color; // 0 - черный, 1 - красный
        Node* parent;
        Node* left;
        Node* right;

        // Конструктор
        Node(int value) : data(value), color(1), parent(nullptr), left(nullptr), right(nullptr) {}
    };

    // Корень
    Node* root; 

    // Вспомогательная функция: левое вращение
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

    // Вспомогательная функция: правое вращение
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

    // Вспомогательная функция: разрешение противоречий в дереве при вставке
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

    // Вспомогательная функция: помощник для симметричного обхода
    void inOrderTraversalHelper(Node* root) {

        if (!root) return;

        // Сначала обходим левое поддерево
        inOrderTraversalHelper(root->left);

        // Посещаем текущий узел
        cout << root->data << " ";

        // Затем обходим правое поддерево
        inOrderTraversalHelper(root->right);
    }

    // Вспомогательная функция: помощник для обхода в ширину
    void levelOrderTraversalHelper(Node* root) {
        if (root == nullptr) {
            return;
        }

        // Очередь для хранения узлов на текущем уровне
        queue<Node*> q;

        // Помещаем корень в очередь
        q.push(root);

        while (!q.empty()) {
            // Извлекаем узел из очереди
            Node* current = q.front();
            q.pop();

            // Обрабатываем текущий узел
            cout << current->data << " ";

            // Добавляем левое поддерево в очередь
            if (current->left != nullptr) {
                q.push(current->left);
            }

            // Добавляем правое поддерево в очередь
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
    }

    // Вспомогательная функция: помощник для нахождения суммы листьев
    int sumOfLeavesHelper(Node* root) {
        if (root == nullptr) {
            return 0; // Если узел пустой, возвращаем 0
        }

        // Если узел является листом
        if (root->left == nullptr && root->right == nullptr) {
            return root->data;
        }

        // Рекурсивно суммируем листья в левом и правом поддеревьях
        return sumOfLeavesHelper(root->left) + sumOfLeavesHelper(root->right);
    }

    //  Вспомогательная функция: помощник для подсчета суммы значений узлов и их количества
    void calculateSumAndCount(Node* root, int& sum, int& count) {
        if (root == nullptr) {
            return;
        }

        // Добавляем значение текущего узла в сумму
        sum += root->data;

        // Увеличиваем счетчик узлов
        count++;

        // Рекурсивно обходим левое и правое поддерево
        calculateSumAndCount(root->left, sum, count);
        calculateSumAndCount(root->right, sum, count);
    }

    // Вспомогательная функция: помощник для вычисления среднего арифметического
    double findAverageHelper(Node* root) {
        if (root == nullptr) {
            return 0.0; // Если дерево пустое, среднее равно 0
        }

        int sum = 0;
        int count = 0;

        // Вычисляем сумму и количество узлов
        calculateSumAndCount(root, sum, count);

        // Возвращаем среднее арифметическое
        return static_cast<double>(sum) / count;
    }

    // Вспомогательная функция: помощник для вывода Красно-Черного дерева
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
                = (root->color) ? "Красный" : "Черный";
            cout << root->data << "(" << sColor << ")"
                << endl;
            printHelper(root->left, indent, false);
            printHelper(root->right, indent, true);
        }
    }

    

public:
    // Конструктор
    RedBlackTree() : root(nullptr) {}

    // Метод вставки
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

    // Метод симмтеричного обхода
    void inOrderTraversal() {
        if (root == nullptr) {
            cout << "Дерево пусто." << endl;
        }
        else {
            cout << "Симметричный обход дерева: ";
            inOrderTraversalHelper(root);
            cout << endl;
        }
        
    }
    
    // Метод обхода в ширину
    void levelOrderTraversal() {
        if (root == nullptr) {
            cout << "Дерево пусто." << endl;
        }
        else {
            cout << "Обход дерева в ширину: ";
            levelOrderTraversalHelper(root);
            cout << endl;
        }
    }
    
    // Метод вывода суммы листьев
    void sumOfLeaves() {
        if (root == nullptr) {
            cout << "Дерево пусто." << endl;
        }
        else {
            cout << "Сумма листьев равна ";
            cout << sumOfLeavesHelper(root);
            cout << endl;
        }
    }

    // Метод вывода среднего арифм. узлов 
    void findAverage() {
        if (root == nullptr) {
            cout << "Дерево пусто." << endl;
        }
        else {
            cout << "Среднее арифметическое всех узлов равно ";
            cout << findAverageHelper(root);
            cout << endl;
        }
    }

    // Метод вывода дерева
    void printTree()
    {
        if (root == nullptr)
            cout << "Дерево пусто." << endl;
        else {
            cout << "Дерево:" << endl;
            printHelper(root, "", true);
        }
    }
};

// Функция для пользовательского меню
void menu() {
    RedBlackTree tree; // Создаем экземпляр красно-черного дерева
    int choice;

    // Вывод списка команд один раз
    cout << "=== Меню работы с Красно-Черным деревом ===\n";
    cout << "1. Вставить узел\n";
    cout << "2. Симметричный обход\n";
    cout << "3. Обход в ширину\n";
    cout << "4. Вывести сумму листьев\n";
    cout << "5. Найти среднее арифметическое узлов\n";
    cout << "6. Вывести дерево\n";
    cout << "0. Выход\n";

    do {
        cout << "\n> ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            cout << "Введите значение для добавления: ";
            cin >> value;
            tree.insert(value);
            cout << "Узел с значением " << value << " добавлен." << endl;
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
            cout << "Выход из программы." << endl;
            break;
        }
        default: {
            cout << "Неверный выбор. Попробуйте снова." << endl;
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
