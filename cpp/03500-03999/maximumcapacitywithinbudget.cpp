
// 3814. Maximum Capacity Within Budget
// https://leetcode.com/problems/maximum-capacity-within-budget/


class Solution {
private:
    const static int INF = 100001;

    struct N {
        int cost;
        int capacity;
        N() : cost(INF), capacity(0) {}
    };

    N t[200002]; // segment tree, memory efficient implementation, max range query, point update

    N combine(N a, N b) {
        if( a.capacity > b.capacity )
            return a;
        if( b.capacity > a.capacity )
            return b;

        // a.capacity == b.capacity
        N nd;
        nd.capacity = a.capacity;
        nd.cost = min(a.cost, b.cost);

        return nd;
    }

    void build(vector<int>& a, int v, int tl, int tr) {
        if (tl == tr) {
            t[v].cost = tl;
            t[v].capacity = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(a, v+1, tl, tm);
            build(a, v+2*(tm-tl+1), tm+1, tr);
            t[v] = combine(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

    N get_max(int v, int tl, int tr, int l, int r) {
        if (l > r)
            return N();
        if (l == tl && r == tr) {
            return t[v];
        }
        int tm = (tl + tr) / 2;
        return combine(get_max(v+1, tl, tm, l, min(r, tm)),
                       get_max(v+2*(tm-tl+1), tm+1, tr, max(l, tm+1), r));
    }

    void update(int v, int tl, int tr, int pos, int new_val) {
        if (tl == tr) {
            t[v].cost = tl;
            t[v].capacity = new_val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm)
                update(v+1, tl, tm, pos, new_val);
            else
                update(v+2*(tm-tl+1), tm+1, tr, pos, new_val);
            t[v] = combine(t[v+1],t[v+2*(tm-tl+1)]);
        }
    }

public:
    int maxCapacity(vector<int>& costs, vector<int>& capacity, int budget) {
        int n = costs.size(); // 1 <= n <= 1e5; costs.size() == capacity.size()
                              // 1 <= costs[i], capacity[i] <= 1e5

        int mn_cost = INF;    // lowest cost of any machine
        int mxmx_cost = 0;    // highest cost of any machine
        int mx_cost = 0;      // second highest cost of any machine
        int mxmx_cap = 0;     // highest capacity of any machine
        int mx_cap = 0;       // second highest capacity of any machine
        // keep track of best one machine we could buy given our budget
        int best_one_machine_cost = -1; // could also init to 100000, or not init at all
        int best_one_machine_capacity = 0;
        vector<int> cap1(INF+1, 0); // best capacity for given cost
        vector<int> cap2(INF+1, 0); // second best capacity for given cost
        for(int i = 0; i < n; ++i) {
            int costi = costs[i];
            int capi  = capacity[i];

            mn_cost = min(mn_cost, costi);

            if( costi >= mxmx_cost ) {
                mx_cost = mxmx_cost;
                mxmx_cost = costi;
            } else if( costi > mx_cost ) {
                mx_cost = costi;
            }
            if( capi >= mxmx_cap ) {
                mx_cap = mxmx_cap;
                mxmx_cap = capi;
            } else if( capi > mx_cap ) {
                mx_cap = capi;
            }

            if( costi < budget ) {
                if( capi > best_one_machine_capacity ) {
                    best_one_machine_cost = costi;
                    best_one_machine_capacity = capi;
                } else if( capi == best_one_machine_capacity ) {
                    if( costi < best_one_machine_cost ) {
                        best_one_machine_cost = costi;
                    }
                }
            }

            if( capi >= cap1[costi] ) {
                cap2[costi] = cap1[costi];
                cap1[costi] = capi;
            } else if( capi > cap2[costi] ) {
                cap2[costi] = capi;
            }
        }
        /*
        for(int i = 1; i <= mxmx_cost; ++i)
            cout << i << ":" << cap1[i] << " ";
        cout << endl;
        */

        if( mn_cost >= budget )
            return 0;

        // we know at this point we can buy at least one machine

        if( n == 1 )
            return capacity[0];

        if( mxmx_cost + mx_cost < budget )
            return mxmx_cap + mx_cap;

        if( budget <= 2 )
            return best_one_machine_capacity;

        // buying only one machine is an option
        // cout << "best_one_machine_capacity " << best_one_machine_capacity << endl;
        int ans = best_one_machine_capacity;

        // for cost spent in range budget-2..1
        //    we buy the best possible machine aka highest capacity
        //    now we have remaining budget rem = budget - spent
        //    we buy the best possible machine

        build(cap1, 1, 0, mxmx_cost);

        // TODO we only need to investigate costs where we have machines
        for(int spend = 1; spend < budget-1; ++spend) {
            int rem = (budget-1) - spend;
            // cout << "spend " << spend << " rem " << rem << " spend+rem " << spend+rem << endl;
            if( rem < spend )
                break;

            // let us buy the best machine that spend can get us
            N nd1 = get_max(1, 0, mxmx_cost, 0, min(spend, mxmx_cost));
            int m1 = nd1.capacity;
            if( m1 == 0 )
                continue;
            int actual_spend = nd1.cost;
            // cout << "  m1 " << m1 << " actual_spend " << actual_spend << endl;

            // replace the best machine at cost with the machine of second best capacity, if any
            update(1, 0, mxmx_cost, actual_spend, cap2[actual_spend]);

            int actual_rem = (budget-1) - actual_spend;
            // cout << "  actual_rem " << actual_rem << "  actual_spend+actual_rem " << actual_spend+actual_rem << endl;
            // let us buy the second best machine that actual rem can get us
            N nd2 = get_max(1, 0, mxmx_cost, 0, min(actual_rem, mxmx_cost));
            int m2 = nd2.capacity;
            // cout << "  m2 " << m2 << endl;

            ans = max(ans, m1 + m2);

            // backtrack
            update(1, 0, mxmx_cost, actual_spend, cap1[actual_spend]);
        }

        return ans;
    }
};
