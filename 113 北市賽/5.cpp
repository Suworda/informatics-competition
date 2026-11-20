#include <bits/stdc++.h>
using namespace std;
#define int long long

string s;
int p[100005];

struct Ctree{
    int n;
    vector<int> lh, ll, rh, rl;
    int root;

    Ctree(int _n): n(_n), lh(n+1), ll(n+1), rl(n+1), rh(n+1){
        build();
        find_root();
    }

    void build(){
        vector<int> stk;
        for(int i=1; i<=n; i++){
            int last = -1;
            while(stk.size() && p[i] > p[stk.back()]){
                last = stk.back();
                stk.pop_back();
            }

            if(stk.size()){
                rl[stk.back()] = i;
                lh[i] = stk.back();
            }
            if(last != -1){
                rh[last] = i;
                ll[i] = last;
            }

            stk.push_back(i);

        }
    } 

    void find_root(){
        for(int i=1; i<=n; i++){
            if(!lh[i] && !rh[i]){
                root = i;
                return;
            }
        }
    }
};

void f(Ctree &ctree, int id){
    // cout << id << '\n';
    if(!ctree.ll[id] && !ctree.rl[id]){
        cout << "(" <<  s[id-1] << "+" << s[id] << ")";
        return;
    }

    cout << "("; 
    if(ctree.ll[id]) f(ctree, ctree.ll[id]); 
    else cout << s[id-1];
    cout << "+"; 
    if(ctree.rl[id]) f(ctree, ctree.rl[id]);
    else cout << s[id]; 
    cout << ")"; 
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>s;
    string tmp;
    for(char c: s) if(c != '+') tmp.push_back(c);
    swap(s, tmp);

    int x;
    int tmp_i = 1;
    vector<int> order;
    for(int i=1; i<s.size(); i++){
        order.push_back(i);
        cin>>x;
        p[x] = tmp_i++;
    }

    if(s.size() == 1){
        cout << s[0] << '\n';
        return 0;
    }

    Ctree ctree(s.size()-1);

    f(ctree, ctree.root);
}