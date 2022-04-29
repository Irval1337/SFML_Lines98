#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <set>
#include <queue>
#include "Game_settings.hpp"

using namespace std;

struct Ball {
    int color;
    int x, y;
    int bomb_id;
    Ball(int color, int x, int y, int bomb_id) {
        this->color = color;
        this->x = x;
        this->y = y;
        this->bomb_id = bomb_id;
    }
};

class Field {
public:
    void setColors(int c) {
        colors_count = c;
    }

    void fill_graph(int N) {
        for (int i = 0; i < N; i++)
            this->graph[i].clear();
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i > 0)
                    this->graph[i * N + j].push_back((i - 1) * N + j);
                if (i < N - 1)
                    this->graph[i * N + j].push_back((i + 1) * N + j);
                if (j > 0)
                    this->graph[i * N + j].push_back(i * N + j - 1);
                if (j < N - 1)
                    this->graph[i * N + j].push_back(i * N + j + 1);
            }
        }
    }

    void set_n(int N) {
        this->N = N;
        this->graph = vector<vector<int>>(N * N);
        this->field_info = vector<vector<int>>(N, vector<int>(N, 0));
        this->bomb_info = vector<vector<int>>(N, vector<int>(N, 0));
        fill_graph(N);
    }

    Field(int N) {
        srand(time(NULL));
        set_n(N);
    }


    int get_N() {
        return this->N;
    }

    int get_free_count() {
        int count = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (this->field_info[i][j] == 0) count++;
            }
        }
        return count;
    }

    bool isLoose() {
        return get_free_count() == 0;
    }

    vector<Ball> generate_next_balls(int count, int clr = -1) { // TODO: choose colors
        Game_settings_info game_settings;
        if (!game_settings.isExists()) {
            game_settings.set_default();
            game_settings.saveConfig();
        }
        else game_settings.loadConfig();

        vector<Ball> balls;
        vector<int> prev;
        for (int i = 0; i < count; i++) {
            int prop_bomb = rand() % 100;
            int bomb = 0;

            int prev_count = 0;
            if (game_settings.multicolor) {
                if (prop_bomb <= prev_count + game_settings.prop_multi && bomb == 0)
                    bomb = 1;
                prev_count += game_settings.prop_multi;
            }
            if (game_settings.zone_bomb) {
                if (prop_bomb <= prev_count + game_settings.prop_zone && bomb == 0)
                    bomb = 2;
                prev_count += game_settings.prop_zone;
            }
            if (game_settings.v_h_bomb) {
                if (prop_bomb <= prev_count + game_settings.prop_v_h && bomb == 0)
                    bomb = 3;
                prev_count += game_settings.prop_v_h;
            }

            int color = clr == -1 ? (rand() % colors_count + 1) : clr;
            int x, y;
            int number = rand() % (get_free_count() - prev.size());

            int c = 0;
            bool needExit = false;
            for (int j = 0; j < N && !needExit; j++) {
                for (int k = 0; k < N && !needExit; k++) {
                    if (this->field_info[j][k] == 0 && find(prev.begin(), prev.end(), j * N + k) == prev.end()) {
                        if (c == number) {
                            x = k, y = j;
                            needExit = true;
                            break;
                        }
                        else c++;
                    }
                }
            }
            if (!needExit) {
                cout << "WTF";
            }
            balls.push_back(Ball(color, x, y, bomb));
            prev.push_back(y * N + x);
        }

        return balls;
    }

    int get_cell(int x, int y) {
        return this->field_info[y][x];
    }

    int get_bomb(int x, int y) {
        return this->bomb_info[y][x];
    }

    void set_cell(int value, int x, int y, int bomb_id) {
        this->field_info[y][x] = value;
        if (bomb_id != -1)
            this->bomb_info[y][x] = bomb_id;
    }

    vector<int> get_path(int from, int to) {
        queue<int> q;
        vector<vector<int>> paths(this->N * this->N);

        q.push(from);
        paths[from] = { from };

        while (!q.empty()) {
            int _v = q.front();
            q.pop();
            for (auto _u : graph[_v]) {
                if (this->field_info[_u / this->N][_u % this->N] != 0) continue;

                if (paths[_u].empty()) {
                    paths[_u] = paths[_v];
                    paths[_u].push_back(_u);
                    q.push(_u);
                }
            }
        }

        return paths[to];
    }

    vector<vector<int>> get_lines(int x, int y) {
        vector<vector<int>> max_ans;

        vector<int> colors;
        if (bomb_info[y][x] != 1)
            colors.push_back(field_info[y][x]);
        else colors = { 1, 2, 3, 4, 5, 6, 7 };

        int max_ans_count = 0;

        for (auto color : colors) {
            vector<vector<int>> ans;
            vector<int> tmp = { y * N + x };
            int same_count = 1;
            int current_ans = 0;

            for (int i = y + 1; i < N; i++) {
                if (field_info[i][x] == color || bomb_info[i][x] == 1) {
                    same_count++;
                    tmp.push_back(i * N + x);
                }
                else break;
            }

            for (int i = y - 1; i >= 0; i--) {
                if (field_info[i][x] == color || bomb_info[i][x] == 1) {
                    same_count++;
                    tmp.push_back(i * N + x);
                }
                else break;
            }

            if (same_count >= 5) {
                ans.push_back(tmp);
                current_ans += same_count;
            }
            tmp = { y * N + x };
            same_count = 1;

            for (int i = x + 1; i < N; i++) {
                if (field_info[y][i] == color || bomb_info[y][i] == 1) {
                    same_count++;
                    tmp.push_back(y * N + i);
                }
                else break;
            }

            for (int i = x - 1; i >= 0; i--) {
                if (field_info[y][i] == color || bomb_info[y][i] == 1) {
                    same_count++;
                    tmp.push_back(y * N + i);
                }
                else break;
            }

            if (same_count >= 5) {
                ans.push_back(tmp);
                current_ans += same_count;
            }
            tmp = { y * N + x };
            same_count = 1;

            int tmp_x = x + 1, tmp_y = y + 1;

            while (tmp_x < N && tmp_y < N) {
                if (field_info[tmp_y][tmp_x] == color || bomb_info[tmp_y][tmp_x] == 1) {
                    same_count++;
                    tmp.push_back(tmp_y * N + tmp_x);
                }
                else break;
                tmp_x++, tmp_y++;
            }

            tmp_x = x - 1, tmp_y = y - 1;

            while (tmp_x >= 0 && tmp_y >= 0) {
                if (field_info[tmp_y][tmp_x] == color || bomb_info[tmp_y][tmp_x] == 1) {
                    same_count++;
                    tmp.push_back(tmp_y * N + tmp_x);
                }
                else break;
                tmp_x--, tmp_y--;
            }

            if (same_count >= 5) {
                ans.push_back(tmp);
                current_ans += same_count;
            }

            tmp = { y * N + x };
            same_count = 1;

            tmp_x = x + 1, tmp_y = y - 1;

            while (tmp_x < N && tmp_y < N && tmp_x >= 0 && tmp_y >= 0) {
                if (field_info[tmp_y][tmp_x] == color || bomb_info[tmp_y][tmp_x] == 1) {
                    same_count++;
                    tmp.push_back(tmp_y * N + tmp_x);
                }
                else break;
                tmp_x++, tmp_y--;
            }

            tmp_x = x - 1, tmp_y = y + 1;

            while (tmp_x < N && tmp_y < N && tmp_x >= 0 && tmp_y >= 0) {
                if (field_info[tmp_y][tmp_x] == color || bomb_info[tmp_y][tmp_x] == 1) {
                    same_count++;
                    tmp.push_back(tmp_y * N + tmp_x);
                }
                else break;
                tmp_x--, tmp_y++;
            }

            if (same_count >= 5) {
                ans.push_back(tmp);
                current_ans += same_count;
            }

            if (current_ans > max_ans_count) {
                max_ans_count = current_ans;
                max_ans = ans;
            }
        }

        auto new_ans = max_ans;
        for (auto anses : max_ans) {
            for (auto ball : anses) {
                x = ball % N, y = ball / N;

                if (bomb_info[y][x] == 2 && max_ans.size() > 0)
                {
                    vector<int> tmp;

                    if (x - 1 >= 0 && field_info[y][x - 1] != 0) tmp.push_back(y * N + x - 1);
                    if (x + 1 < N && field_info[y][x + 1] != 0) tmp.push_back(y * N + x + 1);
                    if (y - 1 >= 0 && field_info[y - 1][x] != 0) tmp.push_back((y - 1) * N + x);
                    if (y + 1 < N && field_info[y + 1][x] != 0) tmp.push_back((y + 1) * N + x);
                    if (x - 1 >= 0 && y - 1 >= 0 && field_info[y - 1][x - 1] != 0) tmp.push_back((y - 1) * N + x - 1);
                    if (x + 1 < N && y - 1 >= 0 && field_info[y - 1][x + 1] != 0) tmp.push_back((y - 1) * N + x + 1);
                    if (x - 1 >= 0 && y + 1 < N && field_info[y + 1][x - 1] != 0) tmp.push_back((y + 1) * N + x - 1);
                    if (x + 1 < N && y + 1 < N && field_info[y + 1][x + 1] != 0) tmp.push_back((y + 1) * N + x + 1);

                    new_ans.push_back(tmp);
                }

                if (bomb_info[y][x] == 3 && max_ans.size() > 0) {
                    vector<int> tmp;

                    int start_x = x, start_y = y;

                    x--;
                    while (x >= 0) {
                        if (field_info[y][x] != 0)
                            tmp.push_back(y * N + x);
                        x--;
                    }
                    x = start_x;

                    x++;
                    while (x < N) {
                        if (field_info[y][x] != 0)
                            tmp.push_back(y * N + x);
                        x++;
                    }
                    x = start_x;

                    y--;
                    while (y >= 0) {
                        if (field_info[y][x] != 0)
                            tmp.push_back(y * N + x);
                        y--;
                    }
                    y = start_y;

                    y++;
                    while (y < N) {
                        if (field_info[y][x] != 0)
                            tmp.push_back(y * N + x);
                        y++;
                    }
                    y = start_y;

                    new_ans.push_back(tmp);
                }
            }
        }

        return new_ans;
    }

private:
    vector<vector<int>> graph;
    vector<vector<int>> field_info;
    vector<vector<int>> bomb_info;
    int N;
    int colors_count;
};