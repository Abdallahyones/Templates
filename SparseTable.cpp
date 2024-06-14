#include <bits/stdc++.h>


#define Body_code  ios_base::sync_with_stdio(false);cin.tie(NULL);
#define files    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
#define clo cout << "Time execute: " << clock()/ (double)CLOCKS_PER_SEC << " sec" << endl;
#define all(ele)  ele.begin(), ele.end()
#define fo(i , n) for (int i =0 ; i < n ; i++)
#define ll long long
#define Ull unsigned long long
#define MX INT_MAX
#define MN INT_MIN
#define LMX  LONG_LONG_MAX
#define LMN LONG_LONG_MIN
#define yes cout << "YES";
#define no cout << "NO";
#define X first
#define Y second



using namespace std;

const int N = 2e5+7, mod = 1e9+7 ;


ll st[25][N];
int arr[N] , lg[N];

ll fun(ll a , ll b){
    return min(a , b);
}

void SparseTable(){ // O(nLog(n))
    copy(arr , arr+N , st[0]);
    for(int i = 1 ; i < 25 ; i++){
        for(int j = 0 ; j+(1 << i) < N ; j++){ // j+(1<< i) <= n
            st[i][j] = fun(st[i-1][j] , st[i-1][j + (1 << (i-1)) ]);
        }
    }
}

void calc_Log(){
    lg[0] = 1 ;
    for(int i = 1 ; i < N ; i++){
        lg[i] = lg[i/2]+1;
    }
}

ll query(int l , int r){
    ll ans = MX ;
    int k = lg[r-l+1]; // O(1)
    return fun( st[k][l] , st[k][r-(1<<k)+1]);


    /* O(1)
       if min or max or gcd k...  O(1)
       int k = __lg(r-l+1) ;  time log2(n) = O(Log)
       int k = lg(r-l+1) ; time for log = O(1)
       ans = fun( st[k][l] , st[k][r-(1<<k)+1)] ) ;
     */

    /* O(Log)
      for(int i = 25 ; i >= 0 ; i--){
         if ((1<<i) <= r-l+1){
             ans = fun(ans , st[i][l]);
             l += 1 << i ;
         }
       }
    */

    return ans ;
}

void burn() {
    int n , q ;
    cin >> n >> q ;
    fo(i , n){
        cin >> arr[i];
    }

    SparseTable();
    calc_Log();

    while (q--){
        int l , r ;
        cin >> l >> r ;
        cout << query(--l , --r) << endl ;
    }
}

int main() {
    Body_code
#ifndef ONLINE_JUDGE
    files
#endif
    int cas = 0 ;
//    cin >> cas ;
    while (cas--) {
        burn();
        cout << endl;
    }
    return 0;
}
