
// 2151. Maximum Good People Based on Statements
// https://leetcode.com/problems/maximum-good-people-based-on-statements/



class Solution {
private:
    int n;

    void printBinary(int x) {
        for(int i = n-1; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }

    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    bool solve(vector<vector<int>>& statements, int mask) {
        // cout << "solve mask " << mask << " "; printBinary(mask); cout << endl;
        for(int i = 0; i < n; ++i) {
            int personi = ((1<<i) & mask) ? 1 : 0;     // 1 is good, 0 is bad
            if( !personi )
                continue;

            for(int j = 0; j < n; ++j) {
                if( i == j || statements[i][j] == 2 )
                    continue;

                int personj = ((1<<j) & mask) ? 1 : 0; // 1 is good, 0 is bad
                if( personj != statements[i][j] )
                    return false;
            }
        }

        return true;
    }

public:
    int maximumGood(vector<vector<int>>& statements) {
        n = statements.size(); // statements is of size n x n 2 <= n <= 15

        // statements[i][j]
        //     0 which represents a statement made by person i that person j is a bad person
        //     1 which represents a statement made by person i that person j is a good person
        //     2 represents that no statement is made by person i about person j

        // sort by number of setbits
        vector<int> v(pow(2,n));
        generate(v.begin(), v.end(), [i = 0] () mutable { return i++; });
        sort(v.begin(),v.end(),[&](const int& a, const int& b){
            return countSetBits(a) > countSetBits(b);
        });

        for(int mask: v)
            if( solve(statements,mask) )
                return countSetBits(mask);

        return -1; // we should never get here
    }
};
