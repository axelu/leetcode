
// 3519. Count Numbers with Non-Decreasing Digits
// https://leetcode.com/problems/count-numbers-with-non-decreasing-digits/


/* resources
    https://cs.stackexchange.com/questions/10318/the-math-behind-converting-from-any-base-to-any-base-without-going-through-base

   example l = "4417051", r = "7512894", b = 9 => ans 3313
    convert l to base ->  "8272044"
    convert r to base -> "15120670"
    as we cannot have any non-decreasing,
    we now need to determine the bottom and top edge
    our max digit is b-1 (base - 1)
              l  "8272044"
    bottom edge  "8888888"
              r "15120670"
       top edge "14888888"


   there could be a case like this
    l = "3000", r = "3222", b = 10 => ans 0
    convert l to base ->  "3000" -> bottom edge 3333
    convert r to base ->  "3222" -> top edge 2999
    the bottom edge > top edge

 */
class Solution {
private:
    const long mod = 1000000007;

    // 2081. Sum of k-Mirror Numbers
    // https://leetcode.com/problems/sum-of-k-mirror-numbers/
    // base k encoding
    string basekencode(long long num, int k) {
        if( num == 0 )
            return "0";
        string ret = "";
        long rem;
        while( num > 0 ) {
            rem = num % k;
            ret = to_string(rem) + ret;
            num /= k;
        }
        return ret;
    }

    string get_bottom(string& s) {
        int s_sz = s.size();
        string ret;
        ret.push_back(s[0]);

        for(int i = 1; i < s_sz; ++i) {
            if( s[i] < s[i-1] ) {
                // we are done
                // fill in the rest with nums[i-1]
                char c = s[i-1];
                for( ; i < s_sz; ++i)
                    ret.push_back(c);
            } else {
                ret.push_back(s[i]);
            }
        }

        return ret;
    }

    string get_top(string& s, int b) {
        int s_sz = s.size();
        string ret;
        ret.push_back(s[0]);

        for(int i = 1; i < s_sz; ++i) {
            if( s[i] < s[i-1] ) {
                // we are done
                // we need to lower s[i-1] by 1, which could become 0 !!!
                // we need to propagate that change to the left
                // example 4442 b 10 becomes 3339
                // example 2442 b 10 becomes 2399
                char c = (b-1) + '0';
                ret[i-1] = s[i-1] - 1;
                char a = ret[i-1];
                for(int j = i-2; j >= 0; --j) {
                    if( ret[j] > a ) {
                        ret[j+1] = c;
                        ret[j] = a;
                    } else {
                        break;
                    }
                }
                // fill in the rest with b
                for( ; i < s_sz; ++i)
                    ret.push_back(c);
            } else {
                ret.push_back(s[i]);
            }
        }

        // trim leading 0s
        for(auto it = ret.begin(); it != ret.end(); ) {
            if( *it != '0' )
                break;
            it = ret.erase(it);
        }

        return ret;
    }

    bool cmp(string& be, string& te) {
        //returns true if be <= te
        int be_sz = be.size();
        int te_sz = te.size();
        if( be_sz > te_sz )
            return false;
        if( te_sz > be_sz )
            return true;

        // be_sz == te_sz
        for(int i = 0; i < be_sz; ++i)
            if( be[i] < te[i] )
                return true;
            else if( be[i] > te[i] )
                return false;

        return true; // be == te
    }

    char modulo_div(string& n, int destination_base) {
        int original_base = 10; // n is in base 10
        int carry = 0;
        int n_sz = n.size();
        for(int i = 0; i < n_sz; ++i) {
            int d = n[i]-'0';
            d += original_base * carry;
            carry = d % destination_base;
            d = d / destination_base;
            n[i] = d + '0';
        }
        return carry + '0';
    }

    bool is_zero(string n) {
        for(char c: n)
            if( c != '0' )
                return false;
        return true;
    }

    string convertBase(string n, int destination_base) {
        // n is in base 10, but easy to modify for any base
        string digits;
        while( !is_zero(n) )
            digits.push_back(modulo_div(n, destination_base));

        reverse(digits.begin(), digits.end());
        return digits;
    }

    /*
    // just for dirty test
    int rec(int pos, int pre) {
        // cout << "rec pos " << pos << " pre " << pre << endl;
        if( pos == 8 )
            return 1;

        int ret = 0;

        if( pos == 0 ) {
            ret += rec(pos + 1, 1);
        } else if( pos == 1 ) {
            for(int i = 1; i <= 4; ++i) {
                ret += rec(pos + 1, i);
            }
        } else {
            for(int i = pre; i <= 8; ++i) {
                ret += rec(pos+1, i);
            }
        }
        return ret;
    }
    */

    // pre 0-9
    // pos 0-?  depends on the base converted to
    // onbe 0 or 1
    // onte 0 or 1

    // unordered_map<unsigned long long, long> mem;
    long mem[400][10][2][2]; // 400 based on 100 digit 999... resulting in 333 base 2 number


    long rec(vector<int>& be, vector<int>& te, int pre, int pos, bool onbe, bool onte, int b) {
        int n = be.size(); // be.size() == te.size(), be maybe filled with leading zeros
        if( pos == n )
            return 1L;

        /*
        unsigned long long key = (pos<<6) + (pre<<2) + (onbe<<1) + onte;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;
        */
        if( mem[pos][pre][onbe][onte] != -1 )
            return mem[pos][pre][onbe][onte];

        long ret = 0L;

        // pre is previous value, we cannot go below that one

        if( pos == 0 ) {
            // we are just starting out
            if( be[pos] == te[pos] ) {
                ret = (ret + rec(be, te, be[pos], pos+1, true, true, b)) % mod;
            } else {
                // bottom edge
                ret = (ret + rec(be, te, be[pos], pos+1, true, false, b)) % mod;
                // in between bottom edge and top edge
                int i_mn = be[pos] + 1;
                int i_mx = te[pos] - 1;
                for(int i = i_mn; i <= i_mx; ++i)
                    ret = (ret + rec(be, te, i, pos+1, false, false, b)) % mod;
                // top edge
                ret = (ret + rec(be, te, te[pos], pos+1, false, true, b)) % mod;
            }

        } else { // pos > 0
            // onbe onte  min      max
            //   x   -    be[pos]  b-1
            //   -   x    pre      te[pos]
            //   -   -    pre      b-1
            //   x   x    be[pos]  te[pos]
            int i_mn, i_mx;
            if( onbe && !onte ) {
                i_mn = be[pos];
                i_mx = b-1;
                ret = (ret + rec(be, te, i_mn, pos+1, true, false, b)) % mod;
                for(int i = i_mn+1; i <= i_mx; ++i)
                    ret = (ret + rec(be, te, i, pos+1, false, false, b)) % mod;

            } else if( !onbe && onte ) {
                i_mn = pre;
                i_mx = te[pos];
                for(int i = i_mn; i < i_mx; ++i)
                    ret = (ret + rec(be, te, i, pos+1, false, false, b)) % mod;
                ret = ret + rec(be, te, i_mx, pos+1, false, true, b);

            } else if( !onbe && !onte ) {
                i_mn = pre;
                i_mx = b-1;
                for(int i = i_mn; i <= i_mx; ++i)
                    ret = (ret + rec(be, te, i, pos+1, false, false, b)) % mod;

            } else { // onbe && onte
                i_mn = be[pos];
                i_mx = te[pos];
                if( i_mn == i_mx ) {
                    ret = (ret + rec(be, te, i_mn, pos+1, true, true, b)) % mod;
                } else {
                    ret = (ret + rec(be, te, i_mn, pos+1, true, false, b)) % mod;
                    for(int i = i_mn+1; i < i_mx; ++i)
                        ret = (ret + rec(be, te, i, pos+1, false, false, b)) % mod;
                    ret = (ret + rec(be, te, i_mx, pos+1, false, true, b)) % mod;
                }
            }
        }

        // return ret;
        // return mem[key] = ret;
        return mem[pos][pre][onbe][onte] = ret;
    }

public:
    int countNumbers(string l, string r, int b) {
        // convert l and r to representation in base b
        string lb = convertBase(l, b); // cout << "lb " << lb << endl;
        string rb = convertBase(r, b); // cout << "rb " << rb << endl;

        // determine bottom edge and top edge
        string be = get_bottom(lb); cout << "lb " << lb << endl; cout << "be " << be << endl;
        string te = get_top(rb, b); cout << "rb " << rb << endl; cout << "te " << te << endl;

        // check if bottom edge <= top edge
        if( !cmp(be,te) )
            return 0;
        if( be == te )
            return 1;

        // cout << rec(0,-1) << endl;

        int be_sz = be.size();
        int te_sz = te.size();
        if( be_sz == 1 && te_sz == 1 )
            return te[0] - be[0] + 1;

        // simplifying from string to vector<int>
        vector<int> be_int(be_sz);
        for(int i = 0; i < be_sz; ++i)
            be_int[i] = be[i]-'0';
        vector<int> te_int(te_sz);
        for(int i = 0; i < te_sz; ++i)
            te_int[i] = te[i]-'0';

        // simplifying to prefil be with leading 0s to match length of te
        while( be_int.size() < te_sz )
            be_int.insert(be_int.begin(), 0);

        memset(mem,-1,sizeof mem);
        /*
        // let us pre-built cache bottom up for the case of
        // [pos][pre][false][false]
        for(int i = b-1; i > 0; --i)
            mem[be_sz-1][i][0][0] = (long)(b-i);
        for(int j = be_sz-2; j > 0; --j) {
            mem[j][b-1][0][0] = 1L;
            for(int i = b-2; i > 0; --i) {
                mem[j][i][0][0] = (mem[j+1][i][0][0] + mem[j][i+1][0][0]) % mod;
            }
        }
        */
        return rec(be_int, te_int, 0, 0, false, false, b);
    }
};




// tests used to develop
/*

"4417051"
"7512894"
10
"3000"
"3222"
10
"1000"
"1011"
10
"2345"
"2442"
10
"1000"
"1101"
10
"1"
"9"
10
"1111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111111"
"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
10
"1"
"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
10
"1"
"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
2

"1"
"9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
10
"3"
"27"
3
"11"
"222"
10




*/
