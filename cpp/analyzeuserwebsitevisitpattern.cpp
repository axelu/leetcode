
// 1152. Analyze User Website Visit Pattern
// https://leetcode.com/problems/analyze-user-website-visit-pattern/




class Solution {
private:
    void getThreeSeqences(string arr[], int n, int r, int index, vector<string>& data, int i,
        set<vector<string>>& threeSequences, set<vector<string>>& globalThreeSeqences) {

        if( index == r ) {
            threeSequences.insert(data);
            globalThreeSeqences.insert(data);
            return;
        }

        if (i >= n)
            return;

        data[index] = arr[i];
        getThreeSeqences(arr, n, r, index + 1, data, i + 1, threeSequences, globalThreeSeqences);
        getThreeSeqences(arr, n, r, index, data, i + 1, threeSequences, globalThreeSeqences);
    }

public:
    vector<string> mostVisitedPattern(vector<string>& username, vector<int>& timestamp, vector<string>& website) {
        int n = username.size(); // username.length = timestamp.length = website.length

        // sort data by timestamp
        multimap<int,pair<string,string>> vh; // timestamp,{username,website}
        for(int i = 0; i < n; ++i)
            vh.insert({timestamp[i],{username[i],website[i]}});

        // create path for every user
        unordered_map<string,vector<string>> userPath; // username,path = web sites visited in chronologial order
        pair<unordered_map<string,vector<string>>::iterator,bool> p;
        for(auto it = vh.begin(); it != vh.end(); ++it) {
            // userName = it->second.first
            // webSite  = it->second.second
            p = userPath.insert({it->second.first,{it->second.second}});
            if( !p.second )
                p.first->second.push_back(it->second.second);
        }

        // for every user, get all the unique 3-sequences she visited AND
        // create list of unique global 3-sequences amongst all users
        unordered_map<string,set<vector<string>>> userThreeSeq;
        set<vector<string>> globalThreeSeqences;
        for(auto it = userPath.begin(); it != userPath.end(); ++it) {
            vector<string> threeSeq(3);
            set<vector<string>> threeSeqences; // per user
            getThreeSeqences(it->second.data(),it->second.size(),3,0,threeSeq,0,threeSeqences,globalThreeSeqences);
            userThreeSeq.insert({it->first,threeSeqences});
        }

        // for every unique 3-seqence count the number of users who visited it
        vector<string> ans;
        int ansCnt = 0;
        int cnt;
        for(auto ito = globalThreeSeqences.begin(); ito != globalThreeSeqences.end(); ++ito) {
            cnt = 0;
            for(auto iti = userThreeSeq.begin(); iti != userThreeSeq.end(); ++iti)
                if( iti->second.find(*ito) != iti->second.end() ) ++cnt;
            if( cnt > ansCnt ) {
                ans = *ito;
                ansCnt = cnt;
            }
        }

        return ans;
    }
};
