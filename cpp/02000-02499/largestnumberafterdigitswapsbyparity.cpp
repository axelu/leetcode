
// 2231. Largest Number After Digit Swaps by Parity
// https://leetcode.com/problems/largest-number-after-digit-swaps-by-parity/



class Solution {
public:
    int largestInteger(int num) {
        string s = to_string(num);

        vector<int> odds;
        vector<int> evens;
        int n = s.size();
        int is_odd[n];memset(is_odd,0,sizeof is_odd);
        for(int i = 0; i < n; ++i) {
            int x = s[i]-'0';
            if( x % 2 == 0 ) {
                evens.push_back(x);
            } else {
                odds.push_back(x);
                is_odd[i] = 1;
            }
        }
        sort(begin(odds),end(odds),greater<int>());
        sort(begin(evens),end(evens),greater<int>());

        int idx_odd = 0, idx_even = 0;
        for(int i = 0; i < n; ++i)
            if( is_odd[i] )
                s[i] = odds[idx_odd++]+'0';
            else
                s[i] = evens[idx_even++]+'0';

        return stoi(s);
    }
};
