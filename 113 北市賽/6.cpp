#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long

const ll INF = 4e18;

struct Mountain{
    int p, h, id;
};

struct Query{
    int mid, H, id;
    vector<int> v;
    bool operator< (const Query &b) const{
        return H > b.H;
    }
};


signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m;
    cin>>n>>m;
    vector<Mountain> mt(n);
    for(int i=0; i<n; i++) cin>>mt[i].p;
    for(int i=0; i<n; i++) cin>>mt[i].h;
    for(int i=0; i<n; i++) mt[i].id = i;

    vector<Query> Q;

    for(int round=0; round<m; round++){
        int k;
        cin>>k;
        vector<int> v;
        int mx_h = 0;
        
        for(int i=0; i<k; i++){
            int x;
            cin>>x;
            v.push_back(x);
            mx_h = max(mx_h, mt[x].h);
        }
        
        sort(v.begin(), v.end(), [&](int x, int y){
            if(mt[x].p != mt[y].p) return mt[x].p < mt[y].p;
            return x < y;
        });
        
        int mid = v[(k-1)/2];

        Q.push_back({mid, mx_h, round, v});
    }

    sort(Q.begin(), Q.end());
    vector<int> ans(m, INF);

    auto mt2 = mt;
    sort(mt2.begin(), mt2.end(), [&](Mountain x, Mountain y){
        return x.h > y.h;
    });

    set<pair<int,int>> st; //位置
    int mt2_id = 0;
    for(auto &[mid, H, id, v]: Q){
        while(mt2_id < n && mt2[mt2_id].h >= H){
            st.insert({mt2[mt2_id].p, mt2[mt2_id].id});
            mt2_id++;
        }

        auto it = st.lower_bound({mt[mid].p, 0});
        if(it == st.end()) it--;
        auto it2 = (it != st.begin() ? prev(it) : it);

        for(int i: {it->second, it2->second}){
            int tot = 0;

            for(int x: v){
                tot += abs(mt[x].p-mt[i].p);
            }
            ans[id] = min(ans[id], tot);
        }
    }

    for(int i=0; i<m; i++) cout << ans[i] << '\n';
}

/*
10 5
1 5 1
2 3 1
3 7 1
4 2 1
5 1 1

8 3
2 5 1 3 9 7 8 4
1 6 6 4 2 5 0 2
3 3 7 5
4 2 2 7 5
1 0

5 2
1 0 5 9 4
0 0 0 0 0
3 4 0 1
6 3 3 0 2 2 2
*/