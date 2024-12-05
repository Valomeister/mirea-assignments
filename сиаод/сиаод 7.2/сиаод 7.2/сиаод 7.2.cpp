#include <iostream>
#include <vector>
#include <limits.h>
#include <iomanip>
#include <thread>   // Для работы с потоками
#include <chrono> 
#include <queue>
#include <stack>
#include <windows.h>

using namespace std;

const int INF = INT_MAX;  // Для отсутствующих рёбер

class Graph {
public:
    int V;  // Количество вершин
    vector<vector<int>> adjMatrix;  // Матрица смежности

    // Конструктор графа
    Graph(int vertices) {
        V = vertices;
        adjMatrix.resize(V, vector<int>(V, INF));  // Инициализация матрицы весами INF
        for (int i = 0; i < V; ++i) {
            adjMatrix[i][i] = 0;  // Вес ребра от вершины к самой себе - 0
        }
    }

    // Добавление ребра с заданным весом
    void addEdge(int u, int v, int weight) {
        adjMatrix[u][v] = weight;
        adjMatrix[v][u] = weight;  // Так как граф неориентированный
    }

    // Вывод матрицы смежности
    void printGraph() {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                cout << left << setw(5);
                if (adjMatrix[i][j] == INF) {
                    cout << "INF";
                }
                else {
                    cout << adjMatrix[i][j];
                }
            }
            cout << endl;
        }
    }
    void printTree(int depth = 0, int node = 0, int prevNode = 0) {
        // отступы
        if (node != 0) {
            for (int i = 0; i < depth - 1; ++i) {
                cout << "|------";
            }

            cout << "|-[";
            cout << (adjMatrix[node][prevNode] < 10 ? "0" : "");
            cout << adjMatrix[node][prevNode] << "]-";

            
        }
        // номер узла
        cout << node << endl;

        // Рекурсивно выводим детей
        for (int i = node + 1; i < V; i++) {
            if (adjMatrix[node][i] == INF) continue;
            /*cout << node << "; " << i;
            std::this_thread::sleep_for(std::chrono::seconds(2));*/
            printTree(depth + 1, i, node);
        }
    }

    Graph* buildSpanningTree() {
        Graph* spanningTree = new Graph(this->V);
        vector<bool> used (this->V, false);
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                // нужны именно ребра
                if (i == j || this->adjMatrix[i][j] == INF) continue;
                // нельзя добавлять связь между двумя вершинами, если обе уже в дереве - иначе будет цикл
                if (used[i] && used[j]) continue;

                // добавляем ребро в дерево
                spanningTree->addEdge(i, j, this->adjMatrix[i][j]);
                used[i] = true;
                used[j] = true;
            }
        }
        return spanningTree;
    }

    int dijkstra(int a, int b) {
        vector<int> dist(V, INF); // Расстояния от начальной вершины
        vector<int> prev(V, -1);  // Для восстановления пути
        queue<int> q;            // Обычная очередь (FIFO)

        dist[a] = 0;        // Расстояние до себя = 0
        q.push(a);          // Добавляем начальную вершину в очередь

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            // Проходим по всем соседям текущей вершины
            for (int neighbor = 0; neighbor < V; ++neighbor) {
                if (adjMatrix[current][neighbor] != 0 && adjMatrix[current][neighbor] != INF) { // Есть ребро
                    int newDist = dist[current] + adjMatrix[current][neighbor];
                    if (newDist < dist[neighbor]) {
                        dist[neighbor] = newDist;
                        prev[neighbor] = current;
                        q.push(neighbor); // Добавляем соседа в очередь
                    }
                }
            }

            
        }
        // Восстановление пути
        stack<int> path;
        for (int v = b; v != -1; v = prev[v]) {
            path.push(v);
        }

        // Вывод пути
        cout << "Кратчайший путь от вершины " << a << " до вершины " << b << ": ";
        while (!path.empty()) {
            cout << path.top();
            path.pop();
            if (!path.empty()) cout << " -> ";
        }
        cout << endl;

        return dist[b];
    }

};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    Graph g(8);  // Граф с 4 вершинами
    g.addEdge(0, 1, 23);
    g.addEdge(0, 2, 12);
    g.addEdge(1, 2, 25);
    g.addEdge(1, 4, 22);
    g.addEdge(1, 7, 35);
    g.addEdge(2, 3, 18);
    g.addEdge(3, 5, 20);
    g.addEdge(4, 5, 23);
    g.addEdge(4, 6, 14);
    g.addEdge(5, 6, 24);
    g.addEdge(6, 7, 16);

    g.printGraph();  // Печать матрицы смежности
    Graph* spanningTree = g.buildSpanningTree();
    cout << endl;
    spanningTree->printGraph();
    spanningTree->printTree();
    cout << g.dijkstra(6, 5) << endl;
    return 0;
}