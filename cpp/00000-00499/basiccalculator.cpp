
// 224. Basic Calculator
// https://leetcode.com/problems/basic-calculator/

class Solution {
private:
    int calculate(string& s, int n, int& i) {
        // cout << "calculate i " << i << " " << s[i] << endl;

        deque<int> o; // operands and operations

        char c;
        string t = "";
        for(; i < n; ++i) {
            c = s[i];

            if( isdigit(c) ) {
                t += c;
                continue;
            }

            if( !t.empty() ) {
                o.push_back(stoi(t));
                t.clear();
            }

            if( c == '(' ) {
                ++i;
                o.push_back(calculate(s,n,i));
            } else if( c == ')' ) {
                break;
            } else if( c == '+' ) {
                o.push_back(0);
            } else if( c == '-' ) {
                o.push_back(1);
            }
        }
        if( !t.empty() ) {
            o.push_back(stoi(t));
            t.clear();
        }

        // accounting for '-' as unary operator
        if( o.size()%2 == 0 )
            o.push_front(0);

        int a,op,b,r;
        // cout << "  o.size() " << o.size() << endl;
        while( o.size() > 1 ) {
            a  = o.front();o.pop_front();
            op = o.front();o.pop_front();
            b  = o.front();o.pop_front();
            r = op == 0 ? a+b : a-b;
            o.push_front(r);
        }

        // cout << "  returning res " << o.front() << " i " << i << endl;
        return o.front();
    }

public:
    int calculate(string s) {
        int n = s.size();
        int pos = 0;
        return calculate(s,n,pos);
    }
};
