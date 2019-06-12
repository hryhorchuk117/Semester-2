#pragma once

#include "graphMatrix.h"

#include <iostream>
#include <random>
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>


struct graphEdges  {
    std::vector<std::vector<std::pair<int, int>>> edges;
    bool isOriented;

    graphEdges(int n, bool _isOriented) {
        std::vector<std::vector<std::pair<int, int>>> temp(n);
        edges = temp;
        isOriented = _isOriented;
    }
};


void addEdge(graphEdges& graph, int vertex1, int vertex2, int weight) {
    graph.edges[vertex1].push_back({vertex2, weight});
    if (!graph.isOriented) {
        graph.edges[vertex2].push_back({vertex1, weight});
    }
}

void printGraph(const graphEdges& graph) {
    for (int i = 0; i < graph.edges.size(); ++i) {
        for (auto& [vert, weight] : graph.edges[i]) {
            std::cout << i << "-" << vert << " " << weight << '\n';
        }
    }
}

graphEdges randomGraphEdge(int vertexNumber, int edgeNumber, bool isOriented) {
    graphEdges graph(vertexNumber, isOriented);
    std::vector<std::pair<int, int>> notConnected;

  if (isOriented) {
      for (int i = 0; i < vertexNumber; ++i) {
          for (int j = 0; j < vertexNumber; ++j) {
              if (i != j) {
                  notConnected.emplace_back(i, j);
              }
          }
      }
  } else {
      for (int i = 0; i < vertexNumber - 1; ++i) {
          for (int j = i + 1; j < vertexNumber; ++j) {
              notConnected.emplace_back(i, j);
          }
      }
  }

  for (int i = 0; i < edgeNumber; ++i) {
      int index = randomInt(0, notConnected.size() - 1);
      addEdge(graph, notConnected[index].first, notConnected[index].second, randomInt(0, MAX_WEIGHT));
      notConnected.erase(begin(notConnected) + index);
  }

  return graph;
}


template <class M>
void dfsComp (int v, M& used, std::vector<int>& comp, const graphEdges& graph) {
    used[v] = true;
    comp.push_back (v);
    for (auto item : graph.edges[v]) {
        if (!used[item.first]) {
            dfsComp(item.first, used, comp, graph);
        }
    }
}


void findComps(const graphEdges& graph) {
    bool used[MAX_VERT];
    std::vector<int> comp;

    for (int i = 0; i < graph.edges.size(); ++i) {
        used[i] = false;
    }
    for (int i = 0; i < graph.edges.size(); ++i)
        if (!used[i]) {
            comp.clear();
            dfsComp(i, used, comp, graph);

            std::cout << "Component:";
            for (auto item : comp)
                std::cout << ' ' << item;
            std::cout << "\n";
        }
}



template <class massive>
void dfs(int index, massive& used, graphEdges graph) {
    used[index] = true;
    for (int i = 0; i < graph.edges.size(); ++i) {
        if (!used[i]) {
            dfs(i, used, graph);
        }
    }
}

template <class massive>
void dfsWeight(int index, massive& used, graphEdges graph) {
    used[index] = true;
    std::vector<std::pair<int ,int>> next = graph.edges[index];

    std::sort(begin(next), end(next),
        [](std::pair<int ,int> lhs, std::pair<int ,int> rhs){return lhs.second < rhs.second;});

    for (auto& [ind, weight] : next) {
        if (!used[ind]) {
            dfsWeight(ind, used, graph);
        }
    }
}

void floyd(const graphEdges& graph, matr& res) {

    for (int i = 0; i < graph.edges.size(); ++i) {
        for (int j = 0; j < graph.edges.size(); ++j) {
            if (i == j) {
                res[i][j] = 0;
            } else res[i][j] = INT16_MAX;
        }
    }


    for (int i = 0; i < graph.edges.size(); ++i) {
        for (auto [vert, w] : graph.edges[i]) {
            res[i][vert] = w;
        }
    }

    for (int i = 0; i < graph.edges.size(); ++i) {
        for (int j = 0; j < graph.edges.size(); ++j) {
            for (int k = 0; k < graph.edges.size(); ++k) {
                if (res[j][k] > res[j][i] + res[i][k]) {
                    res[j][k] = res[j][i] + res[i][k];
                }
            }
        }
    }

    for (int i = 0; i < graph.edges.size(); ++i) {
        for (int j = 0; j < graph.edges.size(); ++j) {
            if (res[i][j] == INT16_MAX) {
                res[i][j] = -1;
            }
        }
    }

}


template <class massive>
void dfsTopol (int index, massive& used, graphEdges graph, std::vector<int>& res) {
    used[index] = true;
    for (auto item : graph.edges[index]) {
        if (!used[item.first]) {
            dfsTopol(item.first, used, graph, res);
        }
    }
    res.push_back(index);
}

std::vector<int> topologicalSort(graphEdges& graph) {
    std::vector<int> res;
    bool used[MAX_VERT];
    for (int i = 0; i < graph.edges.size(); ++i) {
        used[i] = false;
    }

    for (int i = 0; i < graph.edges.size(); ++i) {
        if (!used[i]) {
            dfsTopol(i, used, graph, res);
        }
    }

    reverse(res.begin(), res.end());
    return res;
}

graphMatrix bfsTree(graphEdges& graph) {
    std::queue<int> q;
    std::vector<std::pair<int, int>> edges;
    std::vector<bool> connected, visited;
    graphMatrix res(graph.edges.size(), graph.isOriented);
    int currVert = 0;

    for (int i = 0; i < graph.edges.size(); i++) {
        connected.push_back(false);
        visited.push_back(false);
    }

    for (int i = 0; i < graph.edges.size(); ++i) {
        for (int j = 0; j < graph.edges.size(); ++j) {
            res.matrix[i][j] = 0;
        }
    }

    q.push(currVert);
    connected[currVert] = true;

    while(!q.empty()) {
        currVert = q.front();
        q.pop();

        for (auto& item : graph.edges[currVert]) {
            if (!connected[item.first]) {
                res.matrix[currVert][item.first] = item.second;
                if (!graph.isOriented) {
                    res.matrix[item.first][currVert] = item.second;
                }
                connected[item.first] = true;
            }
        }

        for (const auto& item : graph.edges[currVert]) {
            edges.push_back(item);
        }

        sort(begin(edges), end(edges));

        for (int i = 0; i < edges.size(); i++) {
            if (!visited[edges[i].first]) {
                visited[edges[i].first] = true;
                q.push(edges[i].first);
            }
        }
  }

  return res;
}
