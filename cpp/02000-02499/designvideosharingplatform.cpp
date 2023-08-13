
// 2254. Design Video Sharing Platform
// https://leetcode.com/problems/design-video-sharing-platform/




class VideoSharingPlatform {
private:
    set<int> nxtVideoId;

    struct Video {
        string content;
        int likes;
        int dislikes;
        int views;
        Video(string c) : content(c), likes(0), dislikes(0), views(0) {}
    };

    unordered_map<int,Video*> lib;

public:
    VideoSharingPlatform() {
        nxtVideoId.insert(0);
    }

    int upload(string video) {
        int id = *nxtVideoId.begin();
        nxtVideoId.erase(nxtVideoId.begin());
        if( nxtVideoId.empty() )
            nxtVideoId.insert(id+1);

        Video * v = new Video(video);
        lib[id] = v;

        return id;
    }

    void remove(int videoId) {
        auto f = lib.find(videoId);
        if( f != lib.end() ) {
            delete(f->second);
            nxtVideoId.insert(f->first);
            lib.erase(f);
        }
        return;
    }

    string watch(int videoId, int startMinute, int endMinute) {
        auto f = lib.find(videoId);
        if( f != lib.end() ) {
            ++f->second->views;
            if( endMinute >= f->second->content.size() )
                return f->second->content.substr(startMinute);
            else
                return f->second->content.substr(startMinute, endMinute-startMinute+1);
        }
        return "-1";
    }

    void like(int videoId) {
        auto f = lib.find(videoId);
        if( f != lib.end() )
            ++f->second->likes;
        return;
    }

    void dislike(int videoId) {
        auto f = lib.find(videoId);
        if( f != lib.end() )
            ++f->second->dislikes;
        return;
    }

    vector<int> getLikesAndDislikes(int videoId) {
        auto f = lib.find(videoId);
        if( f != lib.end() )
            return {f->second->likes,f->second->dislikes};
        return {-1};
    }

    int getViews(int videoId) {
        auto f = lib.find(videoId);
        if( f != lib.end() )
            return f->second->views;
        return -1;
    }
};

/**
 * Your VideoSharingPlatform object will be instantiated and called as such:
 * VideoSharingPlatform* obj = new VideoSharingPlatform();
 * int param_1 = obj->upload(video);
 * obj->remove(videoId);
 * string param_3 = obj->watch(videoId,startMinute,endMinute);
 * obj->like(videoId);
 * obj->dislike(videoId);
 * vector<int> param_6 = obj->getLikesAndDislikes(videoId);
 * int param_7 = obj->getViews(videoId);
 */
