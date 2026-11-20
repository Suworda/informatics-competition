#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long

struct BIT2D{
    int n, m;
    vector<vector<int>> b;
    vector<vector<int>> ys;

    BIT2D(int _n, int _m): n(_n), m(_m), ys(n+1), b(n+1){}

    int lowbit(int x){
        return x&-x;
    }

    void reserve(int x, int y){
        while(x <= n){
            ys[x].push_back(y);
            x += lowbit(x);
        }
    }

    void build(){
        for(int i=1; i<=n; i++){
            auto &v = ys[i];
            sort(v.begin(), v.end());
            v.resize(unique(v.begin(), v.end()) - v.begin());

            b[i].assign(v.size()+1, 0);
        }
    }

    void upd(int x, int _y, int val){

        auto change = [&](int x, int y) -> int {
            return lower_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin() + 1;
        };

        while(x <= n){
            int y = change(x, _y);
            while(y < b[x].size()){
                b[x][y] = max(b[x][y], val);
                y += lowbit(y);
            }
            x += lowbit(x);
        }  
    }

    int query(int x, int _y){

        auto change = [&](int x, int y) -> int {
            return upper_bound(ys[x].begin(), ys[x].end(), y) - ys[x].begin();
        };

        int ans = 0;

        while(x){
            int y = change(x, _y);
            while(y){
                ans = max(ans, b[x][y]);
                y -= lowbit(y);
            }
            x -= lowbit(x);
        }

        return ans;
    }
};

struct Point{
    int a, b, c;
    int val;
    
    bool operator> (const Point &other) const{
        return a > other.a && b > other.b && c > other.c;
    }
};

void dist(vector<int> &a, vector<int> &d){
    for(int i=1; i<a.size(); i++){
        a[i] = lower_bound(d.begin(), d.end(), a[i]) - d.begin() + 1;
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int na, nb, nc;
    cin>>na>>nb>>nc;

    vector<int> a(na+1, -1);
    vector<int> b(nb+1, -1);
    vector<int> c(nc+1, -1);

    vector<int> d;

    for(int i=1; i<=na; i++){
        cin>>a[i];
        d.push_back(a[i]);
    }
    for(int i=1; i<=nb; i++){
        cin>>b[i];
        d.push_back(b[i]);
    }
    for(int i=1; i<=nc; i++){
        cin>>c[i];
        d.push_back(c[i]);
    }

    sort(d.begin(), d.end());
    d.resize(unique(d.begin(), d.end()) - d.begin());

    dist(a, d);
    dist(b, d);
    dist(c, d);

    int N = d.size() + 5;
    vector<int> a_pos(N+5), b_pos(N+5), c_pos(N+5);

    for(int i=1; i<a.size(); i++){
        a_pos[a[i]] = i;
    }
    for(int i=1; i<b.size(); i++){
        b_pos[b[i]] = i;
    }
    for(int i=1; i<c.size(); i++){
        c_pos[c[i]] = i;
    }
    
    vector<Point> points;
    for(int x=1; x<=N; x++){
        if(a_pos[x] && b_pos[x] && c_pos[x]) points.push_back({a_pos[x], b_pos[x], c_pos[x], d[x-1]});
    }

    sort(points.begin(), points.end(), [](Point x, Point y){
        if(x.a != y.a) return x.a < y.a;
        if(x.b != y.b) return x.b < y.b;
        return x.c < y.c;
    });

    reverse(points.begin(), points.end());

    BIT2D bit(nb+5, nc+5);

    for(auto &[_, b, c, _2]: points){
        int x = nb - b + 1;
        int y = nc - c + 1;
        bit.reserve(x, y);
    }

    bit.build();

    int ans_len = 0;
    vector<vector<Point>> v(N+5);
    for(auto &p: points){
        auto [_, b, c, val] = p;
        int x = nb - b + 1;
        int y = nc - c + 1;

        int rst = bit.query(x-1, y-1);

        ans_len = max(ans_len, rst+1);
        bit.upd(x, y, rst+1);

        v[rst+1].push_back(p);
    }

    vector<int> ans;
    Point last = {0,0,0,0};

    for(int i=ans_len; i>=1; i--){
        Point cur = {0,0,0,(int)1e9};
        for(Point &p: v[i]){
            if(ans.size()){
                if(p > last && p.val < cur.val){
                    cur = p;
                }
            }
            else{
                if(p.val < cur.val) cur = p;
            }
        }

        ans.push_back(cur.val);
        last = cur;
        
    }

    if(ans_len){
        cout << ans_len << '\n';
        for(int x: ans) cout << x << ' ' ;
        cout << '\n';
    }
    else{
        cout << -1 << '\n';
    }
    
} 