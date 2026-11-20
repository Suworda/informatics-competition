#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int INF = 1e9;
const int MAX_V = 2000005;
int m, n;
int p[105];
bitset<MAX_V+5> dp;


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int ans = INF;
    cin>>m>>n;
    dp[0] = 1;

    for(int i=1; i<=n; i++){
        cin>>p[i];
        for(int j=MAX_V; j>=0; j--){
            if(j-p[i] >= 0 && dp[j-p[i]]) dp[j] = 1;
            if(dp[j] && j >= m) ans = min(ans, j-m);
        }
    }

    cout << ans << '\n';
    
}