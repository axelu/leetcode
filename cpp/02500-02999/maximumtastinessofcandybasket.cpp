
// 2517. Maximum Tastiness of Candy Basket
// https://leetcode.com/problems/maximum-tastiness-of-candy-basket/




class Solution {
private:
    int n,K;
    int * _price;

    bool solve(int x) {
        int added = 1;
        int last_price = _price[0];
        for(int i = 1; i < n && added < K; ++i)
            if( _price[i] >= last_price + x ) {
                ++added;
                last_price = _price[i];
            }
        return added == K;
    }

    // binary search
    int search(int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = solve(mid);
        if( f ) {
            // can we do better?
            int t = search(mid+1,e);
            return t != -1 ? t : mid;
        } else {
            return search(s,mid-1);
        }

    }

public:
    int maximumTastiness(vector<int>& price, int k) {
        sort(price.begin(),price.end());

        n = price.size();
        K = k;
        _price = price.data();

        int e = price[n-1] - price[0];
        return search(0,e);
    }
};
