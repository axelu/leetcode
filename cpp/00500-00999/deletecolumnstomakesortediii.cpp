
// 960. Delete Columns to Make Sorted III
// https://leetcode.com/problems/delete-columns-to-make-sorted-iii/



class Solution {
private:
    int n,m;
    int mem[100][101]; // pos, lst_idx + 1

    int rec(vector<string>& strs, int pos, int lst_idx) {
        // pos = current position in strs[k][i] where 0 <= k < n
        // lst_idx is the lst_idx that we kept or -1 if we didn't keep any so far

        if( pos == m )
            return 0;

        if( mem[pos][lst_idx+1] != -1 )
            return mem[pos][lst_idx+1] ;

        // we have a choice
        //    keep the char(s) at the current pos if we can
        //        meaning if strs[0][lst_idx] <= strs[0][pos],...,strs[n-1][lst_idx] <= strs[n-1][pos] OR
        //    delete the char(s) at the current pos

        // keep
        int a = m;
        if( lst_idx == -1 ) {
            a = rec(strs,pos+1,pos);
        } else {
            bool can_keep = true;
            for(int i = 0; i < n; ++i)
                if( strs[i][lst_idx] > strs[i][pos] ) {
                    can_keep = false;
                    break;
                }
            if( can_keep )
                a = rec(strs,pos+1,pos);
        }

        // delete
        int b = 1 + rec(strs,pos+1,lst_idx);

        return mem[pos][lst_idx+1] = min(a,b);
    }


public:
    int minDeletionSize(vector<string>& strs) {
        n = strs.size();
        m = strs[0].size();

        memset(mem,-1,sizeof mem);
        return rec(strs,0,-1);
    }
};
