#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int module = 1000000007;
int n, h, H;
vector<vector<int>> previous, curr;
int total;

int mod_abs(int a, int mod) {
  return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b, int mod) {
  return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}

void arc(){
  for (int i=0;i<n-1;i++) {
    for (int j=0;j<=H-h && !(j>n+1 && curr[j][0]==0);j++) {
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
    total = mod_add(total, curr[0][1], module); // ignora logo a primeira linha e na segunda não pode ter
    previous = curr;
    fill(curr.begin(), curr.end(), vector<int> (2,0));
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

        if ( n<3 || h >= H) {
          cout << "0\n";
          continue;
        }
        previous.clear();
        curr.clear();

        if(n%2==0){
            H_aux = h + (h-1)*(n/2 - 1);
        }
        else{
            H_aux = h + (h-1)*((n+1)/2 - 1);
        }

        if(H > H_aux){
            H = H_aux;
        }

        previous.resize(H-h+1, vector<int> (2,0));
        curr.resize(H-h+1, vector<int> (2,0));

        previous[0][0] = 1;
        arc();
        cout << total << '\n';
        total = 0;
    }
    return 0;
}