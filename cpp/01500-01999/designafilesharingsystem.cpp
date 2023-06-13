
// 1500. Design a File Sharing System
// https://leetcode.com/problems/design-a-file-sharing-system/



class FileSharing {
private:
    int next_userid;
    priority_queue<int,vector<int>,greater<int>> userids;

    unordered_map<int,unordered_set<int>> byuserid; // userid, list of chunkids
    vector<set<int>> bychunkid;                     // chunckid, list of userids

public:
    FileSharing(int m) {
        next_userid = 1;
        bychunkid.assign(m+1,{}); // chunks are 1-indexed
    }

    int join(vector<int> ownedChunks) {
        // get userid
        int userid;
        if( userids.empty() ) {
            userid = next_userid++;
        } else {
            userid = userids.top();
            userids.pop();
        }

        for(auto chunk: ownedChunks) {
            byuserid[userid].insert(chunk);
            bychunkid[chunk].insert(userid);
        }

        return userid;
    }

    void leave(int userID) {
        for(auto chunk: byuserid[userID])
            bychunkid[chunk].erase(userID);

        byuserid.erase(userID);

        userids.push(userID);
    }

    vector<int> request(int userID, int chunkID) {
        auto st = bychunkid[chunkID];
        if( st.empty() )
            return {};

        bychunkid[chunkID].insert(userID);
        byuserid[userID].insert(chunkID);

        vector<int> v;
        v.insert(v.end(), st.begin(), st.end());
        return v;
    }
};

/**
 * Your FileSharing object will be instantiated and called as such:
 * FileSharing* obj = new FileSharing(m);
 * int param_1 = obj->join(ownedChunks);
 * obj->leave(userID);
 * vector<int> param_3 = obj->request(userID,chunkID);
 */
