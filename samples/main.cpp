#include <iostream>
#include <random>
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

#include <iostream>
#include <random>

void createCompleteGraph(Graph& graph) {
    size_t vertices;
    int percent;

    std::random_device rd;
    std::mt19937 gen(rd());

    while (true) {
        std::cout << "������� ���������� ������ ����� (>= 2): ";
        std::cin >> vertices;
        if (vertices >= 2) break;
        std::cout << "������: ���������� ������ ������ ���� �� ����� 2!\n";
    }

    while (true) {
        std::cout << "������� ������� ������������� ����� (0-100): ";
        std::cin >> percent;
        if (percent >= 0 && percent <= 100) break;
        std::cout << "������: ������� ������ ���� � ��������� �� 0 �� 100!\n";
    }

    graph = Graph(vertices);

    myVector<size_t> unused_vertices;
    myVector<size_t> used_vertices;

    size_t first_vertex = gen() % vertices;
    used_vertices.push_back(first_vertex);

    for (size_t i = 0; i < vertices; ++i) {
        if (i != first_vertex) {
            unused_vertices.push_back(i);
        }
    }

    for (size_t i = 0; i < unused_vertices.size(); ++i) {
        size_t range = unused_vertices.size() - i;
        size_t j = i + (gen() % range);
        size_t temp = unused_vertices[i];
        unused_vertices[i] = unused_vertices[j];
        unused_vertices[j] = temp;
    }

    while (!unused_vertices.empty()) {
        size_t new_vertex = unused_vertices.back();
        unused_vertices.pop_back();

        size_t random_index = gen() % used_vertices.size();
        size_t connect_to = used_vertices[random_index];

        int weight = 1 + (gen() % 100);
        graph.addEdge(new_vertex, connect_to, weight);
        std::cout << "��������� �����: " << new_vertex << " - "
            << connect_to << " (���: " << weight << ")\n";

        used_vertices.push_back(new_vertex);
    }

    size_t maxEdges = vertices * (vertices - 1) / 2;
    size_t targetEdges = (maxEdges * percent) / 100;
    size_t remainingEdges = targetEdges > (vertices - 1) ? targetEdges - (vertices - 1) : 0;

    std::cout << "\n��������� �������������� �����...\n";
    std::cout << "����� ����� ��������� �����: " << remainingEdges << "\n";

    myVector<std::pair<size_t, size_t>> possible_edges;
    for (size_t i = 0; i < vertices; ++i) {
        for (size_t j = i + 1; j < vertices; ++j) {
            if (graph.getEdgeWeight(i, j) == -1) {
                possible_edges.push_back(std::pair<size_t, size_t>(i, j));
            }
        }
    }

    for (size_t i = 0; i < possible_edges.size(); ++i) {
        size_t range = possible_edges.size() - i;
        size_t j = i + (gen() % range);
        std::pair<size_t, size_t> temp = possible_edges[i];
        possible_edges[i] = possible_edges[j];
        possible_edges[j] = temp;
    }

    for (size_t i = 0; i < remainingEdges && i < possible_edges.size(); ++i) {
        size_t u = possible_edges[i].first;
        size_t v = possible_edges[i].second;
        int weight = 1 + (gen() % 100);
        graph.addEdge(u, v, weight);
        std::cout << "��������� �������������� �����: " << u << " - "
            << v << " (���: " << weight << ")\n";
    }

    std::cout << "\n���� ������� ������!\n";
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