
// 916. Word Subsets
// https://leetcode.com/problems/word-subsets/
// day 26 March 2021 challenge
// https://leetcode.com/explore/featured/card/march-leetcoding-challenge-2021/591/week-4-march-22nd-march-28th/3685/




class Solution {
private:
    bool isSubset(string& a, string& b) {
        // are the letters in b a subset of the letters in a?
        int na = a.size();
        int nb = b.size();
        if( na < nb  ) return false;
        // assumes b is sorted !!!
        sort(a.begin(),a.end());
        if( na == nb ) return a == b;

        char cb;
        int j = 0;                    // idx in a
        for(int i = 0; i < nb; ++i) { // idx in b
            cb = b[i];
            // advance index in a to the same letter as we have in b
            while( a[j] != cb && j < na )
                ++j;
            if( j == na ) return false;
            ++j;
        }
        return true;
    }

public:
    vector<string> wordSubsets(vector<string>& A, vector<string>& B) {

        // preprocessing B
        // we are creating a string b that is sorted and each letter
        // appears the max times that it appeared in any string in B
        int arr[26]; memset(arr,0,sizeof arr);
        int c,n,l;
        for(int i = 0; i < B.size(); ++i) {
            sort(B[i].begin(),B[i].end());
            n = 0;
            l = B[i].size();
            for(int j = 0; j < l; ++j) {
                if( j == 0 )
                    c = B[i][j]-'a';
                if( B[i][j]-'a' != c ) {
                    arr[c] = max(arr[c],n);
                    c = B[i][j]-'a';
                    n = 0;
                }
                ++n;
                if( j == l-1 )
                    arr[c] = max(arr[c],n);
            }
        }
        string b = "";
        for(int i = 0; i < 26; ++i) {
            for(int j = 0; j < arr[i]; ++j) {
                b += i+'a';
            }
        }
        // cout << b << endl;

        vector<string> ans;
        string a;
        for(int i = 0; i < A.size(); ++i) {
            // cout << "a " << A[i] << endl;
            a = A[i];
            if( isSubset(a,b) ) ans.push_back(A[i]);
        }

        return ans;
    }
};
