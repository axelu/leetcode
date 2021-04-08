
// Best Time to Buy and Sell Stock IV
// day 18 October 2020 challenge
// https://leetcode.com/explore/challenge/card/october-leetcoding-challenge/561/week-3-october-15th-october-21st/3499/
// https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/



#include <iostream>
#include <cassert>
#include <chrono>

#include <vector>
#include <string>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <set>
#include <iterator>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <map>
#include <cmath>
#include <bitset>
#include <cstring>


using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
	    int n = prices.size();
	    if( n <= 1 || k == 0 ) return 0;

        if( k >= n / 2  ) {
            // unable to pick 2k points from n points, hence unable reach k
            // iterate each day, if the price of day i is higher than prior day
            // buy the stock in i-1 day and sell it on i day.
		    int profit = 0;
		    for(int i = 1; i < n; i++)
			    if( prices[i] > prices[i - 1] )
                    profit += prices[i] - prices[i - 1];
		    return profit;
	    }

        int a[10000]; memset(a, 0, sizeof a); // profits of prior transaction
        int b[10000]; memset(b, 0, sizeof b); // profits of current transaction

        // loop over prices as many times as we can transact
        // in each iteration, pick the transaction with the next highest profit
        int * pt = a;
        int * ct = b;
	    for(int i = 1; i <= k; ++i)  {
		    int minPrice = prices[0]; // init
		    for(int j = 1; j < n; ++j) {
                // consider the profit we already have, and with that
                // link our transactions
                minPrice = min(minPrice, prices[j] - pt[j-1]);
                ct[j] = max(ct[j-1],prices[j] - minPrice);
		    }
            int * t = ct;
            ct = pt;
            pt = t;
	    }

        return pt[n-1];
    }
};

int main() {

    chrono::time_point<chrono::system_clock> start;
    chrono::time_point<chrono::system_clock> end;
    chrono::duration<double> elapsed_seconds;

    // start = chrono::system_clock::now();
    // do something
    // end = chrono::system_clock::now();
    // elapsed_seconds = end - start;
    // cout << "elapsed_seconds " << elapsed_seconds.count() << endl;

    Solution s;
    int k;
    vector<int> prices;
    int r;

    // Example 1
    // k = 2;
    // prices = {2,4,1};
    // r = s.maxProfit(k,prices);
    // assert(r == 2);

    // Example 2
    k = 2;
    prices = {3,2,6,5,0,3};
    for(auto i : prices) cout << i << " ";
    cout << endl;
    r = s.maxProfit(k,prices);
    assert(r == 7);


    // Example Axel 1
    k = 3;
    prices = {3,2,6,5,4,6,0,3};
    for(auto i : prices) cout << i << " ";
    cout << endl;
    r = s.maxProfit(k,prices);
    assert(r == 9);

    // Example Axel 1
    k = 2;
    prices = {1,3,2,4,4,4};
    for(auto i : prices) cout << i << " ";
    cout << endl;
    r = s.maxProfit(k,prices);
    assert(r == 4);



    return 0;
}
