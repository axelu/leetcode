
// 10. Regular Expression Matching
// https://leetcode.com/problems/regular-expression-matching/




class Solution {
    int sn,pn;
    int mem[20][30];
    
    bool rec(string& s, int i, string& p, int j) {
        // i = index in s
        // j = index in p
        // cout << "i " << i << " j " << j << endl;
        
        if( i == sn && j == pn )
            return true;
        
        if( i != sn && j == pn )
            return false;
        
        if( i == sn && j != pn ) {
            // there could be an acceptable tail in the pattern
            // like .* or <char>* one or more times
            if( (pn-j)%2 != 0 )
                return false;

            while( j+1 < pn ) {
               if( p[j+1] != '*' )
                   return false;
                j += 2;
            }
            return true;
        }
        
        if( mem[i][j] != -1 ) {
            // cout << "i " << i << " j " << j << " result " << mem[i][j] << " hit" << endl;
            return mem[i][j];
        }
        
        bool ret = false;
        
        // advance in string s as far as we can
        // if that has no success, then it is a fail

        
        // peek forward in pattern
        // a * means 0 or more of the preceding char
        if( j < pn-1 && p[j+1] == '*' ) {
            // stay put in s and advance in pattern first
            ret = rec(s,i,p,j+2);
            
            // p[j] could be a certain char OR a .
            // if p[j] is a char, it could match s[i] or not
            /*if( !ret && p[j] == '.' ) {
                while( i < sn ) {
                    if( rec(s,i+1,p,j+2) ) {
                        ret = true;
                        break;
                    }
                    ++i;
                }
            } else if( !ret ) {
                while( s[i] == p[j] ) {
                    if( rec(s,i+1,p,j+2) ) {
                        ret = true;
                        break;
                    }
                    ++i;
                }
            }*/
            
            if( !ret && (p[j] == '.' || s[i] == p[j]) )
                ret = rec(s,i+1,p,j);
            
        } else {
            if( p[j] == '.' || s[i] == p[j] )
                ret = rec(s,i+1,p,j+1);            
        }
        
        //cout << "i " << i << " j " << j << " result " << ret << endl;
        return mem[i][j] = ret;
    }    
    
    
public:
    bool isMatch(string s, string p) {
        sn = s.size();
        pn = p.size();
        
        // there has to be a path through s and p that brings us
        // to the end of both
        
        for(int i = 0; i < sn; ++i)
            for(int j = 0; j < pn; ++j)
                mem[i][j] = -1;
        
        return rec(s,0,p,0);
    }
};
