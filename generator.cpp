#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
        long long seed = argc > 1 ? atoll(argv[1]) : 1;
    int maxN = argc > 2 ? atoi(argv[2]) : 10;
    long long maxAbsA = argc > 3 ? atoll(argv[3]) : 10;
    long long maxAbsK = argc > 4 ? atoll(argv[4]) : 10;

    mt19937_64 rng(seed);
    auto randRange = [&](long long lo, long long hi) {
        uniform_int_distribution<long long> dist(lo, hi);
        return dist(rng);
    };

    int t = 1;
    printf("%d\n", t);
    int n = (int)randRange(1, maxN);
    long long K = randRange(-maxAbsK, maxAbsK);
    int Lmin = (int)randRange(1, n);
    int Lmax = (int)randRange(Lmin, n);
    printf("%d %lld %d %d\n", n, K, Lmin, Lmax);
    for (int i = 0; i < n; i++) {
        printf("%lld ", randRange(-maxAbsA, maxAbsA));
    }
    printf("\n");
    return 0;
}