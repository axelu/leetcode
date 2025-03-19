
// 3483. Unique 3-Digit Even Numbers
// https://leetcode.com/problems/unique-3-digit-even-numbers/




class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        int n = digits.size();

        // brute force
        // we will form number IJK and JIK

        bool seen[1000]; memset(seen,false,sizeof seen);

        int ans = 0;

        for(int k = 0; k < n; ++k) {
            int K = digits[k];
            if( K % 2 )
                continue;

             for(int i = 0; i < n; ++i) {
                if( i == k )
                    continue;
                int I = digits[i];
                for(int j = 0; j < n; ++j) {
                    if( j == k || j == i )
                        continue;
                    int J = digits[j];

                    if( I != 0 ) {
                        int A = I * 100 + J * 10 + K;
                        if( !seen[A] ) {
                            ++ans;
                            seen[A] = true;
                        }
                    }
                    if( J != 0 ) {
                        int B = J * 100 + I * 10 + K;
                        if( !seen[B] ) {
                            ++ans;
                            seen[B] = true;
                        }
                    }
                }
            }
        }

        return ans;
    }
};
