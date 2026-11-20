#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,q;
    cin>>n>>q;
    int a[n+1];
    for(int i=1; i<=n; i++){
        cin>>a[i];
    }

    while(q--){
        int l,r,k;
        cin>>l>>r>>k;

        int ans = 2e9;
        

        // set<int> st, apr;
        
        // for(int i=l; i<=r; i++){
        //     if(apr.count(a[i])) st.erase(a[i]);
        //     else{
        //         apr.insert(a[i]);
        //         st.insert(a[i]);
        //     } 
        // }

        // int th=1;
        // for(auto &x: st){
        //     if(th == k){
        //         cout<<x<<'\n';
        //         break;
        //     }
        //     th++;
        // }

        // if(th == st.size()+1) cout<<-1<<'\n';
    }
}