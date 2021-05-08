#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <stack>
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
vector<vector<int>> Scc;
int t;
stack<int> C;
stack<int> S;
vector<bool> onStack;

void print(vector<vector<int>> grid) {
  for ( const std::vector<int> &v : grid )
  {
    for ( int x : v ) std::cout << x << ' ';
    std::cout << std::endl;
  }
  cout << '\n';
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

void Tarjan(int v){
    static stack<int> st;

    dfs[v]=low[v]=t++;
    st.push(v);
    onStack[v]=true;
    for(auto w:adj[v]){
        if(dfs[w]==-1){
            Tarjan(w);
            low[v]=min(low[v],low[w]);
        }
        else if(onStack[w])
            low[v]=min(low[v],dfs[w]);
    }
    if(dfs[v]==low[v]){
        vector<int> C;
        while(1){
            int w=st.top();
            st.pop();
            onStack[v]=false;
            C.push_back(v);
            if(v==w)
                break;
        }
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

        t = 1;

        adj.clear();
        adj.resize(n);

        low.clear();
        low.resize(n);

        dfs.clear();
        dfs.resize(n ,-1);

        Scc.clear();

        onStack.clear();
        onStack.resize(n);

        // MELHORAR
        vector<int> temp (n);
        fill (adj.begin(), adj.end(), temp);

        C = stack<int>();
        S = stack<int>();

        // MAL

        for (int j =0; j< m; j++) {
          cin >> x >> y >> v;
          adj[x-1][y-1] = v;
        }

        for (int k = 0;k < n; k++) {
          if (dfs[x-1] == -1)
            Tarjan(x-1);
        }

        print(Scc);
        //print_deque(Scc);
    }
    cout << "final\n";
    return 0;
}