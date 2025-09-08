

// 3656. Determine if a Simple Graph Exists
// https://leetcode.com/problems/determine-if-a-simple-graph-exists/




    /*
    process nodes starting from max degree
    take the first node (largest degree),
    connect to nodes max degree downward,
    if success, continue (nodes that have degree 0,
    don't consider anymore)
    so we could do a segment tree, nodes in order
    of degree starting at largest
    then we do a range update -1 for the number
    of edges we need to add to current node for
    'number edges' nodes starting from rightmost
    node who's degree > 0
    before we do, if we know the leftmost 0 degree,
    we can check if we cross us from the rigt, if
    we do, we have no solution

    3 3 3 3 3 2 2 2 2 1 1 expected: false
    0 2 2 2 3 2 2 2 2 1 1
    0 0 1 1 3 2 2 2 2 1 1
    0 0 0 0 3 2 2 2 2 1 1
    0 0 0 0 0 1 1 1 2 1 1
    0 0 0 0 0 0 0 1 2 1 1
    0 0 0 0 0 0 0 0 1 1 1
    0 0 0 0 0 0 0 0 0 0 1 halt when degree > remaining [non-zero] positions

    3 3 3 3 2 2 2 2 1 1 expected: true
    0 2 2 2 2 2 2 2 1 1
    0 0 1 1 2 2 2 2 1 1
    0 0 0 0 2 2 2 2 1 1
    0 0 0 0 0 1 1 2 1 1
    0 0 0 0 0 0 0 2 1 1
    0 0 0 0 0 0 0 0 0 0

    3 3 1 1 expected: false
    0 2 0 0
    0 0-1-1

    3 3 2 1 1 expected true, but our idea doesn't work
    0 2 1 0 1
    0 0 0-1 1 as we are failing when we hit -1 position

    we always need to continue with the nodes
    that we have with the highest degree!!!
    hence we will count by degree, and 'push'
    the once we cannot connect to their next respective
    degree
 */
class Solution {
public:
    bool simpleGraphExists(vector<int>& degrees) {
        int n = degrees.size();

        vector<int> cnt(n); // 0 <= degrees[i] <= n - 1, hence n sufficient
        for(int i = 0; i < n; ++i)
            ++cnt[degrees[i]];

        // right to left aka highest degree to lowest
        for(int i = n - 1; i > 0; --i) { // i is our degree
            while( cnt[i] > i ) {
                // connect one node to i other nodes
                // that satisfies all required connections on that node
                // the other i nodes now have a degree i-1
                // so we 'push' them down to the next lower degree
                cnt[i] -= i + 1;
                cnt[i-1] += i;
            }

            if( cnt[i] == 0 ) // nothing to do
                continue;

            // 0 < cnt[i] <= i
            // we have cnt[i] nodes
            // connect one node to cnt[i] - 1 other nodes
            // let us call the nodes we connected to carry, as those
            // nodes have now a degree i-1, and we need to push them down
            // to the next lower degree
            // the node that we connected, still may have
            // unsatisfied connections, let us call those rem
            // we will satisfy those with lower degree nodes,
            // if we can
            // at each lower degree, we get a new carry
            int carry = cnt[i] - 1; // nodes we connected to that now have degree i-1
            int rem = i - (cnt[i] - 1); // connections still to be satisfied

            cnt[i] = 0;

            for(int j = i - 1; j > 0; j--) {
                if( cnt[j] > 0 ) {
                    int can_satisfy = min(cnt[j], rem);
                    rem -= can_satisfy;

                    // subtract the nodes that we connected
                    cnt[j] -= can_satisfy;

                    // push the nodes from prior step
                    cnt[j] += carry;

                    // the nodes we connected to become our NEW carry
                    // as we need to push them to the next lower degree
                    // in the next step
                    carry = can_satisfy;

                } else if( carry > 0 )  {
                    // push the nodes from prior step
                    cnt[j] += carry;
                    carry = 0;
                }

                // early exit
                if( carry == 0 && rem == 0 )
                    break;
            }
            // if we were not able to satisfy all remaining connections
            // then we have no solutions
            if( rem > 0 )
                return false;

        }

        return true;
    }
};
