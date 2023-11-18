
// 2412. Minimum Money Required Before Transactions
// https://leetcode.com/problems/minimum-money-required-before-transactions/




class Solution {
public:
    long long minimumMoney(vector<vector<int>>& transactions) {
        int n = transactions.size();

        // the answer is somewhere between
        //    mn = max of transaction[i][0] for all 0 <= i < n (we could start with any of the most expensive transactions) AND
        //    mx = sum of transaction[i][0] for all 0 <= i < n (we would not rely on cachback to proceed)

        // potentially possible worst case scenarios
        //    execute transactions in order of cost desc
        //        if two transactions have the same cost, execute the one with less cachback first
        //    execute transactions in order of cashback asc
        //        if two transactions have the same cashback, execute the one with more cost first
        // transactions fall into two buckets:
        //     transactions that do not loose money cost <= cashback
        //     transactions that loose money        cost >  cashback
        // potentially worst case if we execute all the money loosing transactions first
        //     in the order of least cashback
        //     at any step along the way (including the very end) we would need to have enough money
        //     to execute the most expensive non-money loosing transaction or most expensive remaining
        //     money-loosing transaction, whatever is greater

        int mx = 0; // global max transaction cost
        int not_loose_money_mx = 0; // max transaction cost for transactions that don't loose money
        vector<vector<vector<int>>::iterator> loose_money_tx;

        vector<vector<int>>::iterator it = transactions.begin();
        for(; it != transactions.end(); ++it) {
            mx = max(mx, it->at(0));
            if( it->at(0) <= it->at(1) ) {
                not_loose_money_mx = max(not_loose_money_mx, it->at(0));
            } else {
                loose_money_tx.push_back(it);
            }
        }

        /*
        // debug
        cout << "money loosing tx ";
        for(auto it: loose_money_tx)
            cout << it->at(0) << ":" << it->at(1) << " ";
        cout << endl;
        cout << "not money loosing tx ";
        for(auto it: not_loose_money_tx)
            cout << it->at(0) << ":" << it->at(1) << " ";
        cout << endl;
        */

        // sort money loosing transactions by cachback asc
        sort(begin(loose_money_tx),end(loose_money_tx),[](const vector<vector<int>>::iterator a, const vector<vector<int>>::iterator b){
          return a->at(1) < b->at(1);
        });

        /*
        // debug
        cout << "money loosing tx sorted by cashback asc ";
        for(auto it: loose_money_tx)
            cout << it->at(0) << ":" << it->at(1) << " ";
        cout << endl;
        */

        int loose_money_tx_sz = loose_money_tx.size();
        if( loose_money_tx_sz == 0 )
            return mx;

        int mn_needed[loose_money_tx_sz];
        mn_needed[loose_money_tx_sz-1] = not_loose_money_mx;
        for(int i = loose_money_tx_sz - 2; i >= 0; --i)
            mn_needed[i] = max(mn_needed[i+1],loose_money_tx[i+1]->at(0));

        long long ans  = mx; // assumed starting money
        long long curr = mx;

        for(int i = 0; i < loose_money_tx_sz; ++i) {
            long long cost = loose_money_tx[i]->at(0);
            long long cashback = loose_money_tx[i]->at(1);

            // execute the current money loosing transactions
            curr = curr - cost + cashback;
            if( curr < mn_needed[i] ) {
                // we need to start with more money
                long long shortfall = mn_needed[i] - curr;
                ans = ans + shortfall;
                curr = mn_needed[i];
            }
        }

        return ans;
    }
};
