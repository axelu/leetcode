
// 1169. Invalid Transactions
// https://leetcode.com/problems/invalid-transactions/




class Solution {
public:
    vector<string> invalidTransactions(vector<string>& transactions) {
        // sort by name and transaction time
        sort(transactions.begin(),transactions.end(),[](const string& a, const string& b) {
            // a
            vector<string> va;
            stringstream ssa(a);
            string s;
            while( getline(ssa,s,',') )
                va.push_back(s);
            // b
            vector<string> vb;
            stringstream ssb(b);
            while( getline(ssb,s,',') )
                vb.push_back(s);

            // vx[0] name
            // vx[1] time
            // vx[2] amount
            // vx[3] city

            if( va[0] < vb[0] )
                return true;

            if( va[0] == vb[0] ) {
                if( stoi(va[1]) < stoi(vb[1]) ) {
                    return true;
                }
            }
            return false;
        });

        // for(string s : transactions) cout << s << endl;

        unordered_set<int> ansSet;

        string curName = "";
        int j,curTime;
        for(int i = 0; i < transactions.size(); ++i) {

            vector<string> v;
            stringstream ss(transactions[i]);
            string s;
            while( getline(ss,s,',') )
                v.push_back(s);

            // v[0] name
            // v[1] time
            // v[2] amount
            // v[3] city

            if( stoi(v[2]) > 1000 ) ansSet.insert(i);

            curTime = stoi(v[1]);
            j = i-1;
            while( j >= 0 ) {
                vector<string> vp;
                stringstream ssp(transactions[j]);
                while( getline(ssp,s,',') )
                    vp.push_back(s);
                if( vp[0] != v[0] ) break;              // different person
                if( stoi(vp[1]) < curTime-60 ) break;   // more than 60min in the past
                if( vp[3] != v[3] ) {                   // different city
                    ansSet.insert(i);
                    ansSet.insert(j);
                }
                --j;
            }
        }

        vector<string> ans;
        for(auto it = ansSet.begin(); it != ansSet.end(); ++it)
            ans.push_back(transactions[*it]);
        return ans;
    }
};
