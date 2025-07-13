
// 3571. Find the Shortest Superstring II
// https://leetcode.com/problems/find-the-shortest-superstring-ii/






class Solution {
private:
    string solve(string s1, string s2) {
        int n1 = s1.size(); // n1 >= n2
        int n2 = s2.size();

        if( n2 == 1 )
            return s1 + s2;

        // pass 1
        string ret1 = "";
        int k = 1;          // index in s2
        while( k < n2 ) {
            int i = 0;      // index in s1
            int j = k;      // index in s2
            for(; j < n2; ++i,++j) {
                if( s1[i] != s2[j] )
                    break;
            }
            if( j == n2 ) {
                ret1 = s2.substr(0,k) + s1;
                break;
            }
            ++k;
        }

        // pass 2
        string ret2 = "";
        k = n1 - (n2 - 1);  // index in s1
        while( k < n1 ) {
            int i = k;
            int j = 0;
            for(; i < n1; ++i,++j) {
                if( s1[i] != s2[j] )
                    break;
            }
            if( i == n1 ) {
                ret2 = s1.substr(0,k) + s2;
                break;
            }
            ++k;
        }

        if( ret1 == "" && ret2 == "" )
            return s1 + s2;
        else if( ret1 == "" )
            return ret2;
        else if( ret2 == "" )
            return ret1;
        else
            return ret1.size() < ret2.size() ? ret1 : ret2;

    }
public:
    string shortestSuperstring(string s1, string s2) {
        int n1 = s1.size();
        int n2 = s2.size();

        // equal
        if( n1 == n2 && s1 == s2 )
            return s1;
        // s1 substring of s2
        if( n1 < n2 && s2.find(s1) != string::npos )
            return s2;
        // s2 substring of s1
        if( n2 < n1 && s1.find(s2) != string::npos )
            return s1;

        if( n1 < n2 )
            swap(s1,s2);

        return solve(s1, s2);
    }
};
