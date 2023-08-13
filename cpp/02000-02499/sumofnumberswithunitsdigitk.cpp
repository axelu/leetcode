
// 2310. Sum of Numbers With Units Digit K
// https://leetcode.com/problems/sum-of-numbers-with-units-digit-k/



class Solution {
private:
    int mem[3001];

    int rec(int num, const int k) {
        // cout << "rec num " << num << endl;
        if( num == 0 )
            return 0;
        if( num < 0 )
            return INT_MAX;

        if( mem[num] != -1 )
            return mem[num];

        int ret = INT_MAX;
        for(int i = num; i >= 1; --i) { // TODO go in increments of k ( k== 0 increment 10 )
            if( i % 10 == k ) {
                int t = rec(num-i, k);
                if( t == INT_MAX )
                    continue;
                ret = min(ret, 1 + t);
            }
        }

        return mem[num] = ret;
    }
public:
    int minimumNumbers(int num, int k) {
        memset(mem,-1,sizeof mem);

        int ans = rec(num,k);
        return ans != INT_MAX ? ans : -1;
    }
};
