

// 2746. Decremental String Concatenation
// https://leetcode.com/problems/decremental-string-concatenation/




class Solution {
private:
    int rec(vector<string>& words, int n, int i, int front, int back, int mem[][26][26]) {
        if( i == n )
            return 0;

        if( mem[i][front][back] != -1 )
            return mem[i][front][back];

        // we have a choice
        //    add current string to front OR
        //    add current string to the end
        int wordi_sz = words[i].size();
        int fronti = words[i][0] - 'a';
        int backi = words[i][wordi_sz-1] - 'a';

        int a;
        if( backi == front ) {
            a = (wordi_sz - 1) + rec(words,n,i+1,fronti,back,mem);
        } else {
            a = wordi_sz + rec(words,n,i+1,fronti,back,mem);
        }

        int b;
        if( back == fronti ) {
            b = (wordi_sz - 1) + rec(words,n,i+1,front,backi,mem);
        } else {
            b = wordi_sz + rec(words,n,i+1,front,backi,mem);
        }

        return mem[i][front][back] = min(a,b);
    }
public:
    int minimizeConcatenatedLength(vector<string>& words) {
        int n = words.size();
        int word0_sz = words[0].size();
        if( n == 1 )
            return word0_sz;

        int mem[n][26][26];memset(mem,-1,sizeof mem);

        return word0_sz + rec(words,n,1,words[0][0]-'a',words[0][word0_sz-1]-'a',mem);
    }
};
