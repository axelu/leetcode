
// 2269. Find the K-Beauty of a Number
// https://leetcode.com/problems/find-the-k-beauty-of-a-number/



class Solution {
public:
    int divisorSubstrings(int num, int k) {
        string s = to_string(num);

        int ans = 0;

        string t = "";
        for(int i = 0; i < s.size(); ++i) {
            t = t + s[i];
            if( i >= k-1 ) {
                int a = stoi(t);
                if( a > 0 && num % a == 0 )
                    ++ans;
                t.erase(0,1);
            }
        }

        return ans;
    }
};
