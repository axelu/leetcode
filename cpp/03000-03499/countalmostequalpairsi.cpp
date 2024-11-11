
// 3265. Count Almost Equal Pairs I
// https://leetcode.com/problems/count-almost-equal-pairs-i/





/* [50701,751] as almost equal
    50701 -> 00751
 */
class Solution {
private:
    vector<int> int2vector(int num) {
        vector<int> ret;
        while( num > 0 ) {
            ret.push_back(num % 10);
            num /= 10;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }

    bool is_almost_equal(int a, int b) {
        if( a == b )
            return true;

        vector<int> va = int2vector(a);
        vector<int> vb = int2vector(b);

        while( va.size() < vb.size() )
            va.insert(va.begin(), 0);
        while( vb.size() < va.size() )
            vb.insert(vb.begin(), 0);

        vector<int> vd;
        for(int i = 0; i < va.size(); ++i) { // va.size() == vb.size()
            if( va[i] != vb[i] )
                vd.push_back(i);
        }
        if( vd.size() == 1 || vd.size() > 2 )
            return false;

        return va[vd[0]] == vb[vd[1]] && va[vd[1]] == vb[vd[0]];
    }

public:
    int countPairs(vector<int>& nums) {
        int n = nums.size(); // 2 <= nums.length <= 100

        int ans = 0;

        // small constraint -> brute force
        for(int i = 0; i < n-1; ++i) {
            for(int j = i+1; j < n; ++j) {
                if( is_almost_equal(nums[i], nums[j]) )
                    ++ans;
            }
        }

        return ans;
    }
};
