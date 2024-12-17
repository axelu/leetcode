
// 3287. Find the Maximum Sequence Value of Array
// https://leetcode.com/problems/find-the-maximum-sequence-value-of-array/




class Solution {
private:
    bool seen[400][201][128];

    void rec_forward(vector<int>& nums, int k, int pos, int rem, int state, int mn[]) {
        int n = nums.size();

        // rem is how many more elements we have to still pick
        if( rem == 0 ) {
            mn[state] = min(mn[state], pos-1);
            return;
        }

        if( seen[pos][rem][state] )
            return;

        seen[pos][rem][state] = true;

        // we have a choice
        //     don't pick nums[pos] OR
        //     pick nums[pos]

        // we know we are working on our left side
        // meaning the right side has to at least pick k elements
        int t = (n - (k + rem)); // the pos at which we must pick, we can no longer skip

        if( pos < t )
            rec_forward(nums, k, pos+1, rem, state, mn);

        rec_forward(nums, k, pos+1, rem-1, state | nums[pos], mn);

        return;
    }

    void rec_backward(vector<int>& nums, int k, int pos, int rem, int state, int mx[]) {
        int n = nums.size();

        // rem is how many more elements we have to still pick
        if( rem == 0 ) {
            mx[state] = max(mx[state], pos+1);
            return;
        }

        if( seen[pos][rem][state] )
            return;

        seen[pos][rem][state] = true;

        // we have a choice
        //     don't pick nums[pos] OR
        //     pick nums[pos]

        // we know we are working on our right side
        // meaning the left side has to at least pick k elements
        int t = (k - 1) + rem; // the pos at which we must pick, we can no longer skip

        if( pos > t )
            rec_backward(nums, k, pos-1, rem, state, mx);

        rec_backward(nums, k, pos-1, rem-1, state | nums[pos], mx);

        return;
    }


public:
    int maxValue(vector<int>& nums, int k) {
        int n = nums.size(); // 2 <= nums.size() <= 400
        // 1 <= nums[i] < 128

        // we are dividing nums into two parts left and right
        //        left                 right
        // ------------------   ------------------
        //     0 ... left_r     left_r + 1 ... n-1
        // int left_rmin = k;
        // int left_rmax = (n-1) - k;
        // in the left side and right side we pick k elements and calculate their OR
        // then we are doing XOR on those two resulting values, and we are looking to maximize the result

        // given that 1 <= nums[i] < 128, with OR we can get values between 1 and 127
        // from left to right, after we have selected k elements, we track the min index where we get a certain OR val
        // from right to left, after we have selected k elements, we track the max index where we get a cetrain OR val
        // we can then hold each OR val left against OR val right if left min index < right max index and track max XOR

        int mn[128];
        for(int i = 0; i < 128; ++i)
            mn[i] = 400;
        memset(seen,false,sizeof seen);
        rec_forward(nums, k, 0, k, 0, mn);
        /*
        cout << "forward" << endl;
        for(int i = 0; i < 128; ++i)
            cout << i << ":" << mn[i] << " ";
        cout << endl;
        */

        int mx[128];
        for(int i = 0; i < 128; ++i)
            mx[i] = -1;
        memset(seen,false,sizeof seen);
        rec_backward(nums, k, n-1, k, 0, mx);
        /*
        cout << "backward" << endl;
        for(int i = 0; i < 128; ++i)
            cout << i << ":" << mx[i] << " ";
        cout << endl;
        */

        int ans = 0;
        for(int l = 1; l < 128; ++l)
            for(int r = 1; r < 128; ++r)
                if( mn[l] < mx[r] )
                    ans = max(ans, l ^ r);

        return ans;
    }
};
