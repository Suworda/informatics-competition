#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long

// const int N = 100005;

int n;
vector<pair<int,int>> nxt[300005];
int dis[300005];
bitset<300005> vis;

vector<int> dist(vector<int> v){
    auto d = v;
    sort(d.begin(), d.end());
    d.resize(unique(d.begin(), d.end())-d.begin());

    vector<int> rst{0};
    for(int i=0; i<v.size(); i++){
        auto it = lower_bound(d.begin(), d.end(), v[i]);
        rst.push_back(it-d.begin()+1);
    }
    return rst;
}

signed main(){
    cin>>n;

    vector<int> v;
    for(int i=1; i<=n; i++){
        int x;
        cin>>x;
        v.push_back(x);
    }

    v = dist(v);

    for(int i=1; i<=n; i++){
        int x = v[i];
        if(i+1 <= n) nxt[i].push_back({i+1, 1});
        if(i-1 >= 1) nxt[i].push_back({i-1, 1});
        nxt[i].push_back({n+x, 0});
        nxt[2*n+x].push_back({i, 0});
    }

    for(int i=1; i<=n; i++){
        nxt[n+i].push_back({2*n+i, 1});
    }

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0, 1});

    while(pq.size()){
        auto [cur, u] = pq.top(); pq.pop();
        if(vis[u]) continue;

        vis[u] = 1;
        dis[u] = cur;

        for(auto [v, w]: nxt[u]){
            pq.push({cur+w, v});
        }
    }

    cout << dis[n] << '\n';
    
}