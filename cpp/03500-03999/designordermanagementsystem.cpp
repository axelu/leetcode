
// 3822. Design Order Management System
// https://leetcode.com/problems/design-order-management-system/



class OrderManagementSystem {
private:
    // need to key orders by orderId
    //                    by orderType AND price

    unordered_map<int,int> orders; // key: orderId, value: price (price < 0 sell, otherwise buy)
    unordered_map<int,unordered_set<int>> prices; // key: price, value: set of orders at that price
    // TODO instead of unordered_set, we could use a vector or list with pointers back to
    // our order in the map

public:
    OrderManagementSystem() {
    }

    void addOrder(int orderId, string orderType, int price) {
        // orderId if guaranteed to be unique
        // orderType is "buy" or "sell"
        // initial orderState is active
        if( orderType == "sell" )
            price *= -1;
        orders.insert({orderId, price});
        prices[price].insert(orderId);
        return;
    }

    void modifyOrder(int orderId, int newPrice) {
        // it is guaranteed that the order exists and is active.
        int oldPrice = orders[orderId];
        prices[oldPrice].erase(orderId);
        // TODO if no orders anymore for old price, delete the price
        if( oldPrice < 0 )
            newPrice *= -1;
        orders[orderId] = newPrice;
        prices[newPrice].insert(orderId);
        return;
    }

    void cancelOrder(int orderId) {
        // it is guaranteed that the order exists and is active.
        // given the constraints and requirements, we can delete the order
        int price = orders[orderId];
        prices[price].erase(orderId);
        orders.erase(orderId);
        return;
    }

    vector<int> getOrdersAtPrice(string orderType, int price) {
        // orderType is "buy" or "sell"
       if( orderType == "sell" )
            price *= -1;

        return vector<int>(prices[price].begin(), prices[price].end());
    }
};

/**
 * Your OrderManagementSystem object will be instantiated and called as such:
 * OrderManagementSystem* obj = new OrderManagementSystem();
 * obj->addOrder(orderId,orderType,price);
 * obj->modifyOrder(orderId,newPrice);
 * obj->cancelOrder(orderId);
 * vector<int> param_4 = obj->getOrdersAtPrice(orderType,price);
 */
