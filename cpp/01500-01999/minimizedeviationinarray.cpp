
// 1675. Minimize Deviation in Array
// https://leetcode.com/problems/minimize-deviation-in-array/
// day 30 January 2021 challenge
// https://leetcode.com/explore/challenge/card/january-leetcoding-challenge-2021/583/week-5-january-29th-january-31st/3622/



class Solution {
public:
    int minimumDeviation(vector<int>& nums) {
        size_t n = nums.size();

        priority_queue<int> evens;
        int mn = INT_MAX;
        int k;
        for(int i = 0; i < n; ++i) {
            k = nums[i];
            if( k % 2 == 0 ) {
                evens.push(k);
                mn = min(mn,k);
            } else {
                evens.push(k*2);
                mn = min(mn,k*2);
            }
        }
        int ans = INT_MAX;
        while(!evens.empty()) {
            k = evens.top();
            evens.pop();
            ans = min(ans,k-mn);
            if( k % 2 == 0 ) {
                evens.push(k/2);
                mn = min(mn,k/2);
            } else {
                // if the max is odd, break as we cannot make it smaller
                break;
            }
        }
        return ans;
    }
};
