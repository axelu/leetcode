
// 1797. Design Authentication Manager
// https://leetcode.com/problems/design-authentication-manager/



class AuthenticationManager {
private:
    // Definition of a doubly-linked list
    struct ListNode {
        string tokenId;
        int expirationTime;
        ListNode *prev;
        ListNode *next;
        ListNode(string s, int t) : tokenId(s), expirationTime(t), prev(nullptr), next(nullptr) {}
    };

    int n;
    int timeToLive;
    unordered_map<string,ListNode*> um;
    ListNode* head;
    ListNode* tail;

public:
    AuthenticationManager(int timeToLive) {
        n = 0;
        this->timeToLive = timeToLive;
        head = nullptr;
        tail = nullptr;
    }

    void generate(string tokenId, int currentTime) {
        // cout << "adding " << tokenId << " expiration " << currentTime+timeToLive << " currentTime " << currentTime << endl;
        ListNode* ln = new ListNode(tokenId,currentTime+timeToLive);
        if( head == nullptr ) {
            head = ln;
            tail = ln;
        } else {
            head->prev = ln;
            ln->next = head;
            head = ln;
        }
        um.insert({tokenId,ln});
        ++n;
    }

    void renew(string tokenId, int currentTime) {
        auto f = um.find(tokenId);
        if( f == um.end() ) return;
        // remove token from its current place in the list in all cases
        // if the token is expired, then all tokens beyond it are expired also
        // if the token is not expired, set its new expiration time and stick it to front of list
        ListNode* ln = f->second;
        if( ln->expirationTime <= currentTime ) {
            tail = ln->prev;
            if( tail == nullptr ) {
                // our token was the head of the list
                head = nullptr;
            } else {
                tail->next = nullptr;
            }
            while( ln != nullptr ) {
                --n;
                um.erase(ln->tokenId);
                ListNode* t = ln->next;
                delete ln;
                ln = t;
            }
        } else {
            if( ln == head && ln == tail ) {
                ln->expirationTime = currentTime+timeToLive;
            } else if( ln == head ) {
                ln->expirationTime = currentTime+timeToLive;
            } else if( ln == tail ) {
                ln->expirationTime = currentTime+timeToLive;
                tail = ln->prev;
                tail->next = nullptr;
                ln->prev = nullptr;
                head->prev = ln;
                ln->next = head;
                head = ln;
            } else {
                ln->expirationTime = currentTime+timeToLive;
                ln->prev->next = ln->next;
                ln->next->prev = ln->prev;
                ln->prev = nullptr;
                head->prev = ln;
                ln->next = head;
                head = ln;
            }
        }
    }

    int countUnexpiredTokens(int currentTime) {
        // cout << "countUnexpiredTokens currentTime " << currentTime << " tokencount " << n << endl;

        if( n == 0 ) return 0;
        ListNode* ln = tail;
        while( ln != nullptr && ln->expirationTime <= currentTime) {
            // cout << "evicting tokenId " << ln->tokenId << " expirationTime " << ln->expirationTime << endl;
            --n;
            um.erase(ln->tokenId);
            tail = ln->prev;
            if( tail == nullptr ) {
                // our token was the head of the list
                head = nullptr;
            } else {
                tail->next = nullptr;
            }
            delete ln;
            ln = tail;
        }
        return n;
    }
};

/**
 * Your AuthenticationManager object will be instantiated and called as such:
 * AuthenticationManager* obj = new AuthenticationManager(timeToLive);
 * obj->generate(tokenId,currentTime);
 * obj->renew(tokenId,currentTime);
 * int param_3 = obj->countUnexpiredTokens(currentTime);
 */
