
// 239. Sliding Window Maximum
// https://leetcode.com/problems/sliding-window-maximum/
// day 28 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/567/week-4-november-22nd-november-28th/3546/



class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        // constraints: 1 <= nums.length <= 10^5
        //              1 <= k <= nums.length
        if( k == 1 ) return nums;
        size_t n = nums.size();
        if( k == n ) return {*max_element(nums.begin(),nums.end())};

        vector<int> r(n-k+1);

        int windowsize = 0, windowstartidx = 0, j = 0;
        multiset<int> ms;
        multiset<int>::node_type nh;
        for(int i = 0; i < n; ++i) {
            ++windowsize;

            if( windowsize <= k )
                ms.insert(nums[i]);

            if( windowsize > k ) {
                nh = ms.extract(nums[windowstartidx]);
                nh.value() = nums[i];
                ms.insert(move(nh));
                ++windowstartidx;
                --windowsize;
            }

            if( windowsize == k ) {
                r[j] = *(ms.rbegin());
                ++j;
            }
        }

        return r;
    }
};
