
// 3478. Choose K Elements With Maximum Sum
// https://leetcode.com/problems/choose-k-elements-with-maximum-sum/




class Solution {
public:
    vector<long long> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size(); // nums1.size() == nums2.size()

        vector<long long> ans(n);

        // sort nums1 in non-decreasing order
        vector<pair<int,int>> _nums1(n); // val, idx
        for(int i = 0; i < n; ++i)
            _nums1[i] = {nums1[i], i};
        sort(_nums1.begin(), _nums1.end(), [](const pair<int,int>& a, const pair<int,int>& b){
            return a.first < b.first;
        });

        // we are going to maintain a sum and a multiset of k largest values
        long long sum = 0LL;
        multiset<int> mst; // we could also use a priority queue
        queue<pair<int,int>> q;
        for(int i = 0; i < n; ++i) {
            int val = _nums1[i].first;
            int idx = _nums1[i].second;

            if( !q.empty() && q.front().first < val ) {
                while( !q.empty() ) {
                    int _idx = q.front().second;
                    q.pop();
                    sum += (long long)nums2[_idx];
                    mst.insert(nums2[_idx]);
                    if( mst.size() > k ) {
                        sum -= (long long)*mst.begin();
                        mst.erase(mst.begin());
                    }
                }
            }
            ans[idx] = sum;
            q.push({val, idx});
        }

        return ans;
    }
};
