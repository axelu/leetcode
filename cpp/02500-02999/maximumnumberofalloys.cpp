
// 2861. Maximum Number of Alloys
// https://leetcode.com/problems/maximum-number-of-alloys/






class Solution {
private:
    bool canmake(long alloys, int machine, int n, long budget, vector<vector<int>>& composition, vector<int>& stock, vector<int>& cost) {
        // cout << "canmake alloys " << alloys << " on machine " << machine << endl;
        // can we make alloys 'alloys' with machine 'machine' within budget?

        for(int i = 0; i < n; ++i) {    // metal
            // to make 1 alloy, it takes composition[machine][i] units of metal i
            long metali_needed = alloys * composition[machine][i];
            long metali_have   = stock[i];
            if( metali_have >= metali_needed )
                continue;

            long metali_buy  = metali_needed - metali_have;
            long metali_cost = metali_buy * cost[i];

            budget -= metali_cost;
            if( budget < 0 )
                return false;
        }

        return true;
    }

    bool solve(int alloys, int n, int k, int budget, vector<vector<int>>& composition, vector<int>& stock, vector<int>& cost) {
        // cout << "solve alloys " << alloys << endl;
        for(int i = 0; i < k; ++i)      // machine
            if( canmake(alloys,i,n,budget,composition,stock,cost) )
                return true;

        return false;
    }

    // binary search
    int search(int s, int e,
               int n, int k, int budget, vector<vector<int>>& composition, vector<int>& stock, vector<int>& cost) {

        // cout << "search s " << s << " e " << e << endl;

        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        bool f = solve(mid,n,k,budget,composition,stock,cost);
        if( f ) {
            // can we do better?
            int t = search(mid+1,e,n,k,budget,composition,stock,cost);
            return t != -1 ? t : mid;
        }
        return search(s,mid-1,n,k,budget,composition,stock,cost);
    }


public:
    int maxNumberOfAlloys(int n, int k, int budget, vector<vector<int>>& composition, vector<int>& stock, vector<int>& cost) {
        // upper end picked arbitrarily
        return search(0,INT_MAX,n,k,budget,composition,stock,cost);
    }
};
