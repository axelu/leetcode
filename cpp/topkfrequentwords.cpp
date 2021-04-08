
// 692. Top K Frequent Words
// https://leetcode.com/problems/top-k-frequent-words/


class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        size_t n = words.size();
        if( n == 1 ) return words;

        unordered_map<string,int> um;
        pair<unordered_map<string,int>::iterator,bool> p;
        for(int i = 0; i < n; ++i) {
            p = um.insert({words[i],1});
            if( !p.second ) ++p.first->second;
        }

        auto cmp = [](const pair<int,string>& a, const pair<int,string>& b){
            if( a.first < b.first ) return true;
            if( a.first == b.first && a.second > b.second ) return true;
            return false;
        };
        priority_queue<pair<int,string>,vector<pair<int,string>>,decltype(cmp)> pq(cmp);
        for(auto it = begin(um); it != end(um); ++it) {
            pq.push({it->second,it->first});
            // if( pq.size() > k ) pq.pop();
        }

        vector<string> ans(k);
        for(int i = 0; i < k; ++i) {
            ans[i] = pq.top().second;
            pq.pop();
        }

        return ans;
    }
};
