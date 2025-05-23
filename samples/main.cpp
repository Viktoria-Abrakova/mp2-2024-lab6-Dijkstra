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
    cout << "8. ��������� ��� �����" << endl; 
    cout << "9. �����" << endl;
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
    cout << "\n���� ������� ������!\n";
}

void createCompleteGraph(Graph& graph) {
    size_t vertices;
    int percent;

    while (true) {
        cout << "������� ���������� ������ ����� (>= 2): ";
        cin >> vertices;

        if (vertices >= 2) break;
        cout << "������: ���������� ������ ������ ���� �� ����� 2!" << endl;
    }

    while (true) {
        cout << "������� ������� ������������� ����� (0-100): ";
        cin >> percent;

        if (percent >= 0 && percent <= 100) break;
        cout << "������: ������� ������ ���� � ��������� �� 0 �� 100!" << endl;
    }

    graph = Graph(vertices);
    int weight = 1;

    for (size_t i = 1; i < vertices; ++i) {
        graph.addEdge(i - 1, i, weight++);
        cout << "��������� �����: " << i - 1 << " - " << i << " (���: " << weight - 1 << ")\n";
    }

    size_t maxEdges = vertices * (vertices - 1) / 2;
    size_t targetEdges = (maxEdges * percent) / 100;
    size_t remainingEdges = targetEdges > (vertices - 1) ? targetEdges - (vertices - 1) : 0;

    cout << "\n��������� �������������� �����...\n";
    cout << "����� ����� ��������� �����: " << remainingEdges << "\n";

    for (size_t i = 0; i < vertices && remainingEdges > 0; ++i) {
        for (size_t j = i + 2; j < vertices && remainingEdges > 0; ++j) {
            if (graph.getEdgeWeight(i, j) == -1) {
                graph.addEdge(i, j, weight++);
                cout << "��������� �����: " << i << " - " << j << " (���: " << weight - 1 << ")\n";
                remainingEdges--;
            }
        }
    }

    cout << "\n���� ������� ������!\n";
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

        if (choice == 9) break;

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

            myVector<int> predecessors;
            clock_t start = clock();
            distances = dijkstra->shortestPathsWithPredecessors(startVertex, Dijkstra::D_HEAP, predecessors, 2);
            double time = (clock() - start) / (double)CLOCKS_PER_SEC;

            cout << "��������� �� " << time * 1000 << " ��" << endl;
            break;
        }

        case 5: {
            if (startVertex == -1) {
                cout << "������� ������� ��������� �������!" << endl;
                break;
            }

            myVector<int> predecessors;
            clock_t start = clock();
            distances = dijkstra->shortestPathsWithPredecessors(startVertex, Dijkstra::BINOMIAL_HEAP, predecessors, 2);
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

                myVector<int> predecessors;
                dijkstra->shortestPathsWithPredecessors(startVertex, Dijkstra::D_HEAP, predecessors, 2);
                myVector<int> path = graph.getPath(startVertex, target, predecessors);

                if (path.empty()) {
                    cout << "���� �� ������!" << endl;
                }
                else {
                    cout << "����: ";
                    for (size_t i = 0; i < path.size(); ++i) {
                        cout << path[i];
                        if (i != path.size() - 1) {
                            cout << " -> ";
                        }
                    }
                    cout << endl;
                }
            }
            break;
        }

        case 7:
            graph.printGraph();
            break;

        case 8: {  
            int u, v;
            cout << "������� ������� u: ";
            cin >> u;
            cout << "������� ������� v: ";
            cin >> v;

            try {
                int weight = graph.getEdgeWeight(u, v);
                if (weight == -1) {
                    cout << "����� (" << u << ", " << v << ") �����������!" << endl;
                }
                else {
                    cout << "��� ����� (" << u << ", " << v << "): " << weight << endl;
                }
            }
            catch (const std::out_of_range& e) {
                cout << "������: " << e.what() << endl;
            }
            break;
        }

        default:
            cout << "�������� �����! ����������, �������� �� 1 �� 9." << endl;
        }
    }

    return 0;
}