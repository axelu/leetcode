
// 2999. Count the Number of Powerful Integers
// https://leetcode.com/problems/count-the-number-of-powerful-integers/





class Solution {
private:
    string str_start;
    string str_start_prefix;
    string str_finish;
    string str_finish_prefix;
    int str_finish_prefix_sz;
    int limit;

    string get_str_start_prefix(string str_start, int s_sz, bool& f) {
        // example limit 6: 557 -> 560; 567 -> 600; 667 -> 1000; 575 -> 600
        int str_start_sz = str_start.size();
        string _str_start_prefix;
        if( str_start_sz > s_sz ) {
            _str_start_prefix = str_start.substr(0,str_start_sz - s_sz);
        } else {
            _str_start_prefix = "1";
            f = true;
            return _str_start_prefix;
        }

        if( (_str_start_prefix[0] - '0') > limit ) {
            _str_start_prefix = string(_str_start_prefix.size(),'0');
            _str_start_prefix = "1" + _str_start_prefix;
            f = true;
            return _str_start_prefix;
        }

        int carry = 0;
        for(int i = 0; i < _str_start_prefix.size(); ++i) {

            // the first position we encounter where (_str_start_prefix[i] - '0') > limit
            if( (_str_start_prefix[i] - '0') > limit ) {
                f = true;
                for(int j = i; j < _str_start_prefix.size(); ++j)
                    _str_start_prefix[j] = '0';
                carry = 1;
                --i;
                for(; i >= 0; --i) {
                    if( (_str_start_prefix[i] - '0') + 1 > limit ) {
                        _str_start_prefix[i] = '0';
                    } else {
                        _str_start_prefix[i] = _str_start_prefix[i] + 1;
                        carry = 0;
                        break;
                    }
                }
                break;
            }
        }
        if( carry )
            _str_start_prefix = "1" + _str_start_prefix;

        return _str_start_prefix;
    }

    string get_str_finish_prefix(string str_finish, int s_sz, bool& f) {
        int str_finish_sz = str_finish.size();
        string _str_finish_prefix = str_finish.substr(0, str_finish_sz - s_sz);
        for(int i = 0; i < _str_finish_prefix.size(); ++i) {
            if( (_str_finish_prefix[i] - '0') > limit ) {
                _str_finish_prefix[i] = '0' + limit;
                f = true;
            }
        }

        return _str_finish_prefix;
    }

    long long mem[16][2][2][2];

    long long rec(int pos, int start, int le, int te) {
        // cout << "rec pos " << pos << " start " << start << " le " << le << " te " << te << endl;
        // start = is start, then we cannot use 0
        // le    = is low edge?
        // te    = is top edge?

        if( pos == str_finish_prefix_sz )
            return 1LL;

        if( mem[pos][start][le][te] != -1LL )
            return mem[pos][start][le][te];

        long long ret = 0;

        int i = le ? (str_start_prefix[pos] - '0') : start ? 1 : 0;
        int i_limit = te ? (str_finish_prefix[pos] - '0') : limit;
        for(; i <= i_limit; ++i) {

            int le_new = 0;
            if( le && i == (str_start_prefix[pos] - '0') )
                le_new = 1;
            int te_new = 0;
            if( te ) {
                if( str_finish_prefix[pos] != str_finish[pos] ) {
                    // do nothing

                } else if( i == (str_finish_prefix[pos] - '0') ) {
                    te_new = 1;
                }
            }

            ret += rec(pos + 1, 0, le_new, te_new);
        }

        return mem[pos][start][le][te] = ret;
    }

public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        this->limit = limit;

        // 1 <= start <= finish <= 1e15
        // 1 <= limit <= 9
        // 1 <= s.length <= floor(log10(finish)) + 1
        //     in other words, s is never longer than finish, but still, finish could be less than s
        //     long long f = 1000000000000000LL;
        //     cout << floor(log10(f)) + 1 << endl; // 16

        // worst case s.size() == 16 and limit == 9 -> s = "9999999999999999"
        //                LLONG_MAX = 9223372036854775807 > 9999999999999999
        // so we can convert s to long long
        long long ll_s = stoll(s);
        if( finish < ll_s )
            return 0LL;
        if( finish == ll_s )
            return 1LL;

        long long ans = 0LL;

        // we are only interested in max(ll_s,start) <= x <= finish
        if( start <= ll_s ) {
            start = ll_s;
            ans = 1LL;
        }

        // we know by now also: start < finish and finish > ll_s

        int s_sz = s.size();

        str_finish = to_string(finish);
        int str_finish_sz = str_finish.size();
        if( str_finish_sz == s_sz ) {
            // also start must have the same number of digits
            return start > ll_s ? 0LL : 1LL;
        }

        str_start = to_string(start);
        int str_start_sz = str_start.size();

        bool is_start_prefix_adjusted_up = false;
        str_start_prefix = get_str_start_prefix(str_start, s_sz, is_start_prefix_adjusted_up);

        // we know by now: str_finish_sz > s_sz
        bool is_finish_prefix_adjusted_down = false;
        str_finish_prefix = get_str_finish_prefix(str_finish, s_sz, is_finish_prefix_adjusted_down);
        str_finish_prefix_sz = str_finish_prefix.size();

        if( str_finish_prefix_sz < str_start_prefix.size() )
            return 0LL;
        long long ll_start_prefix = stoll(str_start_prefix);
        long long ll_finish_prefix = stoll(str_finish_prefix);
        if( ll_start_prefix > ll_finish_prefix )
            return 0LL;

        int start_pos = str_finish_prefix_sz - str_start_prefix.size();

        while( str_start_prefix.size() < str_finish_prefix_sz )
            str_start_prefix = "0" + str_start_prefix;

        /*
        cout << "str_start_prefix      " << str_start_prefix << endl;
        cout << "str_finish_prefix     " << str_finish_prefix << endl;
        cout << "str_finish_prefix_sz  " << str_finish_prefix_sz << endl;
        cout << "start_pos             " << start_pos << endl;
        */

        // cout << "ans before rec.       " << ans << endl;

        memset(mem,-1,sizeof mem);
        for(int i = start_pos; i >= 0; --i) {
            int le = i == start_pos ? 1 : 0;
            int te = i == 0 ? 1 : 0;
            ans += rec(i, 1, le, te);
        }

        // cout << "ans before adjustment " << ans << endl;

        if( !is_start_prefix_adjusted_up ) {
            string str_start_suffix = str_start.substr(str_start_sz - s_sz);
            long long ll_start_suffix = stoll(str_start_suffix);
            if( ll_start_suffix > ll_s )
                --ans;
        }

        if( !is_finish_prefix_adjusted_down ) {
            string str_finish_suffix = str_finish.substr(str_finish_sz - s_sz);
            long long ll_finish_suffix = stoll(str_finish_suffix);
            if( ll_finish_suffix < ll_s )
                --ans;
        }

        // cout << "ans after adjustment  " << ans << endl;

        // cannot be less than 0 example: start = 1299, finish = 1299, limit = 9, s = "399"
        return ans < 0LL ? 0LL : ans;
    }
};
