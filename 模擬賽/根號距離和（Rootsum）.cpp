#include <bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,q;
    cin>>n>>q;
    double x[n];
    for(int i=0; i<n; i++){
        cin>>x[i];
    }

    double y;
    while(q--){
        double ans=0;

        cin>>y;
        for(int i=0; i<n; i++){
            ans += sqrt(abs(x[i] - y));
        }
        
        cout<<ans<<'\n';
    }

}