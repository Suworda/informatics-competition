#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
const int M = 1e9+7;
const int K = 16;

struct Martix{
    int a[K][K] = {};
};

int id(int c, int b){
    return c * 2 + b;
}

int da_id(int b){
    return 14 + b;
}

void add(int &a, int b){
    a = (a + b)%M;
}

Martix mul(Martix A, Martix B){
    Martix C;
    for(int i=0; i<K; i++){
        for(int j=0; j<K; j++){
            for(int k=0; k<K; k++){
                add(C.a[i][j], A.a[i][k] * B.a[k][j] % M);
            }
        }
    }

    return C;
}

Martix fpow(Martix A, int b){
    if(b == 0){
        Martix I;
        for(int i=0; i<K; i++){
            I.a[i][i] = 1;
        }
        return I;
    }

    Martix m = fpow(A, b/2);

    if(b & 1){
        return mul(mul(m,m),A);
    }
    else{
        return mul(m,m);
    }
}


int n;
int DA[2][2];
int dp[2][128][2];
Martix T;
array<int,K> s1;

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin>>n;

    s1[id(0,0)] = 1;
    s1[id(1,0)] = 1;
    s1[id(2,0)] = 1;
    s1[id(3,0)] = 1;
    s1[id(4,1)] = 1;
    s1[id(5,0)] = 1;
    s1[id(6,1)] = 1;

    for(int c=0; c<=6; c++){
        for(int b=0; b<2; b++){
            if(c == 1 || c == 2 || c == 5){
                T.a[id(c,b)][id(0,b)] += 1;
                T.a[id(c,b)][id(1,b)] += 1;
                T.a[id(c,b)][id(2,b)] += 1;
                T.a[id(c,b)][id(3,b)] += 1;
                T.a[id(c,b)][id(4,b)] += 1;
                T.a[id(c,b)][id(5,b)] += 1;
                T.a[id(c,b)][id(6,b)] += 1;
            }
            else if(c == 3){
                T.a[id(c,b)][id(0,b)] += 1;
                T.a[id(c,b)][id(1,b)] += 1;
                T.a[id(c,b)][id(2,b)] += 1;
                T.a[id(c,b)][id(3,b)] += 1;
                T.a[id(c,b)][id(4,b)] += 1;
                T.a[id(c,b)][id(5,b)] += 1;
                T.a[id(c,b)][id(6,b)] += 1;
                T.a[id(c,b)][da_id(b)] += 1;
            }
            else if(c == 0){
                T.a[id(c,b)][id(0,b)] += 1;
                T.a[id(c,b)][id(1,b)] += 1;
                T.a[id(c,b)][id(2,b)] += 1;
                T.a[id(c,b)][id(4,b)] += 1;
                T.a[id(c,b)][id(5,b)] += 1;
                T.a[id(c,b)][id(6,b)] += 1;
                T.a[da_id(b)][id(3,b)] += 1;
            }
            else{ //if(c == 4 || c == 6){
                T.a[id(c,b)][id(0,b^1)] += 1;
                T.a[id(c,b)][id(1,b^1)] += 1;
                T.a[id(c,b)][id(2,b^1)] += 1;
                T.a[id(c,b)][id(3,b^1)] += 1;
                T.a[id(c,b)][id(4,b^1)] += 1;
                T.a[id(c,b)][id(5,b^1)] += 1;
                T.a[id(c,b)][id(6,b^1)] += 1;
            }

        }
    }

    Martix P = fpow(T, n-1);
    array<int, K> sn{};
    for(int i=0; i<K; i++){
        for(int j=0; j<K; j++){
            add(sn[i], P.a[i][j] * s1[j] % M);
        }
    }

    int ans = sn[da_id(0)];
    for(int i=0; i<7; i++){
        add(ans, sn[id(i,0)]);
    }

    cout << ans << '\n';
}