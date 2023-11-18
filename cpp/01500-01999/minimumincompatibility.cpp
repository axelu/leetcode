
// 1681. Minimum Incompatibility
// https://leetcode.com/problems/minimum-incompatibility/







class Solution {
private:
    // debug
    void printBinary(int x, int c) {
        for(int i = c-1; i >= 0; --i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }

    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    int mem[65536];

    int rec(vector<int>& nums, const int n, const int k, const int k_inc, const int mask, const int mask_limit) {
        // cout << "rec mask "; printBinary(mask,n); cout << endl;
        if( mask == mask_limit )
            return 0;

        if( mem[mask] != -1 )
            return mem[mask];

        int ret = 1000000000;

        // cout << "  target mask countSetBits   " << t_target << endl;
        for(int i = mask; i <= mask_limit; ++i) {
            // in our new mask i, the original bits must be set
            // and the count set bits is t_target
            if( (mask & i) == mask && countSetBits(i) == k ) {
                bool has_dup = false;
                int cnt[n+1];memset(cnt,0,sizeof cnt);
                int mn = INT_MAX;
                int mx = INT_MIN;
                for(int j = 0; j < n; ++j) {
                    if( !(mask & (1<<j)) && (i & (1<<j)) ) {
                        ++cnt[nums[j]];
                        if( cnt[nums[j]] == 2 ) {
                            has_dup = true;
                            break;
                        }
                        mn = min(mn,nums[j]);
                        mx = max(mx,nums[j]);
                    }
                }
                if( has_dup )
                    continue;
                int incompatibility = mx - mn;
                ret = min(ret, incompatibility + rec(nums,n,k+k_inc,k_inc,i,mask_limit));
            }
        }

        return mem[mask] = ret;
    }

    int rec2(vector<pair<int,int>>& subset_masks, int mask, int mask_limit) {
        if( mask == mask_limit )
            return 0;

        if( mem[mask] != -1 )
            return mem[mask];

        int ret = 1000000000;

        for(auto it = subset_masks.begin(); it != subset_masks.end(); ++it) {
            if( (it->first & mask) != 0 )
                continue;

            ret = min(ret, it->second + rec2(subset_masks,it->first|mask,mask_limit));
        }

        return mem[mask] = ret;
    }




public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        int n = nums.size();    // 1 <= k <= nums.length <= 16
                                // nums.length is divisible by k
        if( n == k )
            return 0;

        // precalculate subsets
        int setbits_target = n / k;
        int mask_limit = pow(2,n)-1;
        vector<pair<int,int>> subset_masks; // mask, incompatibility
        for(int i = 0; i <= mask_limit; ++i) {
            if( countSetBits(i) == setbits_target ) {
                bool has_dup = false;
                int cnt[n+1];memset(cnt,0,sizeof cnt);
                int mn = INT_MAX;
                int mx = INT_MIN;
                for(int j = 0; j < n; ++j) {
                    if( (i & (1<<j)) ) {
                        if( ++cnt[nums[j]] == 2 ) {
                            has_dup = true;
                            break;
                        }
                        mn = min(mn,nums[j]);
                        mx = max(mx,nums[j]);
                    }
                }
                if( !has_dup ) {
                    subset_masks.push_back({i, mx-mn});
                }
            }
        }
        // for(auto it = subset_masks.begin(); it != subset_masks.end(); ++it)
        //    printBinary(it->first,n);cout << endl;

        memset(mem,-1,sizeof mem);
        int ans = rec2(subset_masks,0,mask_limit);
        return ans >= 1000000000 ? -1 : ans;

        /*
        memset(mem,-1,sizeof mem);
        int ans = rec(nums,n,n/k,n/k,0,pow(2,n)-1);
        return ans >= 1000000000 ? -1 : ans;
        */
    }
};
