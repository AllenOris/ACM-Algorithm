//首先需要处理p以内的阶乘与逆元,实现Cnm的O1计算
//仅考虑p是素数

const int maxn = 1000000 + 5; //一般为1e6以下
long long F[maxn], inv[maxn];
//long long p;

long long qpow(long long a, long long b, long long MOD) //a^b %MOD
{
    long long ans = 1;
    while (b)
    {
        if (b & 1)
        {
            ans = ans * a % MOD;
        }
        a = a * a % MOD;
        b >>= 1;
    }
    return ans;
}

void init(long long p)
{
    inv[0] = F[0] = 1;
    for (int i = 1; i <= p; i++)
    {
        F[i] = F[i - 1] * i % p;
    }
    for (int i = 1; i <= p; i++)
    {
        inv[i] = qpow(F[i], p - 2, p);
    }
}

long long Lucas(long long La, long long Lb, long long Lp) // C La Lb %Lp
{
    if (La < Lp)
    {
        return (F[La] * inv[Lb] % Lp) * inv[La - Lb] % Lp;
    }
    return Lucas(La / Lp, Lb / Lp, Lp) * Lucas(La % Lp, Lb % Lp, Lp) % Lp;
}
