#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

/*
https://gist.github.com/APwhitehat/e2ae94b811defc7407bc320f98fd268b#file-tarjan-cpp-L51
*/

int n, t;
vector<vector<int>> adj; // -> fazer vec com matriz para guardar os dados
vector<vector<int>>arcs;
vector<int> set, ranks;
vector<int> low, dfs;
vector<vector<vector<int>>> Scc;
stack<int> C;
stack<int> S;
vector<bool> onStack;

bool sortcol( const vector<int>& v1, const vector<int>& v2 ) {
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

                    if(T[i][0]>arc[0] || i == T.size() - 1){
                        T.push_back(arc);
                        break;
                    }
                    if(T[i][0]==arc[0] && T[i][1]==arc[1] && T[i][1]==arc[1]){
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
    for ( int x : v ) std::cout << x+1 << ' ';
    std::cout << std::endl;
  }
  cout << '\n';
}

void print(vector<vector<vector<int>>> grid) {
  for ( const std::vector<vector<int>> &v : grid )
  {
    for ( vector<int> x : v ) {
        for ( int y : x ) {
            std::cout << y+1 << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}


void print(vector<int> vec) {
  for(auto iter = vec.begin(); iter != vec.end(); ++iter) {
        cout << *iter << ' ';
  }
  cout << "\n";
}

void Tarjan(int v){
    static stack<int> S;    // guardar a informação toda

    dfs[v]=low[v]=t++;

    S.push(v);
    onStack[v]=true;
    //for(auto i:adj[v]){
    for (int i=0;i<n;i++) {
        if (adj[v][i]!=-1){
            if(adj[v][i]!=-1 && dfs[i]==-1){
                Tarjan(i);
                low[v]=min(low[v],low[i]);
            }
            else if(onStack[i])
                low[v]=min(low[v],dfs[i]);
        }
    }
    if(dfs[v]==low[v]){
        vector<vector<int>> C;
        int w;
        do{
            w = S.top();
            S.pop();
            onStack[w]=false;
            C.push_back(vector<int> {adj[v][w], v, w}); // ! MAL
        } while(w!=v);
        if (C.size()>1) {
           Scc.push_back(C);
        }
    }
}

void callTarjan() {
  t = 1;

  dfs.clear();
  dfs.resize(n , -1);

  low.clear();
  low.resize(n);

  Scc.clear();

  onStack.clear();
  onStack.resize(n, 0);

  for (int k = 0;k < n; k++) {
    if (dfs[k] == -1)
      Tarjan(k);
  }
}

int findBiggestPath() {
    int best = 0;
    for (auto circuit: Scc) {
        if ((int) circuit.size() > best) {
            best = circuit.size();
        }
    }
    return best;
}

int main() {

    int m, q;
    int z;
    int x, y, v;

    vector<int> aux;

    cin >> z;

    for (int i =0; i<z;i++){
        cin >> n >> m >> q;

        if (q>=1) {

            t = 1;
            adj.clear();
            adj.resize(n);

            vector<int> temp (n, -1);
            fill (adj.begin(), adj.end(), temp);

            arcs.clear();

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

            callTarjan();
            print(Scc);
            //cout << Scc.size() << ' ';

            if (q>=2) {
                //cout << findBiggestPath() << ' ';

                if (q>=3){
                    sort(arcs.begin(), arcs.end(), sortcol); //ordenar por ordem crescente edges pelo custo
                    Kruskal();
                    // calc Krustal
                    if (q==4) {

                    }
                }
            }
            cout << '\n';
        }

        /*cout << "\n-----------------TARJAN--------------------\n";

        print(Scc);

        cout << "\n-----------------ARCS--------------------\n";

        print(arcs);

        cout << "\n-----------------KRUSKAL--------------------\n";

        print(Kruskal());*/
    }
    return 0;
}
