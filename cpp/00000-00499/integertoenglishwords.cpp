
// 273. Integer to English Words
// https://leetcode.com/problems/integer-to-english-words/





class Solution {
private:
    vector<string> singles{
        "Zero",
        "One",
        "Two",
        "Three",
        "Four",
        "Five",
        "Six",
        "Seven",
        "Eight",
        "Nine",
        "Ten",
        "Eleven",
        "Twelve",
        "Thirteen",
        "Fourteen",
        "Fifteen",
        "Sixteen",
        "Seventeen",
        "Eighteen",
        "Nineteen"
    };
    vector<string> tens{
        "",
        "Ten",
        "Twenty",
        "Thirty",
        "Forty",
        "Fifty",
        "Sixty",
        "Seventy",
        "Eighty",
        "Ninety"
    };

    vector<int> int2vector(int num) {
        vector<int> ret;
        while( num > 0 ) {
            ret.push_back(num % 10);
            num /= 10;
        }
        return ret;
    }

public:
    string numberToWords(int num) {
        if( num <= 19 )
            return singles[num];

        string ans = "";

        auto vnum = int2vector(num);
        int n = vnum.size();
        for(int i = 0; i < n; ++i) {
            if( i == 3 ) {
                if( vnum[i] != 0 || ( i+1 < n && vnum[i+1] != 0 ) || ( i+2 < n && vnum[i+2] != 0 ) )
                    ans = "Thousand " + ans;
            }
            if( i == 6 ) {
               if( vnum[i] != 0 || ( i+1 < n && vnum[i+1] != 0 ) || ( i+2 < n && vnum[i+2] != 0 ) )
                    ans = "Million " + ans;
            }
            if( i == 9 ) {
               if( vnum[i] != 0 || ( i+1 < n && vnum[i+1] != 0 ) || ( i+2 < n && vnum[i+2] != 0 ) )
                    ans = "Billion " + ans;
            }

            if( i % 3 == 0 ) { // 0, 3, 6, 9
                if( i < n-1 ) {
                    if( vnum[i+1] == 0 && vnum[i] == 0 ) {
                        // 0
                    } else if( vnum[i+1] == 0 || vnum[i+1] == 1 ) {
                        // 1 .. 19
                        int t = 10 * vnum[i+1] + vnum[i];
                        ans = singles[t] + " " + ans;
                    } else {
                        // 20 ... 99
                        if( vnum[i] > 0 )
                            ans = singles[vnum[i]] + " " + ans;
                        ans = tens[vnum[i+1]] + " " + ans;
                    }
                    ++i;

                } else {
                    ans = singles[vnum[i]] + " " + ans;
                }
            }

            if( (i == 2 || i == 5 || i == 8) && vnum[i] > 0 ) {
                ans = singles[vnum[i]] + " Hundred " + ans;
            }
        }
        if( ans.back() == ' ' )
            ans.pop_back();

        return ans;
    }
};
