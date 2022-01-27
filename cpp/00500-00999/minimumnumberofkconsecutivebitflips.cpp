
// 995. Minimum Number of K Consecutive Bit Flips
// https://leetcode.com/problems/minimum-number-of-k-consecutive-bit-flips/



class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        int n = nums.size();
        // base cases
        if( k == 1 ) {
            int t = accumulate(nums.begin(),nums.end(),0);
            return n-t;
        }
        if( k == n ) {
            int t = accumulate(nums.begin(),nums.end(),0);
            if( t == n )
                return 0;
            else if( t == 0 )
                return 1;
            else
                return -1;
        }

        int ans = 0;


        // every 0 has to be flipped
        // if nums[i] has been flipped an even number of times,
        //    then it has its original value
        // if nums[i] has been flipped an odd number of times,
        //    then it has the oposite of its original value
        // when we flip a nums[i], we will record
        // the index of the last item flipped, which is i+k-1 (0-indexed)
        // we will move from left to right

        queue<int> q; // when we flip, record last item fliped
                      // queue size will tell us how many times the current
                      // index has been flipped
        for(int i = 0; i < n; ++i) {
            if( i > n-k ) { // we cannot flip anymore
                if( (nums[i] == 1 && q.size() % 2 != 0) ||
                    (nums[i] == 0 && q.size() % 2 == 0) )
                    return -1;
            }

            if( (nums[i] == 1 && q.size() % 2 != 0) ||
                (nums[i] == 0 && q.size() % 2 == 0) ) {
                ++ans;
                q.push(i+k-1);
            }

            if( !q.empty() && q.front() == i )
                q.pop();
        }

        return ans;
    }
};
