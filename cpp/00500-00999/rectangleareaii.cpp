
// 850. Rectangle Area II
// https://leetcode.com/problems/rectangle-area-ii/
// day 22 Aug 2021 challenge
// https://leetcode.com/problems/rectangle-area-ii/


// coordinate compression based on 
// https://leetcode.com/problems/rectangle-area-ii/discuss/138206/C%2B%2B-10-lines-normalized-canvas
/*
class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int n = rectangles.size(); // 1 <= rectangles.length <= 200

        // coordinate compression
        set<int> uniqueX;   // unique x coordinates, at most 400 distinct x values
        set<int> uniqueY;   // unique y coordinates, at most 400 distinct y values
        int x1,y1,x2,y2;    // x1,y1 bottom-left corner; x2,y2 top-right ocrner
        for(int i = 0; i < n; ++i) {
            x1 = rectangles[i][0];
            y1 = rectangles[i][1];
            x2 = rectangles[i][2];
            y2 = rectangles[i][3];
            uniqueX.insert(x1);uniqueX.insert(x2);
            uniqueY.insert(y1);uniqueY.insert(y2);
        }
        
        vector<vector<int>> grid(uniqueX.size(),vector<int>(uniqueY.size(),0));
        
        // coordinate to grid index
        unordered_map<int,int> mX;
        int i = 0;
        for(auto it = uniqueX.begin(); it != uniqueX.end(); ++it)
            mX.insert({*it,i++});
        unordered_map<int,int> mY;
        i = 0;
        for(auto it = uniqueY.begin(); it != uniqueY.end(); ++it)
            mY.insert({*it,i++});
        
        
        long ans = 0L;
        
        for(int i = 0; i < n; ++i) {
            x1 = rectangles[i][0];
            y1 = rectangles[i][1];
            x2 = rectangles[i][2];
            y2 = rectangles[i][3];
            
            for(int i = mX[x1]; i != mX[x2]; ++i) {
                auto itx = uniqueX.begin();
                advance(itx,i);

                for(int j = mY[y1]; j != mY[y2]; ++j) {
                    auto ity = uniqueY.begin();
                    advance(ity,j);
                
                    if( grid[i][j] == 0 ) {
                        ans += ((long)*next(itx) - *itx) * (*next(ity) - *ity);
                        grid[i][j] = 1; // mark as counted
                    }
                }
            }
        }
        
        return ans%1000000007;
    }
};
*/


// segment tree and line sweep
// https://stackoverflow.com/questions/55702005/area-of-union-of-rectangles-using-segment-trees
// https://tryalgo.org/en/geometry/2016/06/25/union-of-rectangles/
// using concept from https://leetcode.com/problems/describe-the-painting/ solution
class Solution {
private:
    struct Node{
        int s; // begin
        int e; // end
        int count; 
        long score;
        Node* left;
        Node* right;
        Node(int s, int e) : s(s), e(e), count(0), score(0), left(nullptr), right(nullptr) {}
    };

    Node* build(vector<int>& arr, int s, int e) {
        //cout << "build s " << s << " e " << e << endl;
        Node* node = new Node(arr[s],arr[e]);
        if( e-s == 1 )
            return node;
        
        int mid = s + ((e-s)/2);
        node->left =  build(arr,s,mid);
        node->right = build(arr,mid,e);
        return node;
    }
    
    // debug
    // level order traversal
    void levelOrderTraversal(Node* root) {
        // BFS
        queue<pair<Node*,int>> q;
        q.push({root,0});
        
        Node* node;
        int level;
        int currLevel = -1;
        while( !q.empty() ) {
            node  = q.front().first;
            level = q.front().second;
            q.pop();
            
            if( currLevel != level ) {
                cout << endl;
                cout << level << ": ";
                currLevel = level;
            }
            cout << "{" << node->s << "," << node->e << "}";
            if( node->left == nullptr && node->right == nullptr)
                cout << "leaf";
            cout << " ";
            
            if( node->left != nullptr )
                q.push({node->left,level+1});
            if( node->right != nullptr )
                q.push({node->right,level+1});
        }
    }
    
    long update(Node* node, int s, int e, int type) {
        // cout << "update s " << s << " e " << e << " type " << type << endl;
        
        if( node->s == s && node->e == e ) {
            node->count += type;
        } else {
            if( node->left != nullptr && node->left->e > s )
                update(node->left,s,min(node->left->e,e),type);
            if( node->right != nullptr && node->right->s < e )
                update(node->right,max(node->right->s,s),e,type);
        }
        
        if( node->count > 0 ) 
            node->score = node->e - node->s;
        else {
            long leftScore  = node->left != nullptr  ? node->left->score  : 0;
            long rightScore = node->right != nullptr ? node->right->score : 0;
            node->score = leftScore+rightScore;
        }
        
        return node->score;
    }
    

public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        int n = rectangles.size(); // 1 <= rectangles.length <= 200

        // we are going to build a segment tree along the y (veritcal) axis
        // each leaf of that segment tree represents a range of y values encountered
        // we will then do a horizontal line sweep along the x (horizontal) axis, 
        // while we walk accross the horizontal line, when we encounter the begin
        // of a rectangle, we will increase the count of that y range in our segment tree,
        // when we encounter the end of a rectangle we decrease the count of that y range,
        // all positive counts at each step add to our area
        
        set<int> uniqueY;
        vector<vector<int>> events;
        int x1,y1,x2,y2;    // x1,y1 bottom-left corner; x2,y2 top-right ocrner
        for(int i = 0; i < n; ++i) {
            x1 = rectangles[i][0];
            y1 = rectangles[i][1];
            x2 = rectangles[i][2];
            y2 = rectangles[i][3];            
            uniqueY.insert(y1);uniqueY.insert(y2);
            events.push_back({x1, 1,y1,y2});    // begin of current rectangle
            events.push_back({x2,-1,y1,y2});    // end of current rectangle
        }
        sort(events.begin(),events.end(),[](const vector<int>& a, const vector<int>& b){
            return a[0] < b[0];
        });
        
        // build empty segment tree
        vector<int> arr(uniqueY.begin(),uniqueY.end());
        int t = arr.size();
        Node* root = build(arr,0,t-1);
        // levelOrderTraversal(root);
        
        
        
        // horizontal line sweep along the x axis
        long ans = 0;
        long yRangeSum = 0; // sum of all active y ranges
        int currX;
        int prevX = 0;      // initial value irrelevant, just to init
        int type;
        for(int i = 0; i < events.size(); ++i) {
            currX = events[i][0];
            type  = events[i][1]; // 1 begin of rectangle, -1 end of rectangle
            y1    = events[i][2];
            y2    = events[i][3];
            
            // tally up everything seen so far that is active
            // note that multiple events can occur on the same x
            // in that case currX == prevX -> currX-prevX = 0, so we will not doublecount
            ans += (currX-prevX) * yRangeSum;
            
            yRangeSum = update(root,y1,y2,type);
            prevX = currX;
        }
        
        return ans%1000000007;
    }
};
