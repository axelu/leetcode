
// 1801. Number of Orders in the Backlog
// https://leetcode.com/problems/number-of-orders-in-the-backlog/



class Solution {
private:
    long mod = 1000000007;

public:
    int getNumberOfBacklogOrders(vector<vector<int>>& orders) {
        // orders[i] = [pricei, amounti, orderTypei]
        // orderType 0: batch of buy orders
        // orderType 1: batch of sell orders

        auto cmp_sell = [](const pair<int,long>& a, const pair<int,long>& b){
            return a.first > b.first;
        };
        priority_queue<pair<int,long>,vector<pair<int,long>>,decltype(cmp_sell)> sell_orders(cmp_sell);

        auto cmp_buy = [](const pair<int,long>& a, const pair<int,long>& b){
            return a.first < b.first;
        };
        priority_queue<pair<int,long>,vector<pair<int,long>>,decltype(cmp_buy)> buy_orders(cmp_buy);

        int n = orders.size();
        for(int i = 0; i < n; ++i) {
            int order_type   = orders[i][2];

            if( order_type == 0 ) { // buy order
                int buy_order_price  = orders[i][0];
                int buy_order_amount = orders[i][1];

                // while we have sell orders where sell_order_price <= buy_order_price
                while( !sell_orders.empty() &&
                       sell_orders.top().first <= buy_order_price &&
                       buy_order_amount > 0 ) {

                    auto p = sell_orders.top();
                    sell_orders.pop();

                    if( p.second <= buy_order_amount ) {
                        buy_order_amount -= p.second;
                    } else {
                        p.second -= buy_order_amount;
                        sell_orders.push(p);
                        buy_order_amount = 0;
                    }
                }

                if( buy_order_amount > 0 )
                    buy_orders.push({buy_order_price, buy_order_amount});

            } else {  // sell order
                int sell_order_price  = orders[i][0];
                int sell_order_amount = orders[i][1];

                // while we have buy orders where buy_order_price >= sell_order_price
                while( !buy_orders.empty() &&
                        buy_orders.top().first >= sell_order_price &&
                        sell_order_amount > 0 ) {

                    auto p = buy_orders.top();
                    buy_orders.pop();

                    if( p.second <= sell_order_amount ) {
                        sell_order_amount -= p.second;
                    } else {
                        p.second -= sell_order_amount;
                        buy_orders.push(p);
                        sell_order_amount = 0;
                    }
                }

                if( sell_order_amount > 0 )
                    sell_orders.push({sell_order_price, sell_order_amount});
            }
        }

        long ans = 0;

        while( !buy_orders.empty() ) {
            ans = (ans + buy_orders.top().second) % mod;
            buy_orders.pop();
        }
        while( !sell_orders.empty() ) {
            ans = (ans + sell_orders.top().second) % mod;
            sell_orders.pop();
        }

        return ans;
    }
};
