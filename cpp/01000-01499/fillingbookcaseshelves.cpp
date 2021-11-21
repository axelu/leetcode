
// 1105. Filling Bookcase Shelves
// https://leetcode.com/problems/filling-bookcase-shelves/





class Solution {
private:
    int rec(vector<vector<int>>& books, int n, int currBook, int shelfWidth, int mem[]) {
        if( currBook == n )
            return 0;

        // we have a choice
        // put only the current book on the shelf by itself OR
        // as long as books fit on the shelf, put them on the shelf

        if( mem[currBook] != -1 )
            return mem[currBook];

        int ret = INT_MAX;
        int h = books[currBook][1]; // at least the current book will fit
        int remShelfWidth = shelfWidth;
        for(int i = currBook; i < n; ++i) {

            // does the current book still fit on hour shelf?
            if( remShelfWidth - books[i][0] >= 0 ) {
                // put the current book on the shelf
                h = max(h,books[i][1]);
                remShelfWidth -= books[i][0];
                ret = min(ret,h+rec(books,n,i+1,shelfWidth,mem));

            } else {
                break;
            }
        }

        return mem[currBook] = ret;
    }
public:
    int minHeightShelves(vector<vector<int>>& books, int shelfWidth) {
        int n = books.size();

        int mem[n];memset(mem,-1,sizeof mem);
        return rec(books,n,0,shelfWidth,mem);
    }
};
