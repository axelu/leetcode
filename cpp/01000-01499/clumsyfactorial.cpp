
// 1006. Clumsy Factorial
// https://leetcode.com/problems/clumsy-factorial/



class Solution {
public:
    int clumsy(int n) {

        //            *  /  +  -
        int opi[4] = {-1,-2,-3,-4};
        //char op[4] = {'*','/','+','-'};

        deque<int> stck;
        int o = 0;
        for(; n >= 1; --n) {
            //cout << n;
            //if( n > 1 )
            //    cout << " " << op[o] << " ";

            if( !stck.empty() && stck.back() == -1 ) {
                stck.pop_back();
                int a = stck.back();
                stck.pop_back();
                a *= n;
                stck.push_back(a);
            } else if( !stck.empty() && stck.back() == -2 ) {
                stck.pop_back();
                int a = stck.back();
                stck.pop_back();
                a /= n;
                stck.push_back(a);
            } else {
                stck.push_back(n);
            }

            if( n > 1 )
                stck.push_back(opi[o]);

            ++o;
            o %= 4;
        }

        // process stack
        while( stck.size() > 1 ) {
            int a  = stck.front(); stck.pop_front();
            int op = stck.front(); stck.pop_front();
            int b  = stck.front(); stck.pop_front();
            if( op == -3 )
                stck.push_front(a+b);
            else
                stck.push_front(a-b);
        }


        return stck.front();
    }
};
