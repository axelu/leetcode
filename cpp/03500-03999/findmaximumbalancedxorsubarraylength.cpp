

// 3755. Find Maximum Balanced XOR Subarray Length
// https://leetcode.com/problems/find-maximum-balanced-xor-subarray-length/

// see 2588. Count the Number of Beautiful Subarrays
// https://leetcode.com/problems/count-the-number-of-beautiful-subarrays/

class Solution {
public:
    int maxBalancedSubarray(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 1e5
        if( n == 1 )
            return 0;

        // let us create a prefixSum, we map odd to 1, even to -1
        // example
        // index     0  1  2  3  4  5  6  7  8  9  0  1 
        //           o  o  o  e  o  o  e  e  o  e  e
        //           1  1  1 -1  1  1 -1 -1  1 -1 -1
        // prefixSum 0  1  2  3  2  3  4  3  2  3  2  1
        //                -----------------------
        // let us assume we are at position i = 2, then we can find
        // subarrays with equal number of odd and even numbers, where
        // prefixSum[j] = 2, then i..j-1 have equal number of odd and even
        // similarly, compute the prefix xor for every index
        // xor of subarray [left, right] is equal to zero if prefix_xor[left] ^ perfix_xor[right] == 0
        // or said differently, if prefix_xor[left] == perfix_xor[right], 
        // then xor of subarray [left, right] is equal to zero

        int prefix_eos[100001];
        prefix_eos[0] = 0;
        int prefix_xor[100001];
        prefix_xor[0] = 0;
        map<pair<int,int>,int> mp; // key: {prefix_eos, prefix_xor}, value: i first seen
        mp[{0,0}] = 0;

        int best = 0;
        for(int i = 1; i <= n; ++i) {
            int parity = nums[i-1] % 2 ? 1 : -1;
            prefix_eos[i] = prefix_eos[i-1] + parity;
            prefix_xor[i] = prefix_xor[i-1] ^ nums[i-1];
            auto p = mp.insert({{prefix_eos[i], prefix_xor[i]}, i});
            if( !p.second )
                best = max(best, i - p.first->second);
        }

        return best;
    }
};




// passes 469/598 test cases as of 11/24/2025, then TLE
// test case 470 runs in ~ 2010ms returning correct result, but obviously too slow

class Solution {
private:
    int t[400000]; // segment tree, range query XOR

    void build(int a[], int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = t[v*2] ^ t[v*2+1];
        }
    }

    int XOR(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return XOR(v*2, tl, tm, l, min(r, tm))
               ^ XOR(v*2+1, tm+1, tr, max(l, tm+1), r);
    }

public:
    int maxBalancedSubarray(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 1e5
        if( n == 1 )
            return 0;

        build(nums.data(),1,0,n-1);

        // let us create a prefixSum, we map odd to 1, even to -1
        // example
        // index     0  1  2  3  4  5  6  7  8  9  0  1
        //           o  o  o  e  o  o  e  e  o  e  e
        //           1  1  1 -1  1  1 -1 -1  1 -1 -1
        // prefixSum 0  1  2  3  2  3  4  3  2  3  2  1
        //                -----------------------
        // let us assume we are at position i = 2, then we can find
        // subarrays with equal number of odd and even numbers, where
        // prefixSum[j] = 2, then i..j-1 have equal number of odd and even

        int prefixSum[100001];
        prefixSum[0] = 0;
        unordered_map<int,vector<int>> pspos; // key: prefixSum, value: {pos, pos, ...}
        pspos[0].push_back(0);
        for(int i = 1; i <= n; ++i) {
            int parity = nums[i-1] % 2 ? 1 : -1;
            prefixSum[i] = prefixSum[i-1] + parity;
            pspos[prefixSum[i]].push_back(i);
        }

        int best = 0;
        for(int i = 0; i < n; ++i) {
            int ps = prefixSum[i];
            int pos_sz = pspos[ps].size();
            for(int k = pos_sz-1; k >= 0; --k) {
                int j = pspos[ps][k];
                int l = j-i;
                if( l == 1 || l <= best )
                    break;
                // l is better than best
                int _xor = XOR(1, 0, n-1, i, j-1);
                if( _xor == 0 ) {
                    best = l;
                    break;
                }
            }
        }

        return best;
    }
};
