
// 1977. Number of Ways to Separate Numbers
// https://leetcode.com/problems/number-of-ways-to-separate-numbers/


class Solution {    
public:
    int numberOfCombinations(string num) {
        if( num[0] == '0' )
            return 0;
        
        const long mod = 1000000007;
        
        // we will start with the longest length
        // whenever we check the segment after us, we also include the result from the prior length
        // because any number longer than the current partition will be greater.
        // we will carry the result forward, which will get us from O(n^3) to O(n^2)
        // when we are at index 0, we basically will have collected the result for the final answer.
        
        int n = num.size();
        
        long _pre[n+1];memset(_pre,0,sizeof _pre); long * pre = _pre;  // result for prior length, l + 1
        long _cur[n+1]; long * cur = _cur; 
        
        for(int l = n; l >= 1; --l) {
            memset(cur,0,sizeof(long) * (n+1));
            
            for(int i = n - l; i >= 0; --i) { // current partition start
                if( num[i] != '0' ) {
                    int j = i + l - 1;        // current partition end

                    if( j == n-1 ) {
                        cur[i] = 1L;
                        
                    } else {
                        // partition after the current partition, same length
                        int nxt_i = j + 1;
                        int nxt_j = nxt_i + l - 1;

                        // can we use same length?
                        if( nxt_j < n && memcmp(&num[i], &num[nxt_i], l) <= 0 )
                            cur[i] = cur[nxt_i];

                        // harvest results from all greater lengths
                        cur[i] = (cur[i] + pre[nxt_i]) % mod;
                    }
                }
                // carry forward
                cur[i+l] = (cur[i+l] + pre[i+l]) % mod;
            }            
            // carry forward the remaining positions
            for(int i = l-1; i >= 0; --i)
                cur[i] = (cur[i] + pre[i]) % mod;
            
            swap(pre, cur);
        }
        
        return pre[0];
    }
};






// top-down DP solution, but will lead to TLE

class Solution {
private:

    long mod = 1000000007;

    // unordered_map<int,long> mem;
    // unordered_map<int,bool> mem1;
    long mem3[3500][3500];

    bool is_same(string& num, int pos, int l) {
        // cout << "is_same pos " << pos << " l " << l << endl;
        // int key = (pos<<12) + l;
        // auto f = mem1.find(key);
        // if( f != mem1.end() ) {
        //    // cout << "hit" << endl;
        //    return f->second;
        //}


        int i = pos - l;

        int t = memcmp(&num[i],&num[pos],l);
        return t <= 0;




        bool flag = true;
        for(int k = 0; k < l; ++k) {
            if( num[i+k] > num[pos + k] ) {
                flag = false;
                break;
        } else if( num[i+k] < num[pos + k] ) {
                break;
            }
        }
        return flag;
        // return mem1[key] = flag;
    }



    long rec(string& num, int n, int pos, int prel) {
        // cout << "rec pos " << pos << " prel " << prel << endl;
        // we can make the next number starting from pos
        //    - with the same length as the prior one it that yields a number >= the prior one OR
        //    - any number with l > prel will be larger
        // we can never start with a 0
        // we don't need to call further down if the remainder cannot result in an equal length or larger number

        // if pos == 0, we are just starting out TODO

        if( pos == n ) {
            // cout << "rec pos " << pos << " prel " << prel << " result " << 1 << endl;
            return 1;
        }

        // remaining positions after we make a string with the same length as prel
        int rem =  n - (pos + prel);

        // int key = (pos<<12) + prel;
        // auto f = mem.find(key);
        //if( f != mem.end() ) {
            // cout << "hit" << endl;
        //    return f->second;
        //}
        if( mem3[pos][prel] != -1L ) {
            // cout << "rec pos " << pos << " prel " << prel << endl;
            // cout << "hit" << endl;
            return mem3[pos][prel];
        }

        long ret = 0L;

        if( rem == 0 ) {
            // cout << "    rem == 0" << endl;
            // the only option we have is to make a string of same length TODO externalize to cache and to not duplicate
            //ret = is_same(num, pos, prel);
            ret = memcmp(&num[pos - prel],&num[pos], prel) <= 0;
            // cout << "rec pos " << pos << " prel " << prel << " result " << ret << endl;
            // return mem[key] = ret;
            return mem3[pos][prel] = ret;

        } else  if( rem < prel ) {
            // cout << "rec pos " << pos << " prel " << prel << " result " << 1 << endl;
            return mem3[pos][prel] = 1L;
        }


        int l_max = (n - pos) / 2;
        // we can make a strings of length l with prel <= l <= l_max

        // same length
        // same length, it is guaranteed that we can make that length
        if( pos != 0 ) {
            // if( is_same(num, pos, prel) && num[pos + prel] != '0' )
            if( memcmp(&num[pos - prel],&num[pos],prel) <= 0 && num[pos + prel] != '0' )
                ret = (ret + rec(num, n, pos + prel, prel)) % mod;
        }

        for(int l = prel + 1; l <= l_max; ++l) {
            if( num[pos + l] != '0' )
                ret = (ret + rec(num, n, pos + l, l)) % mod;
        }

        ret = (ret + 1L) % mod; // just extend to the end

        // cout << "rec pos " << pos << " prel " << prel << " result " << ret << endl;
        // return mem[key] = ret;
        return mem3[pos][prel] = ret;
    }


public:
    int numberOfCombinations(string num) {
        if( num[0] == '0' )
            return 0;

        memset(mem3,-1,sizeof mem3);

        return rec(num, num.size(), 0, 0);
    }
};
