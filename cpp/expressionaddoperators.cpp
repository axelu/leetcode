
// 282. Expression Add Operators
// https://leetcode.com/problems/expression-add-operators/





class Solution {
private:
    void rec(string& num, int pos, int& n, long& target,
             string& s, string pop, long poperand, long res, vector<string>& ans) {

        // pop      prior operation
        // poperand prior operand

        // cout << "rec pos " << pos << " s " << s << endl;

        if( pos == n ) {
            // we are at the end
            // cout << s << endl;
            if( res == target )
                ans.push_back(s);
            return;
        }

        // current operation to be performed
        string op = "";
        if( !s.empty() ) op += s.back();
        else op = "+";

        // at each pos we have the choice to inject +,-,*
        int i = pos;
        string t = "";
        long x,r,curResult;
        string pop_new;
        long poperand_new;
        for(; i < n; ++i) {
            // valid number -> cannot have leading 0
            if( i - pos == 1 ) {
                if( num[pos] == '0' ) break;
            }

            t += num[i];
            x  = stol(t);
            if( op == "+" ) {           // current operation addition
                curResult = res + x;
                pop_new      = "+";
                poperand_new = x;
            } else if( op == "-" ) {    // current operation addition
                curResult = res - x;
                pop_new      = "-";
                poperand_new = x;
            } else {                    // current operation multiplication
                if( !pop.empty() && pop != "*" ) {
                    if( pop == "+" ) {
                        r = res - poperand;
                        curResult = r + poperand * x;
                        pop_new      = "+";
                        poperand_new = poperand * x;
                    } else {
                        r = res + poperand;
                        curResult = r - poperand * x;
                        pop_new      = "-";
                        poperand_new = poperand * x;
                    }
                } else {
                    curResult = res * x;
                    pop_new      = "*";
                    poperand_new = x;
                }
            }

            s += num[i];

            // addition (next operation)
            if( i < n-1 ) s += '+';
            rec(num,i+1,n,target,s,pop_new,poperand_new,curResult,ans);
            if( i < n-1 ) s.pop_back(); // back tracking the operation

            if( i < n-1 ) {
                // subtraction (next operation)
                s += '-';
                rec(num,i+1,n,target,s,pop_new,poperand_new,curResult,ans);
                s.pop_back(); // back tracking the operation

                // multiplication (next operation)
                s += '*';
                rec(num,i+1,n,target,s,pop_new,poperand_new,curResult,ans);
                s.pop_back(); // back tracking the operation
            }

        }

        // back tracking
        s = s.substr(0,s.size()-(i-pos));
    }

public:
    vector<string> addOperators(string& num, int target) {
        int n = num.size();
        if( n == 1 ) return {};

        string s = "";
        vector<string> ans;
        long t = target;
        rec(num,0,n,t,s,"",-1,0,ans);
        return ans;
    }
};
