
// 3271. Hash Divided String
// https://leetcode.com/problems/hash-divided-string/




class Solution {
public:
    string stringHash(string s, int k) {
        int n = s.size(); // n is a multiple of k

        string ans = "";

        for(int i = 0; i < n/k; ++i) {

            int hash_val_sum = 0;

            for(int j = i*k; j < i*k + k; ++j) {
                int hash_val = s[j] - 'a';
                hash_val_sum += hash_val;
            }

            int rem = hash_val_sum % 26;

            ans.push_back('a' + rem);
        }


        return ans;
    }
};
