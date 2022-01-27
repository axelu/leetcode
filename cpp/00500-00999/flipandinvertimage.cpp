
// 832. Flipping an Image
// day 10 November 2020 challenge
// https://leetcode.com/explore/challenge/card/november-leetcoding-challenge/565/week-2-november-8th-november-14th/3526/
// https://leetcode.com/problems/flipping-an-image/



class Solution {
public:
    vector<vector<int>> flipAndInvertImage(vector<vector<int>>& A) {
        auto n = A.size();
        for(int i = 0; i < n; ++i) {
            reverse(begin(A[i]),end(A[i]));
            for(auto it = begin(A[i]); it != end(A[i]); ++it)
                *it = *it == 0 ? 1 : 0;
        }
        return A;
    }
};
