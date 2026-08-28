#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    int ans = 0;
    for (int l = 1; l <= n; l++) {
        int g = 0, x = 0;
        for (int r = l; r <= n; r++) {
            g = __gcd(g, a[r]);
            x ^= a[r];
            ans = max(ans, g ^ x);
        }
    }
    cout << ans << "\n";
    return 0;
}
