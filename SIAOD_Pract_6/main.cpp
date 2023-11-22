#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class Graph {
private:
    int vertexCount;
    vector<vector<int>> adjacencyMatrix;

public:
    // Конструктор
    Graph(int vertices) : vertexCount(vertices + 1), adjacencyMatrix(vertices + 1, vector<int>(vertices + 1, 0)) {}

    // Метод для добавления ребра с весом
    void addEdge(int from, int to, int weight) {
        adjacencyMatrix[from][to] = weight;
        adjacencyMatrix[to][from] = weight; // для двунаправленного графа
    }

    // Метод для вывода матрицы смежности
    void displayMatrix() {
        cout << "Adjacency Matrix:" << endl;
        for (int i = 1; i <= vertexCount - 1; ++i) {
            for (int j = 1; j <= vertexCount - 1; ++j) {
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Метод для поиска в глубину
    void depthFirstSearch(int startVertex, vector<bool>& visited, stack<int>& path) {
        visited[startVertex] = true;
        path.push(startVertex);

        cout << "Path: ";
        while (!path.empty()) {
            int currentVertex = path.top();
            path.pop();
            cout << currentVertex << " ";

            for (int i = 1; i <= vertexCount - 1; ++i) {
                if (adjacencyMatrix[currentVertex][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    path.push(i);
                }
            }
        }
        cout << endl;
    }

    // Метод для поиска кратчайших путей
    void shortestPath(int startVertex, int method) {
        vector<int> distance(vertexCount, INT_MAX);
        vector<int> parent(vertexCount, -1);
        vector<bool> inTree(vertexCount, false);

        distance[startVertex] = 0;

        for (int count = 1; count <= vertexCount - 2; ++count) {
            int minDistance = INT_MAX;
            int minIndex = -1;

            // Выбор ближайшей вершины
            for (int i = 1; i <= vertexCount - 1; ++i) {
                if (!inTree[i] && distance[i] < minDistance) {
                    minDistance = distance[i];
                    minIndex = i;
                }
            }

            if (minIndex == -1) {
                // Все оставшиеся вершины недостижимы, выходим из цикла
                break;
            }

            inTree[minIndex] = true;

            // Обновление расстояний
            for (int i = 1; i <= vertexCount - 1; ++i) {
                if (!inTree[i] && adjacencyMatrix[minIndex][i] && distance[minIndex] != INT_MAX
                    && distance[minIndex] + adjacencyMatrix[minIndex][i] < distance[i]) {
                    distance[i] = distance[minIndex] + adjacencyMatrix[minIndex][i];
                    parent[i] = minIndex;
                }
            }
        }

        // Вывод кратчайших путей
        cout << "Shortest Paths (Method " << method << "):" << endl;
        for (int i = 1; i <= vertexCount - 1; ++i) {
            if (i != startVertex) {
                cout << "Path from " << startVertex << " to " << i << ": ";
                printPath(parent, i);
                cout << " Distance: " << distance[i] << endl;
            }
        }
    }

    // Вспомогательный метод для вывода пути
    void printPath(vector<int>& parent, int j) {
        if (parent[j] == -1)
            return;
        printPath(parent, parent[j]);
        cout << j << " ";
    }

    // Метод для получения количества вершин
    int getSize() const {
        return vertexCount - 1;
    }
};

int main() {
    // Создание графа
    Graph graph(5);

    // Добавление рёбер с весами
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 5, 10);
    graph.addEdge(2, 5, 6);
    graph.addEdge(3, 5, 7);
    graph.addEdge(5, 4, 11);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 4, 4);

    // Вывод матрицы смежности
    graph.displayMatrix();

    // Поиск в глубину
    vector<bool> visited(graph.getSize() + 1, false);
    stack<int> path;
    graph.depthFirstSearch(1, visited, path);

    // Поиск кратчайших путей (метод Дейкстры)
    graph.shortestPath(1, 1);

    // Поиск кратчайших путей (метод Флойда-Уоршелла)
    graph.shortestPath(1, 2);

    return 0;
}