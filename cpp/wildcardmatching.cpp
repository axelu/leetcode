
// 44. Wildcard Matching
// https://leetcode.com/problems/wildcard-matching/




// see also 10. Regular Expression Matching
// https://leetcode.com/problems/regular-expression-matching/


class Solution {
private:
    int sn,pn;
    
    bool rec(const string& s, int i, const string& p, int j, int* mem) {
        // i = index in s
        // j = index in p
        // cout << "i " << i << " j " << j << endl;
        
        if( i < 0 && j < 0 )
            return true;
        
        if( i >= 0 && j < 0 )
            return false;
        
        if( i < 0 && j >= 0 ) {
            // there could be an acceptable prefix in the pattern
            // like *'s
            while( j >= 0 ) {
                if( p[j] != '*' )
                    return false;
                --j;
            }
            return true;
        }
        
        int memIdx = i*pn+j;
        if( mem[memIdx] != -1 )
            return mem[memIdx];
        
        bool ret = false;
        
        if( p[j] == '*' ) {
            // stay put in s and advance in pattern first
            // then try advancing in s and stay put in pattern
            // a * means 0 or more
            ret = rec(s,i-1,p,j,mem) || rec(s,i,p,j-1,mem);
        } else {
            if( p[j] == '?' || s[i] == p[j] )
                ret = rec(s,i-1,p,j-1,mem);  
        }
                
        return mem[memIdx] = ret;
    }
    
    
public:
    bool isMatch(string s, string p) {
        sn = s.size();
        pn = p.size();

        
        // handle cases where either sn and/or pn is 0
        if( sn == 0 && pn == 0 )
            return true;
        if( pn == 0 )
            return false;
        if( sn == 0 ) {
            for(int j = 0; j < pn; ++j)
                if( p[j] != '*' )
                    return false;
            return true;
        }
            
        // different than compared to problem 10. Regular Expression Matching
        // we will start from the back this time

        int mem[sn*pn];memset(mem,-1,sizeof mem);
        
        return rec(s,sn-1,p,pn-1,mem);
    }
};
