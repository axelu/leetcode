
// 638. Shopping Offers
// https://leetcode.com/problems/shopping-offers/


class Solution {
private:
    /*
    unordered_map<string,int> mem;

    string getKey(vector<int>& needs, int n, int pos) {
        string key = "";

        int k = 0;
        for(int i = 0; i < n; ++i)
            key += "#" + to_string(needs[i]);
        key += "#" + to_string(pos);

        return key;
    }
    */

    int rec(vector<int>& price, vector<vector<int>>& special, vector<int>& needs,
            int n, int pos) {

        // pos is pos in special
        // needs is remaining items

        // if we can no longer add from any special,
        // procure the remaining items paying regular price
        if( pos == special.size() ) {
            int cost = 0;
            for(int i = 0; i < n; ++i)
                cost += needs[i]*price[i];
            return cost;
        }

        /*
        string key = getKey(needs,n,pos);
        auto it = mem.find(key);
        if( it != mem.end() )
            return it->second;
        */

        // we have a choice
        // buy 0 or more of 1st special offer
        //   buy 0 or more of 2nd special offer
        //     buy 0 or more of nth special offer
        int a = rec(price,special,needs,n,pos+1);

        int k = 0;
        while(true) {
            ++k;
            bool f = true;
            for(int i = 0; i < n; ++i) {
                needs[i] -= special[pos][i];
                if( needs[i] < 0 )
                    f = false;
            }
            if( !f )
                break;

            a = min(a, special[pos][n]*k + rec(price,special,needs,n,pos+1));

        }
        // backtrack
        for(int i = 0; i < n; ++i)
            needs[i] += special[pos][i]*k;

        // mem.insert({key,a});
        return a;
    }

public:
    int shoppingOffers(vector<int>& price, vector<vector<int>>& special, vector<int>& needs) {
        int n = price.size(); // n == price.length == needs.length

        return rec(price,special,needs,n,0);
    }
};
