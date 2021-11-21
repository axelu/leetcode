

// 1239. Maximum Length of a Concatenated String with Unique Characters
// https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/
// https://leetcode.com/explore/featured/card/september-leetcoding-challenge-2021/639/week-4-september-22nd-september-28th/3984/





class Solution {
private:
    int countSetBits(int i) {
        unsigned int count = 0;
        while (i) {
            count += i & 1;
            i >>= 1;
        }
        return count;
    }

    int ans;

    void genSubsequences(vector<int>& arr, int i, int substring) {
        if( i == arr.size() ) {
            ans = max(ans,countSetBits(substring));
        } else {
            // we have a choice
            // don't include string at current index
            genSubsequences(arr,i+1,substring);

            // include string at current index
            // we can only include, if it remains unique
            int mask = arr[i];
            int j = 0;
            for(; j < 26; ++j) {
                if( !((mask >> j) & 1) )
                   continue;

                if( !((substring >> j) & 1) )
                    substring |= 1 << j;
                else
                    break;
            }
            if( j == 26 )
                genSubsequences(arr,i+1,substring);
        }
        return;
    }

public:
    int maxLength(vector<string>& arr) {

        vector<int> masks;
        int mask,j,k;
        bool hasDuplicateChars;
        for(int i = 0; i < arr.size(); ++i) {
            mask = 0;
            hasDuplicateChars = false;
            for(j = 0; j < arr[i].size(); ++j) {
                k = arr[i][j]-'a';
                if( !((mask >> k) & 1) ) {
                    mask |= 1 << k;
                } else {
                    // this string has already duplicates by itself
                    hasDuplicateChars = true;
                    break;
                }
            }
            if( !hasDuplicateChars )
                masks.push_back(mask);
        }

        int n = masks.size();
        if( n == 0 )
            return 0;
        if( n == 1 )
            return countSetBits(masks[0]);


        ans = 0;

        int substring = 0;
        genSubsequences(masks,0,substring);


        return ans;
    }
};
