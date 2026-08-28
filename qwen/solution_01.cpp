#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    long long ans = 0;
    for (int l = 1; l <= n; ++l) {
        int g = a[l], x = a[l];
        ans = max(ans, (long long)(g ^ x));
        for (int r = l+1; r <= n; ++r) {
            g = __gcd(g, a[r]);
            x ^= a[r];
            ans = max(ans, (long long)(g ^ x));
        }
    }
    cout << ans << '\n';
    return 0;
}