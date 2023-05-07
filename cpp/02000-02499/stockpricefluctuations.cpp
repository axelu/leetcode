
// 2034. Stock Price Fluctuation 
// https://leetcode.com/problems/stock-price-fluctuation/




class StockPrice {
private:
    map<int,int> tp;                // timestamp, price
    map<int,unordered_set<int>> pt; // price, list of timestamps

public:
    StockPrice() {

    }

    void update(int timestamp, int price) {

        auto p = tp.insert({timestamp,price});
        if( p.second ) {
            // this is a new timestamp
            pt[price].insert(timestamp);

        } else {
            // this is a correction to a prior timestamp

            // get former price at time stamp
            int old_price = p.first->second;

            // remove timestamp for price from price-timestamp map
            pt[old_price].erase(timestamp);
            if( pt[old_price].empty() )
                pt.erase(old_price);

            // set new price at time stamp
            p.first->second = price;

            // add timestamp to price-timestamp map
            pt[price].insert(timestamp);
        }
    }

    int current() {
        return tp.rbegin()->second;
    }

    int maximum() {
        return pt.rbegin()->first;
    }

    int minimum() {
        return pt.begin()->first;
    }
};

/**
 * Your StockPrice object will be instantiated and called as such:
 * StockPrice* obj = new StockPrice();
 * obj->update(timestamp,price);
 * int param_2 = obj->current();
 * int param_3 = obj->maximum();
 * int param_4 = obj->minimum();
 */
