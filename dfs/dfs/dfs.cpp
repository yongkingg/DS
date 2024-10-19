#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

// �׷��� Ŭ���� ���� (�ܹ��� �׷���)
class Graph {
public:
    unordered_map<char, vector<char>> adjList;  // ���� ����Ʈ

    // �ܹ��� ���� �߰�
    void addEdge(char u, char v) {
        adjList[u].push_back(v);  // u���� v�� ���� ���⸸ �߰�
    }

    // DFS �˰��� ���� (��ǥ ������ ��� ����)
    bool DFS(char start, char target, vector<char>& path) {
        stack<char> s;
        unordered_map<char, bool> visited;

        // ���� ��带 ���ÿ� Ǫ��
        s.push(start);
        visited[start] = true;
        path.push_back(start);  // ��ο� �߰�

        while (!s.empty()) {
            char node = s.top();
            bool hasUnvisited = false;

            // ��ǥ ��忡 �������� ��
            if (node == target) {
                return true;  // ��θ� ã��
            }

            // ������ ��带 Ž��
            for (char neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                    visited[neighbor] = true;
                    path.push_back(neighbor);  // ��ο� �߰�
                    hasUnvisited = true;
                    break;  // ù �湮���� ���� ���� �̵�
                }
            }

            // �湮���� ���� ���� ��尡 ������ ���ÿ��� ��
            if (!hasUnvisited) {
                s.pop();
                path.pop_back();  // ��ο��� ������ ��带 ���� (�߸��� ���)
            }
        }

        return false;  // ��θ� ã�� ����
    }
};

int main() {
    Graph g;

    // �ܹ��� ���� �߰� (ȭ��ǥ ���⿡ �°� �߰�)
    g.addEdge('P', 'R');  // P -> R
    g.addEdge('R', 'X');  // R -> X
    g.addEdge('P', 'W');  // P -> W
    g.addEdge('W', 'S');  // W -> S
    g.addEdge('S', 'T');  // S -> T
    g.addEdge('W', 'Y');  // W -> Y
    g.addEdge('Y', 'Z');  // Y -> Z

    // ��� ����� ����
    vector<char> path;

    // DFS ���� (P���� ����, Z������ ��� Ž��)
    if (g.DFS('P', 'Z', path)) {
        // ��� ���
        cout << "P���� Z������ ���: ";
        for (char node : path) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "Z������ ��θ� ã�� �� �����ϴ�." << endl;
    }

    return 0;
}
