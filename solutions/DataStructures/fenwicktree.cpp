const int N = 200100;

int bit[N];

int query(int x)
{
    int rs = 0;
    while(x)
    {
        rs += bit[x];
        x -= x&-x;
    }
    return rs;
}

void updt(int x, int v)
{
    while(x < N)
    {
        bit[x] += v;
        x += x&-x;
    }
}