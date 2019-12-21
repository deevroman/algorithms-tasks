#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
int main(){
    const int mod = (1<<30)+1;
    int n, m;
    cin >> n >> m;
    if(n == 1 && m == 1){
        cout << 2;
        return 0;
    }
    if(n < m)
        swap(n, m);
    vector<vector<vector<int>>> dp(2, vector<vector<int>>(m, vector<int>(1ll<<(m+1))));
    for(auto &now : dp[0][0]){
        now = 1;
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m - 1; j++){
            for(ll p = 0; p < (1<<(m+1)); p++){
                for(int b = 0; b <= 1; b++) {
                    ll b1 = (p >> j) & 1, b2 = (p >> (j + 1)) & 1, b3 = (p >> (j + 2)) & 1;
                    if (b1 != b2 || b2 != b3 || b != b1) {
                        ll start = p & ((1 << (j + 1)) - 1);
                        ll np = ((p >> (j + 1)));
                        np = ((np >> 1) << 1) + b;
                        np = (np << (j + 1)) + start;
                        dp[i][j + 1][np] = ((ll)dp[i][j + 1][np] + dp[i][j][p]) % mod;
                    }
                }
            }
        }
        if(i == n - 1)
            continue;
        for(ll p = 0; p < (1<<(m+1)); p++){
            for(int b = 0; b <= 1; b++) {
                ll to = ((p & (~(1 << (m)))) << 1) + b;
                dp[i + 1][0][to] = ((ll)dp[i + 1][0][to] + dp[i][m - 1][p]) % mod;
            }
        }
        if(i >= 2){
            dp[i-2].clear();
        }
        dp.push_back(vector<vector<int>>(m, vector<int>(1ll<<(m+1))));

        for(int j = 0; j < (int)dp[i].size() - 1; j++){
            dp[i][j].clear();
        }
    }
    ll sum = 0;
    for(auto &now : dp[n-2].back()){
        sum = (sum + now) % mod;
    }
    cout << sum;
    return 0;
}