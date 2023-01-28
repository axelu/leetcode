
// 373. Find K Pairs with Smallest Sums
// https://leetcode.com/problems/find-k-pairs-with-smallest-sums/



class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        // because nums1 and nums2 are sorted in asc order and
        // we only have to deliver the 1st k smallest sum pairs,
        // we don't need to go further than k in either nums1 or nums2
        int n1 = min((int)nums1.size(),k);
        int n2 = min((int)nums2.size(),k);

        priority_queue<array<int,3>> pq; // sum = nums1[i] + nums2[i], nums1[i], nums2[i]

        // brute force, but only till we have our k smallest sum pairs
        for(int i = 0; i < n1; ++i) {
            for(int j = 0; j < n2; ++j) {
                int sum = nums1[i] + nums2[j];

                // fill our answer up till we have k pairs
                // after that we only keep going if the pair's sum is smaller
                if( pq.size() < k ) {
                    pq.push({sum,nums1[i],nums2[j]});
                } else if( sum < pq.top()[0] ) {
                    // we have a better pair
                    pq.pop();
                    pq.push({sum,nums1[i],nums2[j]});
                } else {
                    break;
                }
            }
        }

        vector<vector<int>> ans;
        while( !pq.empty() ) {
            ans.push_back({pq.top()[1],pq.top()[2]});
            pq.pop();
        }

        return ans;
    }
};
