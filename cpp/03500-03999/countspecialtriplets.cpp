
// 3583. Count Special Triplets
// https://leetcode.com/problems/count-special-triplets/




class Solution {
public:
    int specialTriplets(vector<int>& nums) {
        int n = nums.size(); // 3 <= n <= 1e5

        const long mod = 1000000007;

        long ans = 0L;

        // right to left

        unordered_map<int,long> cnt;


        unordered_map<int,int> last; // value, last seen position
        vector<long> aggr(n,0L);

        for(int i = n-1; i >= 0; --i) {
            int val = nums[i];
            if( i <= n-3 && val % 2 == 0 ) {
                int valh = val / 2;
                // when did we last see valh?
                int last_seen_valh_at = -1;
                auto fh = last.find(valh);
                if( fh != last.end() )
                    last_seen_valh_at = fh->second;
                if( last_seen_valh_at != -1 )
                    ans = (ans + aggr[last_seen_valh_at]) % mod;
            }

            // how many times have we seen val * 2 so far?
            int val2 = val * 2;
            int cur_cnt = cnt[val2];
            aggr[i] = cur_cnt;
            // when did we last see val?
            int last_seen_val_at = -1;
            auto f = last.find(val);
            if( f != last.end() )
                last_seen_val_at = f->second;
            if( last_seen_val_at != -1 )
                aggr[i] = (aggr[i] + aggr[last_seen_val_at]) % mod;


            ++cnt[val];
            last[val] = i;
        }


        return ans;
    }
};
