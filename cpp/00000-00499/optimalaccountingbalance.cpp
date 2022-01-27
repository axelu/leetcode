
// 465. Optimal Account Balancing
// https://leetcode.com/problems/optimal-account-balancing/



class Solution {
private:
    void printArr(string msg, vector<int>& arr) {
        cout << msg << " size:";
        cout << arr.size() << " ";
        int sum = 0;
        for(int i : arr) {
            cout << i << " ";
            sum += i;
        }
        cout << " sum:" << sum;
        cout << endl;
    }
private:
    int rec(vector<int>& givers, int g, vector<int>& takers, int t) {
        // cout << "rec g " << g << " t " << t << endl;
        // printArr("  givers",givers);
        // printArr("  takers",takers);

        // a giver needs to eventually give all its money away
        int ret = INT_MAX;

        for(int i = t; i < takers.size(); ++i) {
            if( takers[i] == 0 )
                continue;

            // we have a choice
            // give the current taker money or not

            // skip
            int a = INT_MAX;
            // only skip the current taker if we can still get rid
            // of all the money of the giver with the remaining takers
            // if the current taker is the last one, we have to give
            int s = 0; // remaining debt
            for(int k = i+1; k < takers.size(); ++k)
                s += takers[k];
            if( s >= givers[g] )
                a = rec(givers,g,takers,i+1);


            // give
            int b = INT_MAX;
            if( takers[i] == givers[g] ) {
                // cout << "takers[" << i << "] == givers[" << g << "]" << endl;
                // printArr("    givers",givers);
                // printArr("    takers",takers);
                int park = givers[g];
                givers[g] = 0;
                takers[i] = 0;
                b = 1;
                // our current giver gave all its money away
                // only if there is another giver left do we go on
                if( g < givers.size()-1 )
                    b += rec(givers,g+1,takers,0);
                // backtrack
                givers[g] = park;
                takers[i] = park;
            } else if( takers[i] > givers[g] ) {
                // cout << "takers[" << i << "] > givers[" << g << "]" << endl;
                // printArr("    givers",givers);
                // printArr("    takers",takers);
                int park = givers[g];
                givers[g] = 0;
                takers[i] = takers[i]-park;
                b = 1 + rec(givers,g+1,takers,0);
                // backtrack
                givers[g] = park;
                takers[i] = takers[i]+park;
            } else {
                // takers[i] < givers[g]
                // cout << "takers[" << i << "] < givers[" << g << "]" << endl;
                // printArr("    givers",givers);
                // printArr("    takers",takers);
                // our giver will have money left after giving it
                // to the current taker, this is only an option,
                // if there is another taker left
                int park = takers[i];
                takers[i] = 0;
                givers[g] = givers[g]-park;
                //if( i < takers.size()-1 && takers[i+1] != 0 ) {
                //    b = 1 + rec(givers,g,takers,i+1);
                //} else {
                    b = 1 + rec(givers,g,takers,0);
                //}
                // backtrack
                takers[i] = park;
                givers[g] = givers[g]+park;
            }

            // remember min
            ret = min({ret,a,b});
        }

        return ret;
    }


public:
    int minTransfers(vector<vector<int>>& transactions) {
        // 0 <= fromi, toi <= 20
        int balance[21];memset(balance,0,sizeof balance);
        for(auto t : transactions) {
            balance[t[0]] -= t[2];
            balance[t[1]] += t[2];
        }

        vector<int> givers,takers;
        for(int i = 0; i < 21; ++i)
            if( balance[i] < 0 )
                takers.push_back(-balance[i]);
            else if( balance[i] > 0 )
                givers.push_back(balance[i]);


        // debug
        // printArr("givers",givers);
        // printArr("takers",takers);


        // eliminate any equals between givers and takers
        int base = 0;
        for(auto it = givers.begin(); it != givers.end();) {
            bool flag = false;
            for(auto f = takers.begin(); f != takers.end(); ++f) {
                if( *it == *f ) {
                    takers.erase(f);
                    flag = true;
                    ++base;
                    break;
                }
            }
            if( flag )
                it = givers.erase(it);
            else
                ++it;
        }


        // base cases
        if( takers.size() == 0 ) // givers will be 0 also
            return base;
        if( givers.size() == 1 ) // there is one person with money
            return base + takers.size();
        if( takers.size() == 1 ) // there is one person money owed to
            return base + givers.size();


        return base + rec(givers,0,takers,0);
    }
};
