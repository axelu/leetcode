
// 3378. Count Connected Components in LCM Graph
// https://leetcode.com/problems/count-connected-components-in-lcm-graph/


// LCM of two numbers is the smallest number which can be divided by both numbers

class Solution {
private:
    // disjoint-set path compression size
    vector<int> parent;
    vector<int> size;

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

public:
    int countComponents(vector<int>& nums, int threshold) {
        int n = nums.size(); // 1 <= nums.length <= 1e5, all elements of nums are unique

        // 1 <= nums[i] <= 1e9
        // 1 <= threshold <= 2 * 1e5

        // if a given nums[i] > threshold, then its LCM with any number > threshold
        // we can eliminate aka count all nums[i] > threshold each as one component

        sort(nums.begin(),nums.end());

        // TODO if nums[0] = 1, all nums[i] <= threshold are connected
        // we can count the ones greater threshold, our answer is that count + 1

        parent.resize(threshold+1);
        size.resize(threshold+1);
        for(int i = 0; i <= threshold; ++i) {
            parent[i] = i;
            size[i] = 1;
        }

        for(int i = 0; i < n && nums[i] <= (threshold/2); ++i) {
            int a = nums[i];
            // cout << "val " << a << endl;

            // if our current element is already connected, then we got by it with a
            // smaller element already, meaning
            // all its multiples would already be connected, hence we can skip
            if( find(a) != a )
                continue;

            for(int k = 2; a * k <= threshold; ++k) {
                int b = a * k;
                // cout << "uniting " << a << " " << b << endl;
                unite(a,b);
            }
        }

        int ans = 0;

        unordered_set<int> us;
        for(int i = 0; i < n; ++i) {
            if( nums[i] <= threshold ) {
                int p = find(nums[i]);
                // cout << "nums[i] " << nums[i] << " parent " << p << endl;
                us.insert(p);

            } else {
                ++ans;
            }
        }

        return us.size() + ans;
    }
};
