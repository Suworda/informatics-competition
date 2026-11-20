#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct BIT{
    int n;
    vector<int> bit;

    BIT(int _n): n(_n), bit(n+1){}

    int lowbit(int x){
        return x&-x;
    }

    void upd(int x, int val){
        while(x <= n){
            bit[x] = max(bit[x], val);
            x += lowbit(x);
        }
    }

    int query(int x){
        int ans = 0;
        while(x){
            ans = max(ans, bit[x]);
            x -= lowbit(x);
        }
        return ans;
    }

    void clear(int x){
        while(x <= n){
            bit[x] = 0;
            x += lowbit(x);
        }
    }
};

struct Point{
    int a=0, b=0, c=0, id=0, val=0;

    bool operator> (const Point &other) const{
        return a > other.a && b > other.b && c > other.c;
    }

    bool operator< (const Point &other) const{
        return a < other.a && b < other.b && c < other.c;
    }
};

struct CDQ{
    int n;
    vector<Point> p;
    vector<int> ans;
    BIT bit;

    CDQ(vector<Point> _p, int max_c):
        n(_p.size()), p(_p), ans(n,1), bit(max_c){

        sort(p.begin(), p.end(), [](Point x, Point y){
            return x.a < y.a;
        });
    }

    void calc(int l, int mid, int r){
        vector<int> order;

        for(int i=l; i<=r; i++){
            order.push_back(i);
        }

        sort(order.begin(), order.end(), [&](int i, int j){
            if(p[i].b != p[j].b) return p[i].b < p[j].b;
            return i > j;
        });

        vector<int> added;
        for(int i: order){
            int x = p[i].c;
            if(i <= mid){
                bit.upd(x, ans[p[i].id]);
                added.push_back(x);
            }
            else{
                ans[p[i].id] = max(ans[p[i].id], bit.query(x-1)+1);
            }
        }

        for(int x: added) bit.clear(x);
    }

    void cdq(int l, int r){
        if(l >= r) return;

        int mid = (l+r)/2;

        cdq(l, mid);
        calc(l, mid, r);
        cdq(mid+1, r);
    }

    vector<int> solve(){
        if(n) cdq(0, n-1);
        return ans;
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
        if(!a_pos[x] || !b_pos[x] || !c_pos[x]) continue;

        int id = points.size();

        points.push_back({
            na - a_pos[x] + 1,
            nb - b_pos[x] + 1,
            nc - c_pos[x] + 1, 
            id,
            d[x-1]
        });
    }

    CDQ solver(points, nc+5);
    vector<int> rst = solver.solve();

    int ans_len = 0;
    for(int i=0; i<rst.size(); i++){
        int x = rst[i];
        ans_len = max(ans_len, x);
    }
    
    vector<vector<Point>> v(ans_len+1);
    for(int i=0; i<rst.size(); i++){
        Point p = points[i];
        v[rst[i]].push_back(p);
    }

    Point cur, last;
    vector<int> ans;
    
    for(int i=ans_len; i>=1; i--){
        cur.val = 1e9;
        for(Point p: v[i]){
            if(ans.size()){
                if(p < last && p.val < cur.val){
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