# include <bits/stdc++.h>
# define RG register
# define IL inline
# define Fill(a, b) memset(a, b, sizeof(a))
using namespace std;
typedef long long ll;
const int Zsy(998244353);
const int Phi(998244352);
const int G(3);
const int _(4e5 + 5);

IL ll Input(){
    RG ll x = 0, z = 1; RG char c = getchar();
    for(; c < '0' || c > '9'; c = getchar()) z = c == '-' ? -1 : 1;
    for(; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    return x * z;
}

int n, m, N, l, r[_], A[_], B[_];

IL int Pow(RG ll x, RG ll y){
    RG ll ret = 1;
    for(; y; y >>= 1, x = x * x % Zsy)
        if(y & 1) ret = ret * x % Zsy;
    return ret;
}

IL void NTT(RG int *P, RG int opt){
    for(RG int i = 0; i < N; ++i) if(r[i] < i) swap(P[r[i]], P[i]);
    for(RG int i = 1; i < N; i <<= 1){
        RG int W = Pow(G, Phi / (i << 1));
        if(opt == -1) W = Pow(W, Zsy - 2);
        for(RG int j = 0, p = i << 1; j < N; j += p){
            RG int w = 1;
            for(RG int k = 0; k < i; ++k, w = 1LL * w * W % Zsy){
                RG int X = P[k + j], Y = 1LL * w * P[k + j + i] % Zsy;
                P[k + j] = (X + Y) % Zsy, P[k + j + i] = (X - Y + Zsy) % Zsy;
            }
        }
    }
}

int main(RG int argc, RG char* argv[]){
    n = Input(), m = Input();
    for(RG int i = 0; i <= n; ++i) A[i] = Input();
    for(RG int i = 0; i <= m; ++i) B[i] = Input();
    for(n += m, N = 1; N <= n; N <<= 1) ++l;
    for(RG int i = 0; i < N; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
    NTT(A, 1); NTT(B, 1);
    for(RG int i = 0; i < N; ++i) A[i] = 1LL * A[i] * B[i] % Zsy;
    NTT(A, -1);
    RG int inv = Pow(N, Zsy - 2);
    for(RG int i = 0; i <= n; ++i) printf("%lld ", 1LL * A[i] * inv % Zsy);
    return 0;
}