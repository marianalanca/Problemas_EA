#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <cmath>
using namespace std;

//int board_size, max_moves;
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

int arc(int n, int h, int H){
    return 2;
}

/*
if altura > H
SLIDE 20
*/

int main() {
    // t - number of input lines
    // h - Height of the Lego blocks
    // n - number of Lego blocks given
    // H - Height of ceiling
    int h, t, n, H;
    int res;

    cin >> t;

    for (int i =0; i<t;i++){
        cin >> n >> h >> H;
        res = mod_abs(arc(n, h, H), module); // ?
        cout << res << '\n';
    }

    return 0;
}
