#include <iostream>
#include <ctime>
#include "dijkstra.h"

using namespace std;

void printMenu() {
    cout << "\n=== ���� ===" << endl;
    cout << "1. ������ ���� �������" << endl;
    cout << "2. ������������� ������ ����" << endl;
    cout << "3. ������ ��������� �������" << endl;
    cout << "4. ����� ���� (D-����)" << endl;
    cout << "5. ����� ���� (������������ ����)" << endl;
    cout << "6. �������� ���� �� �������" << endl;
    cout << "7. ������� ����" << endl;
    cout << "8. �����" << endl;
    cout << "�������� ��������: ";
}

void createManualGraph(Graph& graph) {
    int vertices;
    cout << "���������� ������: ";
    cin >> vertices;

    if (vertices <= 0) {
        cout << "���������� ������ ������ ���� �������������!" << endl;
        return;
    }

    graph = Graph(vertices);

    cout << "������� ���� (u v w), -1 ��� ���������:" << endl;
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
            cout << "������������ �����! ���������� �����." << endl;
            continue;
        }
        graph.addEdge(u, v, w);
    }
}

void createCompleteGraph(Graph& graph) {
    int vertices;
    cout << "���������� ������: ";
    cin >> vertices;

    if (vertices <= 0) {
        cout << "���������� ������ ������ ���� �������������!" << endl;
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
            cout << "��������� ������� (0-" << graph.getNumVertices() - 1 << "): ";
            cin >> startVertex;

            if (startVertex < 0 || startVertex >= graph.getNumVertices()) {
                cout << "�������� �������!" << endl;
                startVertex = -1;
            }
            distances.clear(); 
            break;
        }

        case 4: {
            if (startVertex == -1) {
                cout << "������� ������� ��������� �������!" << endl;
                break;
            }

            clock_t start = clock();
            distances = dijkstra->shortestPaths(startVertex, Dijkstra::D_HEAP, 2);
            double time = (clock() - start) / (double)CLOCKS_PER_SEC;

            cout << "��������� �� " << time * 1000 << " ��" << endl;
            break;
        }

        case 5: {
            if (startVertex == -1) {
                cout << "������� ������� ��������� �������!" << endl;
                break;
            }

            clock_t start = clock();
            distances = dijkstra->shortestPaths(startVertex, Dijkstra::BINOMIAL_HEAP);  
            double time = (clock() - start) / (double)CLOCKS_PER_SEC;

            cout << "��������� �� " << time * 1000 << " ��" << endl;
            break;
        }

        case 6: {
            if (distances.empty()) {
                cout << "������� ������� ����!" << endl;
                break;
            }

            int target;
            cout << "������� ������� (0-" << graph.getNumVertices() - 1 << "): ";
            cin >> target;

            if (target < 0 || target >= graph.getNumVertices()) {
                cout << "�������� �������!" << endl;
            }
            else if (distances[target] == -1) {
                cout << "�����������!" << endl;
            }
            else {
                cout << "����������: " << distances[target] << endl;
            }
            break;
        }

        case 7:
            graph.printGraph();
            break;

        default:
            cout << "�������� �����! ����������, �������� �� 1 �� 8." << endl;
        }
    }

    return 0;
}