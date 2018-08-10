const int N = 1000000;
int phi[N], prime[N], mu[N];//线性筛素数 欧拉函数 莫比乌斯函数
bool vis[N];

void init()
{
    phi[1] = 1;
    mu[1] = 1;
    int p = 0;
    for (long long i = 2; i < N; i++)
    {
        if (!vis[i])
        {
            prime[p++] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (long long j = 0; j < p && i * prime[j] < N; j++)
        {
            vis[i * prime[j]] = 1;
            if (i % prime[j])
            {
                phi[i * prime[j]] = phi[i] * (prime[j] - 1);
                mu[i * prime[j]] = -mu[i];
            }
            else
            {
                phi[i * prime[j]] = phi[i] * prime[j];
                mu[i * prime[j]] = 0;
                break;
            }
        }
    }
}