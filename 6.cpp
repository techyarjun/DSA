#include<iostream>
#include<map>
#include<vector>
#include<queue>
using namespace std;

int main() {
    map<string, vector<string>> graph;
    int n;
    cout << "Enter number of flights: ";
    cin >> n;

    cout << "Enter flights as: CityA CityB\n";
    for (int i = 0; i < n; i++) {
        string a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    // Display graph
    cout << "\nFlight paths:\n";
    for (auto& city : graph) {
        cout << city.first << " -> ";
        for (auto& dest : city.second) cout << dest << " ";
        cout << endl;
    }

    // Check connectivity using BFS
    map<string, bool> visited;
    queue<string> q;
    q.push(graph.begin()->first);
    visited[q.front()] = true;

    while (!q.empty()) {
        string city = q.front(); q.pop();
        for (auto& dest : graph[city]) {
            if (!visited[dest]) {
                visited[dest] = true;
                q.push(dest);
            }
        }
    }

    bool connected = true;
    for (auto& c : graph)
        if (!visited[c.first])
            connected = false;

    cout << "\nThe graph is " << (connected ? "connected.\n" : "NOT connected.\n");

    return 0;
}
