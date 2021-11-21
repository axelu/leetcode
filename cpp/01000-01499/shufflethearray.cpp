
// 1470. Shuffle the Array
// https://leetcode.com/problems/shuffle-the-array/

class Solution {
public:
    vector<int> shuffle(vector<int>& nums, int n) {
        // 1 <= n <= 500
        // nums.length == 2n

        int n2 = 2 * n;
        nums.reserve(n2 + 1);

        int k = 1;
        for(int i = n; i <= n2 - 2; ++i) {
            auto it = nums.begin();
            nums.insert(it+k, *(it+i));
            it = nums.begin();
            nums.erase(it+i+1);
            k += 2;
        }

        return nums;
    }
};
