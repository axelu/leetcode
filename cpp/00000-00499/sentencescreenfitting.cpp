
// 418. Sentence Screen Fitting
// https://leetcode.com/problems/sentence-screen-fitting/


class Solution {
private:
    int mem[100][2];

    void solve(vector<int>& v, int n, int k, int cols) {
        // returns number of times we fit the sentence on a row
        // starting from pos k in the sentence and at which position
        // in the sentence the next row would start

        if( mem[k][0] != -1 )
            return;

        int cnt = 0;
        int i = 0;      // start at pos 0
        int curr_k = k;
        while(true) {
            // try to put word k onto the line
            i += v[curr_k];
            if( i > cols ) // word did not fit on the remainder of the line
                break;

            // advance word
            ++curr_k;
            // if we finish a sentence, count that
            if( curr_k == n ) {
                ++cnt;
                curr_k = 0;
            }

            ++i; // seperating space
        }

        mem[k][0] = cnt;
        mem[k][1] = curr_k;
        return;
    }


public:
    int wordsTyping(vector<string>& sentence, int rows, int cols) {

        // we will fit as many words as we can on a given line
        // what we can remember is, if we start a new line and are at pos x
        // in our sentence, we can know our best option to start the next line

        // assumptions
        //    - words have to be seperated by a single space
        //    - max(sentence[i].size()) <= cols
        //    - sentence[0].size() + 1 + sentence[1].size() + 1 ... + sentence[n-1].size() <= rows*cols
        //      but it could be every word goes on one line, so no spaces

        int n = sentence.size();
        vector<int> v(n);
        for(int i = 0; i < n; ++i) {
            int t = sentence[i].size();
            if( t > cols )          // a given word has to fit on a line
                return 0;
            v[i] = t;
        }

        // we have three cases
        // 1 one or more sentences will fit on one line, next line starts a new sentence
        // 2 one or more sentences and some words fit on one line, next line starts at some word
        // 3 a sentence does not fit on one line, next line starts at some word

        int ans = 0;
        memset(mem,-1,sizeof mem);
        int k = 0; // position in sentence
        for(int i = 0; i < rows; ++i) {
            solve(v,n,k,cols);
            ans += mem[k][0];
            k = mem[k][1];
        }

        return ans;
    }
};
