//https://www.spoj.com/problems/LIM/en/
#include <bits/stdc++.h>

using namespace std;

typedef long long   ll;

const double EPS = 1e-9;
const int INF = 2;

int gauss(vector< vector< double > > a, vector< double > &ans, bool frag = false){
    int n = a.size();
    int m = a[0].size() - 1;

    vector< int > where(m, -1);
    for(int col = 0, row = 0 ; col < m && row < n ; ++col){
        int sel = row;
        for(int i = row ; i < n ; i++){
            if(abs(a[i][col]) > abs(a[sel][col])){
                sel = i;
            }
        }

        if(abs(a[sel][col]) < EPS){
            continue;
        }

        for(int i = col ; i <= m ; i++){
            swap(a[sel][i], a[row][i]);
        }
    
        where[col] = row;

        for(int i = 0 ; i < n ; i++){
            if(i != row){
                double c = a[i][col] / a[row][col];
                for(int j = col ; j <= m ; j++){
                    a[i][j] -= a[row][j] * c;
                }
            }
        }
        ++row;
    }

    ans.assign(m, 0);

    for(int i = 0 ; i < m ; i++){
        if(where[i] != -1){
            ans[i] = a[where[i]][m] / a[where[i]][i];
        }
    }

    // if(frag){
    //     cout << " res = " << ans[0] << " " << ans[1] << "\n";
    // }
    
    for(int i = 0 ; i < n  ; i++){
        double sum = 0;
        for(int j = 0 ; j < m ; j++){
            sum += ans[j] * a[i][j];
        }

        if(abs(sum - a[i][m]) > EPS){
            // if(frag){
            //     cout << " error on " << i << " " << " " << sum << " " << " " << a[i][m] << "\n";        
            // }
            return 0;
        }
    }

    return 1;
}

const int N = 310;

vector< int > adj[N];

int main(){
    int n;

    while(scanf("%d", &n) != EOF){
        if(n == 0) break;
        
        for(int i = 0 ; i < n ; i++){
            int ui, vi;

            scanf("%d %d", &ui, &vi);
            
            adj[ui].push_back(vi);
            adj[vi].push_back(ui);
        }

        vector< vector< double > > q;

        for(int i = 0 ; i <= 300 ; i++){
            vector< double > a(302, 0);
            
            a[i] = 1;
            
            if(i == 300){
                a[i + 1] = 1;
            }else if(i <= 290){
                for(auto u: adj[i]){
                    if(u <= 290 || u == 300){
                        a[u] = -(1.0 / adj[i].size());
                        // printf("%lf\n", a[u]);
                    }
                }

            }

            q.push_back(a);
            adj[i].clear();
        }
        // printf("aqui!\n");
        // fflush(stdout);
        vector< double > ans;

        if((gauss(q, ans)))
            printf("%.3lf\n", ans[0]);
        // printf("rodei!\n");
        // fflush(stdout);
    }

    return 0;
}