#include <bits/stdc++.h>
using namespace std;

set<int> st[200005];

int main(){
    int n;
    cin>>n;
    int a,b;
    int ans=0;
    for(int i=0; i<n; i++){
        cin>>a>>b;
        if(st[a].count(b)){
            ans += 2;
            st[a].erase(b);
        }else{
            st[a].insert(b);
        }
    }


    for(int i=1; i<=200000; i++){
        ans+=st[i].size()/2;
    }

    cout<<ans<<'\n';
}