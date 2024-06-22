
// 3049. Earliest Second to Mark Indices II
// https://leetcode.com/problems/earliest-second-to-mark-indices-ii/






class Solution {
private:
    bool solve(int x, vector<int>& nums, int sum, vector<int>& changeIndices, vector<int>& earliest) {
        int n = nums.size();

        // go in reverse order from second x to second 1
        // return true if time_needed <= x, else false
        // in other words: x is the time we have to mark all elements in nums.
        // remember: nums and changeIndices are 1-indexed!

        long time_needed = sum + (long)n; // cout << "time_needed origional " << time_needed << endl;
        if( x >= time_needed )
            return true;

        int spare_seconds = 0;
        priority_queue<int,vector<int>,greater<int>> pq;
        for(int s = x; s >= 1; --s) {
            // cout << "at second s " << s << endl;

            int val = nums[changeIndices[s-1]-1];

            // it is optimal to use the operation to reduce a given index in nums to 0 the 1st time that index occurs in changeIndices and
            // if that given nums[index] value is > 0
            // if those conditions are not met, we initially consider doing nothing and park the current second s for later use
            if( val == 0 || earliest[changeIndices[s-1]] != s ) {
                ++spare_seconds;
                continue;
            }

            pq.push(nums[changeIndices[s-1]-1]);
            if( spare_seconds ) {
                // if we have accumulated spare seconds for marking, the use one of those to mark
                --spare_seconds;
            } else {
                // if we don't a spare second, then pop the smallest val so far (least amount of time saving) from the queue and
                // give us a spare second to mark
                pq.pop();
                ++spare_seconds;
            }
        }

        long time_saved = 0L;
        while( !pq.empty() ) {
            time_saved += pq.top() - 1;
            pq.pop();
        }

        return x >= time_needed - time_saved;
    }

    // binary search
    int search(int s, int e, vector<int>& nums, int sum, vector<int>& changeIndices, vector<int>& earliest) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( solve(mid, nums, sum, changeIndices, earliest) ) {
            // can we do better?
            int t = search(s, mid-1, nums, sum, changeIndices, earliest);
            return t != -1 ? t : mid;
        }

        return search(mid+1, e, nums, sum, changeIndices, earliest);
    }



public:
    int earliestSecondToMarkIndices(vector<int>& nums, vector<int>& changeIndices) {
        // nums and changeIndices are 1-indexed
        int n = nums.size(); // 1 <= n <= 5000
        int m = changeIndices.size();

        // we have 4 possible actions at our disposal and want to apply them greedily
        //    at second s we can set nums[changeIndices[s]] to any non-negative value, best value to set to is of course 0
        //    decrement any nums[i] with i in range [1,n] inclusive by 1
        //    mark any nums[i] with i in range [1,n] inclusive if nums[i] == 0
        //    do nothing

        // if all nums[i] would be 0, then we would need only but at least n seconds
        int zeros = 0;
        long sum = 0L;
        for(int i = 0; i < n; ++i) {
            if( nums[i] != 0 )
                sum += (long)nums[i];
            else
                ++zeros;
        }
        int nonzeros = n - zeros;
        if( nonzeros * 2 + zeros > m ) // nonzeros * 2 + zeros <- best case scenario
            return -1;

        vector<int> earliest(n+1,-1); // earliest occurence of index into nums in changeIndices
        for(int i = m-1; i >= 0; --i)
            earliest[changeIndices[i]] = i+1;

        return search(nonzeros * 2 + zeros, m, nums, sum, changeIndices, earliest);
    }
};
