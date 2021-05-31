
// 544. Output Contest Matches
// https://leetcode.com/problems/output-contest-matches/



class Solution {
private:
    int getK(int n) {
        // n is in range [2, 2^12].
        // it is garuanteed that n can be converted into the form 2^k
        int k = 1;
        int a = 1;
        for(; k <= 12; ++k) {
            a *= 2;
            if( a == n ) break;
        }
        return k;
    }
public:
    string findContestMatch(int n) {
        if( n == 2 ) return "(1,2)"; // 1 round only
        int k = getK(n); // number of rounds

        // build first round
        vector<string> c;
        string p;
        int i = 1,j = n;
        while( i < j ) {
            // pair
            p = "(" + to_string(i) + "," + to_string(j) + ")";
            c.push_back(p);
            ++i;
            --j;
        }

        // round [2,k-1]
        vector<string>* pC = &c;
        vector<string> nxt;
        vector<string>* pNxt = &nxt;
        for(int m = 2; m < k; ++m) {
            i = 0,j = pC->size()-1;
            while(i<j) {
                // pair
                p = "(" + pC->at(i) + "," + pC->at(j) + ")";
                pNxt->push_back(p);
                ++i;
                --j;
            }
            swap(pC,pNxt);
            pNxt->clear();
        }

        // last round
        string ans = "(" + pC->at(0);
        for(i = 1; i < pC->size(); ++i)
            ans += "," + pC->at(i);
        ans += ")";
        return ans;
    }
};
