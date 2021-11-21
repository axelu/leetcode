
// 1357. Apply Discount Every n Orders
// https://leetcode.com/problems/apply-discount-every-n-orders/




class Cashier {
private:
    int cnt,N;
    double Discount;
    unordered_map<int,int> um;
public:
    Cashier(int n, int discount, vector<int>& products, vector<int>& prices) {
        cnt = 0;
        N = n;
        Discount = discount;
        for(int i = 0; i < products.size(); ++i)
            um.insert({products[i],prices[i]});
    }

    double getBill(vector<int> product, vector<int> amount) {
        ++cnt;
        double sum = 0.0;
        for(int i = 0; i < product.size(); ++i)
            sum += um.find(product[i])->second * amount[i];
        if( cnt == N ) {
            sum -= ( sum*Discount/100 );
            cnt = 0;
        }
        return sum;
    }
};

/**
 * Your Cashier object will be instantiated and called as such:
 * Cashier* obj = new Cashier(n, discount, products, prices);
 * double param_1 = obj->getBill(product,amount);
 */
