#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Field.hpp"
#include <set>

class Animation {
public:

    static void startSelectedAnimation(std::vector<std::vector<sf::Sprite>>& field_balls, int* selected_ball_p, int menu_shift, int N, int sleep) {
        int selected_ball = *selected_ball_p;
        if (selected_ball == -1) return;

        int state = 1;
        int start_y = field_balls[selected_ball / N][selected_ball % N].getPosition().y;
        int top_coord = start_y - 7 * 9.0 / (double)N;

        while (true) {
            int selected_ball = *selected_ball_p;
            if (selected_ball == -1) break;

            int current_coord = field_balls[selected_ball / N][selected_ball % N].getPosition().y;
            if (top_coord < current_coord && state == 1) {
                field_balls[selected_ball / N][selected_ball % N].setPosition(field_balls[selected_ball / N][selected_ball % N].getPosition().x,
                    field_balls[selected_ball / N][selected_ball % N].getPosition().y - 1);
            }
            else if (top_coord == current_coord && state == 1)
                state = 2;
            else if (state == 2 && start_y > current_coord) {
                field_balls[selected_ball / N][selected_ball % N].setPosition(field_balls[selected_ball / N][selected_ball % N].getPosition().x,
                    field_balls[selected_ball / N][selected_ball % N].getPosition().y + 1);
            }
            else if (current_coord == start_y && state == 2)
                state = 1;
            Sleep(sleep);
        }
    }

    static void stopSelectedAnimation(std::vector<std::vector<sf::Sprite>>& field_balls, int* selected_ball_p, int N, int menu_shift, int sleep) {
        int selected_ball = *selected_ball_p;
        if (selected_ball == -1) return;

        *selected_ball_p = -1;

        int y_coord = 25 + (selected_ball / N) * (621 / N) + menu_shift;
        int need_y = y_coord + 6.0 * 9.0 / (double)N;

        while (field_balls[selected_ball / N][selected_ball % N].getPosition().y < need_y) {
            field_balls[selected_ball / N][selected_ball % N].setPosition(field_balls[selected_ball / N][selected_ball % N].getPosition().x,
                field_balls[selected_ball / N][selected_ball % N].getPosition().y + 1);
            Sleep(sleep);
        }
    }

    static void animateMovement(int from, std::vector<int> path, int N, std::vector<std::vector<sf::Sprite>>& field_balls, Field& field_class, sf::Vector2f prevPos, int sleep) {
        if (path.size() == 0)
            return;

        if (from == path[0]) {
            path.erase(path.begin());
        }

        if (path.size() == 0)
            return;

        int x_to = path[0] % N, x_from = from % N;
        int y_to = path[0] / N, y_from = from / N;

        int x_diff = field_balls[y_to][x_to].getPosition().x - field_balls[y_from][x_from].getPosition().x;
        int y_diff = field_balls[y_to][x_to].getPosition().y - field_balls[y_from][x_from].getPosition().y;

        int delta_move = 5;

        while (x_diff != 0 || y_diff != 0) {
            x_diff = field_balls[y_to][x_to].getPosition().x - field_balls[y_from][x_from].getPosition().x;
            y_diff = field_balls[y_to][x_to].getPosition().y - field_balls[y_from][x_from].getPosition().y;

            int sing_x = x_diff >= 0 ? 1 : -1, sign_y = y_diff >= 0 ? 1 : -1;

            field_balls[y_from][x_from].setPosition(sf::Vector2f(field_balls[y_from][x_from].getPosition().x + sing_x * min(delta_move, abs(x_diff)),
                field_balls[y_from][x_from].getPosition().y + sign_y * min(10, abs(y_diff))));
            Sleep(sleep);
        }

        swap(field_balls[y_from][x_from], field_balls[y_to][x_to]);
        field_balls[y_from][x_from].setPosition(prevPos);

        int c = field_class.get_cell(x_from, y_from);
        int bomb = field_class.get_bomb(x_from, y_from);
        field_class.set_cell(0, x_from, y_from, 0);
        field_class.set_cell(c, x_to, y_to, bomb);


        path.erase(path.begin());
        animateMovement(x_to + y_to * N, path, N, field_balls, field_class, field_balls[y_to][x_to].getPosition(), sleep);
    }

    static void startDeleteBallAnimation(vector<int> line, int N, Field& field_class, std::vector<std::vector<sf::Sprite>>& field, std::vector<std::vector<sf::Sprite>>& field_balls, int sleep) {
        vector<int> start_x(line.size()), start_y(line.size());

        int _i = 0;
        for (auto cell : line) {
            field_class.set_cell(0, cell % N, cell / N, -1);
            start_x[_i] = field[cell / N][cell % N].getPosition().x;
            start_y[_i] = field[cell / N][cell % N].getPosition().y;
            _i++;
        }

        double absolute = 9.0 / (double)N;
        double current = absolute * pow(0.75, 0);
        double diff = 55.0 * absolute - 55.0 * current;

        _i = 0;
        for (auto cell : line) {
            field_balls[cell / N][cell % N].setScale(sf::Vector2f(current, current));
            field_balls[cell / N][cell % N].setPosition(sf::Vector2f(start_x[_i] + 7.0 * absolute + diff / 2, start_y[_i] + 6.0 * absolute + diff / 2));
            _i++;
        }

        for (int i = 1; i <= 6; i++) {
            Sleep(sleep);
            current = absolute * pow(0.75, i);
            diff = 55.0 * absolute - 55.0 * current;
            _i = 0;
            for (auto cell : line) {
                field_balls[cell / N][cell % N].setScale(sf::Vector2f(current, current));
                field_balls[cell / N][cell % N].setPosition(sf::Vector2f(start_x[_i] + 7.0 * absolute + diff / 2, start_y[_i] + 6.0 * absolute + diff / 2));
                _i++;
            }
        }
        _i = 0;
        for (auto cell : line) {
            field_balls[cell / N][cell % N].setScale(sf::Vector2f(0, 0));
            field_balls[cell / N][cell % N].setPosition(start_x[_i] + 7.0 * 9.0 / (double)N, start_y[_i] + 6.0 * 9.0 / (double)N);
            _i++;
        }
    }

    static void updateScore(int& score, sf::Text& label) {
        label.setString("Score: " + std::to_string(score));
        label.setPosition(802 - 16 * label.getString().getSize() / 2, label.getPosition().y);
    }

    static bool checingLines(int& additionScore, Field& field_class, std::vector<std::vector<sf::Sprite>>& field, std::vector<std::vector<sf::Sprite>>& field_balls, int new_ball, int N, int sleep) {
        auto lines = field_class.get_lines(new_ball % N, new_ball / N);
        vector<int> main_line;
        for (auto line : lines) {
            for (auto ball : line) main_line.push_back(ball);
        }
        set<int> ball_unic;
        for (auto ball : main_line) ball_unic.insert(ball);
        main_line.clear();
        for (auto it = ball_unic.begin(); it != ball_unic.end(); it++) main_line.push_back(*it);
        additionScore += 5 * main_line.size();
        startDeleteBallAnimation(main_line, N, field_class, field, field_balls, sleep);
        return lines.size() != 0;
    }

    static void spawnBallDeletionCheck(int& score, sf::Text& label, std::vector<std::vector<sf::Sprite>>& field_balls, int N, int last, Field& field_class, long long& currentTurnState, int i, std::vector<std::vector<sf::Sprite>>& field, int delete_sleep, int should_wait) {
        Sleep(should_wait);
        int additionScore = 0;

        bool lines = checingLines(additionScore, field_class, field, field_balls, last, N, delete_sleep);

        score += additionScore;
        updateScore(score, label);

        currentTurnState = currentTurnState | (1 << i);
    }

    static bool isAnyLines(Field& field_class, int N) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                auto res = field_class.get_lines(i, j);
                if (res.size() > 0) return true;
            }
        }
        return false;
    }

    static void startAnimateMovement(int& score, sf::Text& label, std::vector<std::vector<sf::Sprite>>& field_balls, int* selected_ball, int menu_shift, int N, vector<int> path, Field& field_class, sf::Vector2f prevPos, int* currentTurnState, std::vector<std::vector<sf::Sprite>>& field, int stop_sleep, int move_sleep, int delete_sleep) {
        int tmp = *selected_ball;
        int y_coord = 25 + (path[path.size() - 1] / N) * (621 / N) + menu_shift;
        int need_y = y_coord + 6.0 * 9.0 / (double)N;
        int additionScore = 0;

        int t = path[path.size() - 1];

        *currentTurnState = 1;
        stopSelectedAnimation(field_balls, selected_ball, N, menu_shift, stop_sleep);
        animateMovement(tmp, path, N, field_balls, field_class, prevPos, move_sleep);
        if (field_balls[tmp / N][tmp % N].getPosition().y != need_y) {
            stopSelectedAnimation(field_balls, &t, N, menu_shift, stop_sleep);
        }
        bool lines = checingLines(additionScore, field_class, field, field_balls, path[path.size() - 1], N, delete_sleep);

        score += additionScore;
        updateScore(score, label);

        if (!lines)
            *currentTurnState = 2;
        else *currentTurnState = 0;
    }

    static void startBallSpawnAnimation(std::vector<std::vector<sf::Sprite>>& field_balls, std::vector<std::vector<sf::Sprite>>& field, Ball ball, int N, int sleep) { // spawn balls
        int start_x = field[ball.y][ball.x].getPosition().x;
        int start_y = field[ball.y][ball.x].getPosition().y;
        int width = 91 * field[ball.y][ball.x].getScale().x;

        double absolute = 9.0 / (double)N;
        double current = absolute * pow(0.75, 6);
        double diff = 55.0 * absolute - 55.0 * current;
        field_balls[ball.y][ball.x].setScale(sf::Vector2f(current, current));
        field_balls[ball.y][ball.x].setPosition(sf::Vector2f(start_x + 7.0 * absolute + diff / 2, start_y + 6.0 * absolute + diff / 2));

        for (int i = 1; i <= 6; i++) {
            Sleep(sleep);
            current = absolute * pow(0.75, 6 - i);
            diff = 55.0 * absolute - 55.0 * current;
            field_balls[ball.y][ball.x].setScale(sf::Vector2f(current, current));
            field_balls[ball.y][ball.x].setPosition(sf::Vector2f(start_x + 7.0 * absolute + diff / 2, start_y + 6.0 * absolute + diff / 2));
        }
    }
};