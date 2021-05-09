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

int n, t;
vector<vector<int>> adj; // -> fazer vec com matriz para guardar os dados
vector<vector<int>>arcs;
vector<int> set, ranks;
vector<int> low, dfs;
vector<vector<int>> Scc;
stack<int> C;
stack<int> S;
vector<bool> onStack;

bool sortcol( const vector<int>& v1,
              const vector<int>& v2 ) {
    return v1[0] < v2[0];
}

void make_set(){
    for(int i=0; i < n;i++){
        set[i]=i;
    }
}

int find_set(int a){

    if (set[a] != a){
        set[a] = find_set(set[a]);
    }

    return set[a];
}

void link(int a, int b){
    if(ranks[a] > ranks[b]){
        set[b] = a;
    }
    else{
        set[a] = b;
    }
    if(ranks[a] == ranks[b]){
        ranks[b]++;
    }
}

void unionLink(int a, int b){
    link(find_set(a), find_set(b));
}


vector<vector<int>> Kruskal(){

    vector<vector<int>> T;
    int u, v;
    
    set.resize(n);
    ranks.resize(n, 0);

    make_set();

    for(auto & arc : arcs){
        u = arc[1];
        v = arc[2];

        if(find_set(u) != find_set(v)){

            if(T.empty()){
                T.push_back(arc);
            }
            else{
                for(int i = 0; i < T.size(); i ++){

                    if(T[i][0]>arc[0] or i == T.size() - 1){
                        T.push_back(arc);
                        break;
                    }
                    if(T[i][0]==arc[0] and T[i][1]==arc[1] and T[i][1]==arc[1]){
                        break;
                    }

                }
            }

            unionLink(u, v);
        }
    }
    
    set.clear();
    ranks.clear();

    return T;
}


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

    vector<int> aux;

    cin >> z;

    for (int i =0; i<z;i++){
        cin >> n >> m >> q;

        t = 1;

        adj.clear();
        adj.resize(n);

        arcs.clear();

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
            aux.resize(3);

            cin >> x >> y >> v;
            adj[x-1][y-1] = v;

            aux[0]=v;
            aux[1]=x-1;
            aux[2]=y-1;
            arcs.push_back(aux);

            aux.clear();
        }

        sort(arcs.begin(), arcs.end(), sortcol); //ordenar por ordem crescente edges pelo custo

        for (int k = 0;k < n; k++) {
          if (dfs[x-1] == -1)
            Tarjan(x-1);
        }

        //print(Scc);
        //print_deque(Scc);

        //print(adj);

        cout << "\n-----------------ARCS--------------------\n";

        print(arcs);

        cout << "\n-----------------KRUSKAL--------------------\n";

        print(Kruskal());
    }
    cout << "final\n";
    return 0;
}
