#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long

int a[1005];
int sum[1005];
int dp[1005];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int k, p, n;
    cin>>k>>p>>n;
    for(int i=1; i<=n; i++){
        cin>>a[i];
    }

    sort(a+1, a+n+1);
    for(int i=1; i<=n; i++) sum[i] = sum[i-1] + a[i];

    for(int i=1; i<=n; i++){
        dp[i] = dp[i-1] + a[i]*(100-p)/100;
        if(i-k >= 0){
            dp[i] = min(dp[i], dp[i-k] + sum[i] - sum[i-k+1]);
        }
    }

    // for(int i=1; i<=n; i++) cout << a[i] << ' ';
    // cout << '\n';
    // for(int i=1; i<=n; i++) cout << dp[i] << ' ';
    cout << dp[n] << '\n';

}