
// 728. Self Dividing Numbers
// https://leetcode.com/problems/self-dividing-numbers/



class Solution {
public:
    vector<int> selfDividingNumbers(int left, int right) {
        vector<int> ans;
        int x, rem;
        bool selfdivisible;
        for(int i = left; i <= right; ++i) {

            x = i;
            selfdivisible = true;
            while( x > 0 ) {
                rem = x % 10;
                if( rem == 0 || i % rem != 0 ) {
                    selfdivisible = false;
                    break;
                }
                x /= 10;
            }
            if( selfdivisible ) ans.push_back(i);

        }

        return ans;
    }
};
