const int N = 100100;
const int K = 450;
ll a[N];
int n, q;
namespace mo
{
    struct query
    {
        int idx, l, r;
    };
    int block;
    vector<query> queries;
    vector<int> ans;

    bool cmp(query x, query y)
    {
        if (x.l / K != y.l / K)
            return x.l / K < y.l / K;
        if((x.l / K)&1)
            return x.r > y.r;
        return x.r < y.r;
    }
    void run()
    {
        sort(queries.begin(), queries.end(), cmp);
        ans.resize(queries.size());
        int cl = 0, cr = -1;
        ll sum = 0;
        auto add = [&](ll x)
        {
            sum += x;
        };
        auto rem = [&](ll x)
        {
            sum -= x;
        };
        for (int i = 0; i < queries.size(); i++)
        {
            while (cl > queries[i].l)
            {
                cl--;
                add(a[cl]);
            }
            while (cr < queries[i].r)
            {
                cr++;
                add(a[cr]);
            }
            while (cl < queries[i].l)
            {
                rem(a[cl]);
                cl++;
            }
            while (cr > queries[i].r)
            {
                rem(a[cr]);
                cr--;
            }
            ans[queries[i].idx] = sum;
        }
    }
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> q;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < q; i++)
    {
        mo::query curr;
        cin >> curr.l >> curr.r;
        curr.l--;
        curr.r--;
        curr.idx = i;
        mo::queries.pb(curr);
    }
    mo::run();
    for (auto const &i : mo::ans)
        cout << i << endl;
}