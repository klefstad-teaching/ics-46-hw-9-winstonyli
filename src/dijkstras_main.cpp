#include "dijkstras.h"

int main(int argc, char *argv[]) {
  Graph g{};
  file_to_graph(argc > 1 ? argv[1] : "src/small.txt", g);

  vector<int> previous(g.numVertices, -1);
  auto distances = dijkstra_shortest_path(g, 0, previous);
  for (int dest = 0; dest < g.numVertices; ++dest) {
    auto path = extract_shortest_path(distances, previous, dest);
    print_path(path, distances[dest]);
  }

  return 0;
}