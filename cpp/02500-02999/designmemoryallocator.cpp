
// 2502. Design Memory Allocator
// https://leetcode.com/problems/design-memory-allocator/

/* test cases
["Allocator","free","free","free","free","free","allocate","allocate","allocate","free","free","free","allocate","allocate","free","free","free","allocate","allocate","free","allocate","allocate","allocate","free","free","free","free","free","free","free","allocate","free","allocate","free","allocate","allocate","free","allocate","allocate","free","free","allocate","free","free","allocate","allocate","allocate","free","allocate","allocate","free","free","allocate","allocate","allocate","free","allocate","allocate","free","free","free","allocate","free","free","free","free","allocate","allocate","allocate","free","allocate","free","free","allocate","free","allocate","free","free"]
[[100],[27],[12],[53],[61],[80],[21,78],[81,40],[50,76],[40],[76],[63],[25,100],[96,12],[92],[92],[84],[19,71],[22,90],[60],[42,79],[26,41],[59,33],[79],[58],[97],[92],[97],[92],[40],[52,74],[40],[53,17],[17],[36,32],[51,13],[41],[5,87],[44,66],[71],[53],[74,14],[78],[14],[32,54],[45,28],[84,47],[16],[100,78],[5,99],[33],[100],[62,79],[31,32],[85,81],[78],[34,45],[47,7],[7],[84],[6],[35,55],[94],[87],[20],[87],[96,60],[40,66],[28,96],[28],[25,2],[100],[96],[19,35],[16],[92,42],[80],[79]]


["Allocator","allocate","allocate","allocate","free","free","free","allocate"]
[[100],[21,78],[81,40],[50,76],[40],[76],[63],[25,100]]

["Allocator","allocate","allocate","free","allocate"]
[[100],[21,78],[50,76],[76],[25,100]]



["Allocator","free","free","free","free","free","allocate","allocate","allocate","free","free","free","allocate","allocate","free","free","free","allocate","allocate","free","allocate","allocate","allocate","free","free","free","free","free","free","free","allocate","free","allocate","free","allocate","allocate","free","allocate","allocate","free","free","allocate","free","free","allocate","allocate","allocate","free","allocate","allocate"]
[[100],[27],[12],[53],[61],[80],[21,78],[81,40],[50,76],[40],[76],[63],[25,100],[96,12],[92],[92],[84],[19,71],[22,90],[60],[42,79],[26,41],[59,33],[79],[58],[97],[92],[97],[92],[40],[52,74],[40],[53,17],[17],[36,32],[51,13],[41],[5,87],[44,66],[71],[53],[74,14],[78],[14],[32,54],[45,28],[84,47],[16],[100,78],[5,99]]



["Allocator","allocate","allocate","free","allocate","allocate","allocate","free","free","free","free","free","free","free","allocate","free","allocate","free","allocate","allocate","free","allocate","allocate","free","free","allocate","free","free","allocate","allocate","allocate","free","allocate","allocate"]
[[100],[21,78],[50,76],[76],[25,100],[19,71],[22,90],[79],[58],[97],[92],[97],[92],[40],[52,74],[40],[53,17],[17],[36,32],[51,13],[41],[5,87],[44,66],[71],[53],[74,14],[78],[14],[32,54],[45,28],[84,47],[16],[100,78],[5,99]]

["Allocator","allocate","allocate","free","allocate","allocate","allocate","allocate","allocate","free","free","allocate","free","free","allocate","allocate","allocate","free","allocate","allocate"]
[[100],[21,78],[50,76],[76],[25,100],[19,71],[22,90],[5,87],[44,66],[71],[53],[74,14],[78],[14],[32,54],[45,28],[84,47],[16],[100,78],[5,99]]



["Allocator","allocate","allocate","allocate","allocate","allocate","free","free","allocate"]
[[100],[1,1],[2,2],[1,3],[1,4],[1,5],[2],[4],[1,6]]


["Allocator","allocate","allocate","free","allocate","allocate","allocate","allocate","free","free","allocate","free","allocate","free","allocate","free","allocate","free","free","allocate","free","allocate","free","free"]
[[100],[21,78],[50,76],[76],[25,100],[19,71],[22,90],[5,87],[71],[78],[5,99],[100],[31,32],[87],[28,96],[28],[25,2],[100],[96],[19,35],[16],[92,42],[80],[79]]
*/

/*
 * need the ability to
 *     keep track of free blocks by size (left most idx)
 *     keep track of free blocks by left most index (left most idx and size)
 *     keep track of blocks per mID (per block we need left most idx and size)
 *
 *      find the left most index that can house size units
 */


class Allocator {
private:
    int n;
    map<int,set<int>> free_by_size;                 // key: size, value: sorted list of indicies
    map<int,int> free_by_idx;                       // key: idx, value: size
    unordered_map<int,vector<pair<int,int>>> used;  // key: mID, value: list of {block left most idx, size} pairs

    void free_by_x_erase(int size, int idx) {
        // cout << "free_by_x_erase size " << size << " idx " << idx << endl;
        free_by_size[size].erase(idx);
        if( free_by_size[size].empty() )
            free_by_size.erase(size);

        free_by_idx.erase(idx);
    }

    map<int,int>::iterator free_by_x_insert(int size, int idx) {
        free_by_size[size].insert(idx);
        return free_by_idx.insert({idx,size}).first;
    }

    void free(pair<int,int> block) {
        int idx = block.first;
        int sz  = block.second;
        // cout << "free size " << sz << " idx " << idx << endl;

        if( free_by_idx.empty() ) {
            free_by_x_insert(sz,idx);
            return;
        }

        // obviously the block we are freeing will not be in the list of free blocks
        auto f = free_by_idx.lower_bound(idx);

        if( f == free_by_idx.begin() ) {
            // our to be free'd block will become the left most free block by idx
            // the question is: does it border the block to its right and needs to be merged?
            int rgt_idx = f->first;
            int rgt_size = f->second;
            bool rgt_merge = idx + sz == rgt_idx ? true : false;

            if( rgt_merge ) {
                free_by_x_erase(rgt_size,rgt_idx);            // delete the free block we found
                free_by_x_insert(sz + rgt_size,idx);                   // insert our new combined block
            } else {
                free_by_x_insert(sz,idx);
            }

        } else if( f == free_by_idx.end() ) {
            // our block will beome the right most free block by idx
            // the question is: does it border the block to its left and needs to be merged?
            int lft_idx = prev(f)->first;
            int lft_size = prev(f)->second;
            bool lft_merge = lft_idx + lft_size == idx ? true: false;

            if( lft_merge ) {
                free_by_x_erase(lft_size,lft_idx);
                free_by_x_insert(lft_size + sz,lft_idx);
            } else {
                free_by_x_insert(sz,idx);
            }

        } else {
            // the idx of the free block we found is greater than the idx of the block we are freeing
            // so basically the block we found is to the right of the block we are freeing
            // there definitely is free block to the left of the free block we found


            // our to be free block is between two other free blocks
            // does it border the block to its left and needs to be merged?
            // does it border the block to its right and needs to be merged?

            int lft_idx = prev(f)->first;
            int lft_size = prev(f)->second;
            bool lft_merge = lft_idx + lft_size == idx ? true: false;

            int rgt_idx = f->first;
            int rgt_size = f->second;
            bool rgt_merge = idx + sz == rgt_idx ? true : false;

            if( lft_merge && rgt_merge ) {
                free_by_x_erase(lft_size,lft_idx);
                free_by_x_erase(rgt_size,rgt_idx);
                free_by_x_insert(lft_size + sz + rgt_size,lft_idx);

            } else if( lft_merge && !rgt_merge ) {
                free_by_x_erase(lft_size,lft_idx);
                free_by_x_insert(lft_size + sz,lft_idx);

            } else if( !lft_merge && rgt_merge ) {
                free_by_x_erase(rgt_size,rgt_idx);
                free_by_x_insert(sz + rgt_size,idx);

            } else {
              free_by_x_insert(sz,idx);
            }
        }
    }

    void free_by_idx_print() {
        cout << "free blocks ";
        for(auto it = free_by_idx.begin(); it != free_by_idx.end(); ++it)
            cout << it->first << ":" << it->second << " ";
        cout << endl;
    }

public:
    Allocator(int n) {
        this->n = n;
        free_by_x_insert(n,0); // initially there is one free block starting at 0 of size n
    }

    int allocate(int size, int mID) {
        if( free_by_idx.empty() || free_by_size.rbegin()->first < size )
            return -1;

        // give me the left most free block with size >= size

        // Note: we already know there will be a free block with sufficient size
        auto it = free_by_idx.begin();
        while(true) {
            int f_idx = it->first;
            int f_size = it->second;
            if( it->second >= size ) {
                free_by_x_erase(f_size,f_idx);
                if( f_size != size )
                    free_by_x_insert(f_size - size, f_idx + size);

                used[mID].push_back({f_idx,size});
                // TODO should we merge blocks if possible at this point?

                // cout << "allocate size " << size << " mID " << mID << " ";free_by_idx_print();
                return f_idx;
            }
            ++it;
        }

        return -1; // satisfy compiler, we should never reach here
    }

    int free(int mID) {
        int ret = 0;
        for(auto block: used[mID]) {
            ret += block.second;
            free(block);
        }
        used.erase(mID);
        // cout << "free mID " << mID << " ";free_by_idx_print();
        return ret;
    }
};

/**
 * Your Allocator object will be instantiated and called as such:
 * Allocator* obj = new Allocator(n);
 * int param_1 = obj->allocate(size,mID);
 * int param_2 = obj->free(mID);
 */
