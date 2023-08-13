
// 2289. Steps to Make Array Non-decreasing
// https://leetcode.com/problems/steps-to-make-array-non-decreasing/




class Solution {
private:

    // brute force
    int solve(vector<int>& nums, int s, int e) {
        int n = e-s;
        if( n == 1 )
            return 0;
        if( n == 2 )
            return 1;

        map<int,int> mp; // idx,val
        vector<array<int,2>> q;  // idx-1, idx to be deleted
        mp[s] = nums[s];
        for(int i = s+1; i < e; ++i) {
            mp[i] = nums[i];
            if( nums[i-1] > nums[i] )
                q.push_back({i-1,i});
        }

        int ret = 0;
        while( mp.size() > 1 ) {
            ++ret;
            // perform deletions
            for(auto a: q)
                mp.erase(a[1]);
            vector<array<int,2>> q_new;
            for(auto a: q) {
                auto f = mp.find(a[0]);
                if( f == mp.end() || next(f) == mp.end() )
                    continue;
                if( f->second > next(f)->second )
                    q_new.push_back({f->first,next(f)->first});
            }
            swap(q,q_new);
        }

        return ret;
    }

public:
    int totalSteps(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 0;

        int last_num = nums[0];
        int last_idx = 0;
        int ans = 0;
        for(int i = 1; i < n; ++i) {
            if( nums[i] >= last_num ) {
                ans = max(ans,solve(nums,last_idx,i));
                last_num = nums[i];
                last_idx = i;
            }
        }
        // finish up
        ans = max(ans,solve(nums,last_idx,n));

        return ans;
    }
};
