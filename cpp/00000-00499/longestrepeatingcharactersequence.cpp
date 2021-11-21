

// 424. Longest Repeating Character Replacement
// https://leetcode.com/problems/longest-repeating-character-replacement/


class Solution {
private:
    // debug
    void printCnt(int cnt[]) {
        for(int i = 0; i < 26; ++i)
            cout << i << " " << cnt[i] << ";";
        cout << endl;
    }
    
    int* mem[26]; // sorted

    int lettersToChange() {
        // sort and put letter with most occurence 1st
        sort(mem,mem+26,[](int* a,int* b){return *a>*b;});
        // count all letters we would need to change
        int d = 0;
        for(int i = 1; i < 26; ++i)
            d += *(mem[i]);    
        return d;
    }
public:
    int characterReplacement(string s, int k) {
        int n = s.size();
        if( n == 1 ) return 1;
        if( k >= n-1 ) return n;
        
        int ans = k+1; // at minimum that is our answer
        
        int* idx[26]; // count for each letter
        for(int i = 0; i < 26; ++i) {
            int * a = new int(0);
            mem[i] = a;
            idx[i] = a;
        }
                    
        int d;
        int l = 0; // left index
        for(int i = 0; i < n; ++i) {
            // cout << "before i " << i << " l " << l << endl;
            ++*(idx[s[i]-'A']);
            // min sliding window size k+1
            if( i-l < k)
                continue;

            while( lettersToChange() > k ) {
                --*(idx[s[l]-'A']);   
                ++l;
            }

            ans = max(ans,i-l+1);
            // cout << "after  i " << i << " l " << l << " d " << d << " ans " << ans << endl;
        } 
        
        // TODO clean up
            
        return ans;
    }
};
