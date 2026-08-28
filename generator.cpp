#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
    long long seed = argc > 1 ? atoll(argv[1]) : 1;
    int maxN = argc > 2 ? atoi(argv[2]) : 10;
    long long maxA = argc > 3 ? atoll(argv[3]) : 20;

    mt19937_64 rng(seed);
    auto randRange = [&](long long lo, long long hi) {
        uniform_int_distribution<long long> dist(lo, hi);
        return dist(rng);
    };

    int n = (int)randRange(1, maxN);
    printf("%d\n", n);
    for (int i = 0; i < n; i++) {
        printf("%lld ", randRange(0, maxA));
    }
    printf("\n");
    return 0;
}
