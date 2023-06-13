
// 2698. Find the Punishment Number of an Integer
// https://leetcode.com/problems/find-the-punishment-number-of-an-integer/




class Solution {
private:

    bool rec(int x, string& s, int i) {
        if( x < 0 )
            return false;

        if( i == s.size() )
            return x == 0;


        int k = 0;
        while( i < s.size() ) {

            k = k * 10 + (s[i]-'0');
            if( rec(x-k,s,i+1) )
                return true;
            ++i;
        }

        return false;
    }

public:
    int punishmentNumber(int n) {

        int ans = 0;

        // brute force
        for(int i = 1; i <= n; ++i) {

            int i2 = i*i;
            string s = to_string(i2);
            if( rec(i,s,0) ) {
                // cout << "i " << i << " i2 " << i2 << endl;
                ans += i2;
            }
        }

        return ans;
    }
};
