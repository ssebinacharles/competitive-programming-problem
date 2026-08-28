#include <bits/stdc++.h>
using namespace std;

const int B = 30;
const int LOG = 20; 
const int MAXN = 200005;

struct TrieNode {
    int child[2];
    int cnt;
    TrieNode() : cnt(0) { child[0] = child[1] = 0; }
};

vector<TrieNode> trie;
vector<int> root;
int emptyRoot;

int cloneNode(int node) {
    trie.push_back(trie[node]);
    return (int)trie.size() - 1;
}

int insert(int val, int prevRoot) {
    int newRoot = cloneNode(prevRoot);
    int cur = newRoot;
    trie[cur].cnt++;
    for (int b = B - 1; b >= 0; --b) {
        int bit = (val >> b) & 1;
        int prevChild = trie[cur].child[bit];
        if (prevChild == 0) {
            trie.push_back(TrieNode());
            trie[cur].child[bit] = (int)trie.size() - 1;
        } else {
            int newChild = cloneNode(prevChild);
            trie[cur].child[bit] = newChild;
        }
        cur = trie[cur].child[bit];
        trie[cur].cnt++;
    }
    return newRoot;
}

int queryMaxXor(int x, int lRoot, int rRoot) {
    int res = 0;
    int l = lRoot, r = rRoot;
    for (int b = B - 1; b >= 0; --b) {
        int bit = (x >> b) & 1;
        int want = bit ^ 1;
        int cntWant = trie[trie[r].child[want]].cnt - trie[trie[l].child[want]].cnt;
        int chosen;
        if (cntWant > 0) {
            chosen = want;
            res |= (1 << b);
        } else {
            chosen = bit;
        }
        l = trie[l].child[chosen];
        r = trie[r].child[chosen];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1), pref(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        pref[i] = pref[i - 1] ^ a[i];
    }

    // Persistent trie on prefix xors
    trie.push_back(TrieNode()); // node 0 = empty root
    emptyRoot = 0;
    root.assign(n + 1, 0);
    root[0] = insert(pref[0], emptyRoot);
    for (int i = 1; i <= n; ++i) {
        root[i] = insert(pref[i], root[i - 1]);
    }

    // Sparse table for gcd
    vector<vector<int>> st(LOG, vector<int>(n + 2));
    for (int i = 1; i <= n; ++i) st[0][i] = a[i];
    for (int k = 1; (1 << k) <= n; ++k) {
        int len = 1 << k;
        int half = len >> 1;
        for (int i = 1; i + len - 1 <= n; ++i) {
            st[k][i] = __gcd(st[k - 1][i], st[k - 1][i + half]);
        }
    }
    vector<int> lg(n + 1);
    lg[1] = 0;
    for (int i = 2; i <= n; ++i) lg[i] = lg[i / 2] + 1;

    auto gcd_query = [&](int l, int r) {
        int len = r - l + 1;
        int k = lg[len];
        return __gcd(st[k][l], st[k][r - (1 << k) + 1]);
    };

    // Process right endpoints
    vector<pair<int,int>> cur; // {gcd, minimal left L}
    int ans = 0;

    for (int i = 1; i <= n; ++i) {
        vector<pair<int,int>> nxt;
        nxt.reserve(cur.size() + 1);
        nxt.push_back({a[i], i});
        int last_g = a[i];

        for (auto [g, L] : cur) {
            int ng = __gcd(g, a[i]);
            if (ng == last_g) {
                nxt.back().second = min(nxt.back().second, L);
            } else {
                nxt.push_back({ng, L});
                last_g = ng;
            }
        }
        cur.swap(nxt);

        int upper = i;
        for (auto &p : cur) {
            int g = p.first;
            int L = p.second;
            int R = upper;
            int ql = L - 1;
            int qr = R - 1;
            int target = g ^ pref[i];
            int lRoot = (ql == 0) ? emptyRoot : root[ql - 1];
            int rRoot = root[qr];
            int cand = queryMaxXor(target, lRoot, rRoot);
            if (cand > ans) ans = cand;

            upper = L - 1;
            if (upper < 1) break;
        }
    }

    cout << ans << '\n';
    return 0;
}