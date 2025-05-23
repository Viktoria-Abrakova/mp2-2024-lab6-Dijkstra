#include <iostream>
#include <ctime>
#include "dijkstra.h"

using namespace std;

void printMenu() {
    cout << "\n=== Меню ===" << endl;
    cout << "1. Задать граф вручную" << endl;
    cout << "2. Сгенерировать полный граф" << endl;
    cout << "3. Задать начальную вершину" << endl;
    cout << "4. Найти пути (D-куча)" << endl;
    cout << "5. Найти пути (Биномиальная куча)" << endl;
    cout << "6. Показать путь до вершины" << endl;
    cout << "7. Вывести граф" << endl;
    cout << "8. Выход" << endl;
    cout << "Выберите действие: ";
}

void createManualGraph(Graph& graph) {
    int vertices;
    cout << "Количество вершин: ";
    cin >> vertices;

    if (vertices <= 0) {
        cout << "Количество вершин должно быть положительным!" << endl;
        return;
    }

    graph = Graph(vertices);

    cout << "Вводите рёбра (u v w), -1 для окончания:" << endl;
    while (true) {
        int u, v, w;
        cout << "u: ";
        cin >> u;
        if (u == -1) break;

        cout << "v: ";
        cin >> v;

        cout << "w: ";
        cin >> w;

        if (u < 0 || v < 0 || u >= vertices || v >= vertices || w <= 0) {
            cout << "Некорректное ребро! Попробуйте снова." << endl;
            continue;
        }
        graph.addEdge(u, v, w);
    }
}

void createCompleteGraph(Graph& graph) {
    int vertices;
    cout << "Количество вершин: ";
    cin >> vertices;

    if (vertices <= 0) {
        cout << "Количество вершин должно быть положительным!" << endl;
        return;
    }

    graph = Graph(vertices);
    for (int i = 0; i < vertices; ++i) {
        for (int j = i + 1; j < vertices; ++j) {
            graph.addEdge(i, j, i + j + 1); 
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    Graph graph(1);
    Dijkstra* dijkstra = new Dijkstra(graph);
    int startVertex = -1;
    myVector<int> distances;
    double time;
    int heapType = 0;

    while (true) {
        printMenu();
        int choice;
        cin >> choice;

        if (choice == 8) break;

        switch (choice) {
                    case 1: {
                createManualGraph(graph);
                delete dijkstra;  
                dijkstra = new Dijkstra(graph);  
                startVertex = -1;
                break;
            }
                
            case 2: {
                createCompleteGraph(graph);
                delete dijkstra;  
                dijkstra = new Dijkstra(graph);  
                startVertex = -1;
                break;
            }

        case 3: {
            cout << "Начальная вершина (0-" << graph.getNumVertices() - 1 << "): ";
            cin >> startVertex;

            if (startVertex < 0 || startVertex >= graph.getNumVertices()) {
                cout << "Неверная вершина!" << endl;
                startVertex = -1;
            }
            distances.clear(); 
            break;
        }

        case 4: {
            if (startVertex == -1) {
                cout << "Сначала задайте начальную вершину!" << endl;
                break;
            }

            clock_t start = clock();
            distances = dijkstra->shortestPaths(startVertex, Dijkstra::D_HEAP, 2);
            double time = (clock() - start) / (double)CLOCKS_PER_SEC;

            cout << "Вычислено за " << time * 1000 << " мс" << endl;
            break;
        }

        case 5: {
            if (startVertex == -1) {
                cout << "Сначала задайте начальную вершину!" << endl;
                break;
            }

            clock_t start = clock();
            distances = dijkstra->shortestPaths(startVertex, Dijkstra::BINOMIAL_HEAP);  
            double time = (clock() - start) / (double)CLOCKS_PER_SEC;

            cout << "Вычислено за " << time * 1000 << " мс" << endl;
            break;
        }

        case 6: {
            if (distances.empty()) {
                cout << "Сначала найдите пути!" << endl;
                break;
            }

            int target;
            cout << "Целевая вершина (0-" << graph.getNumVertices() - 1 << "): ";
            cin >> target;

            if (target < 0 || target >= graph.getNumVertices()) {
                cout << "Неверная вершина!" << endl;
            }
            else if (distances[target] == -1) {
                cout << "Недостижима!" << endl;
            }
            else {
                cout << "Расстояние: " << distances[target] << endl;
            }
            break;
        }

        case 7:
            graph.printGraph();
            break;

        default:
            cout << "Неверный выбор! Пожалуйста, выберите от 1 до 8." << endl;
        }
    }

    return 0;
}