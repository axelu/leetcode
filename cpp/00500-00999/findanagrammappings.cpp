
// 760. Find Anagram Mappings
// https://leetcode.com/problems/find-anagram-mappings/



class Solution {
public:
    vector<int> anagramMappings(vector<int>& A, vector<int>& B) {
        int n = A.size(); // A, B have equal lengths in range [1, 100]
        
        unordered_map<int,vector<int>> m;
        pair<unordered_map<int,vector<int>>::iterator,bool> p;
        for(int i = 0; i < n; ++i) {
            p = m.insert({B[i],{i}});
            if( !p.second )
                p.first->second.push_back(i);
        }
        vector<int> ans(n);
        unordered_map<int,vector<int>>::iterator f;
        for(int i = 0; i < n; ++i) {
            f = m.find(A[i]);
            ans[i] = f->second.back();
            f->second.pop_back();
        }
        return ans;        
    }
};
