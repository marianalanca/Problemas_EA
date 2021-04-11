#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

/*
1. An arc consists of 3 ≤ k ≤ n blocks placed consecutively;

2. The first and last blocks must be placed on the floor;

3. The ith block must share at least 1 height with its neighbors;

4. The values of hi should be monotonically increasing, up to a certain block, and then monotonically decreasing.

*/

vector<vector<int>> T;
int module = 1000000007;

// Statement formulas
int mod_abs(int a, int mod) {
  return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b, int mod) {
  return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}

int mod_sub(int a, int b, int mod) {
  return mod_add(a, -b, mod);
}

void print_matrix (vector<vector<int>> matrix) {
  for ( const auto &row : matrix )
  {
    for ( const auto &s : row ) cout << s << ' ';
    cout << endl;
  }
}

int arc(int n, int h, int H){
  // mudar para resizes!
  int hi = 0, hi1 = 0;
  T.resize(n + 1);
  // são os primeiros 3 - alterar, eleminar 2 1ªs linhas
  T[0].resize(H + 1, 0); // {1st base case}
  T[1].resize(H + 1, 0); // {1st base case}
  T[2].resize(H + 1, 0); // {1st base case}

  for (int j=3; j < n+1; j++){ // {2nd base case}
    T[j].resize(H + 1); // h+1?
    T[j][0] = H+1;
  }

  // mal
  for (int i=3; i<n+1; i++) {
    for (int j=1; j<H+1; j++) {
      for (int k=1; k<h; k++) {
        hi1 = hi + k;
        if (hi1 > j) {
          T[i][j] = T[i-1][j];
        } else {
          T[i][j] = max(T[i-1][j], 1 + T[i][j-hi1]);
        }
      }
    }
  }
  //print_matrix(T);
  return T[n][H];
}

/*
Function change(n, C)
  for i = 0 to n do
    T[i, 0] = 0
  for j = 1 to C do
    T[0, j] = ∞
  for i = 1 to n do
    for j = 1 to C do
      if di > j then
        T[i, j] = T[i − 1, j]
      else
        T[i, j] = min(T[i − 1, j], 1 + T[i, j − di])
  return T[n, C]

*/

int main() {
    // t - number of input lines
    // h - Height of the Lego blocks
    // n - number of Lego blocks given
    // H - Height of ceiling
    int h, t, n, H;

    cin >> t;

    for (int i =0; i<t;i++){
        T.clear();
        cin >> n >> h >> H;
        cout << mod_abs(arc(n, h, H), module) << '\n';
    }

    return 0;
}
