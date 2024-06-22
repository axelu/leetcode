
// 2719. Count of Integers
// https://leetcode.com/problems/count-of-integers/






/* 1 <= num1 <= num2 <= 1e22
 * 1e22 -> 10000000000000000000000
 * worst case digit sum
 *          9999999999999999999999 -> 22 * 9 = 198
 *
 * extreme case
 * num1 = "1", num2 = "10000000000000000000000", min_sum = 1, max_sum = 400
 * ans 10000000000000000000000 % MOD = 490000
 */
class Solution {
private:
    const long MOD = 1000000007;
    string _num1, _num2;
    int _min_sum, _max_sum;

    int get_digit_sum(const string s) {
        int digit_sum = 0;
        for(char c: s) {
            int digit = c - '0';
            digit_sum += digit;
        }
        return digit_sum;
    }

    long membt[24][401][2][2];

    // routine w/o bottom and w/o top
    // anything goes as long as
    //     min_sum <= digit_sum && digit_sum <= max_sum and
    //     leftmost pos is not 0
    long rec(const int pos, const int n, const int digit_sum) {
        if( digit_sum == _max_sum )
            return 1L;

        if( pos == n )
            return digit_sum >= _min_sum ? 1L : 0L;

        int remaining_positions = n - pos;
        if( membt[remaining_positions][digit_sum][false][false] != -1L )
            return membt[remaining_positions][digit_sum][false][false];

        long ret = 0L;

        // we cannot have leading zero
        int min_digit = pos == 0 ? 1 : 0;
        int max_digit = 9;
        for(int digit = min_digit; digit <= max_digit && digit_sum + digit <= _max_sum; ++digit) {
            ret = (ret + rec(pos+1, n, digit_sum + digit)) % MOD;
        }

        return membt[remaining_positions][digit_sum][false][false] = ret;
    }

    long rec_with_bottom(const int pos, const int digit_sum, const bool at_bottom_edge) {
        int n = _num1.size();

        if( digit_sum == _max_sum )
            return 1L;

        if( pos == n )
            return digit_sum >= _min_sum ? 1L : 0L;

        int remaining_positions = n - pos;
        if( membt[remaining_positions][digit_sum][at_bottom_edge][false] != -1L )
            return membt[remaining_positions][digit_sum][at_bottom_edge][false];

        long ret = 0L;

        // if we move along the bottom edge, then the digit we pick
        // cannot be less than the digit in _num1 at the current position
        // for pos 0 the flag at_bottom_edge will be true
        int min_digit = at_bottom_edge ? _num1[pos] - '0' : 0;
        int max_digit = 9;
        bool at_bottom_edge_new = at_bottom_edge;
        for(int digit = min_digit; digit <= max_digit && digit_sum + digit <= _max_sum; ++digit) {
            bool is_bottom_edge = at_bottom_edge && digit == min_digit;
            ret = (ret + rec_with_bottom(pos+1, digit_sum + digit, is_bottom_edge)) % MOD;
        }

        return membt[remaining_positions][digit_sum][at_bottom_edge][false] = ret;
    }

    long rec_with_top(const int pos, const int digit_sum, bool at_top_edge) {
        int n = _num2.size();

        if( digit_sum == _max_sum )
            return 1L;

        if( pos == n )
            return digit_sum >= _min_sum ? 1L : 0L;

        int remaining_positions = n - pos;
        if( membt[remaining_positions][digit_sum][false][at_top_edge] != -1L )
            return membt[remaining_positions][digit_sum][false][at_top_edge];

        long ret = 0L;

        // if we move along the top edge, then the digit we pick
        // cannot be greater than the digit in _num2 at the current position
        // for pos 0 we cannot have a leading 0
        int min_digit = pos == 0 ? 1 : 0;
        int max_digit = at_top_edge ? _num2[pos] - '0' : 9;
        for(int digit = min_digit; digit <= max_digit && digit_sum + digit <= _max_sum; ++digit) {
            bool is_top_edge = at_top_edge && digit == max_digit;
            ret = (ret + rec_with_top(pos+1, digit_sum + digit, is_top_edge)) % MOD;
        }

        return membt[remaining_positions][digit_sum][false][at_top_edge] = ret;
    }

    long rec_with_bottom_and_with_top(const int pos, const int digit_sum, bool at_bottom_edge, bool at_top_edge) {
        int n = _num1.size(); // _num1.size() == _num2.size()

        if( pos == n )
            return _min_sum <= digit_sum && digit_sum <= _max_sum ? 1L : 0L;

        int remaining_positions = n - pos;
        if( membt[remaining_positions][digit_sum][at_bottom_edge][at_top_edge] != -1L )
            return membt[remaining_positions][digit_sum][at_bottom_edge][at_top_edge];

        long ret = 0L;

        int min_digit = at_bottom_edge ? _num1[pos] - '0' : 0;
        int max_digit = at_top_edge ? _num2[pos] - '0' : 9;
        for(int digit = min_digit; digit <= max_digit && digit_sum + digit <= _max_sum; ++digit) {
            bool is_bottom_edge = at_bottom_edge && digit == min_digit;
            bool is_top_edge = at_top_edge && digit == max_digit;
            ret = (ret + rec_with_bottom_and_with_top(pos+1, digit_sum + digit, is_bottom_edge, is_top_edge)) % MOD;
        }

        return membt[remaining_positions][digit_sum][at_bottom_edge][at_top_edge] = ret;
    }

public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        if( num1 == num2 ) {
            int digit_sum = get_digit_sum(num1);
            return min_sum <= digit_sum && digit_sum <= max_sum;
        }

        _num1 = num1;
        _num2 = num2;
        _min_sum = min_sum;
        _max_sum = max_sum;

        memset(membt,-1,sizeof membt);

        if( num1.size() == num2.size() )
            return rec_with_bottom_and_with_top(0,0,true,true);

        long ans = rec_with_bottom(0,0,true);
        for(int n = num1.size() + 1; n <= num2.size() -1; ++n)
            ans = (ans + rec(0,n,0)) % MOD;
        ans = (ans + rec_with_top(0,0,true)) % MOD;

        return ans;
    }
};
