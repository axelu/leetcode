
// 2468. Split Message Based on Limit
// https://leetcode.com/problems/split-message-based-on-limit/






class Solution {
private:
    int cnt_digits(int x) {
        int digits = 0;
        while( x > 0 ) {
            ++digits;
            x /= 10;
        }
        return digits;
    }

    int solve(int msg_sz, int parts, int limit) {
        // suffix <part/parts>
        // number of digits in parts
        int parts_digits = cnt_digits(parts);
        // our suffix will comsume a fixed amount of limit of 3 + parts_digits, the <, /, > and parts number
        int sfx_fixed = 3 + parts_digits;
        // the varriable part will be between 1 and parts_digits inclusive
        if( limit <= sfx_fixed + parts_digits )
            return 1;                       // parts to big

        int chars_delivered = 0;
        int i = 10;
        int start = 1;
        while( true ) {
            i = min(i,parts);
            int var = cnt_digits(i-1);
            int sfx_sz = var + sfx_fixed;
            int chrs_per_part = limit - sfx_sz;

            int cnt = i - start;

            // cout << "i " << i << " sfx_sz " << sfx_sz << " chrs_per_part " << chrs_per_part << " cnt " << cnt << endl;

            chars_delivered +=  chrs_per_part * cnt;

            if( i == parts )
                break;
            start = i;
            i *= 10;
        }
        // cout << "chars_delivered before last part " << chars_delivered << endl;
        // last part - we have one more part
        //    needs to deliver at minimum 1 char
        //    needs to deliver at max limit - sfx_sz
        int sfx_sz = sfx_fixed + parts_digits;
        int rem_chars = msg_sz - chars_delivered;
        if( rem_chars <= 0 ) {
            // parts too big
            return 1;
        } else if( rem_chars <= limit - sfx_sz ) {
            // we have a solution
            return 0;
        } else { // rem_chars > limit - sfx_sz
            // parts too small
            return -1;
        }
    }

    vector<string> construct_parts(string& message, int parts, int limit) {
        vector<string> ret;

        string sfx_lst = "/" + to_string(parts) + ">";
        int sfx_fixed  = 1 + sfx_lst.size();

        int k = 0; // index in message
        int i = 10;
        int start = 1;
        while( true ) {
            i = min(i,parts);
            int var = cnt_digits(i-1);
            int sfx_sz = var + sfx_fixed;
            int chrs_per_part = limit - sfx_sz;

            for(int j = start; j < i; ++j) {
                string msg_prt = message.substr(k,chrs_per_part);
                k += chrs_per_part;
                msg_prt.append("<");
                msg_prt.append(to_string(j));
                msg_prt.append(sfx_lst);
                ret.push_back(msg_prt);
            }

            if( i == parts )
                break;
            start = i;
            i *= 10;
        }
        // last part
        string msg_prt = message.substr(k);
        msg_prt.append("<");
        msg_prt.append(to_string(parts));
        msg_prt.append(sfx_lst);
        ret.push_back(msg_prt);

        return ret;
    }

    // binary search
    int search(int s, int e, int msg_sz, int limit) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        int o = solve(msg_sz,mid,limit);

        if( o == 0 ) {
            // can we do better?
            int t = search(0,mid-1,msg_sz,limit);
            return t != -1 ? t : mid;

        } else if( o == -1 ) {
            return search(mid+1,e,msg_sz,limit);

        } else { // o == 1
            return search(s,mid-1,msg_sz,limit);
        }
    }

public:
    vector<string> splitMessage(string message, int limit) {
        // the suffix with even single digit length takes 5 chars
        // <1/1>, hence any limit below 6 will not work. period.
        if( limit < 6 )
            return {};

        int n = message.size();
        if( limit >= n+5 )
            return {message + "<1/1>"};

        // suffix <part/parts>
        // if (digit in parts) * 2 + 3 >= limit, we have no solution either
        // example lets say we think we need 1200 parts, our limit = 30
        //                <1200/1200> consumes 11 slots of our limit
        //                            suffix size           chars per part
        //                            fix var        cnt    limit - sfxsz     x  cnt
        // <x/1200>    1 <= x <   10   7 + 1 =  8      9    30    -  8 = 22   x    9 =   198
        // <x/1200>   10 <= x <  100   7 + 2 =  9     90    30    -  9 = 21   x   90 =  1890
        // <x/1200>  100 <= x < 1000   7 + 3 = 10   1000    30    - 10 = 20   x  900 = 18000
        // <x/1200> 1000 <= x < 1200   7 + 4 = 11    200    30    - 11 = 19   x  200 =  3800
        //                                                                            ------
        // excluding the last part we can deliver                                      23888 chars
        // <x/1200>         x = 1200   7 + 4 = 11      1    30    - 11 = 19   x    1 = 19    last part
        // if (messagesz - charsdilvered) > 0 && (messagesz - charsdilvered) <= last part, we have a solution

        // find the parts size, if any
        int parts = search(1,10000,n,limit);
        if( parts == -1 )
            return {};

        // construct the answer
        return construct_parts(message,parts,limit);
    }
};
