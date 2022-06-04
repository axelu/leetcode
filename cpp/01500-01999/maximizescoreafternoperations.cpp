
// 1799. Maximize Score After N Operations
// https://leetcode.com/problems/maximize-score-after-n-operations/



class Solution {
private:
    void printBinary(long x, int c) {
        /*
        for(int i = c-1; i >= 0; --i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        */
        for(int i = 0; i < c; ++i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }

    // recursive function to return gcd of a and b
    // long long gcd(long long int a, long long int b) {
    int gcd(int a, int b) {
        if( b == 0 )
            return a;
        return gcd(b,a % b);
    }

    int n;
    int mem[15][16384];

    int rec(vector<int>& nums, int f, int mask) {
        // cout << "rec f " << f << " mask ";printBinary(mask,n);
        if( f > n/2 )
            return 0;

        if( mem[f][mask] != -1 )
            return mem[f][mask];

        int a = 0;

        // pair the 1st available idx with any other available idx
        for(int i = 0; i < n-1; ++i) {
            if( ((mask >> i) & 1) )
                continue;
            mask |= 1 << i;
            for(int j = i+1; j < n; ++j) {
                if( ((mask >> j) & 1) )
                    continue;
                mask |= 1 << j;

                a = max(a,f*gcd(nums[i],nums[j]) + rec(nums,f+1,mask));

                // backtrack
                mask &= ~(1 << j);
            }
            // backtrack
            mask &= ~(1 << i);
        }

        return mem[f][mask] = a;
    }

public:
    int maxScore(vector<int>& nums) {
        n = nums.size(); // 2 <= n <= 14, n is even

        memset(mem,-1,sizeof mem);
        return rec(nums,1,0);
    }
};
