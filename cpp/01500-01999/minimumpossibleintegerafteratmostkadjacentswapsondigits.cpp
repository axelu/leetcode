
// 1505. Minimum Possible Integer After at Most K Adjacent Swaps On Digits
// https://leetcode.com/problems/minimum-possible-integer-after-at-most-k-adjacent-swaps-on-digits/



// https://cp-algorithms.com/data_structures/segment_tree.html#addition-on-segments

class Solution {
private:
    int t[120000]; // segment tree

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = tl;
        } else {
            int tm = (tl + tr) / 2;
            build(v*2, tl, tm);
            build(v*2+1, tm+1, tr);
            t[v] = 0;
        }
    }

    // range update
    void update(int v, int tl, int tr, int l, int r, int add) {
        if (l > r)
            return;
        if (l == tl && r == tr) {
            t[v] += add;
        } else {
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), add);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, add);
        }
    }

    int get(int v, int tl, int tr, int pos) {
        if (tl == tr)
            return t[v];
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            return t[v] + get(v*2, tl, tm, pos);
        else
            return t[v] + get(v*2+1, tm+1, tr, pos);
    }

public:
    string minInteger(string num, int k) {
        // 1 <= num.length <= 3 * 10^4

        int n = num.size();

        // initially our segment tree will have the index
        // of our 'leaves' at those, and each partition of two or more
        // will be 0
        build(1,0,n-1);

        // we will traverse num from left to right
        // at each index we will try to replace with the
        // leftmost lowest number possible that is in reach.
        // when we do that, then we will adjust the indexes
        // to the right by -1 (range update)
        // example
        // 0 1 2 3 4
        // 5 3 2 0 1  <- assuming we are at idx 0 and k >= 4, we replace 5 with 0
        // 0 5 3 2 1
        // however, another way to look at the replacement is the following:
        // 5 3 2 1   in which case we changed the index of '1' from 4 to 3

        // store the idxs of numbers 0,1,2,3,4,5,6,7,8,9
        // the queue for each number will have the left most index in the front
        queue<int> idxs[10];
        for(int i = 0; i < n; ++i)
            idxs[num[i]-'0'].push(i);

        string ans;

        for(int i = 0; i < n; ++i) {
            if( num[i] == '#' )
                continue;
            int x = num[i]-'0';
            int cur_pos = get(1,0,n-1,i);

            // find the best number in reach to replace x with (greedy)
            // which is the left most lowest number in distance <= k
            bool f = false;
            if( k > 0 )
                for(int j = 0; j < x; ++j) {
                    if( !idxs[j].empty() ) {
                        int org_pos = idxs[j].front();
                        int new_pos = get(1,0,n-1,org_pos);
                        int dist = new_pos - cur_pos;
                        if( dist <= k ) {
                            ans.push_back(j+'0');
                            f = true;
                            k -= dist;
                            idxs[j].pop();
                            // decrease all indicies after the position where we found
                            // the replacement -> range update
                            update(1,0,n-1,org_pos+1,n-1,-1);
                            --i; // we will stay at index i (loop will advance i)
                            // mark the original position as consumed
                            num[org_pos] = '#';
                            break;
                        }
                    }
                }
            if( !f ) {
                ans.push_back(num[i]);
                idxs[num[i]-'0'].pop();
            }
        }

        return ans;
    }
};
