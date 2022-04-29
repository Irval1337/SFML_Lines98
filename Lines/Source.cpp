#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.hpp"
#include "Field.hpp"
#include <queue>
#include <algorithm>
#include <thread>
#include <Windows.h>
#include "Animation.hpp"
#include "GraphicSettings.hpp"
#include "Graphic_settings.hpp"
#include "TopScores.hpp"
#include "Top_score_settings.hpp"
#include <chrono>
#include "GameSettings.hpp"
#include "Graphic_settings.hpp"

sf::Texture ball_aqua, ball_blue, ball_green, ball_pink, ball_red, ball_violet, ball_yellow, ball_multi;
sf::Texture ball_v_h_aqua, ball_v_h_blue, ball_v_h_green, ball_v_h_pink, ball_v_h_red, ball_v_h_violet, ball_v_h_yellow;
sf::Texture ball_zone_aqua, ball_zone_blue, ball_zone_green, ball_zone_pink, ball_zone_red, ball_zone_violet, ball_zone_yellow;

void SetBalls(std::vector<std::vector<sf::Sprite>>& field_balls, std::vector<std::vector<sf::Sprite>>& field, Field& field_class, Ball ball, int N, int sleep) {
    if (ball.bomb_id == 0) {
        switch (ball.color) {
        case 1:
            field_balls[ball.y][ball.x].setTexture(ball_aqua);
            break;
        case 2:
            field_balls[ball.y][ball.x].setTexture(ball_blue);
            break;
        case 3:
            field_balls[ball.y][ball.x].setTexture(ball_green);
            break;
        case 4:
            field_balls[ball.y][ball.x].setTexture(ball_pink);
            break;
        case 5:
            field_balls[ball.y][ball.x].setTexture(ball_red);
            break;
        case 6:
            field_balls[ball.y][ball.x].setTexture(ball_violet);
            break;
        case 7:
            field_balls[ball.y][ball.x].setTexture(ball_yellow);
            break;
        }

        field_class.set_cell(ball.color, ball.x, ball.y, ball.bomb_id);
    }
    if (ball.bomb_id == 1) {
        field_balls[ball.y][ball.x].setTexture(ball_multi);
        field_class.set_cell(ball.color, ball.x, ball.y, ball.bomb_id);
    }
    if (ball.bomb_id == 2) {
        switch (ball.color) {
        case 1:
            field_balls[ball.y][ball.x].setTexture(ball_zone_aqua);
            break;
        case 2:
            field_balls[ball.y][ball.x].setTexture(ball_zone_blue);
            break;
        case 3:
            field_balls[ball.y][ball.x].setTexture(ball_zone_green);
            break;
        case 4:
            field_balls[ball.y][ball.x].setTexture(ball_zone_pink);
            break;
        case 5:
            field_balls[ball.y][ball.x].setTexture(ball_zone_red);
            break;
        case 6:
            field_balls[ball.y][ball.x].setTexture(ball_zone_violet);
            break;
        case 7:
            field_balls[ball.y][ball.x].setTexture(ball_zone_yellow);
            break;
        }

        field_class.set_cell(ball.color, ball.x, ball.y, ball.bomb_id);
    }
    if (ball.bomb_id == 3) {
        switch (ball.color) {
        case 1:
            field_balls[ball.y][ball.x].setTexture(ball_v_h_aqua);
            break;
        case 2:
            field_balls[ball.y][ball.x].setTexture(ball_v_h_blue);
            break;
        case 3:
            field_balls[ball.y][ball.x].setTexture(ball_v_h_green);
            break;
        case 4:
            field_balls[ball.y][ball.x].setTexture(ball_v_h_pink);
            break;
        case 5:
            field_balls[ball.y][ball.x].setTexture(ball_v_h_red);
            break;
        case 6:
            field_balls[ball.y][ball.x].setTexture(ball_v_h_violet);
            break;
        case 7:
            field_balls[ball.y][ball.x].setTexture(ball_v_h_yellow);
            break;
        }

        field_class.set_cell(ball.color, ball.x, ball.y, ball.bomb_id);
    }

    std::thread t(Animation::startBallSpawnAnimation, std::ref(field_balls), std::ref(field), ball, N, sleep);
    t.detach();
}

void SetNext(std::queue<Ball>& queue_balls, std::vector<sf::Sprite>& balls_next_sprite, Ball ball, int num) {
    if (ball.bomb_id == 0) {
        switch (ball.color) {
        case 1:
            balls_next_sprite[num].setTexture(ball_aqua);
            break;
        case 2:
            balls_next_sprite[num].setTexture(ball_blue);
            break;
        case 3:
            balls_next_sprite[num].setTexture(ball_green);
            break;
        case 4:
            balls_next_sprite[num].setTexture(ball_pink);
            break;
        case 5:
            balls_next_sprite[num].setTexture(ball_red);
            break;
        case 6:
            balls_next_sprite[num].setTexture(ball_violet);
            break;
        case 7:
            balls_next_sprite[num].setTexture(ball_yellow);
            break;
        }
    }
    if (ball.bomb_id == 1) {
        balls_next_sprite[num].setTexture(ball_multi);
    }
    if (ball.bomb_id == 2) {
        switch (ball.color) {
        case 1:
            balls_next_sprite[num].setTexture(ball_zone_aqua);
            break;
        case 2:
            balls_next_sprite[num].setTexture(ball_zone_blue);
            break;
        case 3:
            balls_next_sprite[num].setTexture(ball_zone_green);
            break;
        case 4:
            balls_next_sprite[num].setTexture(ball_zone_pink);
            break;
        case 5:
            balls_next_sprite[num].setTexture(ball_zone_red);
            break;
        case 6:
            balls_next_sprite[num].setTexture(ball_zone_violet);
            break;
        case 7:
            balls_next_sprite[num].setTexture(ball_zone_yellow);
            break;
        }
    }
    if (ball.bomb_id == 3) {
        switch (ball.color) {
        case 1:
            balls_next_sprite[num].setTexture(ball_v_h_aqua);
            break;
        case 2:
            balls_next_sprite[num].setTexture(ball_v_h_blue);
            break;
        case 3:
            balls_next_sprite[num].setTexture(ball_v_h_green);
            break;
        case 4:
            balls_next_sprite[num].setTexture(ball_v_h_pink);
            break;
        case 5:
            balls_next_sprite[num].setTexture(ball_v_h_red);
            break;
        case 6:
            balls_next_sprite[num].setTexture(ball_v_h_violet);
            break;
        case 7:
            balls_next_sprite[num].setTexture(ball_v_h_yellow);
            break;
        }
    }

    queue_balls.push(ball);
}

bool isMouseOver(sf::RenderWindow& window, sf::Sprite& sprite, int i, int j, int N, int menu_shift) {
    int mouseX = sf::Mouse::getPosition(window).x;
    int mouseY = sf::Mouse::getPosition(window).y;

    int btnPosX = 20 + j * (621 / N);
    int btnPosY = 25 + i * (621 / N) + menu_shift;

    int btnxPosWidth = sprite.getPosition().x + 621 / N;
    int btnyPosHeight = sprite.getPosition().y + 621 / N;

    if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
        return true;
    }
    return false;
}

int main() // WinMain
{
    start:
    Graphic_settings_info graphic_settings;
    if (!graphic_settings.isExists()) {
        graphic_settings.set_default();
        graphic_settings.saveConfig();
    }
    else graphic_settings.loadConfig();

    Game_settings_info game_settings;
    if (!game_settings.isExists()) {
        game_settings.set_default();
        game_settings.saveConfig();
    }
    else game_settings.loadConfig();

    Top_scores_info top_scores;
    top_scores.setHash(game_settings.getHash());

    if (!top_scores.isExists()) {
        top_scores.set_default();
        top_scores.saveConfig();
    }
    else top_scores.loadConfig();


    // Settings
    int N = game_settings.field_size;

    Field field_class(N);

    field_class.setColors(game_settings.color_count);

    sf::ContextSettings csettings;
    csettings.antialiasingLevel = 10;

    sf::RenderWindow window(sf::VideoMode(925, 690), "Lines 98 Game", sf::Style::Close | sf::Style::Titlebar, csettings);

    window.setVerticalSyncEnabled(graphic_settings.vsync);
    window.setFramerateLimit(graphic_settings.max_fps);

    float fps = graphic_settings.max_fps;
    sf::Clock loop_timer;

    sf::Font main_font;
    main_font.loadFromFile("res\\arial.ttf"); // add log

    sf::Font logo_font;
    logo_font.loadFromFile("res\\BebasNeue.ttf"); // add log

    sf::Font menu_font;
    menu_font.loadFromFile("res\\microsoftsansserif.ttf"); // menu font

    // add log
#pragma region Textures 
    sf::Texture background_texture;
    background_texture.loadFromFile(graphic_settings.background);

    sf::Texture cell_normal_texture;
    cell_normal_texture.loadFromFile("res\\cell.png");

    sf::Texture cell_activated_texture;
    cell_activated_texture.loadFromFile("res\\cell_activated.png");

    sf::Texture skip_button_texture;
    skip_button_texture.loadFromFile("res\\skip_button.png");

    sf::Texture skip_button_activated_texture;
    skip_button_activated_texture.loadFromFile("res\\skip_button_activated.png");

    sf::Texture skip_button_pressed_texture;
    skip_button_pressed_texture.loadFromFile("res\\skip_button_pressed.png");

    sf::Texture undo_button_texture;
    undo_button_texture.loadFromFile("res\\undo_button.png");

    sf::Texture undo_button_activated_texture;
    undo_button_activated_texture.loadFromFile("res\\undo_button_activated.png");

    sf::Texture undo_button_pressed_texture;
    undo_button_pressed_texture.loadFromFile("res\\undo_button_pressed.png");

    sf::Texture new_game_button_texture;
    new_game_button_texture.loadFromFile("res\\new_game_button.png");

    sf::Texture new_game_button_activated_texture;
    new_game_button_activated_texture.loadFromFile("res\\new_game_button_activated.png");

    sf::Texture new_game_button_pressed_texture;
    new_game_button_pressed_texture.loadFromFile("res\\new_game_button_pressed.png");

    ball_aqua.loadFromFile(graphic_settings.balls + "\\aqua.png");

    ball_blue.loadFromFile(graphic_settings.balls + "\\blue.png");

    ball_green.loadFromFile(graphic_settings.balls + "\\green.png");

    ball_pink.loadFromFile(graphic_settings.balls + "\\pink.png");

    ball_red.loadFromFile(graphic_settings.balls + "\\red.png");

    ball_violet.loadFromFile(graphic_settings.balls + "\\violet.png");

    ball_yellow.loadFromFile(graphic_settings.balls + "\\yellow.png");

    ball_multi.loadFromFile(graphic_settings.bombs + "\\multicolor.png");

    ball_v_h_aqua.loadFromFile(graphic_settings.bombs + "\\LinesBomb\\aqua.png");

    ball_v_h_blue.loadFromFile(graphic_settings.bombs + "\\LinesBomb\\blue.png");

    ball_v_h_green.loadFromFile(graphic_settings.bombs + "\\LinesBomb\\green.png");

    ball_v_h_pink.loadFromFile(graphic_settings.bombs + "\\LinesBomb\\pink.png");

    ball_v_h_red.loadFromFile(graphic_settings.bombs + "\\LinesBomb\\red.png");

    ball_v_h_violet.loadFromFile(graphic_settings.bombs + "\\LinesBomb\\violet.png");

    ball_v_h_yellow.loadFromFile(graphic_settings.bombs + "\\LinesBomb\\yellow.png");

    ball_zone_aqua.loadFromFile(graphic_settings.bombs + "\\TntBomb\\aqua.png");

    ball_zone_blue.loadFromFile(graphic_settings.bombs + "\\TntBomb\\blue.png");

    ball_zone_green.loadFromFile(graphic_settings.bombs + "\\TntBomb\\green.png");

    ball_zone_pink.loadFromFile(graphic_settings.bombs + "\\TntBomb\\pink.png");

    ball_zone_red.loadFromFile(graphic_settings.bombs + "\\TntBomb\\red.png");

    ball_zone_violet.loadFromFile(graphic_settings.bombs + "\\TntBomb\\violet.png");

    ball_zone_yellow.loadFromFile(graphic_settings.bombs + "\\TntBomb\\yellow.png");

    sf::Texture empty_texture;
    empty_texture.loadFromFile("res\\empty.png");

    sf::Texture game_mode_button_texture;
    game_mode_button_texture.loadFromFile("res\\game_mode_button.png");

    sf::Texture game_mode_button_activated_texture;
    game_mode_button_activated_texture.loadFromFile("res\\game_mode_button_activated.png");

    sf::Texture graphic_button_texture;
    graphic_button_texture.loadFromFile("res\\graphic_button.png");

    sf::Texture graphic_button_activated_texture;
    graphic_button_activated_texture.loadFromFile("res\\graphic_button_activated.png");

    sf::Texture top_button_texture;
    top_button_texture.loadFromFile("res\\top_button.png");

    sf::Texture top_button_activated_texture;
    top_button_activated_texture.loadFromFile("res\\top_button_activated.png");

    sf::Texture menu_background_texture;
    menu_background_texture.loadFromFile("res\\menu_background.png");
#pragma endregion

#pragma region Background
    sf::Sprite background_sprite;
    background_sprite.setTexture(background_texture);
    background_sprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
    background_sprite.setPosition(0, 0);
#pragma endregion

#pragma region Menu
    sf::RectangleShape menu_background;
    menu_background.setTexture(&menu_background_texture);
    menu_background.setPosition(0, 0);
    menu_background.setSize(sf::Vector2f(window.getSize().x, 24));

    std::vector<Button> menu_buttons;

    Button game_mode_button({ 1, 1 }, game_mode_button_texture, game_mode_button_activated_texture, game_mode_button_activated_texture);
    game_mode_button.setFont(main_font);
    game_mode_button.setPosition({ 7, 3 });
    game_mode_button.setTexture(game_mode_button_texture);
    menu_buttons.push_back(game_mode_button);

    Button graphic_button({ 1, 1 }, graphic_button_texture, graphic_button_activated_texture, graphic_button_activated_texture);
    graphic_button.setFont(main_font);
    graphic_button.setPosition({ 135, 3 });
    graphic_button.setTexture(graphic_button_texture);
    menu_buttons.push_back(graphic_button);

    Button top_button({ 1, 1 }, top_button_texture, top_button_activated_texture, top_button_activated_texture);
    top_button.setFont(main_font);
    top_button.setPosition({ 239, 3 });
    top_button.setTexture(top_button_texture);
    menu_buttons.push_back(top_button);
#pragma endregion

#pragma region Labels
    std::vector<sf::Text> labels;

    // Logo label
    sf::Text logo_label;
    logo_label.setFont(logo_font);
    logo_label.setCharacterSize(48);
    logo_label.setFillColor(sf::Color::White);
    logo_label.setStyle(sf::Text::Bold);
    logo_label.setString("LINES 98");
    logo_label.setPosition(713, 25 + menu_background.getSize().y);
    labels.push_back(logo_label);

    // Score label
    sf::Text score_label;
    score_label.setFont(main_font);
    score_label.setCharacterSize(24);
    score_label.setFillColor(sf::Color::White);
    score_label.setStyle(sf::Text::Regular);
    score_label.setString("Score: 0");
    score_label.setPosition(802 - 16 * score_label.getString().getSize() / 2, 85 + menu_background.getSize().y);
    labels.push_back(score_label);

    // Next balls label
    sf::Text next_balls_label;
    next_balls_label.setFont(main_font);
    next_balls_label.setCharacterSize(18);
    next_balls_label.setFillColor(sf::Color(170, 170, 170));
    next_balls_label.setStyle(sf::Text::Bold);
    next_balls_label.setString("Next balls:");
    next_balls_label.setPosition(653, 215 + menu_background.getSize().y);
    labels.push_back(next_balls_label);
#pragma endregion

#pragma region Buttons
    std::vector<Button> buttons;

    Button next_button({ 0.65, 0.65 }, skip_button_texture, skip_button_activated_texture, skip_button_pressed_texture);
    next_button.setFont(main_font);
    next_button.setPosition({ 653, 150 + menu_background.getSize().y });
    next_button.setTexture(skip_button_texture);
    buttons.push_back(next_button);

    Button undo_button({ 0.65, 0.65 }, undo_button_texture, undo_button_activated_texture, undo_button_pressed_texture);
    undo_button.setFont(main_font);
    undo_button.setPosition({ 769, 150 + menu_background.getSize().y });
    undo_button.setTexture(undo_button_texture);
    buttons.push_back(undo_button);

    Button new_game_button({ 0.85, 0.85 }, new_game_button_texture, new_game_button_activated_texture, new_game_button_pressed_texture);
    new_game_button.setFont(main_font);
    new_game_button.setPosition({ 653, 320 + menu_background.getSize().y });
    new_game_button.setTexture(new_game_button_texture);
    buttons.push_back(new_game_button);
#pragma endregion

#pragma region Field
    std::vector<std::vector<sf::Sprite>> field_balls(N, std::vector<sf::Sprite>(N));
    std::vector<std::vector<sf::Sprite>> field(N, std::vector<sf::Sprite>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x_coord = 20 + j * (621 / N);
            int y_coord = 25 + i * (621 / N) + menu_background.getSize().y;

            sf::Sprite cell_sprite;
            cell_sprite.setTexture(cell_normal_texture);
            cell_sprite.setScale(sf::Vector2f(9.0 / (double)N, 9.0 / (double)N));
            cell_sprite.setPosition(x_coord, y_coord);

            field[i][j] = cell_sprite;

            sf::Sprite cell_ball_sprite;
            cell_ball_sprite.setScale(sf::Vector2f(0, 0));
            cell_ball_sprite.setPosition(x_coord + 7.0 * 9.0 / (double)N, y_coord + 6.0 * 9.0 / (double)N);

            field_balls[i][j] = cell_ball_sprite;
        }
    }
#pragma endregion

#pragma region NextBalls
    std::vector<sf::Sprite> nextBalls(5);
    std::vector<sf::Sprite> balls_next_sprite(5);
    for (int i = 0; i < 5; i++) {
        int x_coord = 653 + i * 50;
        int y_coord = 250 + menu_background.getSize().y;

        sf::Sprite cell_sprite;
        cell_sprite.setTexture(cell_normal_texture);
        cell_sprite.setScale(sf::Vector2f(55.0 / 91.0, 55.0 / 91.0));
        cell_sprite.setPosition(x_coord, y_coord);

        nextBalls[i] = cell_sprite;

        sf::Sprite ball_cell_sprite;
        ball_cell_sprite.setScale(sf::Vector2f(55.0 / 91.0, 55.0 / 91.0));
        ball_cell_sprite.setPosition(x_coord + 7.0 * 55.0 / 91.0, y_coord + 6.0 * 55.0 / 91.0);

        balls_next_sprite[i] = ball_cell_sprite;
    }
#pragma endregion

    auto new_balls = field_class.generate_next_balls(game_settings.new_balls_count); // TODO: change count
    for (auto ball : new_balls) {
        SetBalls(field_balls, field, field_class, ball, N, graphic_settings.spawn);
    }

    std::queue<Ball> queue_balls;

    new_balls = field_class.generate_next_balls(game_settings.new_balls_count);
    int num = 0;
    for (auto ball : new_balls) {
        SetNext(queue_balls, balls_next_sprite, ball, num);
        num++;
    }

    int currentTurnState = 0;

    int selected_ball = -1;
    int score = 0;

    Field prev_field_class = field_class;
    std::vector<std::vector<sf::Sprite>> prev_field_balls = field_balls;
    std::vector<sf::Sprite> prev_balls_next_sprite;
    std::queue<Ball> prev_queue_balls;
    int prev_score = 0;
    int prev_used = 0;

    bool isFirstTurn = true;

    std::chrono::system_clock::time_point p1;

    int balls_in_queue = 0;
    long long bitSet = 0;

    while (window.isOpen())
    {
        sf::Event event;
        bool isHand = false;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                if (score > 0) {
                    p1 = std::chrono::system_clock::now();
                    top_scores.scores.push_back(std::make_pair(score, std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count()));
                    if (top_scores.scores[0].first < score) top_scores.successful_attemps++;
                    top_scores.total_attemps++;
                    top_scores.saveConfig();
                }
                window.close();
                exit(0);
                break;
            case sf::Event::MouseMoved:
#pragma region ButtonsColor
                for (int i = 0; i < buttons.size(); i++) {
                    buttons[i].autoSetTexture(window);
                    isHand = isHand || buttons[i].isMouseOver(window);
                }
                for (int i = 0; i < menu_buttons.size(); i++) {
                    menu_buttons[i].autoSetTexture(window);
                }
                if (isHand) {
                    sf::Cursor cursor;
                    if (cursor.loadFromSystem(sf::Cursor::Hand))
                        window.setMouseCursor(cursor);
                }
                else {
                    sf::Cursor cursor;
                    if (cursor.loadFromSystem(sf::Cursor::Arrow))
                        window.setMouseCursor(cursor);
                }
#pragma endregion
#pragma region CellsColor
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                        if (isMouseOver(window, field[i][j], i, j, N, menu_background.getSize().y))
                            field[i][j].setTexture(cell_activated_texture);
                        else field[i][j].setTexture(cell_normal_texture);
                    }
                }
#pragma endregion

                break;
            case sf::Event::MouseButtonPressed:
                if (currentTurnState == 1) break;
#pragma region ButtonsEvents
                for (int i = 0; i < buttons.size(); i++) {
                    if (buttons[i].isMouseOver(window))
                        buttons[i].getPressed(true);
                }

                for (int i = 0; i < menu_buttons.size(); i++) {
                    if (menu_buttons[i].isMouseOver(window))
                        menu_buttons[i].getPressed(true);
                }

                if (buttons[0].isMouseOver(window)) { // skipBtn
                    currentTurnState = 2;
                }
                if (buttons[1].isMouseOver(window)) { // undoBtn
                    if (isFirstTurn) break;
                    score = prev_score;
                    Animation::updateScore(score, labels[1]);
                    balls_next_sprite = prev_balls_next_sprite;
                    field_class = prev_field_class;
                    field_balls = prev_field_balls;
                    selected_ball = -1;

                    while (!queue_balls.empty())
                        queue_balls.pop();

                    int num = 0;
                    while (!prev_queue_balls.empty()) {
                        auto first = prev_queue_balls.front();
                        prev_queue_balls.pop();

                        auto new_ball = field_class.generate_next_balls(1, first.color)[0];

                        SetNext(queue_balls, balls_next_sprite, new_ball, num);
                        num++;
                    }

                    std::thread t(Animation::stopSelectedAnimation, std::ref(field_balls), &prev_used, N, menu_background.getSize().y, graphic_settings.jump);
                    t.detach();
                    isFirstTurn = true;
                }
                if (buttons[2].isMouseOver(window)) { // NewGame
                    if (score > 0) {
                        p1 = std::chrono::system_clock::now();
                        top_scores.scores.push_back(std::make_pair(score, std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count()));
                        if (top_scores.scores[0].first < score) top_scores.successful_attemps++;
                        top_scores.total_attemps++;
                        top_scores.saveConfig();
                    }

                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < N; j++) {
                            int x_coord = 20 + j * (621 / N);
                            int y_coord = 25 + i * (621 / N) + menu_background.getSize().y;

                            field_balls[i][j].setScale(sf::Vector2f(0, 0));
                            field_balls[i][j].setPosition(x_coord + 7.0 * 9.0 / (double)N, y_coord + 6.0 * 9.0 / (double)N);
                            field_class.set_cell(0, j, i, 0);
                        }
                    }
                    selected_ball = -1;
                    score = 0;
                    Animation::updateScore(score, labels[1]);
                    currentTurnState = 2;
                }
                if (menu_buttons[1].isMouseOver(window)) {
                    GraphicSettings::start();
                    graphic_settings.loadConfig();
                    goto start;
                }

                if (menu_buttons[2].isMouseOver(window)) {
                    TopScores::start();
                }

                if (menu_buttons[0].isMouseOver(window)) {
                    GameSettings::start();
                    game_settings.loadConfig();
                    goto start;
                }
#pragma endregion
#pragma region BallsSelection
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                        if (isMouseOver(window, field[i][j], i, j, N, menu_background.getSize().y)) {
                            if (selected_ball == i * N + j) {
                                std::thread t(Animation::stopSelectedAnimation, std::ref(field_balls), &selected_ball, N, menu_background.getSize().y, graphic_settings.jump);
                                t.detach();
                            }
                            else if (selected_ball == -1 && field_class.get_cell(j, i) != 0) {
                                selected_ball = i * N + j;
                                std::thread t(Animation::startSelectedAnimation, std::ref(field_balls), &selected_ball, menu_background.getSize().y, N, graphic_settings.jump);
                                t.detach();
                            }
                            else if (selected_ball != -1 && field_class.get_cell(j, i) == 0) {
                                if (isFirstTurn)
                                    isFirstTurn = false;
                                prev_score = score;
                                prev_balls_next_sprite = balls_next_sprite;
                                prev_queue_balls = queue_balls;
                                prev_field_balls = field_balls;
                                prev_field_class = field_class;
                                prev_used = selected_ball;
                                auto path = field_class.get_path(selected_ball, i * N + j);
                                if (path.size() == 0) continue;
                                std::thread t(Animation::startAnimateMovement, std::ref(score), std::ref(labels[1]), std::ref(field_balls), &selected_ball, menu_background.getSize().y, N, path, std::ref(field_class), field_balls[selected_ball / N][selected_ball % N].getPosition(), &currentTurnState, std::ref(field), graphic_settings.jump, graphic_settings.move, graphic_settings.explosion);
                                t.detach();
                            }
                        }
                    }
                }
#pragma endregion

                break;
            case sf::Event::MouseButtonReleased:
#pragma region ButtonsEvents
                for (int i = 0; i < buttons.size(); i++) {
                    buttons[i].getPressed(false);
                }
                for (int i = 0; i < menu_buttons.size(); i++) {
                    menu_buttons[i].getPressed(false);
                }
#pragma endregion
                break;
            }

        }

        window.clear(); // TODO: ��������� ����� �/��� ����

        window.draw(background_sprite);

        window.draw(menu_background);

        // Field
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                window.draw(field[i][j]);
            }
        }

        // Balls
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                window.draw(field_balls[i][j]);
            }
        }

        // Labels
        for (auto label : labels) {
            window.draw(label);
        }

        for (auto button : buttons)
            button.drawTo(window);

        for (auto button : menu_buttons)
            button.drawTo(window);

        // NextBalls
        for (int i = 0; i < 5; i++) {
            window.draw(nextBalls[i]);
        }

        for (int i = 0; i < 5; i++) {
            window.draw(balls_next_sprite[i]);
        }

        if (currentTurnState == 2) {
            vector<Ball> tmp_balls;
            while (!queue_balls.empty()) {
                auto ball = queue_balls.front();
                queue_balls.pop();

                if (field_class.get_cell(ball.x, ball.y) != 0)
                    ball = field_class.generate_next_balls(1, ball.color)[0];

                SetBalls(field_balls, field, field_class, ball, N, graphic_settings.spawn);
                tmp_balls.push_back(ball);
            }

            std::reverse(tmp_balls.begin(), tmp_balls.end());
            int _i = 0;
            for (auto ball : tmp_balls) {
                std::thread t(Animation::spawnBallDeletionCheck, std::ref(score), std::ref(labels[1]), std::ref(field_balls), N, ball.y * N + ball.x, std::ref(field_class), std::ref(bitSet), _i, std::ref(field), graphic_settings.explosion, graphic_settings.spawn * 6);
                t.detach();
                _i++;
            }

            int free_count = field_class.get_free_count();
            new_balls = field_class.generate_next_balls(min(game_settings.new_balls_count, free_count)); // count
            int num = 0;
            for (auto ball : new_balls) {
                SetNext(queue_balls, balls_next_sprite, ball, num);
                num++;
            }
            for (int i = num; i < 3; i++) {
                balls_next_sprite[i].setTexture(empty_texture);
            }
            currentTurnState = 0;
        }

        int tmp_add_score = 0;
        if (field_class.isLoose()) {
            if (Animation::isAnyLines(field_class, N)) {
                int free_count = field_class.get_free_count();
                new_balls = field_class.generate_next_balls(min(game_settings.new_balls_count, free_count)); // count
                int num = 0;
                for (auto ball : new_balls) {
                    SetNext(queue_balls, balls_next_sprite, ball, num);
                    num++;
                }
                for (int i = num; i < 3; i++) {
                    balls_next_sprite[i].setTexture(empty_texture);
                }
                currentTurnState = 0;
            }
            else {
                if (score > 0) {
                    p1 = std::chrono::system_clock::now();
                    top_scores.scores.push_back(std::make_pair(score, std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count()));
                    if (top_scores.scores[0].first < score) top_scores.successful_attemps++;
                    top_scores.total_attemps++;
                    top_scores.saveConfig();
                }

                int msgboxID = MessageBox(NULL, "The current result will be saved to the best results table on this PC. \nDo you want to start a new con?", "The game is over", MB_YESNO);
                switch (msgboxID) {
                case IDYES:
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < N; j++) {
                            int x_coord = 20 + j * (621 / N);
                            int y_coord = 25 + i * (621 / N) + menu_background.getSize().y;

                            field_balls[i][j].setScale(sf::Vector2f(0, 0));
                            field_balls[i][j].setPosition(x_coord + 7.0 * 9.0 / (double)N, y_coord + 6.0 * 9.0 / (double)N);
                            field_class.set_cell(0, j, i, 0);
                        }
                    }
                    score = 0;
                    Animation::updateScore(score, labels[1]);

                    new_balls = field_class.generate_next_balls(game_settings.new_balls_count); // TODO: change count
                    for (auto ball : new_balls) {
                        SetBalls(field_balls, field, field_class, ball, N, graphic_settings.spawn);
                    }

                    isFirstTurn = true;
                    currentTurnState = 2;
                    break;
                case IDNO:
                    exit(0);
                    break;
                }
            }
        }

        Animation::updateScore(score, labels[1]);

        window.display();

        sf::Int32 frame_duration = loop_timer.getElapsedTime().asMilliseconds();
        sf::Int32 time_to_sleep = int(1000.f / fps) - frame_duration;
        if (time_to_sleep > 0) {
            sf::sleep(sf::milliseconds(time_to_sleep));
        }
        loop_timer.restart();
    }

    return 0;
}