#include <bits/stdc++.h>
using namespace std;

const int B = 30;
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
    return trie.size()-1;
}
int insert(int val, int prevRoot) {
    int newRoot = cloneNode(prevRoot);
    int cur = newRoot;
    trie[cur].cnt++;
    for (int b = B-1; b >= 0; --b) {
        int bit = (val >> b) & 1;
        int prevChild = trie[cur].child[bit];
        if (!prevChild) {
            trie.push_back(TrieNode());
            trie[cur].child[bit] = trie.size()-1;
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
    for (int b = B-1; b >= 0; --b) {
        int bit = (x >> b) & 1;
        int want = bit ^ 1;
        int cntWant = trie[trie[r].child[want]].cnt - trie[trie[l].child[want]].cnt;
        int chosen;
        if (cntWant > 0) { chosen = want; res |= (1 << b); }
        else chosen = bit;
        l = trie[l].child[chosen];
        r = trie[r].child[chosen];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n+1), pref(n+1);
    for (int i=1;i<=n;i++){ cin>>a[i]; pref[i]=pref[i-1]^a[i]; }
    trie.push_back(TrieNode()); emptyRoot=0;
    root.assign(n+1,0);
    root[0]=insert(pref[0],emptyRoot);
    for (int i=1;i<=n;i++) root[i]=insert(pref[i],root[i-1]);

    vector<pair<int,int>> cur;
    int ans=0;
    for (int i=1;i<=n;i++){
        vector<pair<int,int>> nxt;
        nxt.push_back({a[i],i});
        int last_g=a[i];
        for(auto [g,L]:cur){
            int ng=__gcd(g,a[i]);
            if(ng==last_g){ nxt.back().second=min(nxt.back().second,L);}
            else {nxt.push_back({ng,L}); last_g=ng;}
        }
        cur.swap(nxt);
        int upper=i;
        for(auto &p:cur){
            int g=p.first, L=p.second, R=upper;
            // BUG: uses L and R instead of L-1 and R-1
            int ql = L;   // should be L-1
            int qr = R;   // should be R-1
            int target = g ^ pref[i];
            int lRoot = (ql==0)?emptyRoot:root[ql-1];
            int rRoot = root[qr];
            int cand = queryMaxXor(target,lRoot,rRoot);
            ans=max(ans,cand);
            upper=L-1;
        }
    }
    cout<<ans<<"\n";
}