#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <stack>
using namespace std;

int n, t, POIs;
int sum_total, sum_parcial;
vector<vector<int>> adj;
vector<vector<vector<int>>> Scc;
vector<int> set, ranks;
vector<int> low, dfs;
vector<bool> onStack;

// Quando fazes o teu circuito ou seja a componente fortemente conexa ve se quando estas a fazer a MST estas a usar aa edges que vão para fora do circuito
// Se dois circuitos tiverem a mesma lane length ganha o que tiver mais POIs

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

vector<vector<int>> Kruskal(vector<vector<int>> &arcs){

    vector<vector<int>> T;
    int u, v;
    int sum_aux = 0;

    set.resize(n);
    ranks.resize(n, 0);

    make_set();

    for(auto & arc : arcs){
        u = arc[1];
        v = arc[2];

        if(find_set(u) != find_set(v)){

            if(T.empty()){
                T.push_back(arc);
                sum_total += arc[0];
                sum_aux += arc[0];
            }
            else{
                for(int i = 0; i < (int) T.size(); i ++){

                    if(T[i][0]>arc[0] || i == (int) T.size() - 1){
                        sum_total += arc[0];
                        sum_aux += arc[0];
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

    if(sum_parcial < sum_aux){
        sum_parcial = sum_aux;
    }

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
    static stack<int> S;

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
        vector<int> C_aux;
        int w;
        do{
            w = S.top();
            S.pop();
            onStack[w] = false;
            for (int el: C_aux) {
                if (adj[w][el]>0) {
                    C.push_back(vector<int> {adj[w][el], w, el});
                }
                if (adj[el][w]>0) {
                    C.push_back(vector<int> {adj[el][w], el, w});
                }
            }
            C_aux.push_back(w);
        } while(w!=v);
        if (C.size()>1) {
            if ((int) C_aux.size() > POIs) {
                POIs = C_aux.size();
            }
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

int main() {

    int m, q;
    int z;
    int x, y, v;

    cin >> z;

    for (int i =0; i<z;i++){
        cin >> n >> m >> q;

        if (q>=1) {

            t = 1;
            adj.clear();
            adj.resize(n);

            vector<int> temp (n, -1);
            fill (adj.begin(), adj.end(), temp);

            for (int j =0; j< m; j++) {

                cin >> x >> y >> v;
                adj[x-1][y-1] = v;
            }

            POIs = 0;

            callTarjan();
            //print(adj);
            cout << Scc.size();

            if (q>=2) {

                cout << ' ' << POIs;

                if (q>=3){
                    sum_total = 0;
                    sum_parcial=0;
                    for (auto arcs: Scc) {
                        sort(arcs.begin(), arcs.end(), sortcol); //ordenar por ordem crescente edges pelo custo
                        Kruskal(arcs);
                    }

                    cout << ' ' << sum_parcial;

                    if (q==4) {
                        cout << ' ' << sum_total;
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
