#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long

int n, m, t, k;
int a[105];
int dp[105][1005];
vector<int> nxt[105][2];
vector<int> pre[105][2];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>n>>m;
    while(m--){
        int p, a, b;
        cin>>p>>a>>b;
        pre[b][(p-1)&1].push_back(a);
        nxt[a][p&1].push_back(b);
    }

    cin>>t>>k;

    dp[k][t+1] = 1;

    for(int i=t; i>=1; i--){
        for(int u=1; u<=n; u++){
            if(nxt[u][i&1].size() == 0){
                dp[u][i] = dp[u][i+1];//
                continue;
            }
            for(int v: nxt[u][i&1]){
                dp[u][i] += dp[v][i+1];
            }
        }
    }

    int ans = -1;
    int mx = 0;
    for(int i=1; i<=n; i++){
        if(dp[i][1] > mx){
            ans = i;
            mx = dp[i][1];
        }
    }

    cout << ans << '\n';
}