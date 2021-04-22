#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

/*
1. An arc consists of 3 ≤ k ≤ n blocks placed consecutively;

2. The first and last blocks must be placed on the floor;

3. The ith block must share at least 1 height with its neighbors;

4. The values of hi should be monotonically increasing, up to a certain block, and then monotonically decreasing.

*/

int module = 1000000007;
int n, h, H;

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
void print_vector (vector<int> matrix) {
  for ( const auto &row : matrix )
  {
    cout << row << ' ';
    cout << ' ';
  }
  cout << endl;
}

int sum_vector(vector<int> vec) {
  int total = 0;
  for (auto& v : vec)
    total += v;
  return total;
}
// direction -> 1 - up; 0 -> down
vector <int> DP;
int accepted;
int arc(int ni, int hi, bool direction){

  if (ni >= 3 && hi==h) { // se chegou ao final e está na posição certa -> conta
   return 1;
  }
  if (ni == n && hi!=h) { // mudar!!! -> se chegou ao final e não está no chão! -> não conta
    return 0;
  }

  for (int k=1; k < h; k++) {

    if (direction) {
      if (hi+k <=H){
        //cout << "trying to add ascending " << hi+k << "\tH "<<H <<'\n';
        DP[ni] += arc(ni+1, hi + k, true);
        //cout << "var1: "<<var1 << '\n';
      }
    }

    if (hi-k >= h) {
      //cout << "trying to add descending " << hi-k <<'\n';
      DP[ni] += arc(ni+1, hi - k, false);
    }
  }

  return DP[n];
}

int main() {
    // t - number of input lines
    // h - Height of the Lego blocks
    // n - number of Lego blocks given
    // H - Height of ceiling
    int t;

    cin >> t;

    for (int i =0; i<t;i++){
        cin >> n >> h >> H;

        if ( n<3 || h >= H) {
          cout << "0\n";
          continue;
        }
        DP.clear();
        DP.resize(n+1);
        DP[0] = 0;
        accepted = 0;
        arc(1, h, true);
        print_vector(DP);
        //cout << mod_abs(sum_vector(DP), module) << '\n';
    }

    return 0;
}