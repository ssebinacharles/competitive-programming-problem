# Maximum GCD XOR

**Time Limit:** 3 seconds  
**Memory Limit:** 256 megabytes  

You are given an array `a` of `n` integers, indexed from `1` to `n`.  
For any non‑empty subarray `a[l..r]` (`1 ≤ l ≤ r ≤ n`), define:

- `g(l,r) = gcd(a[l], a[l+1], …, a[r])`
- `x(l,r) = a[l] xor a[l+1] xor … xor a[r]`

Find the maximum possible value of `g(l,r) xor x(l,r)` over all subarrays.

# Input
The first line contains one integer `n` (`1 ≤ n ≤ 2·10^5`).  
The second line contains `n` integers `a_1, a_2, …, a_n` (`0 ≤ a_i < 2^30`).

# Output
Print a single integer — the maximum value of `g(l,r) xor x(l,r)`.

#Examples

### Input
```
5
3 6 12 8 4
```

### Output
```
12
```

### Input
```
1
0
```

### Output
```
0
```

### Input
```
4
7 7 7 7
```

### Output
```
7
```

# Note
In the first example, the subarray `[2,3]` has `gcd = 6` and `xor = 10`, giving `6 xor 10 = 12`.