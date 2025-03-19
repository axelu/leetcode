
// 2902. Count of Sub-Multisets With Bounded Sum
// https://leetcode.com/problems/count-of-sub-multisets-with-bounded-sum/

// https://algodaily.com/lessons/coin-change-problem-3bffde34

class Solution {
private:
    const long mod = 1000000007L;
        
public:
    int countSubMultisets(vector<int>& nums, int l, int r) {
        int n = nums.size(); // 1 <= nums.length <= 2 * 1e4, sum of nums does not exceed 2 * 1e4
        
        // sum of nums does not exceed 2 * 1e4
        /*
        int total = 0;
        int unique = 0;
        for(; total <= 20000; ++unique)
            total += unique;
        cout << unique << endl;
        */
        // above shows that if we would start with the smallest possible element, 0,
        // and increment by 1, we would have at most 200 unique elements! 
        
        // also, we will only at most have 20000 different sums
        // so the answer to our problem is
        //     number of multisets summing up to l
        //     number of multisets summing up to l+1
        //     ...
        //     number of multisets summumg up to r-1
        //     number of multisets summing up to r
        // this is basically the coin change problem
        
        
        map<int,int> cnt; // key: val  value: count
        for(int x: nums)
            ++cnt[x];

        // bottom up dp
        
        vector<long> dp(r+1, 0L);  // number of ways we can make a given amount
        // we may or may not have a 'coin' of value 0, but let us assume we have at least 1
        ++cnt[0];
        // with that we will be able to make the amount of 0 in one way (each coin is the same)
        dp[0] = cnt[0];
        
        for(auto& p: cnt) {
            // skip coins with amount of 0
            if( p.first == 0 )
                continue;
            
            for(int amount = r; amount >= 0; --amount) {
                // if we are able to make the current amount in a number of ways,
                // then we can make new amounts by picking 1..k coins of our current denomination
                if( dp[amount] > 0 ) {
                    int denomination = p.first;
                    for(int k = 1; k <= p.second; ++k) {
                        int amount_new = amount + (denomination * k);
                        if( amount_new <= r ) {
                            dp[amount_new] = (dp[amount] + dp[amount_new]) % mod;    
                        } else {
                            break;
                        }
                    }
                }
            }
        }
        
        long ans = 0;
        // we are only interested in the number of ways to make l <= amount <= r
        for(int amount = l; amount <= r; ++amount)
            ans = (ans + dp[amount]) % mod;
        
        return ans;
    }
};



// passes 636/643 test cases as of 12/21/2024, then TLE
// case 637 runs in about 300ms

class Solution {
private:
    const long mod = 1000000007L;
    
    long mem[201][20000]; // pos, sum
    
    long rec(vector<pair<int,int>>& v, int n, int pos, int sum, int l, int r) {
        // cout << "rec pos " << pos << " sum " << sum << endl;
        
        
        // let val be the val at pos
        int val;
        if( pos < n ) {
            val = v[pos].first;
            if( val > r || sum + val > r) {
                // cout << "val " << val << " either val > r || sum + val > r " << (l <= sum && sum <= r) << endl;
                return l <= sum && sum <= r ? 1L : 0L;
            }
        }

        if( pos == n )
            return l <= sum && sum <= r ? 1L : 0L;

        if( sum > r )
            return 0L;
        
        if( mem[pos][sum] != -1 )
            return mem[pos][sum];
        
        // let k be the number of elements with the value at pos
        int k = v[pos].second; // k > 0
        
        // we have a choice
        //    don't grab an element of the current value OR
        //    grab 1..k
        
        long ret = 0L;
        
        ret = rec(v, n, pos+1, sum, l, r);
        
        for(int i = 1; i <= k; ++i) {
            
            long sum_new = sum + (i * val);
            if( sum_new > r ) // early exit
                break;
            
            ret = (ret + rec(v, n, pos+1, sum_new, l, r)) % mod;
        }
        
        // cout << "rec pos " << pos << " sum " << sum << " ret " << ret << endl;
        return mem[pos][sum] = ret;
        // return ret;
    }
    
public:
    int countSubMultisets(vector<int>& nums, int l, int r) {
        int n = nums.size(); // 1 <= nums.length <= 2 * 1e4, sum of nums does not exceed 2 * 1e4
        
        // sum of nums does not exceed 2 * 1e4
        /*
        int total = 0;
        int unique = 0;
        for(; total <= 20000; ++unique)
            total += unique;
        cout << unique << endl;
        */
        // above shows that if we would start with the smallest possible element, 0,
        // and increment by 1, we would have at most 200 unique elements! 
        
        map<int,int> cnt; // key: val  value: count
        for(int x: nums)
            ++cnt[x];
        
        int uniques = cnt.size();
        vector<pair<int,int>> v(uniques); // {{val,count}, ...} with values sorted asc
        int v_idx = 0;
        for(auto it = cnt.begin(); it != cnt.end(); ++it)
            v[v_idx++] = {it->first, it->second};
        
        memset(mem,-1,sizeof mem);
        return rec(v, uniques, 0, 0, l, r);
    }
};
