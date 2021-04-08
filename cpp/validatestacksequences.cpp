
// 946. Validate Stack Sequences
// https://leetcode.com/problems/validate-stack-sequences/
// day 26 February 2021 challenge
// https://leetcode.com/explore/featured/card/february-leetcoding-challenge-2021/587/week-4-february-22nd-february-28th/3653/


class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        // 0 <= pushed.length == popped.length <= 1000
        // pushed and popped have distinct values
        int n = pushed.size();

        // simulate
        stack<int> stck;
        int poppedIdx = 0;
        for(int i = 0; i < n; ++i) { // pushedIdx
            while( !stck.empty() && stck.top() == popped[poppedIdx] ) {
                stck.pop();
                ++poppedIdx;
            }
            stck.push(pushed[i]);
        }
        // empty the stack
        while( !stck.empty() && stck.top() == popped[poppedIdx] ) {
            stck.pop();
            ++poppedIdx;
        }

        return stck.empty();
    }
};
