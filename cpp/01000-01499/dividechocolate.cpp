
// 1231. Divide Chocolate
// https://leetcode.com/problems/divide-chocolate/



class Solution {
private:
    int n;

    int solve(vector<int>& sweetness, int mn, int k) {
        int t = INT_MAX;
        int cnt = 0;
        int sum = 0;
        for(int i = 0; i < n; ++i) {
            sum += sweetness[i];
            if( sum >= mn ) {
                t = min(t,sum);
                sum = 0; // reset
                ++cnt;
            }
        }
        return cnt >= k+1 ? t : -1;
    }

    int search(vector<int>& sweetness, int s, int e, int k) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        int a = solve(sweetness,mid,k);
        if( a != -1 ) {
            // we have a potential solution
            // can we do better?
            //if( a == mid )
            //    return a;
            int t = search(sweetness,a+1,e,k);
            return t != -1 ? t : a;
        } else {
            return search(sweetness,s,mid-1,k);
        }
    }

public:
    int maximizeSweetness(vector<int>& sweetness, int k) {
        n = sweetness.size();

        // our answer is between min element and sum/(k+1)
        int mn = INT_MAX;
        int sum = 0;
        for(int i = 0; i < n; ++i) {
            mn = min(mn,sweetness[i]);
            sum += sweetness[i];
        }
        if( k == 0 )
            return sum;

        int mx = sum/k;


        return search(sweetness,mn,mx,k);
    }
};
