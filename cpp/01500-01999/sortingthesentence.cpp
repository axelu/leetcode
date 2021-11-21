
// 1859. Sorting the Sentence
// https://leetcode.com/problems/sorting-the-sentence/



class Solution {
public:
    string sortSentence(string str) {
        vector<string> v;
        stringstream ss(str);
        string s;
        while( getline(ss,s,' ') )
            v.push_back(s);

        sort(v.begin(),v.end(),[](const string& a, const string& b){
            if( a[a.size()-1] < b[b.size()-1] )
                return true;
            return false;
        });

        string ans = v[0]; ans.pop_back();
        for(int i = 1; i < v.size(); ++i) {
            ans += " " + v[i];
            ans.pop_back();
        }
        return ans;
    }
};
