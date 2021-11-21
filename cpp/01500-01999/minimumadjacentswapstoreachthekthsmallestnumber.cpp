
// 1850. Minimum Adjacent Swaps to Reach the Kth Smallest Number
// https://leetcode.com/problems/minimum-adjacent-swaps-to-reach-the-kth-smallest-number/





class Solution {
private:

    // see solution for problem 31. Next Permutation
    // https://leetcode.com/problems/next-permutation/
    string nextKthSmallestNumber(string num, int n, int k) {

        for(int p = 1; p <= k; ++p) {

            int i = n-1, j = n-1;
            // find 1st instance from back where nums[i-1] < nums[i]
            for(; i > 0; --i)
                if( num[i-1] < num[i] ) break;
            // find 1st number nums[j] from back that is greater than nums[i-1]
            for(; j >= i; --j)
                if( num[j] > num[i-1] ) break;
            iter_swap(begin(num)+i-1,begin(num)+j);
            int q = (n-i)/2;
            for(int l = 0; l < q; ++l)
               iter_swap(begin(num)+i+l,begin(num)+n-1-l);

            // cout << p << ":" << num << " " << endl;
        }

        return num;
    }
public:
    int getMinSwaps(string num, int k) {
        // note: tests are generated in such a way that
        //       kth smallest wonderful integer exists

        int n = num.size();
        string s = nextKthSmallestNumber(num,n,k);

        int ans = 0;
        while( s != num ) {
            int i = 0;
            for(; i < n; ++i)
                if( s[i] != num[i] )
                    break;

            int j = i+1;
            for(; j < n; ++j)
                if( num[i] == s[j] )
                    break;
            ans += j-i;

            rotate(s.begin()+i,s.begin()+j,s.begin()+j+1);
        }


        return ans;
    }
};
