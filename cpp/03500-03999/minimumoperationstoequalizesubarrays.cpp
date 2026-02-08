
// 3762. Minimum Operations to Equalize Subarrays
// https://leetcode.com/problems/minimum-operations-to-equalize-subarrays/



/* resources
 * https://cp-algorithms.com/data_structures/segment_tree.html#finding-the-k-th-smallest-number-in-a-range
 *
 */

class Solution {
private:
    struct Vertex {
        Vertex *l, *r;
        int cnt;
        long long sum;
        Vertex(int cnt, long long sum) : l(nullptr), r(nullptr), cnt(cnt), sum(sum) {}
        Vertex(Vertex *l, Vertex *r) : l(l), r(r), cnt(0), sum(0) {
            if( l ) {
                cnt += l->cnt;
                sum += l->sum;
            }
            if( r ) {
                cnt += r->cnt;
                sum += r->sum;
            }
        }
    };

    Vertex* build(int tl, int tr) {
        if (tl == tr)
            return new Vertex(0, 0);
        int tm = (tl + tr) / 2;
        return new Vertex(build(tl, tm), build(tm+1, tr));
    }

    Vertex* update(Vertex* v, int tl, int tr, int pos, long long val) {
        if (tl == tr)
            return new Vertex(v->cnt+1, v->sum+val);
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            // going left
            return new Vertex(update(v->l, tl, tm, pos, val), v->r);
        } else {
            // going right
            return new Vertex(v->l, update(v->r, tm+1, tr, pos, val));
        }
    }

    int find_kth(Vertex* vl, Vertex *vr, int tl, int tr, int k, long long& out_leftcount, long long& out_leftsum, long long& out_allkth) {
        if (tl == tr) {
            out_allkth += vr->sum - vl->sum;
            return tl;
        }
        int tm = (tl + tr) / 2;
        int left_count = vr->l->cnt - vl->l->cnt;
        if (left_count >= k)
            return find_kth(vl->l, vr->l, tl, tm, k, out_leftcount, out_leftsum, out_allkth);

        // going "right", we need to carry the sum and count of all nodes from left child
        out_leftcount += (long long)left_count;
        out_leftsum += vr->l->sum - vl->l->sum;
        return find_kth(vl->r, vr->r, tm+1, tr, k-left_count, out_leftcount, out_leftsum, out_allkth);
    }

public:
    vector<long long> minOperations(vector<int>& nums, int k, vector<vector<int>>& queries) {
        // vector<int> a(40000);
        // generate(a.begin(), a.end(), [i = 1] () mutable { return i++; });

        int n = nums.size(); // 1 <= n <= 40000; 1 <= nums[i] <= 1e9
        // TODO handle n == 1

        // idea
        // how do we know if we can make a given subarray equal given k
        // the difference between any pair in subarray must be a multiple of k
        // so the difference between neighboring elements must be multiple of k
        //     0   1   2   3   4   5   6   7   8   9   n = 10
        //      \ / \ / \ / \ / \ / \ / \ / \ / \ /
        //       0   1   2   3   4   5   6   7   8
        // so a query [l,r] where r-l > 0 woud be [l,r'] with r' = r-1
        // if the range has a diff not divisible, the whole range is ans -1
        // we know we can make it, the answer is at the median
        // so determine the median, then
        // let l left index of query, let r right index of query
        // let m be the index of the median
        // operations left of median index m:  ((median * (m-l)) - sum(l, m-1))/k
        // operations right of median index m: (sum(m+1, r) - (median * (r-m)))/k
        // we can handle 'can we make it' via prefixSum

        long long prefixSum[40001];
        prefixSum[0] = 0LL;
        int diff_divisible_by_k[40000];
        diff_divisible_by_k[0] = 0;
        map<int,int> dic;
        for(int i = 1; i < n; ++i) {
            prefixSum[i] = prefixSum[i-1] + (long long)nums[i-1];

            int diff = abs(nums[i-1] - nums[i]);
            diff_divisible_by_k[i] = diff_divisible_by_k[i-1] + (diff % k == 0);

            dic[nums[i-1]] = -1;
        }
        // finish up
        prefixSum[n] = prefixSum[n-1] + (long long)nums[n-1];
        dic[nums[n-1]] = -1;

        int dic_sz = dic.size(); // number of unique values in nums
        vector<int> kv(dic_sz);
        int kv_idx = 0;
        for(auto it = dic.begin(); it != dic.end(); ++it) {
            kv[kv_idx] = it->first;
            it->second = kv_idx;
            ++kv_idx;
        }

        // built something that we can ask a range query for the median
        // note when length of range is even, we need two values
        // Persistent Segment Tree
        // worst case scenario, we have 40000 distinct values
        int tl = 0, tr = dic_sz + 1;
        vector<Vertex*> roots;
        roots.push_back(build(tl, tr));
        for (int i = 0; i < n; ++i) {
            int val = nums[i];
            int key = dic[val];
            roots.push_back(update(roots.back(), tl, tr, key, val));
        }

        // find the 5th smallest number from the subarray [a[2], a[3], ..., a[19]]
        // int result = find_kth(roots[2], roots[20], tl, tr, 5);

        //            0 1 2 3 4 5
        // example   [5,7,3,1,3,3]
        // let us ask for range [1..5], and in that range the 3rd smallest
        // range        7 3 1 3 3
        // range sorted 1 3 3 3 7
        //                  x     3rd smallest
        // sum of smaller = 1
        // sum of all with value 3 = 9
        /*
        long long left_sum = 0LL;// sum of all smaller than the kth element in range
        long long all_kth = 0LL; // sum of all element with value of kth element
        int result = find_kth(roots[1], roots[6], tl, tr, 5, left_sum, all_kth);
        // result is a key, to get value: kv[key] aka kv[result];
        cout << kv[result] << endl;
        cout << "leftsum " << left_sum << endl;
        cout << "allkth  " << all_kth << endl;
        */

        int q_sz = queries.size();
        vector<long long> ans(q_sz, 0LL);
        for(int i = 0; i < q_sz; ++i) {
            int l = queries[i][0];
            int r = queries[i][1];
            int len = r-l+1;
            if( len == 1 )
                continue;

            // can we equalize subarray [l,r]?
            int t = diff_divisible_by_k[r] - diff_divisible_by_k[l];
            if( t != len-1 ) {
                ans[i] = -1LL;
                continue;
            }

            // the median is the element in the middle if we sort our range
            int m = len/2 + 1;

            long long left_count = 0LL; // count of all smaller than kth element in range
            long long left_sum = 0LL;   // sum of all smaller than the kth element in range
            long long all_kth = 0LL;    // sum of all element with value of kth element
            int result = find_kth(roots[l], roots[r+1], tl, tr, m, left_count, left_sum, all_kth);
            // result is a key, to get value: kv[key] aka kv[result];
            long long val = kv[result];

            long long sum = prefixSum[r+1] - prefixSum[l]; // total sum of range

            // we know every element in range should be val

            // left
            //     we know we have left_count elements smaller than val
            //     we know their sum is left_sum
            //     we know their sum should be left_count * val
            long long ops = ((left_count * val) - left_sum) / k;

            // right
            //     we know we have a total of len elements in range
            //     we know have have left count
            //     we can calculate number of elements with val ( all_kth/val )
            //     hence right_count = len - left_count - (all_kth/val)
            //     we can calculate right_sum
            long long right_count = len - left_count - (all_kth/val);
            long long right_sum = sum - left_sum - all_kth;
            ops += (right_sum - (right_count * val)) / k;

            ans[i] = ops;

            if( len % 2 == 0 ) {
                // we need to try for m-1 also
                m = m - 1;

                left_count = 0LL; // count of all smaller than kth element in range
                left_sum = 0LL;   // sum of all smaller than the kth element in range
                all_kth = 0LL;    // sum of all element with value of kth element
                result = find_kth(roots[l], roots[r+1], tl, tr, m, left_count, left_sum, all_kth);
                // result is a key, to get value: kv[key] aka kv[result];
                val = kv[result];

                // left
                ops = ((left_count * val) - left_sum) / k;

                // right
                right_count = len - left_count - (all_kth/val);
                right_sum = sum - left_sum - all_kth;
                ops += (right_sum - (right_count * val)) / k;

                ans[i] = min(ans[i], ops);
            }

        }

        return ans;
    }
};
