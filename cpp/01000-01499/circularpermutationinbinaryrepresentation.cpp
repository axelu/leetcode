
// 1238. Circular Permutation in Binary Representation
// https://leetcode.com/problems/circular-permutation-in-binary-representation/




class Solution {
private:
    // https://en.wikipedia.org/wiki/Gray_code#Converting_to_and_from_Gray_code
    uint BinaryToGray(uint num) {
        return num ^ (num >> 1);
    }

public:
    vector<int> circularPermutation(int n, int start) {
        int l = pow(2,n);

        int pivot,val;
        vector<int> ans(l);

        // Hint 1: Use gray code to generate a n-bit sequence.
        for(int i = 0; i < l; ++i) {
            val = BinaryToGray(i);
            ans[i] = val;
            if( val == start ) pivot = i;
        }

        // Hint 2: Rotate the sequence such that its first element is start.
        rotate(ans.begin(),ans.begin()+pivot,ans.end());

        return ans;
    }
};
