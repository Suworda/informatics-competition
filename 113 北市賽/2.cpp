#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long

struct Solar{
    int h, w, p;
};

int dp[505][505];
vector<Solar> v;
bool vis[505][505];

int dfs(int n, int m){
    if(vis[n][m]) return dp[n][m];
    if(n == 1 && m == 1) return dp[1][1];

    int rst = dp[n][m];
    for(int k=1; k<m; k++){
        rst = max(rst, dfs(n,k) + dfs(n,m-k));
    }
    for(int k=1; k<n; k++){
        rst = max(rst, dfs(k, m) + dfs(n-k, m));
    }

    vis[n][m] = 1;
    return dp[n][m] = rst;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k;
    cin>>n>>m>>k;
    for(int i=1; i<=k; i++){
        int h, w, p;
        cin>>h>>w>>p;
        v.push_back({h, w, p});
        dp[h][w] = max(dp[h][w], p);
        dp[w][h] = max(dp[w][h], p);
    }

    cout << dfs(n, m) << '\n';
}
