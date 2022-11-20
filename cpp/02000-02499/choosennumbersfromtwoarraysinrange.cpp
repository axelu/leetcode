
// 2143. Choose Numbers From Two Arrays in Range
// https://leetcode.com/problems/choose-numbers-from-two-arrays-in-range/



class Solution {
private:
    const long mod = 1000000007;
    int n,offset;
    int * _nums1;
    int * _nums2;
    
    long * mem[100];
    
    long rec(long i, int sum) {
        // cout << "i " << i << " sum " << sum << endl;
        // cout << "i " << i << " sum1 " << sum1 << " sum2 " << sum2 << endl;
        // if( i == n )
        //    return 0;
        
        // at each index i, we have to take a number from nums1 or nums2,
        // meaning we have a choice
        //     [unless we are skipping, or better not starting, a new range at index i]
        //     grab nums1[i]
        //     grab nums2[i]
        // instead of tracking two sums, because they have to be equal,
        // we can track one sum and check if that sum is 0
        // when we grab nums1[i] we are adding to the sum
        // when we grab nums2[i] we subtract from the sum
        // only works because all elements are 0 <= nums1[i],nums2[i] !!!
       
        // need to use offset for sum, because sum could be negative
        if( mem[i][sum+offset] != -1 )
            return mem[i][sum+offset];
        
        long ret = 0;
        
        // grab nums1[i]
        int sum1_new = sum + _nums1[i];
        if( sum1_new == 0 )
            ++ret;
        if( i < n-1 )
            ret = (ret + rec(i+1,sum1_new)) % mod;
        
        // grab nums2[i];
        int sum2_new = sum - _nums2[i]; // subtract
        if( sum2_new == 0 )
            ret = ret + 1;
        if( i < n-1 )
            ret = (ret + rec(i+1,sum2_new)) % mod;
        
        return mem[i][sum+offset] = ret;
    }
    
    
public:
    int countSubranges(vector<int>& nums1, vector<int>& nums2) {
        n = nums1.size(); // nums1.length == nums2.length
        
        // important from the rules:
        //     the sum is considered to be 0 if you pick no numbers from an array
        // hence like nums1 = {0} and nums2 = {0} yields answer 2 and
        //            nums1 = {0} and nums2 = {3} yields answer 1
         
        _nums1 = nums1.data();
        _nums2 = nums2.data();
        
        int t = 2 * n * 100 + 2;
        offset = n * 100;
        for(int i = 0; i < n; ++i) {
            mem[i] = new long[t];
            for(int j = 0; j < t; ++j)
                mem[i][j] = -1;
        }
        
        long ans = 0;
        for(int i = 0; i < n; ++i)
            ans = (ans + rec(i,0)) % mod;
        
        return ans;
    }
};
