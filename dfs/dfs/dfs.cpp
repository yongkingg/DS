#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

// 그래프 클래스 정의 (단방향 그래프)
class Graph {
public:
    unordered_map<char, vector<char>> adjList;  // 인접 리스트

    // 단방향 간선 추가
    void addEdge(char u, char v) {
        adjList[u].push_back(v);  // u에서 v로 가는 방향만 추가
    }

    // DFS 알고리즘 구현 (목표 노드까지 경로 추적)
    bool DFS(char start, char target, vector<char>& path) {
        stack<char> s;
        unordered_map<char, bool> visited;

        // 시작 노드를 스택에 푸시
        s.push(start);
        visited[start] = true;
        path.push_back(start);  // 경로에 추가

        while (!s.empty()) {
            char node = s.top();
            bool hasUnvisited = false;

            // 목표 노드에 도달했을 때
            if (node == target) {
                return true;  // 경로를 찾음
            }

            // 인접한 노드를 탐색
            for (char neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    s.push(neighbor);
                    visited[neighbor] = true;
                    path.push_back(neighbor);  // 경로에 추가
                    hasUnvisited = true;
                    break;  // 첫 방문하지 않은 노드로 이동
                }
            }

            // 방문하지 않은 인접 노드가 없으면 스택에서 팝
            if (!hasUnvisited) {
                s.pop();
                path.pop_back();  // 경로에서 마지막 노드를 제거 (잘못된 경로)
            }
        }

        return false;  // 경로를 찾지 못함
    }
};

int main() {
    Graph g;

    // 단방향 간선 추가 (화살표 방향에 맞게 추가)
    g.addEdge('P', 'R');  // P -> R
    g.addEdge('R', 'X');  // R -> X
    g.addEdge('P', 'W');  // P -> W
    g.addEdge('W', 'S');  // W -> S
    g.addEdge('S', 'T');  // S -> T
    g.addEdge('W', 'Y');  // W -> Y
    g.addEdge('Y', 'Z');  // Y -> Z

    // 경로 저장용 벡터
    vector<char> path;

    // DFS 실행 (P에서 시작, Z까지의 경로 탐색)
    if (g.DFS('P', 'Z', path)) {
        // 경로 출력
        cout << "P에서 Z까지의 경로: ";
        for (char node : path) {
            cout << node << " ";
        }
        cout << endl;
    }
    else {
        cout << "Z까지의 경로를 찾을 수 없습니다." << endl;
    }

    return 0;
}
