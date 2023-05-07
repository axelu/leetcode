
// 1419. Minimum Number of Frogs Croaking
// https://leetcode.com/problems/minimum-number-of-frogs-croaking/




class Solution {
public:
    int minNumberOfFrogs(string croakOfFrogs) {
        // 01234
        // croak

        // idea
        // we have 5 buckets in which we count the words that have been completed up to the respective letter
        // bucket
        // 0 c
        // 1 cr
        // 2 cro
        // 3 croa
        // 4 croak
        // if we find the letter 'o', we decrease bucket 1 and increase bucket 2

        int ans = 0;

        int bucket[5]; memset(bucket,0,sizeof bucket);

        for(char c: croakOfFrogs) {
            if( c == 'c' ) {
                ++bucket[0];
            } else if( c == 'r' ) {
                if( bucket[0] > 0 ) {
                    --bucket[0];
                    ++bucket[1];
                } else {
                    return -1;
                }
            } else if( c == 'o' ) {
                if( bucket[1] > 0 ) {
                    --bucket[1];
                    ++bucket[2];
                }
            } else if( c == 'a' ) {
                if( bucket[2] > 0 ) {
                    --bucket[2];
                    ++bucket[3];
                } else {
                    return -1;
                }
            } else { // c == 'k'
                if( bucket[3] > 0 ) {
                    --bucket[3];
                    ++bucket[4];
                } else {
                    return -1;
                }
                // the frog getting out the k just fished her croak
                // we know with that we have at least one frog
                // now we can count the number of frogs that are in the process
                // of croaking
                ans = max(ans,bucket[0]+bucket[1]+bucket[2]+bucket[3]+1);
            }
        }

        if( bucket[0] || bucket[1] || bucket[2] || bucket[3] ) // unfinished croaks
            return -1;

        return ans;
    }
};
