
// 359. Logger Rate Limiter
// https://leetcode.com/problems/logger-rate-limiter/



class Logger {
private:
    unordered_map<string,int> um;
public:
    /** Initialize your data structure here. */
    Logger() {

    }

    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
        If this method returns false, the message will not be printed.
        The timestamp is in seconds granularity. */
    bool shouldPrintMessage(int timestamp, string message) {
        auto p = um.insert({message,timestamp});
        if( p.second ) return true;
        if( p.first->second + 10 <= timestamp ) {
            p.first->second = timestamp;
            return true;
        }
        return false;
    }
};

/**
 * Your Logger object will be instantiated and called as such:
 * Logger* obj = new Logger();
 * bool param_1 = obj->shouldPrintMessage(timestamp,message);
 */
