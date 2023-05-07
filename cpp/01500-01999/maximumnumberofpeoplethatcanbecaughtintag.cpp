
// 1989. Maximum Number of People That Can Be Caught in Tag
// https://leetcode.com/problems/maximum-number-of-people-that-can-be-caught-in-tag/



class Solution {
private:
    vector<int> bit; // binary indexed tree bit, 0 indexed
    int n;

    int sum(int r) { // sum of range [0,r] inclusive
        int ret = 0;
        for(; r >= 0; r = (r & (r + 1)) - 1)
            ret += bit[r];
        return ret;
    }
    
    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }

    void add(int idx, int delta) {
        for(; idx < n; idx = idx | (idx + 1))
            bit[idx] += delta;
    }
    
    // binary search
    int search(int l, int s, int e) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        int lgt = mid - l + 1;

        if( sum(l,mid) == lgt ) {
            // can we do better?
            int t = search(l,mid+1,e);
            return t != -1 ? t : mid;
        }

        return search(l,s,mid-1);
    }

public:
    int catchMaximumAmountofPeople(vector<int>& team, int dist) {
        n = team.size();
        
        // create an initial prefix sum
        // then go through team and for every "it" calculate
        // the range sum for the range in which then can catch a "not it"
        // if the range sum is less than the length of the range, then
        // we know it includes one or more "not it"
        // find the index of the left most "not it" respectively
        // find the right most index of range where range sum == length left to right
        // and mark it as caught
        // then repeat the process for the next "it"
        
        bit.assign(n,0);

        for(int i = 0; i < n; ++i)
            if( team[i] == 1 )
                add(i,1);    
        
        int ans = 0;
        
        for(int i = 0; i < n; ++i) {
            if( team[i] == 1 ) {
                int s = i - dist <  0 ?   0 : i - dist;
                int e = i + dist >= n ? n-1 : i + dist;
                // cout << "i " << i << " s " << s << " e " << e << endl;
                
                // search will return -1 if team[s] == 0
                // search will return e if all elements team[s,e] are 1s
                // otherwise search will return the rightmost index x
                //     where all elements team[s,x] are 1s
                int t = search(s,s,e) + 1;
                if( t <= e ) {
                    ++ans;
                    add(t,1);
                }
            }
        }
    
        return ans;
    }
};
