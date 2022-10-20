
// 2223. Sum of Scores of Built Strings
// https://leetcode.com/problems/sum-of-scores-of-built-strings/



// https://www.hackerearth.com/practice/algorithms/string-algorithm/z-algorithm/tutorial/

class Solution {
public:
    long long sumScores(string& s) {
        int n = s.size();

        int z[n];memset(z,0,sizeof z);

        // z algorithm
        int L = 0, R = 0;
        for (int i = 1; i < n; i++)
        {
            if (i > R)
            {
                L = R = i;
                while (R < n && s[R-L] == s[R])
                {
                    R++;
                }
                z[i] = R-L;
                R--;
            }
            else
            {
                int k = i-L;
                if (z[k] < R-i+1)
                {
                    z[i] = z[k];
                }
                else
                {
                    L = i;
                    while (R < n && s[R-L] == s[R])
                    {
                        R++;
                    }
                    z[i] = R-L;
                    R--;
                }
            }
        }

        long long t = 0;
        for(int i = 0; i < n; ++i)
            t += z[i];


        return t+n;
    }
};
