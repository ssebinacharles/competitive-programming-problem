
cpp_code = '''#include <bits/stdc++.h>
using namespace std;

const int MAX_BITS = 30;

struct Trie {
    struct Node {
        int child[2];
        Node() { child[0] = child[1] = -1; }
    };
    
    vector<Node> nodes;
    
    Trie() {
        nodes.emplace_back(); // root
    }
    
    void insert(int num) {
        int cur = 0;
        for (int i = MAX_BITS - 1; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if (nodes[cur].child[bit] == -1) {
                nodes[cur].child[bit] = nodes.size();
                nodes.emplace_back();
            }
            cur = nodes[cur].child[bit];
        }
    }
    
    int queryMaxXor(int num) {
        int cur = 0;
        int result = 0;
        for (int i = MAX_BITS - 1; i >= 0; i--) {
            int bit = (num >> i) & 1;
            int desired = bit ^ 1; // we want opposite bit for max XOR
            if (nodes[cur].child[desired] != -1) {
                result |= (1 << i);
                cur = nodes[cur].child[desired];
            } else {
                cur = nodes[cur].child[bit];
            }
        }
        return result;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // Prefix XOR
    vector<int> prefixXor(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefixXor[i + 1] = prefixXor[i] ^ a[i];
    }
    
    long long ans = 0;
    
    // For each right endpoint r, maintain list of (gcd_value, start_index, end_index)
    // where [start_index, end_index] is the range of l values giving this gcd
    // Actually, we store (gcd_value, leftmost_l) and process ranges
    
    // currentGcds: list of (gcd, leftmost_l) for subarrays ending at previous position
    vector<pair<int, int>> currentGcds;
    
    for (int r = 0; r < n; r++) {
        vector<pair<int, int>> newGcds;
        
        // Start new subarray at r
        newGcds.push_back({a[r], r});
        
        // Extend previous subarrays
        for (auto &[g, l] : currentGcds) {
            int newGcd = __gcd(g, a[r]);
            if (!newGcds.empty() && newGcds.back().first == newGcd) {
                // Keep the leftmost l (don't update since l <= newGcds.back().second)
            } else {
                newGcds.push_back({newGcd, l});
            }
        }
        
        // For each distinct GCD value in newGcds, we have a range of l values
        // newGcds[i] has gcd = newGcds[i].first, and covers l from newGcds[i].second 
        // to (i > 0 ? newGcds[i-1].second - 1 : r)
        // Wait, let me think again...
        
        // Actually, newGcds is ordered by decreasing l (leftmost first? or last?)
        // Let me reconsider: when we push back, we're adding with decreasing l values
        // No wait, currentGcds has entries with various l values
        
        // Let me think differently:
        // newGcds[j] represents all subarrays [l..r] where l is in some range
        // and gcd(a[l..r]) = newGcds[j].first
        // The ranges are contiguous and non-overlapping
        
        // newGcds[0] corresponds to l = r (just element a[r])
        // newGcds[1] corresponds to l in [newGcds[1].second, r-1] (if exists)
        // etc.
        
        // Actually the structure is:
        // newGcds[i].second is the LEFTMOST l that gives newGcds[i].first as GCD
        // The RIGHTMOST l for newGcds[i] is newGcds[i-1].second - 1 (or r for i=0)
        
        // So for newGcds[i], l ranges from newGcds[i].second to rightBound
        // where rightBound = (i == 0) ? r : newGcds[i-1].second - 1
        
        // Build a trie with prefixXor values for efficient querying
        // But we need range queries... 
        
        // Alternative: just iterate through all possibilities
        // Since newGcds has O(log(max_val)) elements, and for each we might need
        // to check multiple l values... but that could be O(n) per element
        
        // Better approach: for each GCD group, we want max of g ^ (prefixXor[r+1] ^ prefixXor[l])
        // = max of (g ^ prefixXor[r+1]) ^ prefixXor[l]
        // So we want to maximize XOR with (g ^ prefixXor[r+1]) over prefixXor[l] for l in range
        
        // This requires a persistent trie or offline processing...
        
        // Simpler O(n * log^2) approach: for each r, for each GCD group, 
        // just check all l values? No, that's too slow.
        
        // Let me use a different approach: since we only have O(log(max_val)) groups per r,
        // and total across all r is O(n * log(max_val)), we can afford O(log(max_val)) per group
        // if we use tries properly.
        
        // Actually, let's just brute force for now and see if it passes
        // Total work: sum over all r of |newGcds| * (range size)
        // In worst case this is O(n^2), which won't pass
        
        // Need smarter approach. Let me use the fact that we can build tries incrementally
        
        // For now, let me implement a simpler version that checks representative l values
        // Actually, for maximum XOR, we should check boundary values or use trie
        
        // Simplest correct approach: for each group, we need max XOR over a range of prefixXor values
        // Use offline Mo's algorithm? Or segment tree with tries?
        
        // Given constraints (n up to 2*10^5), let me try a different strategy:
        // Process all subarrays efficiently
        
        // REVISED APPROACH: Just check all O(n * log(max_val)) candidate subarrays
        // For each distinct (gcd, l_start) pair, we don't know which l in the range is best
        
        // Hmm, let me just check a few representative l values per group
        // Check l = leftmost and l = rightmost of each range
        
        for (int i = 0; i < (int)newGcds.size(); i++) {
            int g = newGcds[i].first;
            int leftL = newGcds[i].second;
            int rightL = (i == 0) ? r : newGcds[i-1].second - 1;
            
            // Check both endpoints (heuristic, might miss optimal)
            for (int l : {leftL, rightL}) {
                if (l >= 0 && l <= r) {
                    int x = prefixXor[r + 1] ^ prefixXor[l];
                    ans = max(ans, (long long)(g ^ x));
                }
            }
        }
        
        currentGcds = move(newGcds);
    }
    
    cout << ans << "\\n";
    
    return 0;
}
'''

print("This approach might not be optimal. Let me reconsider...")

 # Result 
This approach might not be optimal. Let me reconsider...
