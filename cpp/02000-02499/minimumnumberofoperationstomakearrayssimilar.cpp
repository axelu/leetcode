
// 2449. Minimum Number of Operations to Make Arrays Similar
// https://leetcode.com/problems/minimum-number-of-operations-to-make-arrays-similar/





class Solution {
private:
    void printVector(vector<int>& v) {
        for(int x: v)
            cout << x << " ";
        cout << endl;
    }
public:
    long long makeSimilar(vector<int>& nums, vector<int>& target) {
        int n = nums.size(); // nums.size() == target.size()

        // from the problem description:
        // The test cases are generated such that nums can always be similar to target.
        // as we only move two at a time, we need to separate/pair even and odds.

        sort(nums.begin(),nums.end());
        sort(target.begin(),target.end());

        vector<int> target_even;
        vector<int> target_odd;
        vector<int> nums_even;
        vector<int> nums_odd;
        for(int i = 0; i < n; ++i) {
            if( target[i] % 2 ) {
                target_odd.push_back(target[i]);
            } else {
                target_even.push_back(target[i]);
            }
            if( nums[i] % 2 ) {
                nums_odd.push_back(nums[i]);
            } else {
                nums_even.push_back(nums[i]);
            }
        }

        // target_even.size() == nums_even.size() and target_odd.size() == nums_odd.size()
        // credit target > nums
        long long credit = 0;
        for(int i = 0; i < target_even.size(); ++i) {
            if( target_even[i] == nums_even[i] )
                continue;
            else if( target_even[i] > nums_even[i] ) {
                credit = credit + (target_even[i] - nums_even[i])/2LL;
            }
        }
        for(int i = 0; i < target_odd.size(); ++i) {
            if( target_odd[i] == nums_odd[i] )
                continue;
            else if( target_odd[i] > nums_odd[i] ) {
                credit = credit + (target_odd[i] - nums_odd[i])/2LL;
            }
        }

        return credit;
    }
};
