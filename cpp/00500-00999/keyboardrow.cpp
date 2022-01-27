
// 500. Keyboard Row
// https://leetcode.com/problems/keyboard-row/



class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        //   char      a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z
        int kbRow[] = {2,3,3,2,1,2,2,2,1,2,2,2,3,3,1,1,1,1,2,1,1,3,1,3,1,3};

        vector<string> ans;
        int row;
        int m,j;
        for(int i = 0; i < words.size(); ++i) {
            row = kbRow[tolower(words[i][0])-'a'];
            m = words[i].size();
            j = 1;
            for(; j < m; ++j)
                if( row != kbRow[tolower(words[i][j])-'a'] )
                    break;
            if( j == m ) ans.push_back(words[i]);
        }
        return ans;
    }
};
