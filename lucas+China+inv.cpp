#include <bits/stdc++.h>

using namespace std;

int F[100005];
long long prim[20];

long long tmpans[20];
typedef long long ll;

//ax + by = gcd(a,b)
//传入固定值a,b.放回 d=gcd(a,b), x , y
void extendgcd(ll a, ll b, ll &d, ll &x, ll &y)
{
    if (b == 0)
    {
        d = a;
        x = 1;
        y = 0;
        return;
    }
    extendgcd(b, a % b, d, y, x);
    y -= x * (a / b);
}

ll Exgcd(ll a, ll b, ll &x, ll &y)
{
    if (b == 0)
    {
        x = 1, y = 0;
        return a;
    }
    ll ret = Exgcd(b, a % b, x, y);
    ll tmp = x;
    x = y;
    y = tmp - a / b * y;
    return ret;
}

//Ax=1(mod M)，gcd(A,M)==1
//输入：10^18>=A,M>=1
//输出：返回x的范围是[1,M-1]
ll GetNi(ll A, ll M)
{
    ll rex = 0, rey = 0;
    ll td = 0;
    extendgcd(A, M, td, rex, rey);
    return (rex % M + M) % M;
}

ll C(ll n, ll m, ll p)
{
    if (m > n)
        return 0;
    ll up = 1, dn = 1;
    for (int i = 0; i < m; i++)
    {
        up = up * (n - i) % p;
        dn = dn * (i + 1) % p;
    }
    return up * GetNi(dn, p) % p;
}

ll lucas(ll n, ll m, ll p)
{
    if (m == 0)
        return 1;
    return C(n % p, m % p, p) * lucas(n / p, m / p, p) % p;
}

ll CRT2(ll b[], ll n[], int num) //b[]为余数数组， n[]为模数组
{
    int i;
    bool flag = false;
    ll n1 = n[0], n2, b1 = b[0], b2, bb, d, t, k, x, y;
    for (i = 1; i < num; i++)
    {
        n2 = n[i], b2 = b[i];
        bb = b2 - b1;
        d = Exgcd(n1, n2, x, y);
        if (bb % d) //模线性解k1时发现无解
        {
            flag = true;
            break;
        }
        k = bb / d * x; //相当于求上面所说的k1【模线性方程】
        t = n2 / d;
        if (t < 0)
            t = -t;
        k = (k % t + t) % t; //相当于求上面的K`
        b1 = b1 + n1 * k;    //b1相当于最小正整数解
        n1 = n1 / d * n2;
    }
    return b1;  
}

int main()
{
    //题目来源https://nanti.jisuanke.com/t/29337
    //大意 求 C n m % M
    // M =p1 *p2 *p3 *p4...p10 p为素数 
    int T;
    cin >> T;
    while (T--)
    {
        long long n, m, num;
        scanf("%lld %lld %lld", &n, &m, &num);
        for (int i = 0; i < num; i++)
        {
            scanf("%lld", &prim[i]);
        }
        for (int i = 0; i < num; i++)
        {
            tmpans[i] = lucas(n, m, prim[i]);
        }
        printf("%lld\n", CRT2(tmpans, prim, num));
    }
    system("pause");
    return 0;
}