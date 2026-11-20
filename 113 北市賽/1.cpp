#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long

int Q, n;
struct Query{
    int p, s, t;
    bool operator< (const Query &b){
        return p < b.p;
    }
};

vector<Query> v;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>Q>>n;
    for(int i=1; i<=n; i++){
        int p, s, t;
        cin>>p>>s>>t;
        v.push_back({p, s, t});
    }

    sort(v.begin(), v.end());

    int ans = 4e18;

    for(int i=0; i<(1<<(n-1)); i++){
        int rst = 0;
        int cur = v[0].t;
        int x = v[0].s;
        bool valid = 1;
        for(int j=0; j<n-1; j++){
            if((i >> j) & 1){
                x = v[j+1].s;
                rst += cur;
                cur = v[j+1].t;
            }else{
                x += v[j+1].s;
                cur = max(cur, v[j+1].t);
            }
            if(x > Q){
                valid = 0;
                break;
            }
        }
        if(!valid) continue;
        rst += cur;
        ans = min(ans, rst);
    }

    cout << ans << '\n';

}

/*
10 5
1 5 1
2 3 1
3 7 1
4 2 1
5 1 1
*/