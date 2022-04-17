
// 1898. Maximum Number of Removable Characters
// https://leetcode.com/problems/maximum-number-of-removable-characters/




class Solution {
private:
    int * del;
    int s_sz;

    void reset(vector<int>& removable, int k) {
        for(int i = 0; i < s_sz; ++i)
            del[i] = 0;
        for(int i = 0; i <= k; ++i)
            del[removable[i]] = 1;
    }

    bool isSubsequence(string& a, string& b) {
        // is string a a subsequence of string b?
        // del size == b.size
        // del indicates if char in b is deleted
        int an = a.size();
        int bn = b.size();

        int j = 0;
        for(int i = 0; i < bn && j < an; ++i)
            if( del[i] == 0 && a[j] == b[i] )
                j++;
        return j == an;
    }

    // binary search
    int search(string& s, string& p, vector<int>& removable, int b, int e) {
        // cout << "search b " << b << " e " << e << endl;
        if( b > e )
            return -1;

        int mid = b + ((e-b)/2);
        // cout << "  mid " << mid << endl;

        reset(removable,mid);
        bool f = isSubsequence(p,s);

        if( f ) {
            // can we do better?
            int t = search(s,p,removable,mid+1,e);
            return t != -1 ? t : mid;
        } else {
            return search(s,p,removable,b,mid-1);
        }
    }

public:
    int maximumRemovals(string& s, string& p, vector<int>& removable) {
        // p is a subseqence of of s
        int k = removable.size();

        s_sz = s.size();
        del = new int[s_sz];
        int ans = search(s,p,removable,0,k-1);
        delete []del;

        return ans + 1;
    }
};
