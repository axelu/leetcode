
// 2119. A Number After a Double Reversal
// https://leetcode.com/problems/a-number-after-a-double-reversal/


class Solution {
private:
    vector<int> int2vector(int x) {
        vector<int> ret;
        while( x > 0) {
            ret.insert(ret.begin(),x%10);
            x /= 10;
        }
        return ret;
    }

    void trimLeadingZeros(vector<int>& nums) {
        while( !nums.empty() && nums[0] == 0 ) {
            if( nums.size() == 1 ) break;
            nums.erase(nums.begin());
        }
    }

public:
    bool isSameAfterReversals(int num) {
        vector<int> org = int2vector(num);
        vector<int> rev = org;
        reverse(rev.begin(),rev.end());
        trimLeadingZeros(rev);
        reverse(rev.begin(),rev.end());
        return org == rev;
    }
};
