#include <iostream>
#include <string>
#include <vector>
#include <numeric>

using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> d(2, vector<int>(n));
    for (int z = 0; z < 2; z++) {
        int l = 0, r = 0;
        vector<int> &p = d[z];
        for (int i = 0; i < n; i++) {
            if (i < r) {
                p[i] = min(r - i + !z, p[l + r - i + !z]);
            }
            int L = i - p[i], R = i + p[i] - !z;
            while (L - 1 >= 0 && R + 1 < n && s[L - 1] == s[R + 1]) {
                p[i]++;
                L--;
                R++;
            }
            if (R > r) {
                l = L;
                r = R;
            }
        }
    }
    cout << accumulate(d[0].begin(), d[0].end(), 0ll) + accumulate(d[1].begin(), d[1].end(), 0ll) + s.size();
    return 0;
}