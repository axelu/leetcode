
// 3711. Maximum Transactions Without Negative Balance
// https://leetcode.com/problems/maximum-transactions-without-negative-balance/

// think about using BIT instead of segment tree to make it faster

class Solution {
private:
    long t[400000];      // segment tree (min), lazy propagation, range addition, range query
    long lazy[400000];

    void build(vector<long>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v*2, tl, tm);
            build(a, v*2+1, tm+1, tr);
            t[v] = min(t[v*2], t[v*2+1]);
        }
    }

    void push(int v) {
        t[v*2] += lazy[v];
        lazy[v*2] += lazy[v];
        t[v*2+1] += lazy[v];
        lazy[v*2+1] += lazy[v];
        lazy[v] = 0;
    }

    // range addition
    void update(int v, int tl, int tr, int l, int r, long addend) {
        if (l > r)
            return;
        if (l == tl && tr == r) {
            t[v] += addend;
            lazy[v] += addend;
        } else {
            push(v);
            int tm = (tl + tr) / 2;
            update(v*2, tl, tm, l, min(r, tm), addend);
            update(v*2+1, tm+1, tr, max(l, tm+1), r, addend);
            t[v] = min(t[v*2], t[v*2+1]);
        }
    }

    // get min
    long query(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return LONG_MAX;
        if (l == tl && tr == r)
            return t[v];
        push(v);
        int tm = (tl + tr) / 2;
        return min(query(v*2, tl, tm, l, min(r, tm)),
                   query(v*2+1, tm+1, tr, max(l, tm+1), r));
    }

public:
    int maxTransactions(vector<int>& transactions) {
        // our min ans is count of all non-negatives

        // eliminate all negatives from begin
        for(auto it = transactions.begin(); it != transactions.end(); ) {
            if( *it >= 0 )
                break;
            it = transactions.erase(it);
        }
        int n = transactions.size();
        if( n == 0 ) // all negatives
            return 0;

        vector<long> a; // sum of running non-negatives
        long sum = 0L;
        vector<pair<int,int>> negpos; // {{val,pos}, {val,pos}, ..}
        int a_sz = 0;
        for(int i = 0; i < n; ++i) {
            if( transactions[i] >= 0 ) {
                sum += transactions[i];
            } else {
                a.push_back(sum);
                negpos.push_back({transactions[i],a_sz});
                ++a_sz;
            }
        }

        if( a_sz == 0 ) // all non-negatives
            return n;

        build(a, 1, 0, a_sz-1);

        // we process starting with smaller negatives from the right
        sort(negpos.begin(), negpos.end(), [](const pair<int,int>& a, const pair<int,int>& b){
            if( a.first > b.first ) {
                return true;
            } else if( a.first == b.first ) {
                if( a.second > b.second ) {
                    return true;
                }
            }
            return false;
        });


        int ans = n - a_sz; // count of non-negatives is our base ans
        // cout << "count non-negatives " << ans << endl;

        for(int i = 0; i < a_sz; ++i) {
            long neg = negpos[i].first;
            int pos = negpos[i].second;

            // get min in range [pos..a_sz-1]
            // if that min >= neg, then we can capture it
            long mn = query(1, 0, a_sz-1, pos, a_sz-1);
            if( mn >= (-1L * neg) ) {
                ++ans;
                update(1, 0, a_sz-1, pos, a_sz-1, neg);
            }
        }

        return ans;
    }
};

/* test cases

[2,-5,3,-1,-2]
[-1,-2,-3]
[3,-2,3,-2,1,-1]
[1,0,0,0]
[664,-144,-536,-761,366,-723,-990,248,-732,-689,782,507,92,-535,-638,-118,917,835,-371,-281,-385,-368,-649,492,-489,-630,-241,-782,-540,153,951,988,-131,30,300,-649,-342,286,-952,-217,219,-696,-621,-413,826]
[-4,3]
[-5,8,-4]
[-755,266,-415,629,634,-427,-936,-226,-122,237,211,106,873,-156,52,-195,673,-380,408,-3,244,-95,634,897,-858,-964,-714,-435,727,532,-635,-306,168,-878,-236,97,-898,58,-948,546,104,-248,509,796,-860,-888,-25,-410,-112,489,105,840,837,-505,795,-547,-779,-999,-285,400,201,426,336,-507,-553,-764,-584,838,350,-421,-19,-996,799,-850,-624,-49,-266,-496,-177,192,378,-174,-904,-520,36,-671,793,555,-21]
[-762,-100,-454,-695,60,-688,911,-946,786,99,601,-254,-346,501,-129,-21,-78,-195,-915,-208,434,597,-868,-152,-895,-340,-667,194,414,-26,-624,-25,-402,-103,-401,594,-430,174,515,587,-208,-385,22,12,-800,-912,26,269,-253,591,-302,851,227,-332,364,846,-114,30,-535,744,53,632,-281,-62,-222,792,-607,-338,-875,-985,947,-646,576,572,-486,341,-781,834,457,-892,199,-788,921,-466,-119,-509,749,15,86,-286,-44,-541,730,50,-896,-247,-632]
[6,-3,-3,1,-1,-1,-1,-1,-1,-1,1,-2]

*/
