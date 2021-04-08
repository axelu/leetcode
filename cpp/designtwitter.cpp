
// 355. Design Twitter
// https://leetcode.com/problems/design-twitter/



class Twitter {
private:
    struct Tweet {
        int userId;
        int tweetId;
        Tweet* prev;
        Tweet(int userId, int tweetId, Tweet* prev) : userId(userId), tweetId(tweetId), prev(prev) {}
    };

    Tweet* tail;
    map<int,unordered_set<int>> followers; // userId,[userId1,userId2,userId3,... of followers]

public:
    /** Initialize your data structure here. */
    Twitter() {
        tail = nullptr;
    }

    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        Tweet* tweet = new Tweet(userId,tweetId,tail);
        tail = tweet;
    }

    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        // get userId's of users that this user follows, if any
        vector<int> ans;
        auto it = followers.find(userId);
        Tweet* tweet = tail;
        int i = 0;
        while(tweet!=nullptr) {
            if( tweet->userId == userId ) {
                ans.push_back(tweet->tweetId);
                ++i;
            } else if( it != followers.end() && it->second.find(tweet->userId) != it->second.end() ) {
                ans.push_back(tweet->tweetId);
                ++i;
            }
            if( i == 10 ) break;
            tweet = tweet->prev;
        }
        return ans;
    }

    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        auto p = followers.insert({followerId,{followeeId}});
        if( !p.second )
            p.first->second.insert(followeeId);
    }

    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        auto f = followers.find(followerId);
        if( f != followers.end() ) {
            f->second.erase(followeeId);
            if( f->second.empty() )
                followers.erase(followerId);
        }
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */
