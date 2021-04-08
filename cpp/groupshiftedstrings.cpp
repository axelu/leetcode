
// 249. Group Shifted Strings
// https://leetcode.com/problems/group-shifted-strings/



class Solution {
private:
    string getShiftingSequence(string& s) {
        string shiftingSequence = "";
        size_t n = s.size();
        if( 1 == n ) return shiftingSequence;
        int d;
        for(int i = 1; i < n; ++i) {
            d = (s[i]-'a') - (s[i-1]-'a');
            if( d < 0 ) d += 26;
            shiftingSequence += to_string(d);
        }
        return shiftingSequence;
    }
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        size_t n = strings.size();
        vector<vector<string>> ans;

        unordered_map<string,vector<string>> um;
        pair<unordered_map<string,vector<string>>::iterator,bool> p;
        string s,shiftingSequence;
        for(int i = 0; i < n; ++i) {
            s = strings[i];
            shiftingSequence = getShiftingSequence(s);
            p = um.insert({shiftingSequence,{s}});
            if( !p.second ) p.first->second.push_back(s);
        }

        for(auto it = begin(um); it != end(um); ++it)
            ans.push_back(it->second);

        return ans;
    }
};
