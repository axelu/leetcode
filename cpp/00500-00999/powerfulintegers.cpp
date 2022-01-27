
// 970. Powerful Integers
// https://leetcode.com/problems/powerful-integers/



class Solution {
public:
    vector<int> powerfulIntegers(int x, int y, int bound) {

        int seen[bound+1]; memset(seen,0,sizeof seen);
        vector<int> ans;
        int a,b,t;
        for(int i = 0; i < INT_MAX; ++i) {
            a = pow(x,i);
            if( a >= bound ) break;
            for(int j = 0; j < INT_MAX; ++j) {
                b = pow(y,j);
                if( b >= bound) break;
                t = a+b;
                if( t > bound ) break;
                if( !seen[a+b] ) {
                    ans.push_back(t);
                    seen[a+b] = 1;
                }
                if( 1 == y ) break; // 1e<anything> = 1, so one round suffices
            }
            if( 1 == x ) break; // 1e<anything> = 1, so one round suffices
        }

        return ans;
    }
};
