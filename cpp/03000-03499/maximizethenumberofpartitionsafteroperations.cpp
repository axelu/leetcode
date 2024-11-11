
// 3003. Maximize the Number of Partitions After Operations
// https://leetcode.com/problems/maximize-the-number-of-partitions-after-operations/




class Solution {
private:
    // debug
    void printBinary(long x, int c) {
        for(int i = c-1; i >= 0; --i) {
            if( x & (1UL << i) ) cout << 1;
            else cout << 0;
        }
        // cout << endl;
    }

    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    // key i, mask, can_change
    // i max = 10000 -> binary 10011100010000 14 digts
    // mask max 11111111111111111111111111 26 digits
    //          zyxwvutsrqponmlkjihgfedcba
    // can_change 1 digit
    unordered_map<long, int> mem;

    int rec(string& s, long i, int k, int mask, bool can_change) {
        // cout << "rec i " << i << " mask ";printBinary(mask,26); cout << " can_change " << can_change << endl;

        if( i == s.size() )
            return 1;

        long key = (i<<27) + (mask<<1) + can_change;
        auto f = mem.find(key);
        if( f != mem.end() )
            return f->second;


        // we have a choice
        //     don't change the character at the current OR
        //     change the character at the current index (if we can)

        int c = s[i] - 'a';

        int ret;

        int mask_new = mask | (1<<c);
        int unique = countSetBits(mask_new);
        if( unique > k ) {
            // we must start a new partition at the current index i
            ret = 1 + rec(s, i+1, k, (1<<c), can_change);
        } else {
            ret = rec(s, i+1, k, mask_new, can_change);
        }

        if( can_change ) {
            for(int chr = 0; chr < 26; ++chr) {
                if( chr == c )
                    continue;
                mask_new = mask | (1<<chr);
                unique = countSetBits(mask_new);
                if( unique > k ) {
                    // we must start a new partition at the current index i
                    ret = max(ret, 1 + rec(s, i+1, k, (1<<chr), false));
                } else {
                    ret = max(ret, rec(s, i+1, k, mask_new, false));
                }
            }
        }

        return mem[key] = ret;
    }



public:
    int maxPartitionsAfterOperations(string s, int k) {
        int n = s.size();

        // brute force top down dp
        return rec(s, 0, k, 0, true);
    }
};
