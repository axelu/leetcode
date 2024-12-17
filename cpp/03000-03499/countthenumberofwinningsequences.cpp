
// 3320. Count The Number of Winning Sequences
// https://leetcode.com/problems/count-the-number-of-winning-sequences/





class Solution {
private:
    const long mod = 1000000007;

    long rec(string& a, int n, int i, string& b) {
        if( i == n ) {
            int alice = 0;
            int bob = 0;
            for(int j = 0; j < n; ++j) {
                if( a[j] ==  b[j] )
                    continue;

                if( a[j] == 'F' && b[j] == 'E' )
                    ++alice;
                if( b[j] == 'F' && a[j] == 'E' )
                    ++bob;

                if( a[j] == 'W' && b[j] == 'F' )
                    ++alice;
                if( b[j] == 'W' && a[j] == 'F' )
                    ++bob;

                if( a[j] == 'E' && b[j] == 'W' )
                    ++alice;
                if( b[j] == 'E' && a[j] == 'W' )
                    ++bob;
            }
            cout << a << endl;
            cout << b << " " << (bob > alice) << endl;
            return bob > alice;
        }

        // Bob has a choice
        //    choose the Fire Dragon (if not chosen the last time) OR
        //    choose the Water Serpent (if not chosen the last time) OR
        //    choose the Earth Golem (if not chosen the last time)

        char bob_last = b.size() > 0 ? b.back() : '#';

        long ret = 0;

        if( bob_last != 'F' ) {
            b.append(1,'F');
            ret = ret + rec(a,n,i+1,b);
            // backtrack
            b.pop_back();
        }
        if( bob_last != 'W' ) {
            b.append(1,'W');
            ret = ret + rec(a,n,i+1,b);
            // backtrack
            b.pop_back();
        }
        if( bob_last != 'E' ) {
            b.append(1,'E');
            ret = ret + rec(a,n,i+1,b);
            // backtrack
            b.pop_back();
        }

        return ret;
    }

    int offset = 500;
    long mem[1000][1501][3];

    long rec(const string& a, const int i, const int j, const int k) {
        /*
        cout << "rec i " << i << " j " << j << " k " << k << " ";
        if( k == 0 )
            cout << "F";
        else if( k == 1 )
            cout << "W";
        else
            cout << "E";
        cout << endl;
        */

        // i = pos in s
        // j = diff bob's points and alice's point
        // k = index in {’F’, ‘W’, ‘E’}

        // we cannot get more points than positions we traveled
        if( j > i+1 || (j * -1) > i+1 )
             return 0;

        if( mem[i][j+offset][k] != -1 )
            return mem[i][j+offset][k];

       // we would have achieved j points at current position i
        // Bob's gain at current position
        int bob_gain = 0;
        if( a[i] == 'F' ) {
            if( k == 1 )        // W
                bob_gain = -1;
            else if( k == 2 )   // E
                bob_gain = 1;
        } else if( a[i] == 'W' ) {
            if( k == 0 )        // F
                bob_gain = 1;
            else if( k == 2 )   // E
                bob_gain = -1;
        } else { // a[i] == 'E'
            if( k == 0 )        // F
                bob_gain = -1;
            else if( k == 1 )   // W
                bob_gain = 1;
        }

        if( i == 0 )
            return j == bob_gain * -1;


        // if Bob gains a point at the current position,
        // he would have had to have -1 point at the prior position
        // and so on

        long ret = 0L;

        if( k == 0 ) {
            ret = (ret + rec(a, i-1, j + bob_gain, 1)) % mod;
            ret = (ret + rec(a, i-1, j + bob_gain, 2)) % mod;
        } else if( k == 1 ) {
            ret = (ret + rec(a, i-1, j + bob_gain, 0)) % mod;
            ret = (ret + rec(a, i-1, j + bob_gain, 2)) % mod;
        } else { // k == 2
            ret = (ret + rec(a, i-1, j + bob_gain, 0)) % mod;
            ret = (ret + rec(a, i-1, j + bob_gain, 1)) % mod;
        }

        return mem[i][j+offset][k] = ret;
    }

public:
    int countWinningSequences(string s) {
        int n = s.size();

        /*
         *     A                B
         * Fire Dragon      Earth Golem     A + 1
         * Water Serpent    Fire Dragon     A + 1
         * Earth Golem      Water Serpent   A + 1
         * or vice versa
         *
         */

        // brute force
        // string b = "";
        // return rec(s, n, 0, b);

        memset(mem,-1,sizeof mem);

        long ans = 0L;
        for(int j = 1; j <= n; ++j) {
            for(int k = 0; k < 3; ++k) {

                ans = (ans + rec(s, n-1, j, k)) % mod;
            }
        }


        return ans;
    }
};
