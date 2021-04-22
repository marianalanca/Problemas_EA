#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <array>
#include <algorithm>
using namespace std;

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

int sum_line(vector<vector<int>> vector){
  int sum = 0;
  for (int i=2;i<(int)vector.size();i++){
    sum+= mod_abs(vector[i][1], module);
  }
  return mod_abs(sum, module);
}

void reserve_T() {
  vector<int> aux(2,0);
  T.resize(H-h+1);
  for (int i=0;i<H-h+1;i++) {
    T[i].resize(n);
    fill(T[i].begin(),T[i].end(),aux);
  }

  T[0][0][0] = 1;
}

vector<vector<int>> arc(){
  for (int i=0;i<n-1;i++) {
    for (int j=0;j<=H-h;j++) {
      if (T[j][i][0]!=0 || T[j][i][1]!=0) {
        for (int k=1;k<h;k++) {
          if(j+k<=H-h && T[j][i][0]!=0) {
            T[j+k][i+1][0]+= mod_abs(T[j][i][0], module);
          }
          // descida
          if(j-k>=0)
            T[j-k][i+1][1] += mod_add(T[j][i][0], T[j][i][1], module);
        }
      }
    }
  }
  return T[0];
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
        cout << sum_line(arc()) << '\n';
    }
    return 0;
}