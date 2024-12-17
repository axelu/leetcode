
// 3387. Maximize Amount After Two Days of Conversions
// https://leetcode.com/problems/maximize-amount-after-two-days-of-conversions/





/* example -> answer 2.4
 *   "EUR"
 *   [["EUR","USD"],["USD","JPY"]]
 *   [2.0,3.0]
 *   [["JPY","USD"],["USD","CHF"],["CHF","NGN"],["EUR","USD"]]
 *   [4.0,5.0,6.0,10.0]
 *
 *         Day 1               Day 2
 *   ------------------- -------------------
 *       2.0.     3.0.     4.0.     0.1
 *   EUR  ->  USD  ->  JYP  ->  USD  ->  EUR
 *   1.0      2.0.     6.0      24.0     2.4
 *
 * example -> answer 60.0
 *   "EUR"
 *   [["USD","EUR"],["USD","JPY"]]
 *   [2.0,3.0]
 *   [["JPY","USD"],["USD","CHF"],["CHF","NGN"],["USD","EUR"]]
 *   [4.0,5.0,6.0,10.0]
 *
 *         Day 1                Day 2
 *   ------------------- --------------------
 *        0.5     3.0      4.0      10.0
 *   EUR  ->  USD  ->  JPY  ->  USD  ->  EUR
 *   1.0      0.5      1.5      6.0      60.0
 *
 * even by adding a back edge (opposite of the edge given), pairs for a given day will not have a cycle
 * invalid pairs
 * [["EUR","USD"],["USD","JPY"],["EUR","JPY"]]
 * that means we cannot get back to where we started in a given day pairs,
 * which in turn means if we take a step in day 1, we have to take a step in day 2
 * which in turn means we cannot skip day 1
 */



class Solution {
private:
    unordered_map<string,vector<pair<string,double>>> g1;
    unordered_map<string,vector<pair<string,double>>> g2;
    string target;

    double rec1(string u, string src, double amount) {
        // cout << "rec1 u " << u << " src " << src << " amount " << amount << endl;

        // u = currency current node
        // src = currency node we came from

        // we have a choice
        //    continue in g1 OR
        //    hop over to g2

        double ret = 0.0;

        for(auto it = g1[u].begin(); it != g1[u].end(); ++it) {

            if( it->first == src )
                continue;

            double t = rec1(it->first, u, amount * it->second);
            ret = max(ret, t);
        }

        ret = max(ret, rec2(u, "###", amount));

        return ret;
    }

    double rec2(string u, string src, double amount) {
        // cout << "rec2 u " << u << " src " << src << " amount " << amount << endl;

        if( u == target )
            return amount;

        auto f = g2.find(u);
        if( f == g2.end() )
            return 0.0;

        double ret = 0.0;

        for(auto it = f->second.begin(); it != f->second.end(); ++it) {
            if( it->first == src )
                continue;

            double t = rec2(it->first, u, amount * it->second);
            ret = max(ret, t);
        }

        return ret;
    }


public:
    double maxAmount(string initialCurrency, vector<vector<string>>& pairs1, vector<double>& rates1, vector<vector<string>>& pairs2, vector<double>& rates2) {

        // pairs1.size == rates1.size
        for(int i = 0; i < pairs1.size(); ++i) {
            g1[pairs1[i][0]].push_back({pairs1[i][1], rates1[i]});
            g1[pairs1[i][1]].push_back({pairs1[i][0], 1.0/rates1[i]});
        }

        // pairs2.size == rates2.size
        for(int i = 0; i < pairs2.size(); ++i) {
            g2[pairs2[i][0]].push_back({pairs2[i][1], rates2[i]});
            g2[pairs2[i][1]].push_back({pairs2[i][0], 1.0/rates2[i]});
        }

        target = initialCurrency;
        return rec1(initialCurrency, "###", 1.0);
    }
};
