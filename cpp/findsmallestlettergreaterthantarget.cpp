
// 744. Find Smallest Letter Greater Than Target
// https://leetcode.com/problems/find-smallest-letter-greater-than-target/



class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        int n = letters.size(); // 2 <= letters.size() <= 10000

        int arr[26]; memset(arr,0,sizeof arr);
        for(int i = 0; i < n; ++i)
            ++arr[letters[i]-'a'];

        for(int i = target-'a'+1; i < 26; ++i)
            if( arr[i] > 0 ) return i+'a';
        for(int i = 0; i < target-'a'; ++i)
            if( arr[i] > 0 ) return i+'a';

        return 'a'; // satisfy compiler
    }
};
