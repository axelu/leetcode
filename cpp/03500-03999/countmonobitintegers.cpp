
// 3827. Count Monobit Integers
// https://leetcode.com/problems/count-monobit-integers




// initialize once
vector<int> monobitintegers; // {0, 1, 3, 7, 15, 31, 63, 127, 255, 511}
bool init = false;

class Solution {
public:
    int countMonobit(int n) {
        // 0 <= n <= 1000
        // decimal 1000 -> binary 1111101000 (10 digits)
        if( !init ) {
            for(int i = 0; i < 10; ++i) {
                int monobitint = (1<<i)-1;
                monobitintegers.push_back(monobitint);
            }
            init = true;
        }
        // brute force
        int ans = 0;
        for(int i = 0; i < monobitintegers.size(); ++i) {
            if( monobitintegers[i] > n )
                break;
            ++ans;
        }
        return ans;
    }
};
