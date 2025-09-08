
// 3664. Two-Letter Card Game
// https://leetcode.com/problems/two-letter-card-game/


class Solution {
private:
    pair<int,int> solve(int xx, map<string,int> mp, int& rem) {
        auto cmp = [](const pair<int,string>& a, const pair<int,string>& b){
            if( a.first < b.first ) {
                return true;
            } else if( a.first == b.first ) {
                // don't prefer xx
                if( a.second == "xx" ) {
                    return true;
                }
            }
            return false;
        };
        priority_queue<pair<int,string>, vector<pair<int,string>>, decltype(cmp)> pq(cmp);

        for(auto p: mp)
            pq.push({p.second, p.first});

        if( xx > 0 )
            pq.push({xx, "xx"});

        int ret = 0; // number of pairs we can make

        while( pq.size() > 1 ) {
            ++ret;

            // pick the top two, make a pair,
            // push remainder if anything
            auto pile1 = pq.top(); pq.pop();
            auto pile2 = pq.top(); pq.pop();

            --pile1.first;
            if( pile1.first > 0 )
                pq.push(pile1);

            --pile2.first;
            if( pile2.first > 0 )
                pq.push(pile2);
        }

        // is xx left?
        // there will be at most one left in pq
        xx = 0;
        rem = 0;
        while( !pq.empty() ) {
            if( pq.top().second == "xx" ) {
                xx = pq.top().first;
            } else {
                rem = pq.top().first;
            }
            pq.pop();
        }

        return {ret, xx};
    }

public:
    int score(vector<string>& cards, char x) {

        // counting xsomething and somethingx is not good enough
        // because we must first pair with xx any cards we have multiple off,
        // because we cannot pair those with each other

        int xx = 0;         // count of cards with char x in pos 0 and pos 1
        map<string,int> xsomething;
        map<string,int> somethingx;
        for(string& s: cards) {
            if( s[0] == x && s[1] == x ) {
                ++xx;
            } else if( s[0] == x ) {
                ++xsomething[s];
            } else if( s[1] == x ) {
                ++somethingx[s];
            }
        }

        /*
        cout << x << x << " " << xx << endl;
        cout << "xsomething" << endl;
        for(auto p: xsomething)
            cout << p.first << ":" << p.second << " ";
        cout << endl;
        cout << "somethingx" << endl;
        for(auto p: somethingx)
            cout << p.first << ":" << p.second << " ";
        cout << endl;
        */

        // we may have xx cards
        // xx cards cannot be paired with each other !!!

        int A = 0, B = 0, C = 0, D = 0;
/*
        // Strategy A
        // int A = 0;
        int rem;
        auto a = solve(xx, xsomething, rem);
        // cout << "A xx left after xsomething " << a.second << endl;
        A += a.first;
        auto b = solve(a.second, somethingx, rem);
        A += b.first;
        // cout << "A " << A << endl;

        // Strategy B
        // int B = 0;
        auto c = solve(xx, somethingx, rem);
        // cout << "B xx left after somethingx " << c.second << endl;
        B += c.first;
        auto d = solve(c.second, xsomething, rem);
        B += d.first;
        // cout << "B " << B << endl;

        // strategy C
        // strategy hold back our jokers and apply them to the left overs
        // int C = 0;
        int rem_total = 0;
        auto e = solve(0, somethingx, rem);
        C += e.first;
        rem_total += rem;
        auto f = solve(0, xsomething, rem);
        C += f.first;
        rem_total += rem;
        C += min(xx, rem_total);
        // cout << "C " << C << endl;
*/

        // Strategy D
        // pick from the largest pile

        auto cmp = [](const pair<int,string>& a, const pair<int,string>& b){
            if( a.first < b.first ) {
                return true;
            } else if( a.first == b.first ) {
                // don't prefer xx
                if( a.second == "xx" ) {
                    return true;
                }
            }
            return false;
        };

        priority_queue<int> pq1;
        for(auto p: xsomething)
            pq1.push(p.second);
        pq1.push(0); // sentinel

        priority_queue<int> pq2;
        for(auto p: somethingx)
            pq2.push(p.second);
        pq2.push(0); // sentinel

        // int D = 0;

        while( true ) {
            if( pq1.top() == 0 && pq2.top() == 0 )
                break;
            if( pq1.size() == 2 && pq2.size() == 2 )
                break;

            // cout << "xx " << xx << " pq1.top() " << pq1.top() << " pq1.size() " << pq1.size() << " pq2.top() " << pq2.top() << " pq2.size() " << pq2.size() << endl;

            if( xx > pq1.top() && xx > pq2.top() ) {
                // we use xx
                if( pq1.top() >= pq2.top() ) {
                    int t = pq1.top();
                    pq1.pop();
                    --t;
                    --xx;
                    if( t > 0 )
                        pq1.push(t);
                } else {
                    int t = pq2.top();
                    pq2.pop();
                    --t;
                    --xx;
                    if( t > 0 )
                        pq2.push(t);
                }
                ++D;

            } else {
                // we could use pq1.top() + pq1."next" if we have that OR
                //              pq1.top() + xx if we have xx
                // same applies to pq2

                // lets start simple and use inside pq if we can
                bool executed = false;
                if( pq1.top() >= pq2.top() ) {
                    int t = pq1.top();
                    pq1.pop();
                    if( pq1.top() > 0 ) {
                        int t2 = pq1.top();
                        pq1.pop();
                        --t;
                        --t2;
                        if( t > 0 ) pq1.push(t);
                        if( t2 > 0 ) pq1.push(t2);
                        executed = true;
                    } else {
                        pq1.push(t); // backtrack
                    }
                }
                if( !executed ) {
                    int t = pq2.top();
                    pq2.pop();
                    if( pq2.top() > 0 ) {
                        int t2 = pq2.top();
                        pq2.pop();
                        --t;
                        --t2;
                        if( t > 0 ) pq2.push(t);
                        if( t2 > 0 ) pq2.push(t2);
                        executed = true;
                    } else {
                        pq2.push(t); // backtrack
                    }
                }
                if( !executed ) {
                    if( pq1.size() > 2 ) { // TODO 0 check after 1st pop not needed
                        int t = pq1.top();
                        pq1.pop();
                        if( pq1.top() > 0 ) {
                            int t2 = pq1.top();
                            pq1.pop();
                            --t;
                            --t2;
                            if( t > 0 ) pq1.push(t);
                            if( t2 > 0 ) pq1.push(t2);
                            executed = true;
                        } else {
                            pq1.push(t); // backtrack
                        }
                    }
                }
                if( !executed ) {
                    if( pq2.size() > 2 ) { // TODO 0 check after 1st pop not needed
                        int t = pq2.top();
                        pq2.pop();
                        if( pq2.top() > 0 ) {
                            int t2 = pq2.top();
                            pq2.pop();
                            --t;
                            --t2;
                            if( t > 0 ) pq2.push(t);
                            if( t2 > 0 ) pq2.push(t2);
                            executed = true;
                        } else {
                            pq2.push(t); // backtrack
                        }
                    }
                }
                if( executed ) {
                    ++D;
                } else {
                    // cout << "breaking" << endl;
                    break;
                }
            }
        }
        // cout << "xx after D " << xx << endl;
        // finish up
        D += min(xx, pq1.top() + pq2.top());


        // cout << "A " << A << " B " << B << " C " << C << " D " << D << endl;
        return max({A, B, C, D});
    }
};
