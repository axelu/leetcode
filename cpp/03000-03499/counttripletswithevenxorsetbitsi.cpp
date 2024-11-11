
// 3199. Count Triplets with Even XOR Set Bits I
// https://leetcode.com/problems/count-triplets-with-even-xor-set-bits-i/



class Solution {
private:
    int countSetBits(int x) {
        int ret = 0;
        while(x) {
            if( x & 1 )
                ++ret;
            x = x >> 1;
        }
        return ret;
    }
public:
    int tripletCount(vector<int>& a, vector<int>& b, vector<int>& c) {
        int ans = 0;

        // brute force
        for(int x: a)
            for(int y: b)
                for(int z: c) {
                    int t = x ^ y ^ z;
                    ans += countSetBits(t) % 2 == 0 ? 1 : 0;
                }

        return ans;
    }
};
