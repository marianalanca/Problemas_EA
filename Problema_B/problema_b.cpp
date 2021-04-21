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
vector<vector<int>> T;

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
    cout << '\n';
  }
  cout << endl;
}

int sum_vector(vector<int> vec) {
  int total = 0;
  for (auto& v : vec)
    total += v;
  return total;
}

int sum_line(vector<vector<int>> matrix, int h, int size){
  int sum = 0;
  for (int i=2;i<size;i++){
    sum+=matrix[h][i];
  }
  return sum;
}

int sum_line(vector<int> vector){
  int sum = 0;
  for (int i=2;i<(int)vector.size();i++){
    sum+=vector[i];
  }
  return sum;
}

void reserve_T() {
  T.resize(H+1);
  for (int i=0;i<H+1;i++) {
    T[i].resize(n);
    fill(T[i].begin(),T[i].end(),0);
  }

  T[h][0] = 1;

  /*for (int i=3;i<n+1;i++) {
    T[h][i] = 1;
  }*/

}

vector<int> arc(){
  int h_sub_min = 0;
  vector <int> test;

  for (int i=0;i<n-1;i++) {
    for (int j=h;j<H+1;j++) {
      if (T[j][i]!=0) {
        h_sub_min = j+1;

        for (int k=1; k < h && j+k<H+1; k++) {
          // subida
          if (j+k>=h_sub_min)                                    // HERE
            T[j+k][i+1] += k;
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
        //print_matrix(T);
        //arc();

        // sum_line(T,h,n)
        cout <<mod_abs(sum_line(arc()), module) << '\n';
        print_matrix(T);
        //cout << "\n\n";
    }

    return 0;
}