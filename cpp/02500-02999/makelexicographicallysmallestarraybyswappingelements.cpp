
// 2948. Make Lexicographically Smallest Array by Swapping Elements
// https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/




class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        if( n == 1 )
            return nums;

        // going left to right,
        // if we are at a given position i, we want to swap i with
        // the leftmost j, where nums[j] > nums[i] && nums[j] - nums[i] <= limit

        vector<pair<int,int>> arr(n);
        for(int i = 0; i < n; ++i)
            arr[i] = {nums[i],i};
        sort(arr.begin(),arr.end(),[](const pair<int,int>& a, const pair<int,int>& b){
            return a.first < b.first;
        });
        // debug
        // for(int i = 0; i < n; ++i)
        //     cout << arr[i].first << ":" << arr[i].second << " ";
        // cout << endl;

        priority_queue<int,vector<int>,greater<int>> pq;
        pq.push(arr[0].second);
        int l, i;
        for(int j = 1; j < n; ++j) {
            if( arr[j].first - arr[j-1].first > limit ) {
                // the current element starts a new 'component'
                // so we need to place all the elements of the prior component
                l = pq.size();
                i = j - l;
                for(; i < j; ++i) {
                    nums[pq.top()] = arr[i].first;
                    pq.pop();
                }
            }
            pq.push(arr[j].second);
        }
        // finish up
        l = pq.size();
        i = n - l;
        for(; i < n; ++i) {
            nums[pq.top()] = arr[i].first;
            pq.pop();
        }

        return nums;
    }
};
