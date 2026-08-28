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
            int ng = __gcd(g, a[r]);
            int nx = x ^ a[r];
            if ((ng ^ nx) >= (g ^ x)) { // local improvement only
                g = ng; x = nx;
                ans = max(ans, (long long)(g ^ x));
            } else {
                break; // stops too early
            }
        }
    }
    cout << ans << '\n';
    return 0;
}