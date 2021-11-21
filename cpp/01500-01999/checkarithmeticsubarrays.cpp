
// 1630. Arithmetic Subarrays
// https://leetcode.com/problems/arithmetic-subarrays/




class Solution {
public:
    vector<bool> checkArithmeticSubarrays(vector<int>& nums, vector<int>& l, vector<int>& r) {
        auto n = nums.size();
        auto m = l.size(); // m == l.length == r.length

        vector<bool> ret(m,false);
        int s[n],k,d,o;
        bool isArithmetic;
        for(int i = 0; i < m; ++i) {
            isArithmetic = true;

            k = r[i]-l[i]+1;
            if( k > 2 ) {
                o = 0;
                for(int j = l[i]; j <= r[i]; ++j) {
                    s[o] = nums[j];
                    ++o;
                }
                sort(s,s+k);

                d = s[1] - s[0];
                for(int j = 1; j < k-1; ++j) {
                    if( s[j+1] - s[j] != d ) {
                        isArithmetic = false;
                        break;
                    }
                }
            }

            ret[i] = isArithmetic;
        }

        return ret;
    }
};
