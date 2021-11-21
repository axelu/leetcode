
// 384. Shuffle an Array
// https://leetcode.com/problems/shuffle-an-array/
// day 20 July 2021 challenge
// https://leetcode.com/explore/featured/card/july-leetcoding-challenge-2021/610/week-3-july-15th-july-21st/3820/




class Solution {
private:
    vector<int>* arr;
    int n;
public:
    Solution(vector<int>& nums) {
        arr = &nums;
        n = nums.size();

        srand(time(nullptr));
    }

    /** Resets the array to its original configuration and return it. */
    vector<int> reset() {
       return *arr;
    }

    /** Returns a random shuffling of the array. */
    vector<int> shuffle() {
        // we assign randomly a new position

        int s[n];memset(s,0,sizeof s); // keep track of assigned positions

        vector<int> ans(n);
        for(int i = 0; i < n; ++i) {
            //generate random between zero and n-1
            int i_new = rand() % n;
            while( s[i_new] )
                i_new = rand() % n;

            s[i_new] = 1;
            ans[i_new] = (*arr)[i];
        }

        return ans;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */
