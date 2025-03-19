
// 3145. Find Products of Elements of Big Array
// https://leetcode.com/problems/find-products-of-elements-of-big-array/



class Solution {
private:
    vector<long long> powerfularray(long long x) {
        // it is guaranteed that x > 0
        vector<long long> ret;

        int i = 1;
        long long pow = 1LL;
        while( x ) {
            if( x & 1LL )
                ret.push_back(pow);
            ++i;
            pow *= 2LL;
            x >>= 1LL;
        }

        return ret;
    }

    // exponention using bit manipulation
    long modular_pow(long long base, long long exponent, long long mod) {

        long long ret = 1;

        while(exponent > 0LL) {

            int last_bit = (exponent & 1LL);
            if( last_bit )
                ret = (ret * base) % mod;

            base = (base * base) % mod;

            exponent = exponent >> 1LL;
        }

        return ret % mod;
    }

    long long countSetBitsOneToX(long long x) {
        ++x;
        long long ret = 0LL;
        for (long long i = 0LL; (1LL<<i) < x; ++i) { // the ith bit
            // at ith bit, pattern of 1s and 0s repeats after 2^(i+1)
            // each repeating section contains 2^i ones
            // x/(2^(i+1)) gives number of complete repeating sections
            // take times 2^i to get total ones in ccomplete repeating sections
            long long cnt = (x >> (i+1)) << i;

            // there could be an incomplete repeating section remaining
            // if x has ith bit set
            if( (x>>i) & 1LL )
                // count ones in remainder
                // x & (2^i-1) gives remainder after last complete period
                cnt += x & ((1LL<<i) - 1LL);

            ret += cnt;
        }

        return ret;
    }

    long long getBitSumOneToX(long long x) {
        ++x;
        long long ret = 0LL;
        for (long long i = 0LL; (1LL<<i) < x; ++i) { // the ith bit
            // at ith bit, pattern of 1s and 0s repeats after 2^(i+1)
            // each repeating section contains 2^i ones
            // x/(2^(i+1)) gives number of complete repeating sections
            // take times 2^i to get total ones in ccomplete repeating sections
            long long cnt = (x >> (i+1)) << i;

            // there could be an incomplete repeating section remaining
            // if x has ith bit set
            if( (x>>i) & 1LL )
                // count ones in remainder
                // x & (2^i-1) gives remainder after last complete period
                cnt += x & ((1LL<<i) - 1LL);

            ret += cnt * i;
        }

        return ret;
    }

    long long getValueAtIndex(long long i) {
        ++i;
        long long s = 1LL;
        long long e = 1LL<<50;

        while( s < e ) {
            long long mid = s + ((e-s)/2LL);
            if( countSetBitsOneToX(mid) < i ) {
                s = mid + 1LL;
            } else {
                e = mid;
            }
        }
        return s;
    }


public:
    vector<int> findProductsOfElements(vector<vector<long long>>& queries) {
        // powerful array of a non-negative integer x is defined as the
        // shortest sorted array of powers of two that sum up to x.
        // powerfularray(x) = shortest sorted array of powers of two that sum up to x
        // powers of two: 1, 2, 4, 8, 16, ...

        /*
        auto pa = powerfularray(1000000000000000);
        for(long long pow: pa)
            cout << pow << " ";
        cout << endl;
        */

        /*  powerfularray(1) = [1]
            powerfularray(2) = [2]
            powerfularray(3) = [1,2]
            powerfularray(4) = [4]
            powerfularray(5) = [1,4]
            powerfularray(6) = [2,4]
            powerfularray(7) = [1,2,4]
            ...
            index       0  1  2  3  4  5  6  7  8  9 10 11
            big_nums = [1, 2, 1, 2, 4, 1, 4, 2, 4, 1, 2, 4...]
                        -  -  ----  -  ----  ----  -------
            decimal     1  2   3    4    5     6      7
                        -  -  ----  -  ----  ----  -------
            pow2 exp    0  1  0  1  2  0  2  1  2  0  1  2 = bit

            observation:
            take range 2...5: the product is 8 = 1*2*4*1
            the sum of pow2 exp is 3 = 0+1+2+0 -> 2^3 = 8
            so our problem becomes a prefix sum problem of the pow2 exp
            as we can simply do modular power if we
            knew how many bits are set in range
            lets take a leap:
            bit     3 2 1 0    set    running count
                    8 4 2 1    bits   of set bits
                    --------  -----   -------------
                0   0 0 0 0       0    0
                1   0 0 0 1       1    1
                2   0 0 1 0       1    2
                3   0 0 1 1       2    4
                4   0 1 0 0       1    5
                5   0 1 0 1       2    7
                6   0 1 1 0       2    9
                7   0 1 1 1       3   12
                8   1 0 0 0       1   13

            so we could find the value covering the index we are after
            because for a given value, we can find the number of set bits
            from 1 till that value, wich is our index
        */

        int q_sz = queries.size();
        vector<int> ans(q_sz);
        for(int i = 0; i < q_sz; ++i) {
            long long lft = queries[i][0] - 1LL;
            long long rgt = queries[i][1];
            long long mod = queries[i][2];

            long long a = getValueAtIndex(lft);
            // cout << "index lft " << lft << " is occupied by value " << a << endl;
            // the value will occupy a range of indices including left
            // example 7 which occupies indices 9..11
            // index       0  1  2  3  4  5  6  7  8  9 10 11
            // big_nums = [1, 2, 1, 2, 4, 1, 4, 2, 4, 1, 2, 4...]
            //             -  -  ----  -  ----  ----  -------
            // decimal     1  2   3    4    5     6      7
            // so we need to get the bit count of next lower, and then
            // we will add bits till we reach our index
            long long a_bitsum = getBitSumOneToX(a-1); // cout << "a_bitsum before " << a_bitsum << endl;
            long long a_bitcnt = countSetBitsOneToX(a-1); // cout << "a_bitcnt before " << a_bitcnt<< endl;
            for(long long j = 0; a_bitcnt < lft+1LL; ++j) { // +1 because index is zero based
                if( a & (1LL<<j) ) {
                    a_bitsum += j;
                    ++a_bitcnt;
                }
            }
            // cout << "a_bitsum after  " << a_bitsum << endl;
            // cout << "prefix_sum_1 " << prefix_sum_1 << endl;
            // cout << "a_bitcnt after  " << a_bitcnt<< endl;

            long long b = getValueAtIndex(rgt);
            long long b_bitsum = getBitSumOneToX(b-1);
            long long b_bitcnt = countSetBitsOneToX(b-1);
            for(long long j = 0; b_bitcnt < rgt+1LL; ++j) { // +1 because index is zero based
                if( b & (1LL<<j) ) {
                    b_bitsum += j;
                    ++b_bitcnt;
                }
            }
            // cout << "b_bitsum after  " << b_bitsum << endl;

            ans[i] = modular_pow(2LL, b_bitsum - a_bitsum, mod);
        }

        return ans;
    }
};
