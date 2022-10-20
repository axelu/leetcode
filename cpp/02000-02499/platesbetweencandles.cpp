
// 2055. Plates Between Candles
// https://leetcode.com/problems/plates-between-candles/



class Solution {
private:
    // binary search lower bound
    int lb(vector<int>& nums, int n, int target) {
        // returns 'n' if target greater than greatest element
        // returns  0  if target less or equal than smallest element
        // binary search lower bound while loop
        // lower bound -> equal or greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target <= nums[mid] )
                e = mid;
            else
                s = mid+1;
        }
        if( s < n && nums[s] < target )
            ++s;

        return s;
    }

    // binary search greatest element less than target or equal target
    int gelttoet(vector<int>& nums, int n, int s, int target) {
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        // int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( nums[mid] > target )
                e = mid;
            else
                s = mid+1;
        }
        if( (s < n && nums[s] > target) || s == n )
            --s;

        return s;
    }

public:
    vector<int> platesBetweenCandles(string s, vector<vector<int>>& queries) {
        int n = s.size();

        vector<int> candles; // indicies of candles ascending

        int prefixSum[n+1];  // prefixSum plates
        prefixSum[0] = 0;

        for(int i = 0; i < n; ++i) {
            if( s[i] == '|' ) {
                candles.push_back(i);
                prefixSum[i+1] = prefixSum[i];
            } else {
                prefixSum[i+1] = prefixSum[i]+1;
            }
        }

        /*
        // debug
        cout << "candle indicies" << endl;
        for(int x: candles)
            cout << x << " ";
        cout << endl;
        cout << "prefixSum plates" << endl;
        for(int i = 0; i <= n; ++i)
            cout << i << ":" << prefixSum[i] << " ";
        cout << endl;
        */

        int k = queries.size();
        vector<int> ans(k,0);
        for(int i = 0; i < k; ++i) {
            int s = queries[i][0];
            int e = queries[i][1];
            // cout << "query[" << i << "] s " << s << " e " << e << endl;
            if( s == e )
                continue;

            // get the leftmost candle in range [s,e] inclusive
            int l = lb(candles,candles.size(),s);
            // cout << "l " << l << endl;
            if( l == candles.size() )
                continue;
            int leftmost_candle_idx = candles[l];
            // cout << "leftmost_candle_idx " << leftmost_candle_idx << endl;
            if( leftmost_candle_idx >= e-1 )
                continue;

            // get the rightmost candle in range [s,e] inclusive
            int r = gelttoet(candles,candles.size(),l+1,e);
            // cout << "r " << r << endl;
            if( r == -1 )
                continue;
            int rightmost_candle_idx = candles[r];
            // cout << "rightmost_candle_idx " << rightmost_candle_idx << endl;
            if( rightmost_candle_idx < leftmost_candle_idx + 2 )
                continue;

            // get number of plates between rightmost candle
            // and leftmost candle in rage [s,e] inclusive
            ans[i] = prefixSum[rightmost_candle_idx+1] - prefixSum[leftmost_candle_idx];
        }

        return ans;
    }
};
