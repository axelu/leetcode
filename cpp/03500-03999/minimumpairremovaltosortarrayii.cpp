
// 3510. Minimum Pair Removal to Sort Array II
// https://leetcode.com/problems/minimum-pair-removal-to-sort-array-ii/




class Solution {
private:
   struct T {
        int lft_idx;
        long long lft_val;
        long long rgt_val;
        T * prev;
        T * next;
        T(int lft_idx, long long lft_val, long long rgt_val) : lft_idx(lft_idx), lft_val(lft_val), rgt_val(rgt_val), prev(nullptr), next(nullptr) {}
   };

    map<long long,map<int,T*>> by_pair_sum;

    void remove_node_from_by_pair_sum(T * t) {
        long long pair_sum = t->lft_val + t->rgt_val;
        int lft_idx = t->lft_idx;

        by_pair_sum[pair_sum].erase(lft_idx);
        if( by_pair_sum[pair_sum].empty() )
            by_pair_sum.erase(pair_sum);

        return;
    }

    // debug
    void print_node(T * t) {
        if( t == nullptr ) {
            cout << "t is a nullptr" << endl;
            return;
        }
        cout << "t->lft_idx " << t->lft_idx << " t->lft_val " << t->lft_val << " t->rgt_val " << t->rgt_val << endl;
        return;
    }

public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        if( n == 1 )
            return 0;
        if( n == 2 )
            return nums[0] > nums[1];


        // construct our initial doubly linked list from nums
        // count pairs where left side > right side
        int pairs_lft_gt_rgt = 0;

        T * pre = nullptr;
        for(int i = 0; i < n-1; ++i) {
            // pair nums[i], nums[i+1]
            T * t = new T(i, nums[i], nums[i+1]);
            if( pre != nullptr ) {
                t->prev = pre;
                pre->next = t;
            }
            auto p = by_pair_sum[nums[i]+nums[i+1]].insert({i,t});

            if( nums[i] > nums[i+1] )
                ++pairs_lft_gt_rgt;

            pre = t;
        }

        // cout << "pairs_lft_gt_rgt " << pairs_lft_gt_rgt << endl;

        int ans = 0;

        while( pairs_lft_gt_rgt != 0 ) {
            // cout << "pairs_lft_gt_rgt " << pairs_lft_gt_rgt << endl;
            ++ans;

            // get pair with smallest sum and lowest left index
            auto it = by_pair_sum.begin();
            T * curr = it->second.begin()->second;
            // print_node(curr);
            it->second.erase(it->second.begin());
            if( it->second.empty() )
                by_pair_sum.erase(it);

            T * prev = curr->prev;
            T * next = curr->next;

            long long val_new = curr->lft_val + curr->rgt_val;
            // maintain pairs_lft_gt_rgt
            if( curr->lft_val > curr->rgt_val )
                --pairs_lft_gt_rgt;

            // curr will be removed

            if( prev == nullptr && next == nullptr ) {
                // there is are two values in nums left
                // we are done
                delete (curr);
                break;

            } else if( prev != nullptr && next != nullptr ) {
                // prev and next will be connected
                // we are basically changing the value to (t->lft_val + t->rgt_val)

                // pull prev from its current by_pair_sum
                remove_node_from_by_pair_sum(prev);
                // maintain pairs_lft_gt_rgt
                if( prev->lft_val > prev->rgt_val )
                    --pairs_lft_gt_rgt;
                // prev->rgt_val will become val_new
                prev->rgt_val = val_new;
                // maintain pairs_lft_gt_rgt
                if( prev->lft_val > prev->rgt_val )
                    ++pairs_lft_gt_rgt;
                prev->next = next;
                // add prev to by_pair_sum based on its new sum
                by_pair_sum[prev->lft_val + prev->rgt_val].insert({prev->lft_idx,prev});

                // pull next from its current by_pair_sum
                remove_node_from_by_pair_sum(next);
                // maintain pairs_lft_gt_rgt
                if( next->lft_val > next->rgt_val )
                    --pairs_lft_gt_rgt;
                // next->lft_val will become val_new
                next->lft_val = val_new;
                // maintain pairs_lft_gt_rgt
                if( next->lft_val > next->rgt_val )
                    ++pairs_lft_gt_rgt;
                next->prev = prev;
                // add next to by_pair_sum based on its new sum
                by_pair_sum[next->lft_val + next->rgt_val].insert({next->lft_idx,next});


            } else if( prev == nullptr ) {

                // pull next from its current by_pair_sum
                remove_node_from_by_pair_sum(next);
                // maintain pairs_lft_gt_rgt
                if( next->lft_val > next->rgt_val )
                    --pairs_lft_gt_rgt;
                // next->lft_val will become val_new
                next->lft_val = val_new;
                // maintain pairs_lft_gt_rgt
                if( next->lft_val > next->rgt_val )
                    ++pairs_lft_gt_rgt;
                next->prev = prev;
                // add next to by_pair_sum based on its new sum
                by_pair_sum[next->lft_val + next->rgt_val].insert({next->lft_idx,next});


            } else { // next == nullptr

                // pull prev from its current by_pair_sum
                remove_node_from_by_pair_sum(prev);
                // maintain pairs_lft_gt_rgt
                if( prev->lft_val > prev->rgt_val )
                    --pairs_lft_gt_rgt;
                // prev->rgt_val will become val_new
                prev->rgt_val = val_new;
                // maintain pairs_lft_gt_rgt
                if( prev->lft_val > prev->rgt_val )
                    ++pairs_lft_gt_rgt;
                prev->next = next;
                // add prev to by_pair_sum based on its new sum
                by_pair_sum[prev->lft_val + prev->rgt_val].insert({prev->lft_idx,prev});


            }

            delete (curr);
        }

        return ans;
    }
};
