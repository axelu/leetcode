
// 640. Solve the Equation
// https://leetcode.com/problems/solve-the-equation/




/* goal to get x on one side
 * NOTE: test case "3x+2x=21" fails validation, so I assume it always ends in integer if there is a solution
 *       test case "3x+2x=20" -> x=4
 *       test case "x+x=3" fails validation, confirms that if there is a solution, its an integer
 * no solution if like x-x=3
 * infinte solutions if like x-x=0 -> x = x, also 0x=0
 * also checked "x2=6" fails validation, so coefficient always in fron of x
 *
 * we can boil each side down to two numbers: coefficient and +/- some addends/subtrahend
 */
class Solution {
private:
    pair<int,int> solve(string& equation, int s, int e) {
        int coe = 0;
        int add = 0;
        char op = '+'; // either  + or -
        string t = "";

        for(int i = s; i <= e; ++i) {
            char c = equation[i];

            if( c == 'x' ) {
                // do we have a coefficient?
                if( t.empty() ) {
                    coe = op == '+' ? coe + 1 : coe - 1;
                } else {
                    coe = op == '+' ? coe + stoi(t) : coe - stoi(t);
                }
                t = "";

            } else if( c == '+' || c == '-' ) {
                if( !t.empty() )
                    add = op == '+' ? add + stoi(t) : add - stoi(t);

                op = c;
                t = "";

            } else { // digit
                t = t + c;

            }
        }
        // finish up
        if( !t.empty() )
            add = op == '+' ? add + stoi(t) : add - stoi(t);

        return {coe,add};
    }

public:
    string solveEquation(string equation) {
        int n = equation.size();

        // get pos of equal sign
        // it is guaruanteed, there is one and only one '='
        int equal_idx = equation.find('=');

        auto pl = solve(equation,0,equal_idx-1);   // left side
        // cout << "left coefficient  " << pl.first << " left add  " << pl.second << endl;
        auto pr = solve(equation,equal_idx+1,n-1); // right side
        // cout << "right coefficient " << pr.first << " right add " << pr.second << endl;

        if( pl.first == pr.first && pl.second == pr.second ) {
            return "Infinite solutions";

        } else if( pl.first != pr.first && pl.second == pr.second ) {
            return "x=0";

        } else if( pl.first == pr.first && pl.second != pr.second ) {
            return "No solution";

        }

        // we have a solution other than x=0
        // it is guruanteed that it resolves to an integer
        int result = (pr.second - pl.second)/(pl.first - pr.first);

        return "x=" + to_string(result);
    }
};
