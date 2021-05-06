#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
using namespace std;

int n, h, H;
vector<vector<int>> adj; // -> fazer vec com matriz para guardar os dados

void print(vector<vector<int>> grid) {
  for ( const std::vector<int> &v : grid )
  {
    for ( int x : v ) std::cout << x << ' ';
    std::cout << std::endl;
  }
}

int main() {
    int n, m, q;
    int t;
    int x, y, v;
    string str;

    cin >> t;

    for (int i =0; i<t;i++){
        cin >> n >> m >> q;
        adj.clear();

        // MELHORAR
        vector<int> temp (n , -1);
        adj.resize(n);
        fill (adj.begin(), adj.end(), temp);

        // MAL

        for (int j =0; j< m; j++) {
          cin >> x;
          cin >> y;
          cin >> v;
          adj[x-1][y-1] = v;
        }

        //print(adj);
    }
    return 0;
}