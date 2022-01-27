
// 567. Permutation in String
// https://leetcode.com/problems/permutation-in-string/





class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int n1 = s1.size();
        int n2 = s2.size();
        
        if( n2 < n1 )
            return false;

        vector<int> cnt1(26,0);
        vector<int> cnt2(26,0);
        
        if( n1 == n2 ) {
            for(int i = 0; i < n1; ++i) {
                ++cnt1[s1[i]-'a'];
                ++cnt2[s2[i]-'a'];
            }
            return cnt1 == cnt2;
        }
        
        for(int i = 0; i < n1; ++i)
            ++cnt1[s1[i]-'a'];
        
        // sliding window of length n1 over s2
        for(int i = 0; i < n2; ++i) {
            ++cnt2[s2[i]-'a'];
            if( i < n1-1 )
                continue;
            
            if( cnt1 == cnt2 )
                return true;
        
            --cnt2[s2[i-(n1-1)]-'a'];
        }
        
        return false;
    }
};
