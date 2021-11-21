

// 150. Evaluate Reverse Polish Notation
// https://leetcode.com/problems/evaluate-reverse-polish-notation/
// day 25 May 2021 challenge
// https://leetcode.com/explore/challenge/card/may-leetcoding-challenge-2021/601/week-4-may-22nd-may-28th/3755/





class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        int n = tokens.size();
        if( n == 1 ) return stoi(tokens[0]);

        stack<int> stck;

        int ans = 0;
        int operandA,operandB,res;
        for(int i = 0; i < n; ++i) {
            if( isdigit(tokens[i][0]) ||
                ( tokens[i][0] == '-' && tokens[i].size() > 1 ) ) {
                stck.push(stoi(tokens[i]));
                continue;
            }
            // operation
            operandB = stck.top();
            stck.pop();
            operandA = stck.top();
            stck.pop();
            if( tokens[i][0] == '+' )
                res = operandA + operandB;
            else if( tokens[i][0] == '-' )
                res = operandA - operandB;
            else if( tokens[i][0] == '*' )
                res = operandA * operandB;
            else
                res = operandA / operandB;
            stck.push(res);
        }
        return res;
    }
};
