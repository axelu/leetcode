
// 1236. Web Crawler
// https://leetcode.com/problems/web-crawler/




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
    string getHostName(string& url) {
        int i;
        for(i = 7; i < url.size(); ++i) {
            if( !isalpha(url[i]) && !isdigit(url[i]) && url[i] != '.' && url[i] != '-' )
                return url.substr(7,i-7);
        }
        return url.substr(7,i+1-7);
    }

public:
    vector<string> crawl(string& startUrl, HtmlParser htmlParser) {
        string hostname = getHostName(startUrl);

        vector<string> ans = {startUrl};

        // BFS
        unordered_set<string> seen;
        queue<string> q;
        q.push(startUrl);
        seen.insert(startUrl);
        string url;
        vector<string> urls;
        int i;
        while(!q.empty()) {
            url = q.front();
            q.pop();

            urls = htmlParser.getUrls(url);
            for(i = 0; i < urls.size(); ++i) {
                if( seen.find(urls[i]) != seen.end() || hostname != getHostName(urls[i]) )
                    continue;

                seen.insert(urls[i]);
                ans.push_back(urls[i]);
                q.push(urls[i]);
            }
        }
        return ans;;
    }
};
