
// 1029. Two City Scheduling
// https://leetcode.com/problems/two-city-scheduling/



class Solution {
private:
    void printWhoCost(unordered_set<int>& us, vector<vector<int>>& costs, int city) {
        int cost = 0;
        cout << "going to city " << city << ": ";
        for(int i : us) {
            cout << i << " ";
            cost += costs[i][city];
        }
        cout << "total cost " << cost << endl;
    }


public:
    int twoCitySchedCost(vector<vector<int>>& costs) {
        unordered_set<int> a;
        unordered_set<int> b;
        unordered_set<int> c; // a == b

        int n2 = costs.size();
        int n = n2/2;

        int A = 0, B = 0, C = 0;
        // greedily sending person to cheaper city
        for(int i = 0; i < n2; ++i) {
            if( costs[i][0] < costs[i][1] ) {
                a.insert(i);
                A += costs[i][0];
            } else if( costs[i][0] > costs[i][1] ) {
                b.insert(i);
                B += costs[i][1];
            } else {
                c.insert(i);
                C += costs[i][0];
            }
        }
        if( a.size() == n )
            return A+B;

        // if there are folks in c, then lets distribute
        // those to a and b
        while( c.size() > 0 ) {
            if( a.size() <= b.size() ) {
                a.insert(*c.begin());
                A += costs[*c.begin()][0];
            } else {
                b.insert(*c.begin());
                B += costs[*c.begin()][1];
            }
            c.erase(c.begin());
        }
        if( a.size() == n )
            return A+B;

        // we still have more going to one city
        // cout << "before goeing to a " << a.size() << " goint to b " << b.size() << endl;
        // cout << " cost A " << A << " cost B " << B << endl;
        // printWhoCost(a,costs,0);
        // printWhoCost(b,costs,1);
        // cout << A+B << endl;
        // we need to move the folks where the difference
        // is minimum
        // example, lets assume more to b than a
        //     a    b
        //  1 35    5 changing would increase $30
        //  2 25   10 changing would increase $15
        //  so we would change person 2 from b to a
        if( a.size() > b.size() ) {
            vector<array<int,3>> t;
            for(auto it = a.begin(); it != a.end(); ++it) {
                t.push_back({*it,costs[*it][0],costs[*it][1]});
            }
            sort(t.begin(),t.end(),[](const array<int,3>& lhs, const array<int,3>& rhs){
                int da = lhs[2]-lhs[1];
                int db = rhs[2]-rhs[1];
                return da < db;
            });
            int i = 0;
            while( b.size() < a.size() ) {
                a.erase(t[i][0]); b.insert(t[i][0]);
                A -= t[i][1];     B += t[i][2];
                ++i;
            }
            //cout << "after going to a " << a.size() << " going to b " << b.size() << endl;
            //cout << " cost A " << A << " cost B " << B << endl;
            //printWhoCost(a,costs,0);
            //printWhoCost(b,costs,1);
            return A+B;

        } else {
            // a.size() < b.size()
            vector<array<int,3>> t;
            for(auto it = b.begin(); it != b.end(); ++it) {
                t.push_back({*it,costs[*it][0],costs[*it][1]});
            }
            sort(t.begin(),t.end(),[](const array<int,3>& lhs, const array<int,3>& rhs){
                int da = lhs[1]-lhs[2];
                int db = rhs[1]-rhs[2];
                return da < db;
            });
            int i = 0;
            while( a.size() < b.size() ) {
                b.erase(t[i][0]); a.insert(t[i][0]);
                B -= t[i][2];     A += t[i][1];
                ++i;
            }
            //cout << "after going to a " << a.size() << " going to b " << b.size() << endl;
            //cout << " cost A " << A << " cost B " << B << endl;
            //printWhoCost(a,costs,0);
            //printWhoCost(b,costs,1);
            return A+B;
        }
    }
};
