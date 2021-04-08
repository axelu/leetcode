
// 599. Minimum Index Sum of Two Lists
// https://leetcode.com/problems/minimum-index-sum-of-two-lists/



class Solution {
public:
    vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
        int n1 = list1.size();
        unordered_map<string,int> um1;
        for(int i = 0; i < n1; ++i)
            um1.insert({list1[i],i});

        int n2 = list2.size();
        map<int,vector<string>> m;
        pair<map<int,vector<string>>::iterator,bool> p;
        unordered_map<string,int>::iterator f;
        unordered_map<string,int>::iterator e = um1.end();
        int idxSum;
        for(int i = 0; i < n2; ++i) {
            f = um1.find(list2[i]);
            if( f != e ) {
               idxSum = f->second + i;
                p = m.insert({idxSum,{list2[i]}});
                if( !p.second )
                    p.first->second.push_back(list2[i]);
            }
        }
        // from the problem description:
        //   "You could assume there always exists an answer."
        return m.begin()->second;
    }
};
