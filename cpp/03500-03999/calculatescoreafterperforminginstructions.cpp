
// 3522. Calculate Score After Performing Instructions
// https://leetcode.com/problems/calculate-score-after-performing-instructions/



class Solution {
public:
    long long calculateScore(vector<string>& instructions, vector<int>& values) {
        int n = instructions.size(); // instructions.size() == values.size()

        vector<bool> seen(n, false);
        long long score = 0LL;
        int i = 0;
        while( i >= 0 && i < n && !seen[i] ) {
            seen[i] = true;
            if( instructions[i] == "add" ) {
                score += (long long)values[i];
                ++i;
            } else { // instructions[i] == "jump"
                i += values[i];
            }
        }

        return score;
    }
};
