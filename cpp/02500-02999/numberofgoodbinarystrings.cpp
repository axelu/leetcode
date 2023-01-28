
// 2533. Number of Good Binary Strings
// https://leetcode.com/problems/number-of-good-binary-strings/


/*
 * 0 1 2 3 4 5 6
 * 1 1 1 


 */

class Solution {
private:
    int min_length,max_length,one_group,zero_group;
    
    long mod = 1000000007;
    
    long rec(int i, int last, int mem[][2]) {
        if( i > max_length )
            return 0;
        
        if( mem[i][last] != -1 )
            return mem[i][last];
        
        // at each position i we have a choice
        //   put zero_group 0s or
        //   put one_group 1s
        
        long ret = i >= min_length ? 1 : 0;
        
        ret = (ret + rec(i + zero_group,0,mem)) % mod;
        
        ret = (ret + rec(i + one_group,1,mem)) % mod;
        
        return mem[i][last] = ret;
        return ret;
    }
    
    
public:
    int goodBinaryStrings(int minLength, int maxLength, int oneGroup, int zeroGroup) {
        min_length = minLength;
        max_length = maxLength;
        one_group  = oneGroup;
        zero_group = zeroGroup;
        
        int mem[maxLength+1][2];memset(mem,-1,sizeof mem);
        
        return rec(0,0,mem);
    }
};
