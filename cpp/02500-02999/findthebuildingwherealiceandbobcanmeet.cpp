
// 2940. Find Building Where Alice and Bob Can Meet
// https://leetcode.com/problems/find-building-where-alice-and-bob-can-meet/

// this solution barely passes 

/* Alice height | Bob height  || Alice index | Bob index
 * =============|=============||=============|=============
 *              =             ||             =              case 0 they are already at the same building
 *              <             ||             <              case 1 meet at Bob
 *              >             ||             <              case 2 meet at an index > Bob index and height > Alice height
 *              >             ||             >              case 3 meet at Alice
 *              <             ||             >              case 4 meet at an index > Alice index and height > Bob height
 *              =             ||            !=              case 5 meet at an index > max(Alice index,Bob index) and height > Alice heigt
 *
 * ideally we had a balanced binary search tree
 * where we insert the heights up to max_heights_idx + 1
 * and maintain on each node a property of the min idx seen for anything greater
 * sorted queries
 *        int q_sz = queries.size();
 *       vector<vector<int>> q(q_sz);
 *       for(int i = 0; i < q_sz; ++i)
 *           q[i] = {queries[i][0],queries[i][1],i};
 *       sort(q.begin(),q.end(),[](const vector<int>& a, const vector<int>& b){
 *           int A = max(a[0],a[1]);
 *           int B = max(b[0],b[1]);
 *           return A > B;
 *       });
 * then just go through them and build the search tree as we go along
 */
class Solution {
private:
    map<int,vector<int>> mp; // height, indicies at which height occurs
    map<int,vector<int>>::iterator a[50000];

    vector<int> t[200000]; // segment tree "merge sort tree"

    const int INF = 100000;

    void build(int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl]->second;
        } else {
            int tm = (tl + tr) / 2;
            build(v*2, tl, tm);
            build(v*2+1, tm+1, tr);
            // merge(t[v*2].begin(), t[v*2].end(), t[v*2+1].begin(), t[v*2+1].end(), back_inserter(t[v]));
            // merge
            int i = 0, j = 0, k = 0;
            t[v].resize(t[v*2].size() + t[v*2+1].size());
            while( i < t[v*2].size() && j < t[v*2+1].size() ) {
                if( t[v*2][i] < t[v*2+1][j] ) {
                    t[v][k] = t[v*2][i];
                    ++i;
                } else {
                    t[v][k] = t[v*2+1][j];
                    ++j;
                }
                ++k;
            }
            while( i < t[v*2].size() ) {
                t[v][k] = t[v*2][i];
                ++i;
                ++k;
            }
            while( j < t[v*2+1].size() ) {
                t[v][k] = t[v*2+1][j];
                ++j;
                ++k;
            }
        }
    }

    int query(int v, int tl, int tr, int l, int r, int x) {
        if (l > r)
            return INF;
        if (l == tl && r == tr) {
            vector<int>::iterator pos = upper_bound(t[v].begin(), t[v].end(), x);
            if (pos != t[v].end())
                return *pos;
            return INF;
        }
        int tm = (tl + tr) / 2;
        return min(query(v*2, tl, tm, l, min(r, tm), x),
                   query(v*2+1, tm+1, tr, max(l, tm+1), r, x));
    }

    // binary search upper bound
    int search(int s, int e, int target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( a[mid]->first > target ) {
            // can we do better?
            int t = search(s,mid-1,target);
            return t != -1 ? t : mid;
        }

        return search(mid+1,e,target);
    }

public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        int i;

        int heights_sz = heights.size();
        for(i = 0; i < heights_sz; ++i)
            mp[heights[i]].push_back(i);
        i = 0;
        for(auto it = mp.begin(); it != mp.end(); ++it)
            a[i++] = it;

        int a_sz = mp.size();
        build(1, 0, a_sz-1);

        int q_sz = queries.size();
        vector<int> ans(q_sz);
        int g_max_height = mp.rbegin()->first;
        for(int i = 0; i < q_sz; ++i) {
            int alice_idx = queries[i][0];
            int bob_idx   = queries[i][1];

            // case 0
            if( alice_idx == bob_idx ) {
                ans[i] = alice_idx;
                continue;
            }

            int alice_height = heights[alice_idx];
            int bob_height = heights[bob_idx];
            // case 1
            if( alice_height < bob_height && alice_idx < bob_idx ) {
                ans[i] = bob_idx;
                continue;
            }
            // case 3
            if( alice_height > bob_height && alice_idx > bob_idx ) {
                ans[i] = alice_idx;
                continue;
            }

            // case 2, 4 and 5
            int max_idx = max(alice_idx, bob_idx);
            if( max_idx == heights_sz-1 ) {
                ans[i] = -1;
                continue;
            }
            int max_height = max(alice_height, bob_height);
            if( max_height == g_max_height ) {
                ans[i] = -1;
                continue;
            }
            // cout << "starting search max_height " << max_height << " max_id " << max_idx << endl;
            int l = search(0,a_sz-1,max_height);
            int t = query(1,0,a_sz-1,l,a_sz-1,max_idx);
            ans[i] = t != INF ? t : -1;
        }

        return ans;
    }
};



// this should be faster as it uses fractional cascading to save on binary searches
// https://cp-algorithms.com/data_structures/segment_tree.html#find-the-smallest-number-greater-or-equal-to-a-specified-number-acceleration-with-fractional-cascading
// https://medium.com/@arpitbhayani/fractional-cascading-speeding-up-binary-searches-7679ebd2868

class Solution {
private:
    map<int,vector<int>> mp; // height, indicies at which height occurs
    map<int,vector<int>>::iterator a[50000];

    vector<int> t[200000]; // segment tree "merge sort tree" with fractional cascading
    vector<int> aux_l[200000];
    vector<int> aux_r[200000];

    const int INF = 100000;

    int upper_bound(int v, int target) {

        int n = t[v].size();

        // returns 'n' if nums[n-1] <= target
        // returns  0  if nums[0] > target
        // binary search upper bound while loop
        // upper bound -> greater than target
        int s = 0;
        int e = n; // n = nums.size()
        int mid;
        while(s < e) {
            mid = s + ((e-s)/2);
            if( target >= t[v][mid] )
                s = mid + 1;
            else
                e = mid;
        }
        if( s < n && t[v][s] <= target )
            ++s;

        return s;
    }


    void build(int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl]->second;
        } else {
            int tm = (tl + tr) / 2;
            build(v*2, tl, tm);
            build(v*2+1, tm+1, tr);
            // merge(t[v*2].begin(), t[v*2].end(), t[v*2+1].begin(), t[v*2+1].end(), back_inserter(t[v]));
            // merge
            int i = 0, j = 0, k = 0;
            t[v].resize(t[v*2].size() + t[v*2+1].size());
            aux_l[v].resize(t[v*2].size() + t[v*2+1].size());
            aux_r[v].resize(t[v*2].size() + t[v*2+1].size());
            while( i < t[v*2].size() && j < t[v*2+1].size() ) {
                if( t[v*2][i] < t[v*2+1][j] ) {
                    t[v][k] = t[v*2][i];
                    aux_l[v][k] = i;
                    aux_r[v][k] = j;
                    ++i;
                } else {
                    t[v][k] = t[v*2+1][j];
                    aux_l[v][k] = i;
                    aux_r[v][k] = j;
                    ++j;
                }
                ++k;
            }
            while( i < t[v*2].size() ) {
                t[v][k] = t[v*2][i];
                aux_l[v][k] = i;
                aux_r[v][k] = j;
                ++i;
                ++k;
            }
            while( j < t[v*2+1].size() ) {
                t[v][k] = t[v*2+1][j];
                aux_l[v][k] = i;
                aux_r[v][k] = j;
                ++j;
                ++k;
            }
        }
    }

    int query(int v, int tl, int tr, int l, int r, int x, int ub) {
        if (l > r || ub == t[v].size() )
            return INF;

        // at root
        if( v == 1 )
            ub = upper_bound(v,x);

        if (l == tl && r == tr) {
            /*
            vector<int>::iterator pos = upper_bound(t[v].begin(), t[v].end(), x);
            if (pos != t[v].end())
                return *pos;
            return INF;
            */
            /*
            int pos = upper_bound(v,x);
            if( pos < t[v].size() )
                return t[v][pos];
            return INF;
            */
            return t[v][ub];
        }
        int tm = (tl + tr) / 2;
        return min(query(v*2, tl, tm, l, min(r, tm), x, aux_l[v][ub]),
                   query(v*2+1, tm+1, tr, max(l, tm+1), r, x, aux_r[v][ub]));
    }

    // binary search upper bound
    int search(int s, int e, int target) {
        if( s > e )
            return -1;

        int mid = s + ((e-s)/2);
        if( a[mid]->first > target ) {
            // can we do better?
            int t = search(s,mid-1,target);
            return t != -1 ? t : mid;
        }

        return search(mid+1,e,target);
    }

public:
    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        int i;

        int heights_sz = heights.size();
        for(i = 0; i < heights_sz; ++i)
            mp[heights[i]].push_back(i);
        i = 0;
        for(auto it = mp.begin(); it != mp.end(); ++it)
            a[i++] = it;

        int a_sz = mp.size();
        build(1, 0, a_sz-1);

        int q_sz = queries.size();
        vector<int> ans(q_sz);
        int g_max_height = mp.rbegin()->first;
        for(int i = 0; i < q_sz; ++i) {
            int alice_idx = queries[i][0];
            int bob_idx   = queries[i][1];

            // case 0
            if( alice_idx == bob_idx ) {
                ans[i] = alice_idx;
                continue;
            }

            int alice_height = heights[alice_idx];
            int bob_height = heights[bob_idx];
            // case 1
            if( alice_height < bob_height && alice_idx < bob_idx ) {
                ans[i] = bob_idx;
                continue;
            }
            // case 3
            if( alice_height > bob_height && alice_idx > bob_idx ) {
                ans[i] = alice_idx;
                continue;
            }

            // case 2, 4 and 5
            int max_idx = max(alice_idx, bob_idx);
            if( max_idx == heights_sz-1 ) {
                ans[i] = -1;
                continue;
            }
            int max_height = max(alice_height, bob_height);
            if( max_height == g_max_height ) {
                ans[i] = -1;
                continue;
            }
            // cout << "starting search max_height " << max_height << " max_id " << max_idx << endl;
            int l = search(0,a_sz-1,max_height);
            int t = query(1,0,a_sz-1,l,a_sz-1,max_idx,-1);
            ans[i] = t != INF ? t : -1;
        }

        return ans;
    }
};
