
// 30. Substring with Concatenation of All Words
// https://leetcode.com/problems/substring-with-concatenation-of-all-words/





class Solution {
private:
    // debug
    void printCnt(int A[]) {
        // debug
        for(int i = 0; i < 26; ++i) {
            char c = i+'a';
            cout << c << ":" << A[i] <<  " ";
        }
        cout << endl;
    }

    bool isEqual(int A[], int B[], int n) {
        for(int i = 0; i < n; ++i)
            if( A[i] != B[i] )
                return false;
        return true;
    }

public:
    vector<int> findSubstring(string& s, vector<string>& words) {
        int n = s.size();

        // all words have the same length
        int wl = words[0].size();
        int vn = words.size();
        int al = vn * wl;               // size of the window we need slide accross s

        if( n < al )
            return {};

        vector<int> ans;

        int cntW[26];memset(cntW,0,sizeof cntW);
        for(int i = 0; i < vn; ++i)
            for(int j = 0; j < wl; ++j)
                ++cntW[words[i][j]-'a'];
        // printCnt(cntW);


        // dictionary of unique words in words
        // key: word value: index,count
        unordered_map<string,array<int,2>> dic;
        pair<unordered_map<string,array<int,2>>::iterator,bool> p;
        int di = 0;
        for(int i = 0; i < vn; ++i) {
            p = dic.insert({words[i],{di,1}});
            if( !p.second )
                ++p.first->second[1];
            else
                ++di;
        }
        int uw = dic.size();    // number of unique words
        int cntU[uw];           // count of each unique word

        // cout << "number of unique words uw " << uw << endl;
        for(auto it = dic.begin(); it != dic.end(); ++it) {
            // cout << "word " << it->first << " idx " << it->second[0] << " count " << it->second[1] << endl;
            cntU[it->second[0]] = it->second[1];
        }


        int cntS[26];memset(cntS,0,sizeof cntS);

        int k;
        int i = 0;                      // left index
        for(int j = 0; j < n; ++j) {    // right index
            ++cntS[s[j]-'a'];

            if( j-i+1 < al )
                continue;
            // cout << "i: " << i << endl;
            // printCnt(cntS);

            // is the count of all letters the same?
            if( isEqual(cntS,cntW,26) ) {
                // a permutation of words could start at index i
                // cout << "potential at index " << i << endl;

                int cntH[uw];memset(cntH,0,sizeof cntH);
                bool fd = true;
                for(k = 0; k < al/wl; ++k) {
                    // cout << "checking at index " << i+k*wl << endl;
                    auto f = dic.find(s.substr(i+k*wl,wl));
                    if( f != dic.end() )
                        ++cntH[f->second[0]];
                    else {
                        fd = false;
                        break;
                    }
                }
                /*
                cout << "cntH" << endl;
                for(int p = 0; p < uw; ++p)
                    cout << "word idx " << p << " count " << cntH[p] << endl;
                */

                if( fd && isEqual(cntH,cntU,uw) )
                    ans.push_back(i);
            }

            // 'backtrack'
            --cntS[s[i]-'a'];
            ++i;
        }

        return ans;
    }
};
