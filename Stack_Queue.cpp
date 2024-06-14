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
int n ;
int arr[N];

// the optimal remove last element  stack
stack<pair<int,int>> st ;

// the optimal remove frist element queue method 1 by element , method 2 by indx , method 3
deque<int> qu ;
stack<pair<int, int>> s1, s2; // method 2

void StAdd(int x){
    int mn = st.empty() ? x : min(x , st.top().Y);
    st.push({x , mn});
}
void StRemove(){

    if (!st.empty()) st.pop();
}

void QuAdd(int x){
    while (!qu.empty() && qu.back() > x) qu.pop_back();
    qu.push_back(x);
}
void QuRemove(int ele ){
    // parameter is idx or element

    if ( !qu.empty() && qu.front() == ele) qu.pop_front();

}

void method2(){
    int ele , mn ;

    // find minimum min(s1.top().Y , s2.top().Y)
    if (s1.empty() || s2.empty()){
        mn = s1.empty() ? s2.top().Y : s1.top().Y ;
    }else
        mn = min(s1.top().Y , s2.top().Y);

// -------------------------------------------

    // add in s1
    int minimum = s1.empty() ? ele : min(ele, s1.top().Y);
    s1.push({ele, minimum});

// ------------------------------------------------

    // remove
    if (s2.empty()){
        while (!s1.empty()){
            s2.push(s1.top());
            s1.pop();
        }
    }
    s2.pop();



}

int calc(int d){
    // find min,max in all subarry of a fixed length in an array O(n)
    int mn = MX ;
    fo(i , d){
        QuAdd(arr[i]);
    }
    mn = qu.front();
    for(int i = d ; i < n ; i++){
        QuAdd(arr[i]);
        QuRemove(arr[i-d]);
        mn = max(mn , qu.front());
    }
    return mn ;
}

void burn() {
    int q ;
    cin >> n >> q ;
    fo(i , n){
        cin >> arr[i];
    }
    while (q--){
        int d ;
        cin >> d ;
        cout << calc(d) << endl ;
        while (!qu.empty())qu.pop_front();
    }
}

int main() {
    Body_code
#ifndef ONLINE_JUDGE
    files
#endif
    int cas = 1 ;
//    cin >> cas ;
    while (cas--) {
        burn();
        cout << endl;
    }
    return 0;
}