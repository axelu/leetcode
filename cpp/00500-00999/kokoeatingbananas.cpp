
// 875. Koko Eating Bananas
// https://leetcode.com/problems/koko-eating-bananas/

class Solution {
private:
    // binary search less or equal target
    int search(vector<int>& piles, int n, long s, long e, long target) {
        // cout << "search s " << s << " e " << e << endl;
        if( s > e )
            return -1;
        
        long mid = s + ((e-s)/2);
        // cout << "  mid " << mid << endl;
        long d = 0;
        for(int i = 0; i < n; ++i) {
            if( piles[i] <= mid ) {
                ++d;
            } else {
                d += piles[i] / mid;
                if( piles[i] % mid )
                    ++d;
            }
        }
        if( d <= target ) {
            // can we do better? = can we eat slower?
            int t = search(piles,n,s,mid-1,target);
            return t != -1 ? t : mid;
        } else {
            // we need to eat faster
            return search(piles,n,mid+1,e,target);
        }
    }
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        // ans lies between 1 and max piles[i]
        int n = piles.size();
        int mx = *max_element(piles.begin(),piles.end());
        
        return search(piles,n,1,mx,h);
    }
};
