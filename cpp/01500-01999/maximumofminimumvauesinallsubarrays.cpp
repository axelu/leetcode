
// 1950. Maximum of Minimum Values in All Subarrays
// https://leetcode.com/problems/maximum-of-minimum-values-in-all-subarrays/



class Solution {
public:
    vector<int> findMaximums(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 10^5, 0 <= nums[i] <= 10^9
        if( n == 1 )
            return {nums[0]};

        // for each element in nums we need to know
        // the range for which it is the minimum
        // in other words:
        // find the farthest element to its left that is
        // still equal or greater than the current element
        // same to the right
        vector<array<int,2>> v(n);      // index left,index right
        stack<int> stck;                // monotonically increasing stack, holds index
        // left
        for(int i = 0; i < n; ++i) {
            while( !stck.empty() && nums[stck.top()] >= nums[i] )
                stck.pop();
            v[i][0] = stck.empty() ? 0 : stck.top()+1;
            stck.push(i);   // push current index onto the stack
        }
        while( !stck.empty() )
            stck.pop();
        // right
        for(int i = n-1; i >= 0; --i) {
            while( !stck.empty() && nums[stck.top()] >= nums[i] )
                stck.pop();
            v[i][1] = stck.empty() ? n-1 : stck.top()-1;
            stck.push(i);   // push current index onto the stack
        }

        // debug
        /*
        for(int i = 0; i < n; ++i) {
            cout << v[i][0] << " " << v[i][1] << endl;
        }
        */


        // we know now for each element the length of the range
        // for which it is the minimum, and with that it is a
        // candidate for the query [1,length]
        // we are looking for the largest 'candidate'
        vector<int> ans(n,-1);

        for(int i = 0; i < n; ++i) {
            int l = v[i][1] - v[i][0] + 1;
            ans[l-1] = max(ans[l-1],nums[i]);
        }

        // there can be gaps in what we have found, but we also know
        // that the answer for subarray of length l is the answer
        // for subarray of length l-1 unless we found a better answer
        int prev = -1;
        for(int i = n-1; i >= 0; --i) {
          ans[i] = max(ans[i],prev);
          prev = ans[i];
        }

        return ans;
    }
};
