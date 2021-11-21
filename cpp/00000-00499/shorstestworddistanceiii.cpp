
// 245. Shortest Word Distance III
// https://leetcode.com/problems/shortest-word-distance-iii/



class Solution {
private:
    int minDiff(vector<int> v) {
        // v is sorted in non-decreasing order
        int ans = INT_MAX, t;
        for(int i = 0; i < v.size()-1; ++i) {
            t = v[i+1] - v[i];
            ans = min(ans,t);
        }
        return ans;
    }

    int shortestDistance(vector<int> v1, vector<int> v2) {
        // both v1 and v2 are sorted
        // 0 <= v1[i],v2[i]
        // values in v1 do not occur in v2
        // 1 <= v1.size(),v2.size()

        size_t n1 = v1.size();
        size_t n2 = v2.size();
        if( n1 == 1 && n2 == 1 ) return abs(v1[0]-v2[0]);

        int ans = INT_MAX;

        /*
        if( n1 == 1 ) {
            int a = v1[0];
            for(int i = 0; i < n2; ++i)
                ans = min(ans,abs(a-v2[i]));
        }
        if( n2 == 1 ) {
            int a = v2[0];
            for(int i = 0; i < n1; ++i)
                ans = min(ans,abs(a-v1[i]));
        }
        */

        int i = 0, j = 0, t;
        while(i < n1 && j < n2) {
            t = abs(v1[i] - v2[j]);
            ans = min(ans,t);
            // advance smaller value
            if( v1[i] < v2[j])
                ++i;
            else
                ++j;
        }

        return ans;
    }
public:
    int shortestWordDistance(vector<string>& words, string word1, string word2) {
        // constraints:
        //     word1 may equal word2
        //     word1 and word2 are both in the list
        //     inferred from above: words.size() >= 2 ?

        size_t n = words.size();
        if( n == 0 ) return -1;

        map<string,vector<int>> m;
        for(int i = 0; i < n; ++i) {
            auto p = m.insert({words[i],{i}});
            if( !p.second )
                p.first->second.push_back(i);
        }

        map<string,vector<int>>::iterator f;
        map<string,vector<int>>::iterator e = end(m);
        f = m.find(word1);
        if( f == e ) return INT_MAX;
        vector<int> v1 = f->second;
        f = m.find(word2);
        if( f == e ) return INT_MAX;
        vector<int> v2 = f->second;

        // if we are here, both words are in the list
        if( n == 1 ) return INT_MAX;
        if( n == 2 )
            return word1 == word2 && f->second.size() == 1 ? INT_MAX : 1;

        if( word1 == word2 )
            return minDiff(v1);

        return shortestDistance(v1,v2);

    }
};
