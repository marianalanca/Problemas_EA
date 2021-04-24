#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int module = 1000000007;
int n, h, H;
vector<vector<int>> vec1, vec2;
int total;

int mod_abs(int a, int mod) {
  return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b, int mod) {
  return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}

int mod_sub(int a, int b, int mod) {
  return mod_add(a, -b, mod);
}

void print_vector (vector<vector<int>> vector) {
  for (auto &row: vector) {
    cout << "[" << row[0] << ", " << row[1]<< "]\n";
  }
  cout << "\n";
}

int calc(vector<vector<int>> &previous, vector<vector<int>> &curr, int i){
  // (j-h<i && previous[i-1][0]!=0) 
  for (int j=0;j<=H-h && ((j-h<i) || (j-h>=i && previous[j-h][0]!=0));j++) {          // * O(H-h-1)
    // subida
    curr[j]= vector<int> (2,0); // esvaziar/

    // descida
    if (j==0){
      for (int k=1;k<h && j+k<=H-h && (previous[j+k][0]!=0 || previous[j+k][1]!=0) ;k++) {   // * O(h-1)
        curr[j][1] = mod_add(curr[j][1], previous[j+k][0], module);
        curr[j][1] = mod_add(curr[j][1], previous[j+k][1], module);
      }
    } else if (j>0) {
      // descida                                                                       // * O(1)
      curr[j][1] = curr[j-1][1];
      curr[j][1] = mod_sub(curr[j][1], previous[j][1], module);
      curr[j][1] = mod_sub(curr[j][1], previous[j][0], module);

      if (j+h-1<=H-h){
        curr[j][1] = mod_add(curr[j][1], previous[j+h-1][0], module);
        curr[j][1] = mod_add(curr[j][1], previous[j+h-1][1], module);
      }

      if (j>=i) {
        if (curr[j-1][0]==0) {  // o de baixo ainda não foi calculado
          for (int k=1;k<h && j-k>=0;k++) {                                             // * O(h-2)
            curr[j][0]= mod_add(curr[j][0], previous[j-k][0], module);
          }
        } else {
          curr[j][0] = mod_abs(curr[j-1][0], module);
          curr[j][0]= mod_add(curr[j][0], previous[j-1][0], module);

          if (j-h>=0) {
            curr[j][0]= mod_sub(curr[j][0], previous[j-h][0], module);
          }
        }
      }

    }
  }
  return curr[0][1];
}

void arc(){
  total = 0;
  for (int i=1;i<n;i++) {                                         // * O (n-2)
    if (i%2!=0) {
      total = mod_add(total, calc(vec1, vec2,i), module);
    } else {
      total = mod_add(total, calc(vec2, vec1,i), module);
    }
  }
}

int main() {
    // t - number of input lines
    // h - Height of the Lego blocks
    // n - number of Lego blocks given
    // H - Height of ceiling
    int t, H_aux;
    cin >> t;

    for (int i =0; i<t;i++){
        cin >> n >> h >> H;

         if(n%2==0){
              H_aux = h + (h-1)*(n/2 - 1);
          }
          else{
              H_aux = h + (h-1)*((n+1)/2 - 1);
          }

          if(H > H_aux){
              H = H_aux;
          }

        if ( n<3 || h >= H) {
          cout << "0\n";
        } else {
          vec1.clear();
          vec2.clear();

          vec1.resize(H-h+1, vector<int> (2,0));
          vec2.resize(H-h+1, vector<int> (2,0));

          vec1[0][0] = 1;
          arc();
          cout << total << '\n';
        }
    }
    return 0;
}