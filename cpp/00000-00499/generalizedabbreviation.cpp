
// 320. Generalized Abbreviation
// https://leetcode.com/problems/generalized-abbreviation/





class Solution {
private:
    int n;
    
    void printBinary(int x) {
        for(int i = n-1; i >= 0; --i) {
            if( x & (1 << i) ) cout << 1;
            else cout << 0;
        }
        cout << endl;
    }

public:
    vector<string> generateAbbreviations(string word) {
        n = word.size(); // 1 <= word.length <= 15
        
        // we will use a bitmask to indicate replaced letters
        // 0 indicates letter, 1 indicates replaced
        
        vector<string> ans;
        string t = "";
        int cnt,prev;
        for(int i = 0; i <= pow(2,n)-1; ++i) {
            // printBinary(i);
            
            t.clear();
            cnt = 0;
            prev = 0;
            for(int j = n-1; j >= 0; --j) {
                if( i & (1 << j) ) {
                    ++cnt;
                    prev = 1;
                } else {
                    if( prev == 1 ) {
                        t += to_string(cnt);
                        cnt  = 0;
                        prev = 0;
                    }
                    t.push_back(word[n-1-j]);
                }
            }
            if( prev == 1 )
                t += to_string(cnt);
            
            ans.push_back(t);
        }
        
        return ans;
    }
};
