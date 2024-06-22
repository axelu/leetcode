
// 2979. Most Expensive Item That Can Not Be Bought
// https://leetcode.com/problems/most-expensive-item-that-can-not-be-bought/





class Solution {
public:
    int mostExpensiveItem(int primeOne, int primeTwo) {
        // 1 < primeOne, primeTwo < 1e4
        // it is guaranteed that primeOne * primeTwo < 1e5
        // observation: we can make any number greater than primeOne * primeTwo

        // brute force
        int t = primeOne * primeTwo;
        bool canbuy[t+1];memset(canbuy,false,sizeof canbuy);
        canbuy[primeOne] = true;
        canbuy[primeTwo] = true;
        for(int i = min(primeOne,primeTwo); i <= t; ++i) {
            if( canbuy[i] ) {
                int canbuy_new = i + primeOne;
                if( canbuy_new <= t )
                    canbuy[canbuy_new] = true;
                canbuy_new = i + primeTwo;
                if( canbuy_new <= t )
                    canbuy[canbuy_new] = true;
            }
        }

        for(int i = t; i >= 0; --i)
            if( !canbuy[i] )
                return i;

        return -1; // satisfy compiler
    }
};
