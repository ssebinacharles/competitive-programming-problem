#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        ll K;
        int Lmin, Lmax;
        scanf("%d %lld %d %d", &n, &K, &Lmin, &Lmax);
        vector<ll> a(n + 1);
        for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);

        ll answer = 0;
        for (int l = 1; l <= n; l++) {
            ll sum = 0;
            for (int r = l; r <= n; r++) {
                sum += a[r];
                int len = r - l + 1;
                if (len < Lmin) continue;
                if (len > Lmax) break;
                if (sum >= K * (ll)len) answer++;
            }
        }
        printf("%lld\n", answer);
    }
    return 0;
}