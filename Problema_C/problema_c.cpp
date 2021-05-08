#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <deque>
using namespace std;

/*
Tarjan, FF(GR)

Function FF(GR)
  mflow = 0
  while there is a s-t path P in GR do
  fp
  = minfc(u; v) j (u; v) 2 Pg
  for each arc (u; v) in P do
  c(u; v) = c(u; v) − fp
  c(v; u) = c(v; u) + fp
  mflow = mflow + fp
  return mflow


  For each arc (u; v) in G, GR contains an arc (u; v) with
  capacity c(u; v) and an arc (v; u) with capacity 0.


  But if the s-t path with the least number of arcs is chosen (with
  BFS), the time complexity reduces to O(jV j · jEj2) for any network
  (Edmond-Karp Algorithm).
*/

int n;
vector<vector<int>> adj; // -> fazer vec com matriz para guardar os dados
vector<int> low, dfs;
vector<deque<int>> Scc;
int t;
deque<int> C;
deque<int> S;

void print(vector<vector<int>> grid) {
  for ( const std::vector<int> &v : grid )
  {
    for ( int x : v ) std::cout << x << ' ';
    std::cout << std::endl;
  }
}

void print(vector<int> vec) {
  for(auto iter = vec.begin(); iter != vec.end(); ++iter) {
        cout << *iter << ' ';
  }
  cout << "\n";
}

void print_deque(vector<deque<int>> deque) {
  for(auto iter = deque.begin(); iter != deque.end(); ++iter) {
      for(auto iter_row = (*iter).rbegin(); iter_row != (*iter).rend(); ++iter_row) {
          cout << *iter_row << ' ';
      }
      cout << '\n';
  }
  cout << "\n\n";
}

void print_deque(deque<int> deque) {
    for(auto iter_row = deque.rbegin(); iter_row != deque.rend(); ++iter_row) {
        cout << *iter_row << ' ';
    }
    cout << '\n';
}

void Tarjan(int v) {
  low[v] = dfs[v] = t;
  t++;
  S.push_front(v);
  for (int w=0; w<n;w++){                       // ?
    if (dfs[w] == -1) { // inicializar dfs a -1
      Tarjan(w);
      low[v] = min(low[v], low[w]);
    } else if (find(S.begin(), S.end(), w) == S.end()) {
      low[v] =  min(low[v], low[w]);
    }
  }
  // !DEBUG
  // cout << "v: " << v << " low[v] " << low[v] << " dfs[v] " << dfs[v] << '\n';
  if (low[v] == dfs[v]) {
    int w;
    do {
      w = S.front();
      S.pop_front();
      C.push_front(w);
    } while(w!=v);
    Scc.push_back(C);
  }
}

int main() {
    int m, q;
    int z;
    int x, y, v;

    cin >> z;

    for (int i =0; i<z;i++){
        cin >> n >> m >> q;
        adj.clear();
        t = 1;

        low.clear();
        low.resize(n , 1000);

        dfs.clear();
        dfs.resize(n ,0);
        Scc.clear();

        // MELHORAR
        vector<int> temp (n , -1);
        adj.resize(n);
        fill (adj.begin(), adj.end(), temp);

        // MAL

        for (int j =0; j< m; j++) {
          C.clear();
          cin >> x;
          cin >> y;
          cin >> v;
          adj[x-1][y-1] = v;
          low[y-1] = dfs[y-1] = -1; // ?
          //print(dfs);
          S.clear();
          Tarjan(x-1);
        }

        //print(adj);
        print_deque(Scc);
    }
    return 0;
}