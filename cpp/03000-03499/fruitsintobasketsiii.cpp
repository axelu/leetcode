
// 3479. Fruits Into Baskets III
// https://leetcode.com/problems/fruits-into-baskets-iii/






class Solution {
private:
    long long t[200002]; // segment tree memory efficient indexing, max, max range query, pos update
    // we use our segment tree as a binary search tree (BST)

    long long get_max(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return 0;
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return max(get_max(v+1, tl, tm, l, min(r, tm)),
                   get_max(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r));
    }

    void update(int v, int tl, int tr, int pos, long long new_val) {
        if (tl == tr) {
            t[v] = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v+1, tl, tm, pos, new_val);
            else
                update(v+2*(tm-tl+1), tm+1, tr, pos, new_val);
            t[v] = max(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    // binary search
    int search(int s, int e, int n, int target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        int mx = get_max(1, 0, n-1, 0, mid);
        if( mx >= target ) {
            // can we do better?
            int t = search(s, mid-1, n, target);
            return t != -1 ? t : mid;
        }

        return search(mid+1, e, n, target);
    }

public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int n = fruits.size(); // fruits.size() == baskets.size()

        int ans = 0;

        // we will build our segment tree lazily
        int j = 0; // index in baskets
        for(int i = 0; i < n; ++i) {
            int required_capacity = fruits[i];

            // if our tree has already a basket with
            // basket_capacity >= required_capacity
            // then we need to find the left most of those baskets
            if( t[1] >= required_capacity ) {
                int t = search(0, n-1, n, required_capacity);
                update(1, 0, n-1, t, 0);
            } else {
                if( j == n ) {
                    ++ans;
                    continue;
                } else {
                    bool has_basket_with_required_capacity = false;
                    for(; j < n; ++j) {
                        if( baskets[j] >= required_capacity ) {
                            has_basket_with_required_capacity = true;
                            ++j;
                            break;
                        } else {
                            update(1, 0, n-1, j, baskets[j]);
                        }
                    }
                    if( !has_basket_with_required_capacity )
                        ++ans;
                }
            }
        }

        return ans;
    }
};
