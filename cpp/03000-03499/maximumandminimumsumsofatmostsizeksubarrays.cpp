
// 3430. Maximum and Minimum Sums of at Most Size K Subarrays
// https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays/

// initialize once
long long intsum[80001];
bool init = false;

class Solution {
private:
    const int INF = 1000001; // -1e6 <= nums[i] <= 1e6
public:
    long long minMaxSubarraySum(vector<int>& nums, int k) {
        if( !init ) {
            init = true;
            intsum[0] = 0LL;
            for(int i = 1; i <= 80000; ++i)
                intsum[i] = intsum[i-1] + (long long)i;          
        }

        int n = nums.size();
        if( n == 1 )
            return 2LL * (long long)nums[0];

        long long ans = 0LL;

        stack<pair<int,int>> stck; // val, index; monotonic stack

        // max ////////////////////////////////////////////////////////////////
        // for each index, find the next greater index to the left and
        // the next greater index to the right
        vector<int> ngir(n);
        stck.push({INF,n}); // sentinel
        for(int i = n-1; i >= 0; --i) {
            int x = nums[i];
            while( stck.top().first <= x )
                stck.pop();
            ngir[i] = stck.top().second;
            stck.push({x, i});
        }
        // clear stack for reuse
        while( !stck.empty() )
            stck.pop();

        vector<int> ngil(n);
        stck.push({INF,-1}); // sentinel
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            while( stck.top().first < x ) // !!! by design to not double count
                stck.pop();
            ngil[i] = stck.top().second;
            stck.push({x, i});
        }
        // clear stack for reuse
        while( !stck.empty() )
            stck.pop();

        // 'compress'
        // we must not double count when we have consecutive values
        // examples: [-7,-7] ans -42, [2,3,3,3,3,2] ans 98
        vector<vector<int>> v; // {{val, left, rigt}, ...}
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            if( i == 0 ) {
                v.push_back({x, 0, -1});
                continue;
            }
            if( x != v.back()[0] ) {
                v.back()[2] = i-1;
                v.push_back({x, i, -1});
            }
            if( i == n-1 ) {
                v.back()[2] = n-1;
            }
        }
        /*
        for(auto& t: v)
            cout << t[0] << "," << t[1] << "," << t[2] << " ";
        cout << endl;
        */

        for(int i = 0; i < v.size(); ++i) {
            // the value at index i is the max for the range
            // starting at ngil[i]+1 and ending at ngir[i]-1
            // but k is our limiter
            int _ngil = max(ngil[v[i][1]]+1, v[i][1]-k+1);
            int _ngir = min(ngir[v[i][2]]-1, v[i][2]+k-1);

            // example 0 1 2 3 4 5   
            //         2 3 3 3 3 2     k = 4
            //         -----------

            // subarrays total
            long long l_total = _ngir - _ngil + 1;
            long long subarrays = l_total * (l_total + 1LL)/2LL;
            // how many subarrays on the left 
            long long l_left = v[i][1] - _ngil;
            long long subarrays_left = l_left * (l_left + 1LL)/2LL;
            // how many subarrays on the right
            long long l_right = _ngir - v[i][2];
            long long subarrays_right = l_right * (l_right + 1LL)/2LL;
            // how many subarrays longer than k
            long long subarrays_longer_k = 0LL;
            if( _ngir - _ngil + 1 > k ) {
                subarrays_longer_k = intsum[_ngir - _ngil + 1 - k];
            }

            ans += (subarrays - subarrays_left - subarrays_right - subarrays_longer_k) * (long long)v[i][0];
        }

        // debug
        // long long ans_after_max = ans;
        // cout << "ans after max " << ans_after_max << endl;

        // min ////////////////////////////////////////////////////////////////
        vector<int> nsir(n); // next smaller index to the right
        stck.push({-INF,n}); // sentinel
        for(int i = n-1; i >= 0; --i) {
            int x = nums[i];
            while( stck.top().first >= x )
                stck.pop();
            nsir[i] = stck.top().second;
            stck.push({x, i});
        }
        // clear stack for reuse
        while( !stck.empty() )
            stck.pop();

        vector<int> nsil(n); // next smaller index to the left
        stck.push({-INF,-1}); // sentinel
        for(int i = 0; i < n; ++i) {
            int x = nums[i];
            while( stck.top().first > x ) // !!! by design to not double count
                stck.pop();
            nsil[i] = stck.top().second;
            stck.push({x, i});
        }
        // clear stack for reuse
        // while( !stck.empty() )
        //    stck.pop();

        for(int i = 0; i < v.size(); ++i) {
            // the value at index i is the max for the range
            // starting at ngil[i]+1 and ending at ngir[i]-1
            // but k is our limiter
            int _nsil = max(nsil[v[i][1]]+1, v[i][1]-k+1);
            int _nsir = min(nsir[v[i][2]]-1, v[i][2]+k-1);

            // subarrays total
            long long l_total = _nsir - _nsil + 1;
            long long subarrays = l_total * (l_total + 1LL)/2LL;
            // how many subarrays on the left 
            long long l_left = v[i][1] - _nsil;
            long long subarrays_left = l_left * (l_left + 1LL)/2LL;
            // how many subarrays on the right
            long long l_right = _nsir - v[i][2];
            long long subarrays_right = l_right * (l_right + 1LL)/2LL;
            // how many subarrays longer than k
            long long subarrays_longer_k = 0LL;
            if( _nsir - _nsil + 1 > k ) {
                subarrays_longer_k = intsum[_nsir - _nsil + 1 - k];
            }

            ans += (subarrays - subarrays_left - subarrays_right - subarrays_longer_k) * (long long)v[i][0];
        }

        // debug
        // long long ans_after_min = ans - ans_after_max;
        // cout << "ans after min " << ans_after_min << endl;


        return ans;
    }
};
