
// 3347. Maximum Frequency of an Element After Performing Operations II
// https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-ii/









// see also 3346. Maximum Frequency of an Element After Performing Operations I
// https://leetcode.com/problems/maximum-frequency-of-an-element-after-performing-operations-i/

class Solution {
private:
    // binary search
    int gelt(vector<vector<int>>& nums, int n, long target) {
        // binary search greatest element less than target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( nums[mid][0] < target )
                s = mid+1;
            else
                e = mid;
        }
        if( (s < n && nums[s][0] >= target) || s == n )
            --s;

        return s;
    }

    // binary search
    int gelttoet(vector<vector<int>>& nums, int n, int s, long target) {
        // binary search greatest element less than target or equal target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        // int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( nums[mid][0] > target )
                e = mid;
            else
                s = mid+1;
        }
        if( (s < n && nums[s][0] > target) || s == n )
            --s;

        return s;
    }

    // binary search
    int lower_bound(vector<vector<int>>& nums, int n, long target) {
        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid][0] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s][0] < target )
            ++s;

        return s;
    }

    // binary search
    int upper_bound(vector<vector<int>>& nums, int n, long target) {
        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        // binary search upper bound while loop
        // upper bound -> greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= nums[mid][0] )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && nums[s][0] <= target )
            ++s;

        return s;
    }

public:
    int maxFrequency(vector<int>& nums, int k, int numOperations) {
        int n = nums.size();

        map<int,int> cnt;
        int cnt_mx = 0;
        for(int i = 0; i < n; ++i)
            cnt_mx = max(cnt_mx, ++cnt[nums[i]]);

        if( k == 0 || numOperations == 0 ) {
            // the answer is the most frequent val in nums
            return cnt_mx;
        }

        if( cnt_mx == n )
            return n;

        // add sentinels
        cnt[0] = 0;
        cnt[1000000001] = 0;

        int cnt_sz = cnt.size(); // cout << "cnt_sz " << cnt_sz << endl;
        int prefixSum[cnt_sz+1];
        prefixSum[0] = 0;
        int i = 1;
        vector<vector<int>> v(cnt_sz,vector<int>(2));
        for(auto it = cnt.begin(); it != cnt.end(); ++it, ++i) {
            prefixSum[i] = prefixSum[i-1] + it->second;
            v[i-1] = {it->first,it->second};
        }

        int ans = cnt_mx;

        // TODO we could do one pass and step to next value
        // next value smallest step lower, middle or upper bound

        // pass 1 lower boundary at unique values
        // cout << "pass 1" << endl;
        for(i = 0; i < cnt_sz-1; ++i) {
            long lb = (long)v[i][0];
            long at = (long)v[i][0] + (long)k;
            long ub = (long)v[i][0] + (long)(2*k);

            // cout << "i " << i << " lb " << lb << " at " << at << " ub " << ub << endl;

            // we know we have a cnt at lb, we may not have one at at or at ub

            int e_lb = gelt(v, cnt_sz, at);
            int a = prefixSum[e_lb+1] - prefixSum[i];

            int b = cnt.find(at) != cnt.end() ? cnt[at] : 0;

            int c = 0;
            int s_ub = upper_bound(v, cnt_sz, at);
            if( s_ub < cnt_sz ) {
                int e_ub = gelttoet(v, cnt_sz, s_ub, ub);
                c = prefixSum[e_ub+1] - prefixSum[s_ub];
            }

            // cout << "a " << a << " b " << b << " c " << c << endl;
            ans = max(ans, min(numOperations, a + c) + b);
        }


        // pass 2 unique value
        // cout << "pass 2" << endl;
        for(i = 1; i < cnt_sz-1; ++i) {
            long lb = (long)v[i][0] - (long)k;
            long at = (long)v[i][0];
            long ub = (long)v[i][0] + (long)k;

            // cout << "i " << i << " lb " << lb << " at " << at << " ub " << ub << endl;

            // we know we have a cnt at at, we may not have one at lb or at ub

            int a = 0;
            int e_lb = gelt(v, cnt_sz, at);
            if( v[e_lb][0] >= lb ) {
                int s_lb = lower_bound(v, cnt_sz, lb);
                a = prefixSum[e_lb+1] - prefixSum[s_lb];
            }

            int b = cnt[at];

            int c = 0;
            int s_ub = upper_bound(v, cnt_sz, at);
            if( s_ub < cnt_sz ) {
                int e_ub = gelttoet(v, cnt_sz, s_ub, ub);
                c = prefixSum[e_ub+1] - prefixSum[s_ub];
            }

            // cout << "a " << a << " b " << b << " c " << c << endl;
            ans = max(ans, min(numOperations, a + c) + b);
        }


        // pass 3 uppwer boundary at unique values
        // cout << "passs 3" << endl;
        for(i = 1; i < cnt_sz; ++i) {
            long lb = (long)v[i][0] - (long)(2*k);
            long at = (long)v[i][0] - (long)k;
            long ub = (long)v[i][0];

            // cout << "i " << i << " lb " << lb << " at " << at << " ub " << ub << endl;

            // we know we have a cnt at ub, we may not have one at lb or at at

            int a = 0;
            int e_lb = gelt(v, i, at);
            if( e_lb != -1 && v[e_lb][0] >= lb ) {
                int s_lb = lower_bound(v, e_lb+1, lb);
                a = prefixSum[e_lb+1] - prefixSum[s_lb];
            }

            int b = cnt.find(at) != cnt.end() ? cnt[at] : 0;

            int c = 0;
            int s_ub = upper_bound(v, cnt_sz, at);
            if( s_ub < cnt_sz ) {
                int e_ub = gelttoet(v, cnt_sz, s_ub, ub);
                c = prefixSum[e_ub+1] - prefixSum[s_ub];
            }

            // cout << "a " << a << " b " << b << " c " << c << endl;
            ans = max(ans, min(numOperations, a + c) + b);
        }


        return ans;
    }
};
