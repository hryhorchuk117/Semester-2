#pragma once

#include <iostream>
#include <random>
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

const int MAX_VERT = 1000000;
const int MAX_WEIGHT = 100;

using matr = int[MAX_WEIGHT][MAX_WEIGHT];


struct graphMatrix {
    matr matrix;
    bool isOriented = false;
    int vertexNumber = 0;

    graphMatrix(int newVertexNumber, bool newIsOriented) {
        this->vertexNumber = newVertexNumber;
        for(int i = 0; i < this->vertexNumber; ++i) {
            for(int j = 0; j < this->vertexNumber; ++j) {
                matrix[i][j] = 0;
            }
        }
        this->isOriented = newIsOriented;
    }
};

void addEdge(graphMatrix& graph, int vertex1, int vertex2, int weight) {
    graph.matrix[vertex1][vertex2] = weight;
    if (!graph.isOriented) {
        graph.matrix[vertex2][vertex1] = weight;
    }
}

void printGraph(const graphMatrix& graph) {
    for (int i = 0; i < graph.vertexNumber; ++i) {
        for (int j = 0; j < graph.vertexNumber; ++j) {
            std::cout << graph.matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}

int randomInt(int begin, int end) {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

graphMatrix randomGraphMatr(int vertexNumber, int edgeNumber, bool isOriented) {
    graphMatrix graph(vertexNumber, isOriented);

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
void dfsComp (int v, M& used, std::vector<int>& comp, const graphMatrix& graph) {
    used[v] = true;
    comp.push_back (v);
    for (int i = 0; i < graph.vertexNumber; ++i) {
        if (graph.matrix[v][i] != 0) {
            if (!used[i]) {
                dfsComp(i, used, comp, graph);
            }
        }
    }
}


void findComps(const graphMatrix& graph) {
    bool used[MAX_VERT];
    std::vector<int> comp;

    for (int i = 0; i < graph.vertexNumber; ++i) {
        used[i] = false;
    }
    for (int i = 0; i < graph.vertexNumber; ++i)
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
void dfs(int index, massive& used, graphMatrix graph) {
    used[index] = true;
    for (int i = 0; i < graph.vertexNumber; ++i) {
        if (!used[i]) {
            dfs(i, used, graph);
        }
    }
}

template <class massive>
void dfsWeight(int index, massive& used, graphMatrix graph) {
    used[index] = true;
    std::vector<std::pair<int ,int>> next;

    for (int i = 0; i < graph.vertexNumber; ++i) {
        if (graph.matrix[index][i] != 0) {
            next.emplace_back(i, graph.matrix[index][i]);
        }
    }
    std::sort(begin(next), end(next));

    for (auto& [ind, weight] : next) {
        if (!used[ind]) {
            dfsWeight(ind, used, graph);
        }
    }
}

void floyd(const graphMatrix& graph, matr& res) {
    for (int i = 0; i < graph.vertexNumber; ++i) {
        for (int j = 0; j < graph.vertexNumber; ++j) {
            if (graph.matrix[i][j] != 0) {
                res[i][j] = graph.matrix[i][j];
            } else if(i == j) {
                res[i][j] = 0;
        } else res[i][j] = INT16_MAX;
      }
  }



  for (int i = 0; i < graph.vertexNumber; ++i) {
      for (int j = 0; j < graph.vertexNumber; ++j) {
          for (int k = 0; k < graph.vertexNumber; ++k) {
              if (res[j][k] > res[j][i] + res[i][k]) {
                  res[j][k] = res[j][i] + res[i][k];
              }
          }
      }
  }

  for (int i = 0; i < graph.vertexNumber; ++i) {
      for (int j = 0; j < graph.vertexNumber; ++j) {
          if (res[i][j] == INT16_MAX) {
              res[i][j] = -1;
          }
      }
  }

}


template <class massive>
void dfsTopol (int index, massive& used, graphMatrix graph, std::vector<int>& res) {
  used[index] = true;
  for (int i = 0; i < graph.vertexNumber; ++i) {
      if (graph.matrix[index][i] != 0) {
          int to = graph.matrix[index][i];
          if (!used[to]) {
              dfsTopol(to, used, graph, res);
          }
      }
  }
  res.push_back(index);
}

std::vector<int> topologicalSort(graphMatrix graph) {
    std::vector<int> res;
    bool used[MAX_VERT];
    for (int i = 0; i < graph.vertexNumber; ++i) {
        used[i] = false;
    }

    for (int i = 0; i < graph.vertexNumber; ++i) {
        if (!used[i]) {
            dfsTopol(i, used, graph, res);
        }
    }

    reverse(res.begin(), res.end());
    return res;
}

graphMatrix bfsTree(graphMatrix& graph) {
  std::queue<int> q;
  std::vector<std::pair<int, int>> edges;
  std::vector<bool> connected, visited;
  graphMatrix res(graph.vertexNumber, graph.isOriented);
  int currVert = 0;

  for (int i = 0; i < graph.vertexNumber; i++) {
      connected.push_back(false);
      visited.push_back(false);
  }

  q.push(currVert);
  connected[currVert] = true;

  while(!q.empty()) {
      currVert = q.front();
      q.pop();

      for (int i = 0; i < graph.vertexNumber; i++) {
          if (graph.matrix[currVert][i] != 0 && !connected[i]) {
              res.matrix[currVert][i] = graph.matrix[currVert][i];
              if (!graph.isOriented) {
                  res.matrix[i][currVert] = graph.matrix[currVert][i];
              }
              connected[i] = true;
          }
      }

      for (int i = 0; i < graph.vertexNumber; i++) {
          if (graph.matrix[currVert][i] > 0) {
              edges.emplace_back(std::make_pair(i,graph.matrix[currVert][i]));
          }
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

std::vector<std::pair<int,int>> kruskal(std::vector<std::pair<int, std::pair<int,int>>> edges, int vertexNumber) {

    int cost = 0;
    std::vector<std::pair<int,int>> res;

  sort (begin(edges), end(edges));
  std::vector<int> treeId(vertexNumber);
  for (int i=0; i < vertexNumber; ++i) {
      treeId[i] = i;
  }

  for (int i = 0; i < edges.size(); ++i) {
      int a = edges[i].second.first,  b = edges[i].second.second,  l = edges[i].first;
      if (treeId[a] != treeId[b]) {
          cost += l;
          res.emplace_back(a, b);
          int oldId = treeId[b], newId = treeId[a];

          for (int j = 0; j < vertexNumber; ++j) {
              if (treeId[j] == oldId) {
                  treeId[j] = newId;
              }
          }
    }
  }

  return res;
}