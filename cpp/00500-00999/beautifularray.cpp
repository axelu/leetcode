
// 932. Beautiful Array
// https://leetcode.com/problems/beautiful-array/



class Solution {
private:
    vector<int> r;

    void f(int s, int n) {
        if( n == 1 ) {
            r[s] = 1;
            return;
        }


        // divide
        int n2 = n/2;

        // conquer

        f(s,n2);
        for(int i = 0; i < n2; ++i) // even's on the left
            r[s+i] *= 2;

        f(s+n2,n-n2);
        for(int i = 0; i < n-n2; ++i) // odd's on the right
            r[s+n2+i] = r[s+n2+i]*2-1;
    }

public:
    vector<int> beautifulArray(int N) {
        r = vector<int>(N);
        f(0,N);
        return r;
    }
};
