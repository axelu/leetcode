
// 1648. Sell Diminishing-Valued Colored Balls
// https://leetcode.com/problems/sell-diminishing-valued-colored-balls/



class Solution {
private:
    int M = 1000000007;
    size_t n;
    vector<int> * pInventory;
    int order;

    bool fillOrder(int k) {
        long O = 0; // balls added
        int bi;     // number of balls at idx i
        for(int i = n-1; i >= 0; --i) {
            bi = (*pInventory)[i];
            if( bi <= k ) break;
            O += (long)(bi - k);
            if( O >= order ) return true;
        }
        return false;
    }

    int search(int s, int e) {
        if( s > e || e < s )
            return 0;
        int k = s + ((e - s)/2);
        return fillOrder(k) ? max(k,search(k+1,e)) : search(s,k-1);
    }

public:
    int maxProfit(vector<int>& inventory, int order) {
        sort(begin(inventory),end(inventory));
        n = inventory.size();

        pInventory = &inventory;
        this->order = order;

        // binary search for k where all balls of value > k are sold,
        // and some, (maybe 0) of balls of value k are sold
        long k = search(0,inventory.back()) + 1L;

        long r = 0;

        long O = 0; // balls added
        long bi;    // number of balls at idx i
        for(int i = n-1; i >= 0; --i) {
            bi = inventory[i];
            if( bi <= k ) break;
            O += (long)(bi - (k));
            r = (r + (bi*(bi+1))/2 - ((k)*(k+1))/2) % M;
        }

        // order - O balls of value k are still missing
        long f = order - O;
        r = (r + k*f) % M;

        return r;
    }
};
