
// 2709. Greatest Common Divisor Traversal
// https://leetcode.com/problems/greatest-common-divisor-traversal/




vector<int> divisors[100001]; // lazy population

class Solution {
private:
    // disjoint-set path compression size
    int * parent;
    int * size;

    int find(int v) {
        if (v == parent[v])
            return v;
        return parent[v] = find(parent[v]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b) {
            if (size[a] < size[b])
                swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }

    void calc_divisors(int a) {
        // will exclude 1 as a divisor
        if( !divisors[a].empty() )
            return;

        int square_root = (int) sqrt(a) + 1;
        for(int i = 2; i < square_root; ++i) {
            if( a % i == 0 && i*i!= a ) {
                divisors[a].push_back(i);
                divisors[a].push_back(a/i);
            }
            if( a % i == 0 && i*i== a )
                divisors[a].push_back(i);
        }
        divisors[a].push_back(a);
    }

public:
    bool canTraverseAllPairs(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return true;

        // if nums[i] == 1 for 0 <= i < n, then answer is false
        // it nums[0] == nums[1] == ... = nums[n-1] > 1 , then the answer is true

        int _parent[100001]; parent = _parent;
        int _size[100001]; size = _size;
        for(int i = 0; i < 100001; ++i) {
            parent[i] = i;
            size[i] = 1;
        }

        for(int i = 0; i < n; ++i) {
            if( nums[i] == 1 )
                return false;
            calc_divisors(nums[i]);
            for(int divisor: divisors[nums[i]])
                unite(divisor,nums[i]);
        }

        int root = find(nums[0]);
        for(int i = 1; i < n; ++i)
            if( root != find(nums[i]) )
                return false;

        return true;
    }
};
