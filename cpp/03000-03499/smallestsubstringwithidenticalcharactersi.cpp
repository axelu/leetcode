
// 3398. Smallest Substring With Identical Characters I
// https://leetcode.com/problems/smallest-substring-with-identical-characters-i/






class Solution {
private:
    int get_max_consecutive(string& s) {
        int n = s.size();

        int max_consecutive = 1;
        int count_consecutive = 1;
        for(int i = 1; i < n; ++i) {
            if( s[i-1] == s[i] ) {
                ++count_consecutive;
            } else {
                max_consecutive = max(max_consecutive, count_consecutive);
                count_consecutive = 1;
            }
        }
        // finish up
        max_consecutive = max(max_consecutive, count_consecutive);

        return max_consecutive;
    }

    bool solve_for_1(string& str, int numOps) {
        int n = str.size();
        int maxConsecutive = 1;

        string s = str;
        int ops = numOps;

        bool ret = true;

        int count_consecutive = 1;
        for(int i = 1; i < n; ++i) {
            if( s[i-1] == s[i] ) {
                ++count_consecutive;
                if( count_consecutive > maxConsecutive ) {
                    --ops;
                    if( ops < 0 ) {
                        ret = false;
                        break;
                    }
                    s[i] = s[i] == '1' ? '0' : '1';
                    count_consecutive = 1;
                }
            } else {
                count_consecutive = 1;
            }
        }

        if( !ret ) {
            s = str;
            ops = numOps-1;
            s[0] = s[0] == '1' ? '0' : '1';

            count_consecutive = 1;
            for(int i = 1; i < n; ++i) {
                if( s[i-1] == s[i] ) {
                    ++count_consecutive;
                    if( count_consecutive > maxConsecutive ) {
                        --ops;
                        if( ops < 0 )
                            return false;
                        s[i] = s[i] == '1' ? '0' : '1';
                        count_consecutive = 1;
                    }
                } else {
                    count_consecutive = 1;
                }
            }
        }

        return true;
    }

    int mem[2][1000][1001];

    bool solve(string& s, int maxConsecutive, int pos, int numOps) {
        int n = s.size();
        if( pos == n )
            return true;

        int pre;
        if( pos > 0 ) {
            pre = s[pos-1] != s[pos];
            if( mem[pre][pos][numOps] != -1 )
                return mem[pre][pos][numOps];
        }

        // if we flip the last occurence of
        // consecutive 0s or 1s, it has an impact on
        // the following elements (unless we are at n-1)

        bool ret = true;

        int count_consecutive = 1;
        for(int i = pos+1; i < n; ++i) {
            if( s[i-1] == s[i] ) {
                ++count_consecutive;

                if( count_consecutive > maxConsecutive ) {
                    // we don't have a choice, we must flip
                    if( numOps - 1 < 0 ) {
                        ret = false;
                        break;
                    }
                    // flip
                    s[i] = s[i] == '1' ? '0' : '1';
                    bool f = solve(s, maxConsecutive, i+1, numOps-1);
                    // backtrack
                    s[i] = s[i] == '1' ? '0' : '1';
                    if( f ) {
                        ret = true;
                        break;
                    } else {
                        // assume we flipped the prior position
                        ret = solve(s, maxConsecutive, i+1, numOps-1);
                        break;
                    }
                }
            } else {
                count_consecutive = 1;
            }
        }

        if( pos > 0 )
            mem[pre][pos][numOps] = ret;

        return ret;
    }

    // binary search
    int search(string& str, int numOps, int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = solve(str, mid, 0, numOps);
        if( f ) {
            // can we do better?
            int t = search(str, numOps, s, mid-1);
            return t != -1 ? t : mid;
        }

        return search(str, numOps, mid+1, e);
    }

public:
    int minLength(string s, int numOps) {
        int n = s.size();

        if( n == 1 )
            return 1;

        int max_consecutive = get_max_consecutive(s);
        if( numOps == 0 || max_consecutive == 1 )
            return max_consecutive;

        // can we achive 1?
        if( solve_for_1(s, numOps) )
            return 1;

        // our solution lies somewhere between 2 and
        // the max consecutive run of 0s or 1s (which could be n)
        memset(mem,-1,sizeof mem);
        return search(s, numOps, 2, max_consecutive);
    }
};



/* example test cases
"000001"
1
"0000"
2
"0101"
0
"11100"
1
"000"
0
"000"
1
"00000"
2
"1101"
1
"00110"
2
"01100100111111110110010010000111001111011000101011"
6
"0000"
1
"000000"
1
"1110110101100011011011110110101010111011010100000111100111100011010101101000011000110111011110100111100000000111001000011010000010100101001101000101110011110101111111011010111111010001000101100101000111001101000011100111100101000000101011110100100110111000100010010011000001101110001001110101010100011111101110001001100011001000101111101100010100111001111000011101110010111010111101111011110001010101001010110100110101001110101011001110000111111101010101110111100111110000010100100110001010100100011110011010000110011111110010011000100101101111001101110011101010101101101010000000010010101110111010010100011000000000101001110010010010110100010110101010011000011110101110011010000011110110001101101011011101111010011111111101100100000110111110110011011010000111100000110001001010000011010101001101100011101011101100100011001001011000001000101100000110000101101100101000111011010111010110001111000101110001010000000111100000100101111111011110001000110110011101001011011011101001010011101100100110011101"
83
*/
