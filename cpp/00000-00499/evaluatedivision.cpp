
// day 27 September 2020 challenge
// 399. Evaluate Division
// https://leetcode.com/explore/challenge/card/september-leetcoding-challenge/557/week-4-september-22nd-september-28th/3474/
// https://leetcode.com/problems/evaluate-division/


#include <iostream>
#include <cassert>

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;
//234567890123456789012345678901234567890123456789012345678901234567890123456789
class Solution {
    private:
    auto _buildEG(vector<vector<string>>& equations, vector<double>& values) {
        // Division: Dividend ÷ Divisor = Quotient
        // assume input equation as A / B = k
        // we can get B / A = 1 / k  as follows:
        // ( A / B = k -> A = B * k -> A / k = B -> 1 / k = B / A)

        // eg[Dividend][Divisor] -> Quotient
        unordered_map<string,unordered_map<string,double>> eg;

        for(int i = 0; i < equations.size(); ++i) {
            // A / B = k
            unordered_map<string,double> m = {{equations[i][1], values[i]}};
            auto p  = eg.insert({equations[i][0],m});
            if( !p.second ) {
                p.first->second.insert({equations[i][1], values[i]});
            }
            // B / A = 1 / k
            m = {{equations[i][0], 1.0 / values[i]}};
            p  = eg.insert({equations[i][1],m});
            if( !p.second ) {
                p.first->second.insert({equations[i][0], 1.0 / values[i]});
            }
        }

        return eg;
    }

    vector<double> _calc(
        vector<vector<string>>& queries,
        unordered_map<string,unordered_map<string,double>>& eg) {

        vector<double> r;

        for(auto q : queries) {
            auto dvd = eg.find(q[0]); // searching for Dividend
            if( dvd != eg.end() ) {
                // found Dividend
                if( q[0] == q[1] ) {
                    r.push_back(1.0);
                    continue;
                }
                auto dvr = dvd->second.find(q[1]); // searching for Divisor
                if( dvr != dvd->second.end() ) {
                    // found Divisor -> found result
                    r.push_back(dvr->second);
                } else {
                    // check if we can solve at all
                    // by looking for Divisor as Dividend
                    if( eg.find(q[1]) == eg.end() ) {
                        // NOT solveable
                        r.push_back(-1.0);
                    } else {
                        // potentially solveable
                        vector<string> explored = {q[0]}; // to avoid circle
                        r.push_back(_solve(dvd, q[1], eg, explored));
                        // consider if there is a solution to add to eg
                    }
                }
            } else {
                r.push_back(-1.0);
            }
        }

        return r;
    }

    double _solve(
        unordered_map<string,unordered_map<string,double>>::iterator dvd,
        string dvr,
        unordered_map<string,unordered_map<string,double>>& eg,
        vector<string>& explored) {

        for(auto it = dvd->second.begin(); it != dvd->second.end(); ++it) {
            double t = it->second;
            if( it->first == dvr ) return t; // found
            if( find(explored.begin(), explored.end(), it->first) != explored.end() )
                continue;
            explored.push_back(it->first);
            double s = _solve(eg.find(it->first), dvr, eg, explored);
            if( s != -1.0 ) return t * s;
        }
        return -1.0;
    }
public:
    vector<double> calcEquation(
        vector<vector<string>>& equations,
        vector<double>& values,
        vector<vector<string>>& queries) {

        auto eg = _buildEG(equations, values);
        return _calc(queries, eg);
    }
};

int main() {
    Solution s;
    vector<vector<string>> equations;
    vector<double> values;
    vector<vector<string>> queries;
    vector<double> r;

    equations = {{"a","b"},{"b","c"}};
    values = {2.0, 3.0};
    queries = {{"a","c"},{"b","a"},{"a","e"},{"a","a"},{"x","x"}};
    r = {6.00000,0.50000,-1.00000,1.00000,-1.00000};
    assert(s.calcEquation(equations,values,queries) == r);

    equations = {{"a","b"},{"b","c"},{"bc","cd"}};
    values = {1.5,2.5,5.0};
    queries = {{"a","c"},{"c","b"},{"bc","cd"},{"cd","bc"}};
    r = {3.75000,0.40000,5.00000,0.20000};
    assert(s.calcEquation(equations,values,queries) == r);

    equations = {{"a","b"}};
    values = {0.5};
    queries = {{"a","b"},{"b","a"},{"a","c"},{"x","y"}};
    r = {0.50000,2.00000,-1.00000,-1.00000};
    assert(s.calcEquation(equations,values,queries) == r);

    return 0;
}
