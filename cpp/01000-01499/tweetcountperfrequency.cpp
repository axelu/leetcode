
// 1348. Tweet Counts Per Frequency
// https://leetcode.com/problems/tweet-counts-per-frequency/


class TweetCounts {
private:
    unordered_map<string,unordered_map<int,int>> dic; // map of Binary Indexed Trees BITs

    int sum(int idx, unordered_map<int,int> * bit) {
        int ret = 0;
        for (++idx; idx > 0; idx -= idx & -idx)
            ret += (*bit)[idx];
        return ret;
    }

    int sum(int l, int r, unordered_map<int,int> * bit) {
        return sum(r,bit) - sum(l - 1,bit);
    }


public:
    TweetCounts() {
    }

    void recordTweet(string tweetName, int time) {
        unordered_map<int,int> * bit = &dic[tweetName];

        // point update
        for (++time; time <= 1000000001; time += time & -time)
            (*bit)[time] += 1;
    }

    vector<int> getTweetCountsPerFrequency(string freq, string tweetName, int startTime, int endTime) {
        // minute ->    60 second chunks
        // hour   ->  3600 second chunks
        // day    -> 86500 second chunks

        unordered_map<int,int> * bit = &dic[tweetName];

        int delta;
        if( freq == "minute" )
            delta = 59;
        else if( freq == "hour" )
            delta = 3599;
        else
            delta = 86399;

        vector<int> ans;
        int s = startTime;
        int e;
        while(true) {
            e = s + delta;
            if( e > endTime )
                e = endTime;

            ans.push_back(sum(s,e,bit));

            s = e+1;
            if( s > endTime )
                break;
        }

        return ans;
    }
};

/**
 * Your TweetCounts object will be instantiated and called as such:
 * TweetCounts* obj = new TweetCounts();
 * obj->recordTweet(tweetName,time);
 * vector<int> param_2 = obj->getTweetCountsPerFrequency(freq,tweetName,startTime,endTime);
 */
