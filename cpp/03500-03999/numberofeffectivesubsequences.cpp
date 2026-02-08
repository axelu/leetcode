
// 3757. Number of Effective Subsequences
// https://leetcode.com/problems/number-of-effective-subsequences/


/*  using 2** notation for power with base 2, to avoid confusion with XOR ^
   
    working through an example nums = [3,15,9,1,13] => ans = 12
    nums.size() = n = 5
    bit bit  0  1  2  3  4
    idx val  3 15  9  1 13
    ----------------------
     0   1   1  1  1  1  1
     1   2   1  1  0  0  0
     2   4   0  1  0  0  1
     3   8   0  1  1  0  1
    as a first step let us agree that bits that are either set or not set for all indices,
    those bits don't matter and hence we will remove those bits.
    nums after that step:
    bit bit  0  1  2  3  4
    idx val  1  7  4  0  6
    ----------------------
     0   1   1  1  0  0  0
     1   2   0  1  0  0  1
     2   4   0  1  1  0  1
    we can make a total of 2**5 = 32 subsequences including the empty subsequence.
    the goal is to find the "effective subsequences", the ones that reduce the OR of its elements.
    that means for a given bit, all the indices where that bit is set need to be removed, and
    the remaining elements can be freely chosen.
    let us take bit 0 as an example, we get the following "effective subsequences" (using indices)
    [0,1],[0,1,2],[0,1,3],[0,1,4],[0,1,2,3][,0,1,2,4],[0,1,3,4],[0,1,2,3,4]
    to better visualize
    0 1 2 3 4  0 1 2 3 4  0 1 2 3 4  0 1 2 3 4  0 1 2 3 4  0 1 2 3 4  0 1 2 3 4  0 1 2 3 4
    x x        x x x      x x   x    x x     x  x x x x    x x x   x  x x   x x  x x x x x
                                     ---------             ---------  ---------  ---------
    let us take bit 1 as an example
    0 1 2 3 4  0 1 2 3 4  0 1 2 3 4  0 1 2 3 4  0 1 2 3 4  0 1 2 3 4  0 1 2 3 4  0 1 2 3 4
      x     x  x x     x    x x   x    x   x x  x x x   x  x x   x x    x x x x  x x x x x   
               ---------                        ---------  ---------             ---------
    as we can see, we are double counting (underlined) where a given index has bit0 and bit1 set
    this is classical inclusion-exclusion principle, very specifcally subtraction principle
    res = 2**totalelements 
             - (2**elementswithproperty0 + 2**elementswithproperty1 ...)      // elements with 1 property
             + (2**elementswithproperty01 + 2**elementswithproperty02) ...)   // elements with 2 properties
             - (1**elementswithproperty012 >>)                                // elements with 3 properties
             ...
    property here is meant to be generic, in our case property 0 is bit 0, ans so on.
    so in our example, index 1 with val 7 contributes to:
    bit0, bit1, bit2, bit01, bit02, bit12, bit012
    this is the key insight !!!
    so for every index, we need to count its contribution to every binary subset it represents.
    how? this is where Sum of Subsets comes in. check SOS resources below to understand
    this line is the key:
            for(int j = x; j > 0; j = (j - 1) & x)
                ++cnt[j];
    if x = 7, j will take the following values: 7, 6, 4, 3, 2, 1
    if x = 6, j will take the following values: 6, 4, 2
    this allows us to iterate fast through all binary subsets of a given value.

    now we can apply inclusion-exclusion principal by subtracting the count of subsets with odd bit number
    and adding counts of subsets with even bit numbers.

    for simplicity, we flip the bits, in essence counting ineffective subsequences and then
    subtracting those in the end from the total to get the number of effective subsequences.

    resources:
    Sum of Subsets Dynamic Programming SOS DP
    https://www.geeksforgeeks.org/dsa/sum-subsets-dynamic-programming/
    https://usaco.guide/plat/dp-sos?lang=cpp
    Inclusion-Exclusion Principle very specifically subtraction principle
    Introductory Combinatorics (fifth edition) by Richard A. Brualdi Chapter 6

*/

// initialize once
long pow2[100001];
int popcnt[1048576];
bool init = false;

class Solution {    
private:
    int countSetBits(int i) {
        int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    const long mod = 1000000007L;

    // exponention using bit manipulation
    long modular_pow(long base, long exponent) {
        
        long ret = 1;

        while(exponent > 0) {

            int last_bit = (exponent & 1);
            if( last_bit )
                ret = (ret * base) % mod;

            base = (base * base) % mod;

            exponent = exponent >> 1;
        }

        return ret % mod;
    }    

    pair<int,int> built_masks(int curbit, int maxbit) {
        int lo_mask = 0; // mask with bits 0..i-1 set
        for(int k = 0; k <= curbit-1; ++k)
            lo_mask |= (1<<k);
        int hi_mask = 0; // masks with bits i+1..maxbit set
        for(int k = curbit+1; k <= maxbit; ++k)
            hi_mask |= (1<<k);
        return {lo_mask, hi_mask};
    }

public:
    int countEffective(vector<int>& nums) {
        // constraints
        // 1 <= nums.size() <= 1e5; 
        // 1 <= nums[i] <= 1e6
        // decimal 1e6 => binary 11110100001001000000 (20 digits, bits 0..19)
        //                binary 11111111111111111111 => decimal 1048575
        if( !init ) {
            for(int i = 0; i <= 100000; ++i)
                pow2[i] = modular_pow(2, i);
            for(int i = 0; i <= 1048575; ++i)
                popcnt[i] = countSetBits(i);
            init = true;
        }

        int nums_sz = nums.size(); 
        
        // get max bit, 0 indexed
        int maxbit = 0;
        for(int i = 0; i < nums_sz; ++i) {
            for(int j = 19; j > maxbit; --j)
                if( nums[i] & (1<<j) )
                    maxbit = j;
            if( maxbit == 19 )
                break;
        }
        // cout << "maxbit " << maxbit << endl;

        // prune 
        // eliminate bits where for all nums[i] the bit is set or unset
        for(int i = 0; i <= maxbit; ) {
            int mask = 1<<i;
            int cnt = 0;
            for(int j = 0; j < nums_sz; ++j)
                cnt += nums[j] & mask ? 1 : 0;

            if( cnt == nums_sz || cnt == 0 ) {
                // every nums[i] has the ith bit either set or unset
                if( i == 0 && maxbit == 0 )
                    break;
                
                auto [lo_mask ,hi_mask] = built_masks(i, maxbit);
                for(int j = 0; j < nums_sz; ++j) {
                    int lo_j = nums[j] & lo_mask;
                    int hi_j = nums[j] & hi_mask; hi_j >>= 1;
                    nums[j] = lo_j + hi_j;
                }
                
                --maxbit;
                continue;
            }
            ++i;
        }
        // for(int x : nums)
        //     cout << x << " ";
        // cout << endl;
        // cout << "maxbit " << maxbit << endl;

        // flip all
        int supermask = (1<<(maxbit+1)) - 1; // cout << "supermask " << supermask << endl;
        for(int i = 0; i < nums_sz; ++i)
            nums[i] ^= supermask;
        // for(int x : nums)
        //     cout << x << " ";
        // cout << endl;


        unordered_map<int,int> um; // dedup; key: x, value: count
        for(int i = 0; i < nums_sz; ++i)
            ++um[nums[i]];

        int mx = 0;                                 //   98765432109876543210
        long cnt[1048576];memset(cnt,0,sizeof cnt); // 0b11111111111111111111 -> decimal 1048576
        // for(int i = 0; i < nums_sz; ++i) {
        for(auto p : um) {
            // int x = nums[i];
            int x = p.first;
            // sum of subsets (SOS): this is the key!!! it only iterates of bitwise subsets !!!
            for(int j = x; j > 0; j = (j - 1) & x) {
                // ++cnt[j];
                cnt[j] += p.second;
            }
            mx = max(mx, x);
        }

        long res = pow2[nums_sz];
        for(int i = 1; i <= supermask; ++i) {
            long a = pow2[cnt[i]];
            if( popcnt[i] % 2 ) {
                res = res - a;
                if( res < 0 ) res += mod;
            } else {
                res = (res + a) % mod;
            }
        }
        long ret = pow2[nums_sz] - res;
        if( ret < 0 ) ret += mod;
        return ret;
    }
};


// no caching
// passes 987/1041 test cases, then TLE
// tried various ways to optimize, but didn't get it to pass

// initialize once
long pow2[100001];
bool init = false;

class Solution {
private:
    const long mod = 1000000007L;
    int nums_sz;
    int maxbit; // 0-indexed

    // debug
    void printbits(vector<int>& nums) {
        int n = nums.size();

        cout << "  ";
        for(int j = 0; j < n; ++j)
            cout << j << " ";
        cout << endl;
        for(int i = 0; i <= maxbit; ++i) {
            cout << i << " ";
            for(int j = 0; j < n; ++j)
                if( nums[j] & (1<<i) )
                    cout << 1 << " ";
                else
                    cout << 0 << " ";
            cout << endl;
        }
    }

    pair<int,int> built_masks(int curbit, int maxbit) {
        int lo_mask = 0; // mask with bits 0..i-1 set
        for(int k = 0; k <= curbit-1; ++k)
            lo_mask |= (1<<k);
        int hi_mask = 0; // masks with bits i+1..maxbit set
        for(int k = curbit+1; k <= maxbit; ++k)
            hi_mask |= (1<<k);
        return {lo_mask, hi_mask};
    }

    // exponention using bit manipulation
    long modular_pow(long base, long exponent) {

        long ret = 1;

        while(exponent > 0) {

            int last_bit = (exponent & 1);
            if( last_bit )
                ret = (ret * base) % mod;

            base = (base * base) % mod;

            exponent = exponent >> 1;
        }

        return ret % mod;
    }

    // map<multiset<int>, long> mem[20];
    // map<vector<int>, long> mem[20];
    stack<int> park;

    long rec(vector<int>& nums, int bitidx) {
    // long rec(multiset<int>& nums, int bitidx) {
        // string fll(depth, ' ');
        // cout << fll; cout << "rec bitidx " << bitidx << endl;

        int n = nums.size(); // guaranteed != 0
        long ret = 0L;

        if( bitidx == maxbit ) {
            int nonsetbits = 0;
            for(int x: nums)
                if( !((1<<bitidx) & x) ) ++nonsetbits;
            ret = pow2[nonsetbits] - 1;
            if( ret < 0 ) ret += mod;
            // cout << fll; cout << "rec bitidx " << bitidx << " at maxbit ret " << ret << endl;
            return ret;
        }

        // prune
        /*
        if( n == 1 ) {
            for(int i = bitidx; i <= maxbit; ++i)
               if( !(nums[0] & (1<<bitidx)) ) return 1L;
            return 0L;
        }
        */
        /*
        auto f = mem[bitidx].find(nums);
        if( f != mem[bitidx].end() ) {
            ++hitcounter;
            return f->second;
        }
        */

        // exclude: remove all elements from nums where bit bididx is set
        int parked = 0;
        for(auto it = nums.begin(); it != nums.end(); ) {
            if( (1<<bitidx) & *it ) {
                park.push(*it);
                ++parked;
                it = nums.erase(it);
            } else {
                ++it;
            }
        }
        // theoritically, we can get
        // nums.size() = n - ((2e(park.size())) - 1)
        if( nums.size() > 0 ) {

            ret = pow2[nums.size()] - 1;
            if( ret < 0 ) ret += mod;
            // cout << fll; cout << "rec bitidx " << bitidx << " excl " << endl;
            long exclude = rec(nums, bitidx + 1);
            // cout << fll; cout << "rec bitidx " << bitidx << " excl " << exclude << endl;
            ret = ret - exclude; // TODO mod
            if( ret < 0 ) ret += mod;
        }
        // backtrack
        while( parked > 0 ) {
            nums.push_back(park.top());
            // nums.insert(park.top());
            park.pop();
            --parked;
        }
        // sort for keying or use multiset
        // TODO sort on inserting
        // sort(begin(nums), end(nums));

        // include
        // cout << fll; cout << "rec bitidx " << bitidx << " incl " << endl;
        long include = rec(nums, bitidx + 1);
        // cout << fll; cout << "rec bitidx " << bitidx << " incl " << include << endl;
        ret = (ret + include) % mod;

        // cout << fll; cout << "rec bitidx " << bitidx << " ret " << ret << endl;
        return ret;
        // return mem[bitidx][nums] = ret;
    }

public:
    int countEffective(vector<int>& nums) {
        if( !init ) {
            for(int i = 0; i <= 100000; ++i)
                pow2[i] = modular_pow(2, i);
            init = true;
        }

        nums_sz = nums.size(); // 1 <= n <= 1e5; 1 <= nums[i] <= 1e6
        // decimal 1e6 => binary 11110100001001000000 (20 digits)

        // or just sort and get rightmost set bit of max value
        maxbit = 0;
        for(int i = 0; i < nums_sz; ++i) {
            for(int j = 19; j > maxbit; --j)
                if( nums[i] & (1<<j) )
                    maxbit = j;
            if( maxbit == 19 )
                break;
        }
        // cout << "maxbit " << maxbit << endl;
        // printbits(nums);


        // prune
        // eliminate bits where for all nums[i] the bit is set or unset
        for(int i = 0; i <= maxbit; ) {
            int mask = 1<<i;
            int cnt = 0;
            for(int j = 0; j < nums_sz; ++j)
                cnt += nums[j] & mask ? 1 : 0;

            if( cnt == nums_sz || cnt == 0 ) {
                // every nums[i] has the ith bit either set or unset
                if( i == 0 && maxbit == 0 )
                    break;

                auto [lo_mask ,hi_mask] = built_masks(i, maxbit);
                for(int j = 0; j < nums_sz; ++j) {
                    int lo_j = nums[j] & lo_mask;
                    int hi_j = nums[j] & hi_mask; hi_j >>= 1;
                    nums[j] = lo_j + hi_j;
                }

                --maxbit;
                continue;
            }
            ++i;
        }
        // cout << "maxbit " << maxbit << endl;
        // printbits(nums);

        //multiset<int> ms(begin(nums), end(nums));

        // long ans = 1L; // removing all elements is one option

        long ans = rec(nums, 0) + 1;
        // long ans = rec(ms, 0) + 1;
        // ans = ans % mod;
        return ans;
    }
};



// naive top-down memoization, does not scale respectively will end in TLE
// does give correct results, not submitted

class Solution {
private:
    const long mod = 1000000007L;
    int maxbit = 19; // 0-indexed

    map<vector<int>,long> mem;

    long rec(vector<int>& nums, int n, int pos, vector<int>& bits) {
        if( pos == n ) {
            for(int i = 0; i <= maxbit; ++i)
                if( bits[i] == 0 )
                    return 1;
            return 0;
        }

        vector<int> key = bits; key.push_back(pos);
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;

        // we have a choice
        //     exclude position OR
        //     include pos

        long ret = 0L;

        // if we exclude nums[pos] we could get (2e remaining)-1 subsequences
        // does excluding nums[pos] reduce OR, said differently
        // does excluding nums[pos] reduce the count of a bit to zero?
        long a = rec(nums, n, pos+1, bits);

        int x = nums[pos];
        int i = 0;
        while(x) {
            if( x & 1 ) {
                --bits[i];
            }
            x >>= 1;
            ++i;
        }
        long b = rec(nums, n, pos+1, bits);
        // backtrack
        x = nums[pos];
        i = 0;
        while(x) {
            if( x & 1 )
                ++bits[i];
            x >>= 1;
            ++i;
        }

        return mem[key] = a + b;
    }

public:
    int countEffective(vector<int>& nums) {
        int n = nums.size(); // 1 <= n <= 1e5; 1 <= nums[i] <= 1e6
        // decimal 1e6 => binary 11110100001001000000 (20 digits)

        long ans = 1L; // removing all elements is one option

        vector<int> bits(20, 0);
        for(int j = 0; j < n; ++j) {
            int x = nums[j];
            int i = 0;
            while(x) {
                if( x & 1 ) {
                    ++bits[i];
                }
                x >>= 1;
                ++i;
            }
        }
        for(int i = 0; i <=maxbit; ++i)
            if( bits[i] == 0 )
                bits[i] = 1;

        return rec(nums, n, 0, bits);
    }
};
