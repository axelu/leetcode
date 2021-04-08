
// 758. Bold Words in String
// https://leetcode.com/problems/bold-words-in-string/



class Solution {
public:
    string boldWords(vector<string>& words, string S) {
        int n = S.size();

        int mask[n]; memset(mask,0,sizeof mask);
        string::size_type f;
        string word;
        int wsz,idx;
        for(int i = 0; i < words.size(); ++i) {
            word = words[i];
            wsz = word.size();
            f = S.find(word);
            idx = 0;
            while( f != string::npos ) {
                for(int j = f; j < f+wsz; ++j)
                    mask[j] = 1;
                ++idx;
                if( idx >= n ) break;
                f = S.find(word,idx);
            }
        }

        // debug
        // for(int i = 0; i < n; ++i) cout << mask[i] << " ";
        // cout << endl;

        idx = 0;
        for(int i = 0; i < n; ++i) {
            if( i == 0 && mask[i] ) {
                // insert begin tag <b>
                S = "<b>" + S;
                idx += 3;
            } else if( i > 0 && mask[i] && !mask[i-1] ) {
                // insert begin tag <b>
                S = S.substr(0,idx) + "<b>" + S.substr(idx);
                idx += 3;
            } else if( i > 0 && !mask[i] && mask[i-1] ) {
                // insert end tag </b>
                S = S.substr(0,idx) + "</b>" + S.substr(idx);
                idx += 4;
            }
            if( i == n-1 && mask[i] ) {
                // insert end tag </b>
                S = S + "</b>";
            }
            ++idx;
        }

        return S;
    }
};
