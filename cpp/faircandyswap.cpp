
// 888. Fair Candy Swap
// https://leetcode.com/problems/fair-candy-swap/



class Solution {
public:
    vector<int> fairCandySwap(vector<int>& A, vector<int>& B) {
        int na = A.size(); // 1 <= A.length <= 10000
        int nb = B.size(); // 1 <= B.length <= 10000
        sort(A.begin(),A.end());
        sort(B.begin(),B.end());
        
        int sa = 0, i = 0, sb = 0, j = 0;
        while(i < na || j < nb) {
            if( i < na ) {
                sa += A[i];
                ++i;
            }
            if( j < nb ) {
                sb += B[j];
                ++j;
            }
        }

        int total = sa + sb;
        int total2 = total/2;
        // cout << "sa " << sa << " sb " << sb << " total2 " << total2 << endl;
        if( sa < total2 ) {
            // Alice needs to gain and Bob needs to give up
            int g = total2 - sa; // gain
            
            for(i = 0; i < na; ++i) {
                if( binary_search(B.begin(),B.end(),A[i]+g) ) break;
            }
            return {A[i],A[i]+g};
        } else {
            // Bob needs to gain and Alice needs to give up
            int g = total2 - sb; // gain
            
            for(i = 0; i < nb; ++i) {
                if( binary_search(A.begin(),A.end(),B[i]+g) ) break;
            }
            return {B[i]+g,B[i]};
        }
    }
};
