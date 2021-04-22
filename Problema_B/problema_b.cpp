#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <array>
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
vector<vector<vector<int>>> T;
//array<int, 2>

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

void print_vector (vector<vector<int>> matrix) {
  for ( const auto &row : matrix )
  {
    cout << "[" << row[0] <<","<<row[1] << "] ";
  }
  cout << endl;
}

void print_matrix (vector<vector<vector<int>>> matrix) {
  for ( const auto &row : matrix)
  {
    print_vector(row);
  }
}

int sum_vector(vector<int> vec) {
  int total = 0;
  for (auto& v : vec)
    total += v;
  return total;
}

int sum_line(vector<vector<vector<int>>> matrix, int h, int size){
  int sum = 0;
  for (int i=2;i<size;i++){
    sum+=matrix[h][i][1];
  }
  return sum;
}

int sum_line(vector<vector<int>> vector){
  int sum = 0;
  for (int i=2;i<(int)vector.size();i++){
    sum+=vector[i][1];
  }
  return sum;
}

void reserve_T() {
  vector<int> aux(2,0);
  T.resize(H+1);
  for (int i=0;i<H+1;i++) {
    T[i].resize(n);
    fill(T[i].begin(),T[i].end(),aux);
  }

  T[h][0][0] = 1;
}

vector<vector<int>> arc(){

  for (int i=0;i<n-1;i++) {
    for (int j=h;j<=H;j++) {
      if (T[j][i][0]!=0 || T[j][i][1]!=0) {
        for (int k=1;k<h;k++) {
          if(j+k<=H && T[j][i][0]!=0) {
            T[j+k][i+1][0]+= T[j][i][0];
          }

          // descida
          if(j-k>=h)
            T[j-k][i+1][1] += T[j][i][0] + T[j][i][1];
        }
      }
    }
  }
  return T[h];
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
        T.clear();
        reserve_T();
        // mudar modulo
        cout <<mod_abs(sum_line(arc()), module) << '\n';
    }
    return 0;
}