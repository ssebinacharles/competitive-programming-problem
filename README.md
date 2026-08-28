# Adversarial Problem: Maximum GCD XOR

This repository contains a Codeforces Div1/Div2 level problem designed to be original and difficult for language models.

The optimal solution uses:
- Sparse table for range GCD
- Persistent binary trie for range maximum XOR queries
- Standard technique of enumerating distinct gcd intervals (`O(n log A)`)

Three simulated Qwen attempts are included. They fail due to:
1. Brute force TLE
2. Incorrect greedy
3. Off‑by‑one in persistent trie query

All test cases are small enough to be verified by brute force, except the large hidden case used by the judge.