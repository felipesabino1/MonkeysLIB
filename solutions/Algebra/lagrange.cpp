// modint.cpp is prerequisite
// template.cpp as well
mi f(int x, int k)
{
    // function in a point, normally a exponentiation
    return mypow(x, k);
}
const int N = 1001000;
mi y[N], dif[N];
mi lagrange(int n, int k)
{
    // r tem q ser a potencia do polinomio + 3
    // cuidado, o produto de multiplos polinomios aumenta a potencia
    int r = k+3;
    dif[1] = 1;
    rep(i, 1, r)
    {
        y[i] = f(i, k);
        if(i!=1){
            // caso seja um somatorio, pode não ser
            y[i] += y[i-1];
            dif[1]*=(1-i);
        }
    }
    int big = 1-(r-1);
    int small = 1;
    rep(i, 2, r)
    {
        dif[i] = dif[i-1];
        dif[i] = dif[i]/big;
        dif[i] *= small;
        small++;
        big++;
    }
    if(n < r)
        return y[n];
    mi lj = 1;
    int at;
    rep(i, 1, r)
    {
        at = n-i;
        lj*=at;
    }
    mi rs = 0;
    rep(i, 1, r)
    {
        at = n-i;
        mi lag = lj/(at*dif[i]);
        rs += lag*y[i];
    }
    return rs;
}
