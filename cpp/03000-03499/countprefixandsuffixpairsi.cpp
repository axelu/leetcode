
// 3042. Count Prefix and Suffix Pairs I
// https://leetcode.com/problems/count-prefix-and-suffix-pairs-i/



class Solution {
private:
    bool isPrefixAndSuffix(string& str1, string& str2) {
        // returns true if str1 is both a prefix and a suffix of str2, and false otherwise
        int n1 = str1.size();
        int n2 = str2.size();
        if( n1 > n2 )
            return false;

        for(int i = 0, j = n2 - n1; i < n1; ++i, ++j)
            if( str1[i] != str2[i] || str1[i] != str2[j])
                return false;

        return true;
    }
public:
    int countPrefixSuffixPairs(vector<string>& words) {
        // 1 <= words.length <= 50
        // 1 <= words[i].length <= 10

        int n = words.size();
        // possible pairs n(n-1)/2
        // worst case n = 50 -> 1225 pairs

        int ans = 0;

        // brute force
        for(int i = 0; i < n-1; ++i)
            for(int j = i+1; j < n; ++j)
                if( isPrefixAndSuffix(words[i], words[j]) )
                    ++ans;

        return ans;
    }
};
