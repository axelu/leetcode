
// 325. Maximum Size Subarray Sum Equals k
// https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/
// day 29 Sep 2021 challenge
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge-2021/640/week-5-september-29th-september-30th/3991/

class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        int n = nums.size();
        
        int i;
        
        long pfxSum[200001]; // 1 <= n <= 2 * 1e5
        pfxSum[0] = 0L;
        unordered_map<long,int> um; // pfxSum, rightmost index with given pfxSum
        pair<unordered_map<long,int>::iterator,bool> p;
        for(i = 0; i < n; ++i) {
            pfxSum[i+1] = pfxSum[i]+(long)nums[i];
            p = um.insert({pfxSum[i],i});
            if( !p.second )
                p.first->second = i;
        }
        p = um.insert({pfxSum[i],i});
        if( !p.second )
            p.first->second = i;
        
        /*
        for(i = 0; i <= n; ++i)
            cout << pfxSum[i] << " ";
        cout << endl;
        */
        
        // sum of elements [i,j] inclusive = pfxSum[j+1] - pfxSum[i]
        // k = pfxSum[j+1] - pfxSum[i]  -> pfxSum[j+1] = k + pfxSum[i]
        
        int ans = 0;
        long t;
        unordered_map<long,int>::iterator ite = um.end(),f;
        for(i = 0; i < n; ++i) {
            t = k + pfxSum[i];
            f = um.find(t);
            if( f != ite )
                ans = max(ans,f->second-i);
        }
        
        return ans;
    }
};
