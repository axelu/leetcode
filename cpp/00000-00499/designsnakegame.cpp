
// 353. Design Snake Game
// https://leetcode.com/problems/design-snake-game/



class SnakeGame {
private:
    int m,n;
    unordered_set<int> us;
    deque<array<int,2>> snake;
    vector<vector<int>> * _food;
    
    bool gameOver = false;
    int sz = 0; // score and food index
        
public:
    SnakeGame(int width, int height, vector<vector<int>>& food) {
        m = height;
        n = width;

        // initially snake is size 1 at 0,0
        us.insert(0);
        snake.push_front({0,0});
        
        _food = &food;
    }
    
    int move(string direction) {
        if( gameOver )
            return -1;
        
        // current position of snake's head
        int shx = snake.front()[0];
        int shy = snake.front()[1];
        // cout << "head     " << shx << " " << shy << endl;
        // current position of snake's tail
        int stx = snake.back()[0];
        int sty = snake.back()[1];
        // cout << "tail     " << stx << " " << sty << endl;
        

        // apply move
        if( direction == "R" )
            ++shy;
        else if( direction == "D" )
            ++shx;
        else if( direction == "L" )
            --shy;
        else if( direction == "U" )
            --shx;
        snake.pop_back();
        int t = stx << 15; t+= sty;
        us.erase(t);

        // cout << "head new " << shx << " " << shy << " " << direction << endl;
        
        if( shx < 0 || shx == m || 
            shy < 0 || shy == n ) {

            gameOver = true;
            return -1;
        }    
        
        int h = shx << 15; h+= shy;
        if( us.count(h) ) {
            gameOver = true;
            return -1;
        }    

        // is there food where our snake head is?
        if( sz < _food->size() ) {
            int fx = _food->at(sz)[0];
            int fy = _food->at(sz)[1];
            if( fx == shx && fy == shy ) {
                ++sz;
                us.insert(t);
                snake.push_back({stx,sty});
            }
        }
        snake.push_front({shx,shy});
        us.insert(h);
            
        return sz;
    }
};

/**
 * Your SnakeGame object will be instantiated and called as such:
 * SnakeGame* obj = new SnakeGame(width, height, food);
 * int param_1 = obj->move(direction);
 */
