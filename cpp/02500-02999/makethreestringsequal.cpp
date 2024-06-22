
// 2937. Make Three Strings Equal
// https://leetcode.com/problems/make-three-strings-equal/




class Solution {
public:
    int findMinimumOperations(string s1, string s2, string s3) {
        if( s1[0] != s2[0] || s1[0] != s3[0] )
            return -1;
        
        int n1 = s1.size();
        int n2 = s2.size();
        int n3 = s3.size();
        
        int i = 1;
        for( ; i < n1 && i < n2 && i < n3; ++i)
            if( s1[i] != s2[i] || s1[i] != s3[i] )
                break;
        
        // up to and including position i we need to delete
        return n1-i + n2-i + n3-i;
    }
};
