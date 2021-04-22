#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <array>
#include <algorithm>
using namespace std;

int module = 1000000007;
int n, h, H;
vector<vector<int>> previous, curr;
int total;
vector<int> aux(2,0);

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
    sum= mod_add(sum, vector[i][1], module);
  }
  return sum;
}

void reserve_T() {
  previous.resize(H-h+1, aux);
  curr.resize(H-h+1, aux);

  previous[0][0] = 1;
}

void arc(){
  for (int i=0;i<n-1;i++) {
    for (int j=0;j<=H-h;j++) {
      if (previous[j][0]!=0 || previous[j][1]!=0) {
        for (int k=1;k<h;k++) {
          // subida
          if(j+k<=H-h && previous[j][0]!=0) {
            curr[j+k][0]= mod_add(curr[j+k][0], previous[j][0], module);
          }

          // descida
          if(j-k>=0){
            curr[j-k][1] = mod_add(curr[j-k][1], previous[j][0], module);
            curr[j-k][1] = mod_add(curr[j-k][1], previous[j][1], module);
          }
        }

      }
    }
    total = mod_add(total, curr[0][1], module); // ignora logo a primeira linha e na segunda não pode ter
    previous = curr;
    fill(curr.begin(), curr.end(), aux); // ????????????????
  }
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
        previous.clear();
        curr.clear();
        reserve_T();
        // mudar modulo
        arc();
        cout << total << '\n';
        total = 0;
    }
    return 0;
}