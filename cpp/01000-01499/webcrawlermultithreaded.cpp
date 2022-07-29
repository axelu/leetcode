
// 1242. Web Crawler Multithreaded
// https://leetcode.com/problems/web-crawler-multithreaded/

/**
 * // This is the HtmlParser's API interface.
 * // You should not implement it, or speculate about its implementation
 * class HtmlParser {
 *   public:
 *     vector<string> getUrls(string url);
 * };
 */


class Solution {
private:
    string get_host(string url) {
        // url will be in the form of http://blablabla, http://blablabla/, http://blablabla/... 
        string host = "";
        int slash_cnt = 0;
        for(char c : url) {
            if( c == '/' )
                ++slash_cnt;
            if( slash_cnt == 3 )
                break;
            host += c;
        }
        return host;
    }
    
    string host;
    unordered_set<string> us;
    vector<string> new_urls;
    mutex _mutex;
    
    void accumulate(string url, HtmlParser parser) {
        vector<string> t = parser.getUrls(url);
        int h_sz = host.size();
        for(auto& s : t) {
            if( s.size() < h_sz )
                continue;
            bool is_same_host = true;
            for(int i = 0; i < h_sz; ++i)
                if( s[i] != host[i] ) {
                    is_same_host = false;
                    break;
                }
            if( is_same_host ) {
                _mutex.lock();
                new_urls.push_back(s);
                _mutex.unlock();
            }
        }
        return;                                                            
    }

public:
    vector<string> crawl(string startUrl, HtmlParser htmlParser) {
        host = get_host(startUrl);
        
        us.insert(startUrl);
        
        queue<string> q;
        q.push(startUrl);
        while( !q.empty() ) {
            
            new_urls.clear();
            vector<thread> _threads;
            queue<string> q_new;
            while( !q.empty() ) {
                string url = q.front();
                q.pop();
                _threads.push_back(thread(&Solution::accumulate,this,url,htmlParser));
            }
            for(auto& t : _threads)
                t.join();
            for(auto& url : new_urls) {
                if( us.insert(url).second )
                    q_new.push(url);
            }
            q = q_new;
        }
        
        return vector(us.begin(),us.end());
    }
};
