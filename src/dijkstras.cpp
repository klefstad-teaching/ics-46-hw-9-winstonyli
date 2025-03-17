#include "dijkstras.h"
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

vector<int> dijkstra_shortest_path(const Graph &G, int source,
                                   vector<int> &previous) {
  vector<int> distances(G.numVertices, INF);

  auto compare = [&](auto a, auto b) { return a.second > b.second; };
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> q{
      compare};

  q.push({source, distances[source] = 0});
  previous[source] = -1;

  while (!q.empty()) {
    auto [v, dist] = q.top();
    q.pop();

    for (auto edge : G[v]) {
      int new_dist = dist + edge.weight;
      if (dist < INF && new_dist < distances[edge.dst])
        q.push({edge.dst, distances[edge.dst] = new_dist}),
            previous[edge.dst] = v;
    }
  }

  return distances;
}

vector<int> extract_shortest_path(const vector<int> &distances,
                                  const vector<int> &previous,
                                  int destination) {
  vector<int> path{};
  do
    path.push_back(destination);
  while ((destination = previous[destination]) != -1);
  std::reverse(path.begin(), path.end());
  return path;
}

void print_path(const vector<int> &v, int total) {
  for (int u : v)
    cout << u << ' ';
  cout << "\nTotal cost is " << total << '\n';
}
