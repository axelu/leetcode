
// 241. Different Ways to Add Parentheses
// https://leetcode.com/problems/different-ways-to-add-parentheses/




class Solution {
private:
    vector<int> mem[20][20];

    vector<int> diffWaysToCompute(string& expression, int s, int e) {

        if( !mem[s][e].empty() )
            return mem[s][e];

        vector<int> ret,pfx,sfx;
        char c;
        for(int i = s; i <= e; ++i) {
            c = expression[i];

            if( !isdigit(c) ) { // split at operator
                pfx = diffWaysToCompute(expression,s,i-1); // before operator
                sfx = diffWaysToCompute(expression,i+1,e); // after operator

                for(int j = 0; j < pfx.size(); ++j)
                    for(int k = 0; k < sfx.size(); ++k)
                        if( c == '+')
                            ret.push_back(pfx[j] + sfx[k]);
                        else if( c == '-' )
                            ret.push_back(pfx[j] - sfx[k]);
                        else if( c == '*' )
                            ret.push_back(pfx[j] * sfx[k]);
            }
        }
        // we could have a number only, meaning no operator
        if( ret.size() == 0 )
            ret.push_back(stoi(expression.substr(s,e-s+1)));

        return mem[s][e] = ret;
    }


public:
    vector<int> diffWaysToCompute(string expression) {
        // 1 <= expression.size() <= 20
        // expression has to be of the following form:
        // number operator number operator number ...
        // integer overflow, like expression = "99999999999999999999" !!!


        return diffWaysToCompute(expression,0,expression.size()-1);
    }
};
