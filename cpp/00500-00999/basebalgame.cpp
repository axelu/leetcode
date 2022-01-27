
// 682. Baseball Game
// https://leetcode.com/problems/baseball-game/



class Solution {
public:
    int calPoints(vector<string>& ops) {
        stack<int> stck;

        int t1,t2;
        for(int i = 0; i < ops.size(); ++i) {
            if( ops[i].size() == 1 ) {
                if( ops[i][0] == '+' ) {
                    t1 = stck.top();
                    stck.pop();
                    t2 = t1 + stck.top();
                    stck.push(t1);
                    stck.push(t2);
                } else if( ops[i][0] == 'D' ) {
                    stck.push(2*stck.top());
                } else if( ops[i][0] == 'C' ) {
                    stck.pop();
                } else {
                    // single digit
                    stck.push(ops[i][0]-'0');
                }
            } else {
                stck.push(stoi(ops[i]));
            }
        }

        int ans = 0;
        while(!stck.empty()) {
            ans += stck.top();
            stck.pop();
        }
        return ans;
    }
};
