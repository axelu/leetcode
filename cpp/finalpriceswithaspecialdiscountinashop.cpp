
// Final Prices With a Special Discount in a Shop
// https://leetcode.com/problems/final-prices-with-a-special-discount-in-a-shop/


class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
        if( prices.size() == 1 ) return prices;

        vector<int> r;
        auto ite = prices.end();
        auto ito = prices.begin();
        for(; ito != ite - 1; ++ito) {
            auto iti = find_if(ito + 1, ite, [ito](int a){
                return a <= *ito;
            });
            r.push_back( ( iti != ite ) ? *ito - *iti : *ito );
        }
        r.push_back(*ito); // add the last item for which there will never be a discount

        return r;
    }
};
