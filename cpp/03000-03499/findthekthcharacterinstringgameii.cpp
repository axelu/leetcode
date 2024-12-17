
// 3307. Find the K-th Character in String Game II
// https://leetcode.com/problems/find-the-k-th-character-in-string-game-ii/






class Solution {
public:
    char kthCharacter(long long k, vector<int>& operations) {
        if( k == 1LL )
            return 'a';

        // 1 <= k <= 1e14
        //  <= operations.length <= 100

        // initial s = "a"
        // with each operation, the length of s doubles
        // even though operations.length could be up to 100, 10^14 is reached at i = 46, respectively after 47 operations
        // example
        // k 100000000000000
        // operations [0,0,0,1,0,1,0,0,1,1,0,0,0,1,0,1,0,0,1,1,0,0,0,1,0,1,0,0,1,1,0,0,0,1,0,1,0,0,1,1,0,1,0,1,0,1,1]

        long long n = 1LL;
        int i_max;
        long long s, e;
        for(int i = 0; i < min(47, (int)operations.size()); ++i) {
            // cout << "i " << i << " ";
            s = n; // cout << "begin index " << s << " ";
            n = 2LL * n;
            e = n - 1LL; // cout << "end index   " << e << endl;
            if( n >= k ) {
                i_max = i;
                break;
            }
        }
        // cout << "n " << n << endl;
        // cout << "i_max " << i_max << " s " << s << " e " << e << endl;

        // go backwards and determine the position in each iteration

        int cnt = 0; // count of iterations in which our char advanced to the next char
        long long pos = k - 1LL;
        for(int i = i_max; i >= 0; --i) {
            // cout << "i " << i << " ";
            // cout << "begin index " << s << " ";
            // cout << "end index " << e << " ";
            // cout << "pos " << pos << endl;

            // s <= pos <= e, will be true if i == i_max
            // distance of position from end in current iteration
            long long d = -1LL;
            if( s <= pos && pos <= e ) {
                d = e - pos;
                if( operations[i] == 1 )
                    ++cnt;
            }

            long long l = e - s + 1;
            e = e - l;
            s = e - (l/2LL) + 1;
            if( d != -1LL )
                pos = e - d;
        }

        // we know we start out with s = 0, e = 0 and char at 0 = 'a'
        return 'a' + (cnt % 26);
    }
};
