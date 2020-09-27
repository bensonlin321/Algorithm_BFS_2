#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <queue>
#include <unordered_set>
#include <iostream>
#include <vector>
#include <limits>
#include <utility> // pair
#define INF 2147483647
#define EMPTY_ROOM 2147483647
#define GATE 0
#define WALL -1

class Solution1 {
public:
    void the_walls_gates(std::vector< std::vector<int> > space) {

        // get the size of the room
        int m = space.size();
        if(m < 1) return; 
        int n = space[0].size();
        if(n < 1) return; 

        // print the space
        for(int i = 0 ; i < m ; i++) {
            for(int j = 0 ; j < n ; j++) {
                if(space[i][j] == EMPTY_ROOM) {
                    printf("INF\t");
                } else {
                    printf("%d\t",space[i][j]);
                }
            }
            printf("\n");
        }

        std::queue< std::pair<int, int> > gate_position;
        std::vector< std::pair<int, int> > neighbor_pair;
        // neighbor: up, down, left, right
        std::pair<int, int> up, down, left, right;
        up.first     = -1;
        up.second    = 0;
        down.first   = 1;
        down.second  = 0;
        left.first   = 0;
        left.second  = -1;
        right.first  = 0;
        right.second = 1;
        
        neighbor_pair.push_back(up);
        neighbor_pair.push_back(down);
        neighbor_pair.push_back(left);
        neighbor_pair.push_back(right);

        // find the gates
        for (int i = 0 ; i < m ; i ++) {
            for (int j = 0 ; j < n ; j++) {
                if (space[i][j] == GATE) {
                    std::pair <int, int> position;
                    position.first = i;
                    position.second = j;
                    gate_position.push(position);
                }
            }
        }
        printf("======= Run BFS =======\n");

        // BFS
        int steps = 0;
        std::queue< std::pair<int, int> > next = gate_position;
        while (!next.empty()) { 
            int remain_size = next.size();
            for (int i = remain_size - 1 ; i >= 0; i--) {

                std::pair<int, int> cur = next.front();
                next.pop();
                int y = cur.first;
                int x = cur.second;
                printf("start from x: %d, y: %d\n", x, y);

                // if the space is a empty room, fill in the steps
                if (space[y][x] == EMPTY_ROOM) {
                    printf("x: %d, y: %d is empty room, set the step\n", x, y);
                    space[y][x] = steps;
                }
                if (space[y][x] != WALL) {
                    //printf("space[y][x] != WALL \n");
                    // check if the neighbor space (up, down, left, right) can pass through
                    for (int neighbor_cnt = 0 ; neighbor_cnt < neighbor_pair.size() ; neighbor_cnt++) {
                        int tmp_y = cur.first + neighbor_pair[neighbor_cnt].first;
                        int tmp_x = cur.second + neighbor_pair[neighbor_cnt].second;
                        //printf("tmp_x: %d, tmp_y: %d, nei_sec: %d, nei_first: %d\n", tmp_x, tmp_y, neighbor_pair[neighbor_cnt].second, neighbor_pair[neighbor_cnt].first);

                        std::pair<int, int> tmp_position (tmp_y, tmp_x);
                        if(is_valid(tmp_position, m, n) && space[tmp_y][tmp_x] == EMPTY_ROOM) {
                            printf("get empty room: x: %d, y:%d\n", tmp_x, tmp_y);
                            next.push(tmp_position);
                        }
                    }
                }
            }
            steps++;
            printf("======= steps++ %d ======= \n", steps);
        }

        // print the space
        for(int i = 0 ; i < m ; i++) {
            for(int j = 0 ; j < n ; j++) {
                printf("%d\t",space[i][j]);    
            }
            printf("\n");
        }

    }

    bool is_valid(std::pair<int, int>& cur, int& m, int& n) {
        // not out of the space
        return cur.first >= 0 && cur.first < m && cur.second >= 0 && cur.second < n;
    }

};

int main(int argc, char *argv[]) {
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);
    Solution1 *s1 = new Solution1();
    std::vector< std::vector<int> > input;
    std::vector<int> a, b, c, d;
    a.push_back(EMPTY_ROOM);
    a.push_back(WALL);
    a.push_back(GATE);
    a.push_back(EMPTY_ROOM);

    b.push_back(EMPTY_ROOM);
    b.push_back(EMPTY_ROOM);
    b.push_back(EMPTY_ROOM);
    b.push_back(EMPTY_ROOM);

    c.push_back(EMPTY_ROOM);
    c.push_back(WALL);
    c.push_back(EMPTY_ROOM);
    c.push_back(WALL);

    d.push_back(GATE);
    d.push_back(WALL);
    d.push_back(EMPTY_ROOM);
    d.push_back(EMPTY_ROOM);

    input.push_back(a);
    input.push_back(b);
    input.push_back(c);
    input.push_back(d);
    s1 -> the_walls_gates(input);
    //printf("result: %d\n", res);
}