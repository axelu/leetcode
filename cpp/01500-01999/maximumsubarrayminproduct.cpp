
// 1856. Maximum Subarray Min-Product
// https://leetcode.com/problems/maximum-subarray-min-product/





class Solution {
private:
    long MOD = 1000000007;

    // binary search first element greater than target aka upper bound
    int upperBound(vector<array<int,2>>& v, int s, int e, int target) {
        if( s > e ) return -1;

        int mid = s + ((e - s)/2);
        if( v[mid][0] <= target ) {
            return upperBound(v,mid+1,e,target);
        } else {
            // can we do better?
            int ans = upperBound(v,s,mid-1,target);
            return ans != -1 ? ans : mid;
        }
    }

public:
    int maxSumMinProduct(vector<int>& nums) {
        int n = nums.size();

        vector<array<int,2>> stck;
        long prefix[n+1];
        prefix[0] = 0;
        for(int i = 0; i < n; ++i) {
            stck.push_back({nums[i],i});
            prefix[i+1] = prefix[i]+(long)nums[i];
        }
        sort(begin(stck),end(stck),[](const array<int,2>& a, const array<int,2>& b){
           return a[0] < b[0];
        });

        long mn = stck[0][0];
        long total = prefix[n];
        long ans = mn*total;

        // advance in stack to next number greater than mn
        int i = upperBound(stck,0,n-1,mn);
        if( i == -1 )
            return ans%MOD;

        set<int> st;
        for(int j = 0; j < i; ++j) {
            st.insert(stck[j][1]);
        }

        // we will expand from every position to the left and right
        // till element is smaller than the element at
        // our current starting point
        // for that subarray we will calculate the min-product
        int pos,s,e;
        long sum;
        queue<int> q;
        for(; i < n; ++i) {
            mn = stck[i][0];
            pos = stck[i][1];
            // cout << "mn " << mn << " pos " << pos << endl;

            auto it = st.upper_bound(pos);

            // expand to right
            if( it == st.end() )
                e = n-1;
            else
                e = *it-1;

            // expand to left
            if( it == st.begin() )
                s = 0;
            else
                s = *prev(it) + 1;


            // cout << "  s " << s << " e " << e << endl;

            // l = prefix[s];
            // r = total - prefix[e+1];
            // sum = total - l - r;
            sum = prefix[e+1] - prefix[s];

            ans = max(ans,mn*sum);

            // we only care about the so far proccessed positions if
            // the next element is bigger, otherwise we hold those positions
            q.push(pos);
            if( i < n-1 ) {
                if( stck[i+1][0] > mn ) {
                    while( !q.empty() ) {
                        st.insert(q.front());
                        q.pop();
                    }
                }
            } else {
                while( !q.empty() ) {
                    st.insert(q.front());
                    q.pop();
                }
            }
        }

        return ans%MOD;
    }
};
