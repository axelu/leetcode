
// 2983. Palindrome Rearrangement Queries
// https://leetcode.com/problems/palindrome-rearrangement-queries/




// initialize once
long long p_pow[100001];
bool init = false;

class Solution {
private:
    const int p = 31;
    const int m = 1e9 + 9;

    long long * first_half_h;
    long long * second_half_h;

    bool is_equal_str(const int i, const int j) {
        long long t1 = ( first_half_h[j+1] + m -  first_half_h[i]) % m;
        long long t2 = (second_half_h[j+1] + m - second_half_h[i]) % m;
        return t1 == t2;
    }

    int ** first_half_prefixSum;
    int ** second_half_prefixSum;

    bool is_equal_freq(const int i, const int j) {
        for(int k = 0; k < 26; ++k) {
            int t1 = first_half_prefixSum[k][j+1] - first_half_prefixSum[k][i];
            int t2 = second_half_prefixSum[k][j+1] - second_half_prefixSum[k][i];
            if( t1 != t2 )
                return false;
        }
        return true;
    }

    vector<int> get_freq(const int i, const int j, int ** prefixSum) {
        vector<int> ret(26,0);
        for(int k = 0; k < 26; ++k)
            ret[k] = prefixSum[k][j+1] - prefixSum[k][i];
        return ret;
    }

    void print_freq(vector<int> freq) {
        for(int i = 0; i < 26; ++i)
            cout << (char)('a' + i) << ":" << freq[i] << " ";
        cout << endl;
    }

    bool subtract(vector<int>& freq, const int i, const int j, int ** prefixSum) {
        // freq - freq from prefixSum
        // freq will be modified
        // returns true if freq[i] >= freq from prefixSum
        for(int k = 0; k < 26; ++k) {
            freq[k] -= prefixSum[k][j+1] - prefixSum[k][i];
            if( freq[k] < 0 )
                return false;
        }
        return true;
    }

public:
    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        int n = s.size(); // n % 2 == 0; 2 <= n == s.length <= 1e5

        if( !init ) {
            init = true;
            p_pow[0] = 1;
            for (int i = 1; i < 50001; i++)
                p_pow[i] = (p_pow[i-1] * p) % m;
        }

        // queries[i] = [ai, bi, ci, di]
        // ai,bi are in the 1st half and ci, di are in the second half
        // so we will take the second half, reverse it (including c and d) and
        // then look for achieving equality between 1st half and 2nd half

        // case A range a,b and c,d don't overlap
        //     then we have up to 3 ranges we cannot touch, those have to be equal to begin with, and
        //     we have 2 ranges that char frequency has to be the same
        // case B range a,b and c,d eclipse each other
        //     we have a range min(a,c) and max(b,d)
        //     char frequency has to be the same for that range
        // case C neither A nor B, meaning they overlap partially
        //     a----b
        //        c---d   (note: c and d flipped here)
        //     we will derive the char freq in 1st half c,b by a,c, as we cannot change 2nd half a,c
        //     we will derive the char freq in 2nd half b,c by b,d, as we cannot change 1st half b,d
        //     then the char freq 1st half c,b and 2nd half c,b will have to be the same
        // based on this we need
        //     a way to check equality of substrings of 1st half and 2nd half
        //     a way to check equality of char freq of a range in 1st half and 2nd half
        //     a way to subtract char frequencies

        // rolling hash and prefixSum
        first_half_h = new long long[n/2+1];
        first_half_h[0] = 0LL;
        second_half_h = new long long[n/2+1];
        second_half_h[0] = 0LL;
        first_half_prefixSum = new int *[26];
        second_half_prefixSum = new int *[26];
        for(int i = 0; i < 26; ++i) {
            first_half_prefixSum[i] = new int[n/2+1];
            first_half_prefixSum[i][0] = 0;
            second_half_prefixSum[i] = new int[n/2+1];
            second_half_prefixSum[i][0] = 0;
        }
        for(int i = 0; i < n/2; ++i) {
            int first_half_c = s[i]-'a';
            first_half_h[i+1] = (first_half_h[i] + (first_half_c + 1) * p_pow[i]) % m;

            for(int j = 0; j < 26; ++j)
                first_half_prefixSum[j][i+1] = j != first_half_c ? first_half_prefixSum[j][i] : first_half_prefixSum[j][i] + 1;

            int second_half_c = s[n-1-i]-'a';
            second_half_h[i+1] = (second_half_h[i] + (second_half_c + 1) * p_pow[i]) % m;

            for(int j = 0; j < 26; ++j)
                second_half_prefixSum[j][i+1] = j != second_half_c ? second_half_prefixSum[j][i] : second_half_prefixSum[j][i] + 1;
        }

        int queries_sz = queries.size();
        vector<bool> ans(queries_sz,false);

        // procress query by query;
        for(int i = 0; i < queries_sz; ++i) {
            int a = queries[i][0];
            int b = queries[i][1];
            int c = (n-1) - queries[i][3];
            int d = (n-1) - queries[i][2];

            // printf("a %i b %i c %i d %i\n",a,b,c,d);

            if( b < c || d < a ) {
                // cout << "CASE A" << endl;
                if( d < a ) {
                    // swap
                    int t = a;
                    a = c;
                    c = t;
                    t = b;
                    b = d;
                    d = t;
                }
                // a,b is to the left of c,d
                // range to the left
                if( a > 0 ) {
                    if( !is_equal_str(0, a-1) )
                        continue;
                }
                // range to adjust
                if( !is_equal_freq(a, b) )
                    continue;
                // range in the middle
                if( b+1 < c ) {
                    if( !is_equal_str(b+1, c-1) )
                        continue;
                }
                // range to adjust
                if( !is_equal_freq(c, d) )
                    continue;
                // range to the right
                if( d < n/2-1 ) {
                    if( !is_equal_str(d+1, n/2-1) )
                        continue;
                }

            } else if( ( a <= c && d <= b ) || ( c <= a && b <= d ) ) {
                // cout << "CASE B" << endl;
                int start = min(a,c);
                int end = max(b,d);
                // printf("start %i end %i\n",start,end);
                // range to the left
                if( start > 0 ) {
                    if( !is_equal_str(0, start-1) )
                        continue;
                }
                // range to adjust
                if( !is_equal_freq(start, end) )
                    continue;
                // range to the right
                if( end < n/2 - 1 ) {
                    if( !is_equal_str(end+1, n/2-1) )
                        continue;
                }

            } else {
                // cout << "CASE C" << endl;
                // a----b
                //   c----d
                // OR
                //   a----b
                // c----d
                int start = min(a,c);
                int end = max(b,d);
                // range to the left
                if( start > 0 ) {
                    if( !is_equal_str(0, start-1) )
                        continue;
                }

                // range to adjust
                auto first_half_freq = get_freq(a, b, first_half_prefixSum);
                auto second_half_freq = get_freq(c, d, second_half_prefixSum);
                if( a < c ) {
                    // cout << "a < c" << endl;
                    if( !subtract(first_half_freq, a, c-1, second_half_prefixSum) )
                        continue;
                    if( !subtract(second_half_freq, b+1, d, first_half_prefixSum) )
                        continue;

                } else {
                    // cout << "c < a" << endl;
                    // print_freq(second_half_freq);
                    if( !subtract(second_half_freq, c, a-1, first_half_prefixSum) )
                        continue;
                    // print_freq(second_half_freq);
                    // print_freq(first_half_freq);
                    if( !subtract(first_half_freq, d+1, b, second_half_prefixSum) )
                        continue;
                    // print_freq(first_half_freq);

                }
                if( !(first_half_freq == second_half_freq) )
                    continue;

                // range to the right
                if( end < n/2 - 1 )
                    if( !is_equal_str(end+1, n/2-1) )
                        continue;

            }
            ans[i] = true;
        }

        return ans;
    }
};
