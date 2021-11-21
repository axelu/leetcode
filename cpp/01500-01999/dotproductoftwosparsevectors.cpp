
// 1570. Dot Product of Two Sparse Vectors
// https://leetcode.com/problems/dot-product-of-two-sparse-vectors/




class SparseVector {
private:
    map<int,int> m;
public:

    SparseVector(vector<int> &nums) {
        for(int i = 0; i < nums.size(); ++i)
            if( nums[i] != 0 ) m.insert({i,nums[i]});
    }

    map<int,int>* data() {
        return &m;
    }

    // Return the dotProduct of two sparse vectors
    int dotProduct(SparseVector& vec) {
        map<int,int>::iterator it1 = m.begin();
        map<int,int>::iterator it1e = m.end();
        map<int,int>* m2 = vec.data();
        map<int,int>::iterator it2 = m2->begin();
        map<int,int>::iterator it2e = m2->end();

        int ans = 0;
        while( it1 != it1e && it2 != it2e) {
            if( it1->first == it2->first ) {
                ans += it1->second*it2->second;
                ++it1;
                ++it2;
                continue;
            }
            if( it1->first < it2->first ) {
                while( it1 != it1e && it1->first < it2->first )
                    ++it1;
            } else {
                // it2->first < it1->first
                while( it2 != it2e && it2->first < it1->first )
                    ++it2;
            }
        }
        return ans;
    }
};

// Your SparseVector object will be instantiated and called as such:
// SparseVector v1(nums1);
// SparseVector v2(nums2);
// int ans = v1.dotProduct(v2);
