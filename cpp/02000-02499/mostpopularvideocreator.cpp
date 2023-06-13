
// 2456. Most Popular Video Creator
// https://leetcode.com/problems/most-popular-video-creator/



class Solution {
public:
    vector<vector<string>> mostPopularCreator(vector<string>& creators, vector<string>& ids, vector<int>& views) {
        int n = creators.size(); // creators.length == ids.length == views.length

        unordered_map<string,long> creator_views;
        unordered_map<string,map<string,long>> creator_video_views;

        for(int i = 0; i < n; ++i) {
            creator_views[creators[i]] += views[i];
            auto p = creator_video_views[creators[i]].insert({ids[i],views[i]});
            if( !p.second )
                p.first->second += views[i];
        }

        /*
        // debug
        for(auto it = creator_views.begin(); it != creator_views.end(); ++it) {
            cout << it->first << ":" << it->second << endl;
            auto cvv = creator_video_views[it->first];
            for(auto iti = cvv.begin(); iti != cvv.end(); ++iti)
                cout << "    " << iti->first << " " << iti->second << endl;
        }
        */

        vector<pair<string,long>> cv(creator_views.begin(),creator_views.end());
        sort(cv.begin(),cv.end(),[](const pair<string,long>& a, const pair<string,long>& b){
            return a.second > b.second;
        });

        vector<vector<string>> ans;

        long popularity = cv[0].second;
        for(int i = 0; i < cv.size(); ++i) {
            if( cv[i].second < popularity )
                break;

            auto creator_videos = creator_video_views[cv[i].first];
            long mx_views = -1;
            string video;
            for(auto it = creator_videos.begin(); it != creator_videos.end(); ++it)
                if( it->second > mx_views ) {
                    mx_views = it->second;
                    video = it->first;
                }

            ans.push_back({cv[i].first,video});
        }

        return ans;
    }
};
