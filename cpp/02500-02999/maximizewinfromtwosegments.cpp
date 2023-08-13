
// 2555. Maximize Win From Two Segments
// https://leetcode.com/problems/maximize-win-from-two-segments/




class Solution {
private:
    int geltoet(vector<pair<int,int>>& nums, int target) {
        // binary search greatest element less than target or equal target
        // returns n-1 if nums[n-1] < target
        // returns  -1 if nums[0] > target
        int s = 0;
        int n = nums.size();
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( nums[mid].first > target )
                e = mid;
            else
                s = mid+1;
        }
        if( (s < n && nums[s].first > target) || s == n )
            --s;

        return s;
    }

public:
    int maximizeWin(vector<int>& prizePositions, int k) {
        int ans = 0;

        int prizePositions_sz = prizePositions.size();

        vector<pair<int,int>> prizePositionCount;
        for(int i = 0; i < prizePositions_sz; ++i)
            if( i == 0 || prizePositions[i-1] != prizePositions[i] )
                prizePositionCount.push_back({prizePositions[i],1});
            else
                ++prizePositionCount.back().second;

        // debug
        /*
        for(auto it = prizePositionCount.begin(); it != prizePositionCount.end(); ++it)
            cout << "pos " << it->first << " count " << it->second << " ";
        cout << endl;
        */

        // going from right to left
        // for each index i in prizePositionCount,
        // record the max segment seen to the right incuding at i AND
        // record the value of the segment starting at i also
        int n = prizePositionCount.size();

        // prefixSum of count in prizePositionCount
        int prefixSum[n+1];
        prefixSum[0] = 0;
        for(int i = 1; i <= n; ++i)
            prefixSum[i] = prefixSum[i-1] + prizePositionCount[i-1].second;

        int mx[n]; // max segment seen starting at i

        for(int i = n-1; i >= 0; --i) {
            // find the index j in prizeCount, where
            // where prizePositionCount[j].first < prizePositionCount[i].first + k
            // but the largest value

            // binary search greatest element less than or equal target
            int j = geltoet(prizePositionCount,prizePositionCount[i].first + k);
            int curr_seg = prefixSum[j+1] - prefixSum[i];
            if( i == n-1 ) {
                mx[i] = curr_seg;
                ans = curr_seg;
            } else {
                if( j+1 < n )
                    ans = max(ans, curr_seg + mx[j+1]);
                else
                    ans = max(ans, curr_seg);

                mx[i] = max(mx[i+1],curr_seg);
            }
        }

        return ans;
    }
};
