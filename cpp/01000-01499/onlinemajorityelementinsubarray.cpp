
// 1157. Online Majority Element In Subarray
// https://leetcode.com/problems/online-majority-element-in-subarray/

class MajorityChecker {
private:
    array<int,2> * t; // segment tree holding majority element, voting count
    int n;
    
    unordered_map<int,vector<int>> um; // value, list of indexes at which value occurs

    array<int,2> merge(array<int,2>& a, array<int,2>& b) {
        if( a[0] == b[0] ) 
            return {a[0],a[1] + b[1]};   
        else if( a[1] > b[1] ) 
            return {a[0],a[1] - b[1]};
        else 
            return {b[0],b[1] - a[1]};
    }
    
    void build(vector<int>& arr) {
        // build all the leaf nodes
        for(int i = 0; i < n; ++i)
            t[n+i] = {arr[i],1};
        
        // merge the leaf nodes 
        // Moore's voting algorithm
        for(int i = n-1; i >=1; --i)
            t[i] = merge(t[2*i],t[2*i + 1]);  
    }
    
    int q(int left, int right) {
        // returns the majority element in the range [left,right]

        array<int,2> r = {0,0};

        // walk the tree from the left and right leaf up
        // till the common ancestor
        left  += n;
        right += n;
        while( left <= right ) {
            // cout << "left " << left << " right " << right << endl;
            
            if( left & 1 ) {
                r = merge(r,t[left]);
                ++left;
            }

            if( !(right & 1) ) {
                r = merge(r,t[right]);
                --right;
            }

            left  >>= 1;
            right >>= 1;
        }

        return r[0];
    }

public:
    MajorityChecker(vector<int>& arr) {
        n = arr.size();

        // build a segment tree
        t = new array<int,2>[4*n];
        build(arr);
        
        // for each val build list of indexes at which value occurs
        for(int i = 0; i < n; ++i)
            um[arr[i]].push_back(i);
    }
    
    int query(int left, int right, int threshold) {

        int val = q(left,right); // value of majority element in range [left,right]
        
        // at this point we only know that the val is the majority
        // element in range [left,right], but we don't know how often it occurs
        auto b = um[val].begin();
        auto e = um[val].end();
        auto l = lower_bound(b,e,left);
        auto r = upper_bound(b,e,right);
        
        if( distance(b,r) - distance(b,l) >= threshold )
            return val;
        
        return -1;
     }
};

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */
