#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll INF = 1e9;
using pii = pair<int,int>;
using tiii = tuple<int,int,int>;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

struct Point{
    int time, cnt, x, y, last;

    bool operator> (const Point &b) const{
        if(time != b.time) return time > b.time;
        if(cnt != b.cnt) return cnt > b.cnt;
        return x < b.x;
    }
};

bool valid(int x, int y, int ty){
    if(ty == 1) return true;
    if(ty == 2) return x % 5 == 0 && y % 5 == 0;
    if(ty == 3) return x % 2 == 0 && y % 2 == 0;
    if(ty == 4) return x % 10 == 0 && y % 10 == 0;
    if(ty == 5) return x % 20 == 0 && y % 20 == 0;
}

struct Graph{
    int n;
    int Sx, Sy;
    vector<Point> v;
    
    Graph(int _x, int _y): Sx(_x), Sy(_y) {}
    
    void dijkstra(int Tx, int Ty){
        int x = Sx, y = Sy;
        set<tiii> vis;
        priority_queue<Point, vector<Point>, greater<>> pq;

        
        pq.push({0, 0, x, y, 1});
        
        while(pq.size()){
            auto [time, cnt, x, y, last] = pq.top(); pq.pop();
            if(vis.count({x, y, last}) || max(abs(x - Sx), abs(y - Sy)) > 400 || x < 0 || y < 0 || x >= (int)1e8 || y >= (int)1e8) continue;
            
            // cerr << x << ' ' << y << ' ' << Tx << ' ' << Ty << '\n';
            if(x == Tx && y == Ty){
                cout << time << ' ' << cnt << '\n';
                exit(0);
            }

            vis.insert({x, y, last});

            if(valid(x, y, 5)){
                v.push_back({time, cnt, x, y, last});
            }

            int mx = max(abs(x - Sx), abs(y - Sy));

            for(int dir=0; dir<4; dir++){
                if(valid(x, y, 1) && mx <= 64){
                    int nx = x + dx[dir];
                    int ny = y + dy[dir];
                    pq.push({time+5, cnt, nx, ny, 1});
                }
                if(valid(x, y, 2) && mx <= 64){
                    int nx = x + dx[dir]*5;
                    int ny = y + dy[dir]*5;
                    pq.push({time+10, cnt + (last != 2), nx, ny, 2});
                }
                if(valid(x, y, 3) &&  mx <= 64){
                    int nx = x + dx[dir]*2;
                    int ny = y + dy[dir]*2;
                    pq.push({time+2, cnt + (last != 3), nx, ny, 3});
                }
                if(valid(x, y, 4)){
                    int nx = x + dx[dir]*10;
                    int ny = y + dy[dir]*10;
                    pq.push({time+3, cnt + (last != 4), nx, ny, 4});
                }
                if(valid(x, y, 5)){
                    int nx = x + dx[dir]*20;
                    int ny = y + dy[dir]*20;
                    pq.push({time+5, cnt + (last != 5), nx, ny, 5});
                }
            }
        }
    }
};

void sol(Graph S, Graph T){
    auto v1 = S.v;
    auto v2 = T.v;

    pair<int,int> ans = {INF, INF};
    for(auto p1: v1){
        for(auto p2: v2){
            int dx = abs(p1.x - p2.x);
            int dy = abs(p1.y - p2.y);

            int d=0;
            if(p1.last == 5 && p2.last == 5) d = -1;
            else if(p1.last != 5 && p2.last != 5) d = 1;
            ans = min(ans, {p1.time + p2.time + dx/4 + dy/4, p1.cnt + p2.cnt + d});
        }
    }

    // for(auto [time, cnt, x, y, last]: v1) cout << time << ' ' << cnt << ' ' << x << ' ' << y << ' ' << last << '\n';
    // cout << '\n';
    // for(auto [time, cnt, x, y, last]: v2) cout << time << ' ' << cnt << ' ' << x << ' ' << y << ' ' << last << '\n';

    cout << ans.first << ' ' << ans.second << '\n';
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int Sx, Sy, Tx, Ty;
    cin >> Sx >> Sy >> Tx >> Ty;
    
    Graph g1(Sx, Sy);

    g1.dijkstra(Tx, Ty);

    Graph g2(Tx, Ty);

    g2.dijkstra(Sx, Sy);

    sol(g1, g2);
    
}