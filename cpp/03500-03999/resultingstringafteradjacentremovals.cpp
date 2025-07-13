
// 3561. Resulting String After Adjacent Removals
// https://leetcode.com/problems/resulting-string-after-adjacent-removals/




class Solution {
public:
    string resultingString(string s) {
        int n = s.size();

        if( n == 1 )
            return s;


        auto it = s.begin();
        while( it != s.end() && next(it) != s.end() ) {
            char a = *it;
            char b = *(next(it));
            if( a + 1 == b ||
                a - 1 == b ||
                (a == 'a' && b == 'z') ||
                (a == 'z' && b == 'a') )
            {
                // cout << "adjacent " << a << " " << b << endl;
                it = s.erase(it);
                it = s.erase(it);
                if( it != s.begin() )
                    --it;
                continue;
            }
            ++it;
        }

        return s;
    }
};
