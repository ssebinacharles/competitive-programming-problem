#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // prefix_xor[i] = a[0] ^ a[1] ^ ... ^ a[i-1]
    // xor(l, r) = prefix_xor[r+1] ^ prefix_xor[l]
    vector<int> prefix_xor(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix_xor[i + 1] = prefix_xor[i] ^ a[i];
    }
    
    int ans = 0;
    
    // For each position, maintain list of (gcd_value, earliest_start_index)
    // Actually, we need to track all starts to compute XOR properly
    // But we can optimize: for each distinct gcd, we want to find the best XOR
    
    // Let's maintain: vector of pairs (gcd_value, set of start indices)
    // But that's too expensive. Instead, note that for a fixed gcd value g appearing
    // at multiple start positions, we want max(g XOR (prefix_xor[r+1] ^ prefix_xor[start]))
    // = max over starts of (g XOR prefix_xor[r+1] XOR prefix_xor[start])
    // For fixed g and r, this is maximizing (constant XOR prefix_xor[start])
    // which means we want prefix_xor[start] to be as different from (g XOR prefix_xor[r+1]) as possible
    
    // Better approach: maintain for each distinct gcd value, a trie of prefix_xor values
    // But that might be complex. Let's think differently.
    
    // Alternative: since number of distinct GCDs ending at any position is O(log(max_val)),
    // total distinct (gcd, position) pairs is O(n log(max_val))
    // For each such pair, we have a specific start index, so we can compute XOR directly
    
    // Let's just enumerate all O(n log(max_val)) subarrays defined by their right endpoint
    // and distinct GCD values
    
    // prev_gcds: list of (gcd_value, start_index) for subarrays ending at previous position
    vector<pair<int,int>> prev_gcds;
    
    for (int i = 0; i < n; i++) {
        vector<pair<int,int>> curr_gcds;
        
        // Extend all previous subarrays to include a[i]
        for (auto& [g, start] : prev_gcds) {
            int new_g = __gcd(g, a[i]);
            if (!curr_gcds.empty() && curr_gcds.back().first == new_g) {
                // Keep the earliest start for this gcd (to potentially get more XOR options later)
                // Actually, we need to check all starts, so let's keep all
                curr_gcds.push_back({new_g, start});
            } else {
                curr_gcds.push_back({new_g, start});
            }
        }
        
        // Add subarray consisting of just a[i]
        curr_gcds.push_back({a[i], i});
        
        // Now evaluate each distinct subarray configuration
        // Actually, we should merge same GCDs but keep track of all starts
        // For efficiency, let's just evaluate each entry
        
        for (auto& [g, start] : curr_gcds) {
            int xr = prefix_xor[i + 1] ^ prefix_xor[start];
            ans = max(ans, g ^ xr);
        }
        
        // Merge consecutive entries with same GCD, keeping earliest start
        vector<pair<int,int>> merged;
        for (auto& [g, start] : curr_gcds) {
            if (!merged.empty() && merged.back().first == g) {
                // Keep the one with earlier start (smaller index)
                merged.back().second = min(merged.back().second, start);
            } else {
                merged.push_back({g, start});
            }
        }
        
        prev_gcds = merged;
    }
    
    cout << ans << "\n";
    
    return 0;
}