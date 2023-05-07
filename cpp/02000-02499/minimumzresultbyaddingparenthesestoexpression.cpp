
// 2232. Minimize Result by Adding Parentheses to Expression
// https://leetcode.com/problems/minimize-result-by-adding-parentheses-to-expression/



class Solution {
public:
    string minimizeResult(string expression) {
        int n = expression.size();

        // brute force

        int plus = -1;
        for(int i = 0; i < n; ++i)
            if( expression[i] == '+' ) {
                plus = i;
                break;
            }

        string p1 = expression.substr(0,plus);
        // cout << "p1 " << p1 << endl;
        int p1_sz = p1.size();
        string p2 = expression.substr(plus + 1);
        // cout << "p2 " << p2 << endl;
        int p2_sz = p2.size();

        int mn = INT_MAX;
        string ans;

        int f1,a1,f2,a2;
        string s1,s2;
        for(int i = 0; i < p1_sz; ++i) {
            if( i == 0 ) {
                f1 = 1;
                a1 = stoi(p1);
                s1 = '(' + p1;
            } else {
                f1 = stoi(p1.substr(0,i));
                a1 = stoi(p1.substr(i));
                s1 = p1.substr(0,i) + '(' + p1.substr(i);
            }

            for(int j = 1; j <= p2_sz; ++j) {
                if( j < p2_sz ) {
                    a2 = stoi(p2.substr(0,j));
                    f2 = stoi(p2.substr(j));
                    s2 = p2.substr(0,j) + ')' + p2.substr(j);
                } else {
                    a2 = stoi(p2);
                    f2 = 1;
                    s2 = p2 + ')';
                }

                int t = f1 * (a1 + a2) * f2;
                if( t < mn ) {
                    mn = t;
                    ans = s1 + '+' + s2;
                }
            }
        }

        return ans;
    }
};
