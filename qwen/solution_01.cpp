
cpp_code = r'''#include <bits/stdc++.h>
using namespace std;

const int MAX_BITS = 30;

struct Node {
    int child[2];
    int count;
    Node() : child{-1, -1}, count(0) {}
};

vector<Node> trie;
vector<int> roots;

int newNode() {
    trie.emplace_back();
    return trie.size() - 1;
}

int insert(int oldRoot, int value, int bit = MAX_BITS - 1) {
    int newRoot = newNode();
    if (oldRoot != -1) {
        trie[newRoot] = trie[oldRoot];
    }
    trie[newRoot].count++;
    
    if (bit < 0) {
        return newRoot;
    }
    
    int b = (value >> bit) & 1;
    int nextOld = (oldRoot != -1) ? trie[oldRoot].child[b] : -1;
    trie[newRoot].child[b] = insert(nextOld, value, bit - 1);
    
    return newRoot;
}

int queryMaxXor(int rootR, int rootL, int value, int bit = MAX_BITS - 1) {
    if (bit < 0) {
        return 0;
    }
    
    int b = (value >> bit) & 1;
    int desired = 1 - b;
    
    int countDesiredR = (rootR != -1 && trie[rootR].child[desired] != -1) ? 
                        trie[trie[rootR].child[desired]].count : 0;
    int countDesiredL = (rootL != -1 && trie[rootL].child[desired] != -1) ? 
                        trie[trie[rootL].child[desired]].count : 0;
    
    if (countDesiredR - countDesiredL > 0) {
        int nextRootR = (rootR != -1) ? trie[rootR].child[desired] : -1;
        int nextRootL = (rootL != -1) ? trie[rootL].child[desired] : -1;
        return (1 << bit) | queryMaxXor(nextRootR, nextRootL, value, bit - 1);
    } else {
        int nextRootR = (rootR != -1) ? trie[rootR].child[b] : -1;
        int nextRootL = (rootL != -1) ? trie[rootL].child[b] : -1;
        return queryMaxXor(nextRootR, nextRootL, value, bit - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<int> prefixXor(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefixXor[i + 1] = prefixXor[i] ^ a[i];
    }
    
    // Build persistent trie
    trie.reserve((n + 2) * (MAX_BITS + 2));
    roots.resize(n + 2);
    
    roots[0] = -1;
    for (int i = 0; i <= n; i++) {
        roots[i + 1] = insert(roots[i], prefixXor[i]);
    }
    
    int ans = 0;
    
    // For each right endpoint, maintain list of (gcd, left_start, left_end)
    vector<tuple<int, int, int>> currentGcds;
    
    for (int r = 0; r < n; r++) {
        vector<tuple<int, int, int>> newGcds;
        
        // Add single element subarray [r, r]
        newGcds.emplace_back(a[r], r, r);
        
        // Extend previous subarrays to include a[r]
        for (auto &[g, ls, le] : currentGcds) {
            int newG = __gcd(g, a[r]);
            if (!newGcds.empty() && get<0>(newGcds.back()) == newG) {
                get<2>(newGcds.back()) = le;
            } else {
                newGcds.emplace_back(newG, ls, le);
            }
        }
        
        currentGcds = move(newGcds);
        
        // For each distinct GCD value, find optimal left endpoint
        for (auto &[g, ls, le] : currentGcds) {
            int target = g ^ prefixXor[r + 1];
            int bestXor = queryMaxXor(roots[le + 1], roots[ls], target);
            ans = max(ans, bestXor);
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}
'''

print(cpp_code)

 # Result 
#include <bits/stdc++.h>
using namespace std;

const int MAX_BITS = 30;

struct Node {
    int child[2];
    int count;
    Node() : child{-1, -1}, count(0) {}
};

vector<Node> trie;
vector<int> roots;

int newNode() {
    trie.emplace_back();
    return trie.size() - 1;
}

int insert(int oldRoot, int value, int bit = MAX_BITS - 1) {
    int newRoot = newNode();
    if (oldRoot != -1) {
        trie[newRoot] = trie[oldRoot];
    }
    trie[newRoot].count++;
    
    if (bit < 0) {
        return newRoot;
    }
    
    int b = (value >> bit) & 1;
    int nextOld = (oldRoot != -1) ? trie[oldRoot].child[b] : -1;
    trie[newRoot].child[b] = insert(nextOld, value, bit - 1);
    
    return newRoot;
}

int queryMaxXor(int rootR, int rootL, int value, int bit = MAX_BITS - 1) {
    if (bit < 0) {
        return 0;
    }
    
    int b = (value >> bit) & 1;
    int desired = 1 - b;
    
    int countDesiredR = (rootR != -1 && trie[rootR].child[desired] != -1) ? 
                        trie[trie[rootR].child[desired]].count : 0;
    int countDesiredL = (rootL != -1 && trie[rootL].child[desired] != -1) ? 
                        trie[trie[rootL].child[desired]].count : 0;
    
    if (countDesiredR - countDesiredL > 0) {
        int nextRootR = (rootR != -1) ? trie[rootR].child[desired] : -1;
        int nextRootL = (rootL != -1) ? trie[rootL].child[desired] : -1;
        return (1 << bit) | queryMaxXor(nextRootR, nextRootL, value, bit - 1);
    } else {
        int nextRootR = (rootR != -1) ? trie[rootR].child[b] : -1;
        int nextRootL = (rootL != -1) ? trie[rootL].child[b] : -1;
        return queryMaxXor(nextRootR, nextRootL, value, bit - 1);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    vector<int> prefixXor(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefixXor[i + 1] = prefixXor[i] ^ a[i];
    }
    
    // Build persistent trie
    trie.reserve((n + 2) * (MAX_BITS + 2));
    roots.resize(n + 2);
    
    roots[0] = -1;
    for (int i = 0; i <= n; i++) {
        roots[i + 1] = insert(roots[i], prefixXor[i]);
    }
    
    int ans = 0;
    
    // For each right endpoint, maintain list of (gcd, left_start, left_end)
    vector<tuple<int, int, int>> currentGcds;
    
    for (int r = 0; r < n; r++) {
        vector<tuple<int, int, int>> newGcds;
        
        // Add single element subarray [r, r]
        newGcds.emplace_back(a[r], r, r);
        
        // Extend previous subarrays to include a[r]
        for (auto &[g, ls, le] : currentGcds) {
            int newG = __gcd(g, a[r]);
            if (!newGcds.empty() && get<0>(newGcds.back()) == newG) {
                get<2>(newGcds.back()) = le;
            } else {
                newGcds.emplace_back(newG, ls, le);
            }
        }
        
        currentGcds = move(newGcds);
        
        // For each distinct GCD value, find optimal left endpoint
        for (auto &[g, ls, le] : currentGcds) {
            int target = g ^ prefixXor[r + 1];
            int bestXor = queryMaxXor(roots[le + 1], roots[ls], target);
            ans = max(ans, bestXor);
        }
    }
    
    cout << ans << "\n";
    
    return 0;
}

