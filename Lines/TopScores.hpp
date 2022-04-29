#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include <windows.h>
#include <sstream>
#include <shlobj.h>
#include <vector>
#include "Top_score_settings.hpp"
#include "Game_settings.hpp"

class TopScores {
public:
    static void start() {
        Game_settings_info game_settings;
        if (!game_settings.isExists()) {
            game_settings.set_default();
            game_settings.saveConfig();
        }
        else game_settings.loadConfig();

        Top_scores_info settings;
        settings.setHash(game_settings.getHash());
        if (!settings.isExists()) {
            settings.set_default();
            settings.saveConfig();
        }
        else settings.loadConfig();

        sf::RenderWindow window(sf::VideoMode(435, 231), "Top scores", sf::Style::Close | sf::Style::Titlebar);

        sf::Font main_font;
        main_font.loadFromFile("res\\arial.ttf"); // add log

        sf::Font sec_font;
        main_font.loadFromFile("res\\microsoftsansserif.ttf"); // add log

#pragma region Textures
        sf::Texture background_texture;
        background_texture.loadFromFile("res\\top_scores\\background.png");

        sf::Texture reset_button_texture;
        reset_button_texture.loadFromFile("res\\top_scores\\reset_button.png");

        sf::Texture reset_button_activated;
        reset_button_activated.loadFromFile("res\\top_scores\\reset_button_activated.png");

        sf::Texture reset_button_clicked;
        reset_button_clicked.loadFromFile("res\\top_scores\\reset_button_clicked.png");
#pragma endregion

#pragma region Background
        sf::Sprite background_sprite;
        background_sprite.setTexture(background_texture);
        background_sprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
        background_sprite.setPosition(0, 0);
#pragma endregion

#pragma region Labels
        std::vector<sf::Text> labels;

        sf::Text attemps_label;
        attemps_label.setFont(main_font);
        attemps_label.setCharacterSize(13);
        attemps_label.setFillColor(sf::Color::Black);
        attemps_label.setStyle(sf::Text::Regular);
        attemps_label.setString("Total attemps: " + std::to_string(settings.total_attemps));
        attemps_label.setPosition(234, 35);
        labels.push_back(attemps_label);

        sf::Text attemps_succ_label;
        attemps_succ_label.setFont(main_font);
        attemps_succ_label.setCharacterSize(13);
        attemps_succ_label.setFillColor(sf::Color::Black);
        attemps_succ_label.setStyle(sf::Text::Regular);
        attemps_succ_label.setString("Successful attempts: " + std::to_string(settings.successful_attemps));
        attemps_succ_label.setPosition(235, 58);
        labels.push_back(attemps_succ_label);
#pragma endregion

#pragma region Buttons
        std::vector<Button> buttons;

        Button reset_button({ 1, 1 }, reset_button_texture, reset_button_activated, reset_button_clicked);
        reset_button.setFont(main_font);
        reset_button.setPosition({ 235, 88 });
        reset_button.setTexture(reset_button_texture);
        buttons.push_back(reset_button);
#pragma endregion

#pragma region Scores
        std::vector<sf::Text> labels_score;

        int shift = 5;
        int count = 0;
        for (auto score : settings.scores) {
            if (count >= 13) break;
            time_t epch = score.second;
            std::string time = asctimes(gmtime(&epch));

            sf::Text label;
            label.setFont(main_font);
            label.setCharacterSize(13);
            label.setFillColor(sf::Color::Black);
            label.setStyle(sf::Text::Regular);
            label.setString(std::to_string(score.first) + " [" + time.substr(0, time.size() - 1) + "]");
            label.setPosition(17, 15 + shift);
            labels_score.push_back(label);
            shift += 15;
            count++;
        }
#pragma endregion


        while (true) {
            sf::Event event;
            bool isHand = false;

            while (window.pollEvent(event))
            {
                switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    return;
                
                case sf::Event::MouseMoved:
#pragma region ButtonsColor
                     for (int i = 0; i < buttons.size(); i++) {
                         buttons[i].autoSetTexture(window);
                         isHand = isHand || buttons[i].isMouseOver(window);
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
                     break;

                case sf::Event::MouseButtonPressed:
#pragma region ButtonsEvents
                    for (int i = 0; i < buttons.size(); i++) {
                        if (buttons[i].isMouseOver(window))
                            buttons[i].getPressed(true);
                    }

                    if (buttons[0].isMouseOver(window)) {
                        settings.set_default();
                        settings.saveConfig();

                        labels[0].setString("Total attemps: 0");
                        labels[1].setString("Successful attempts: 0");

                        labels_score.clear();
                    }
#pragma endregion
                    break;
                case sf::Event::MouseButtonReleased:
#pragma region ButtonsEvents
                    for (int i = 0; i < buttons.size(); i++) {
                        buttons[i].getPressed(false);
                    }
#pragma endregion
                    break;
                }
            }

            window.clear();

            window.draw(background_sprite);

            for (auto label : labels)
                window.draw(label);

            for (auto label : labels_score)
                window.draw(label);

            for (auto button : buttons)
                button.drawTo(window);

            window.display();
        }
    }
private:
    static bool isMouseOver(sf::RenderWindow& window, sf::Sprite& sprite, int x, int y, int width, int height) {
        int mouseX = sf::Mouse::getPosition(window).x;
        int mouseY = sf::Mouse::getPosition(window).y;

        int btnPosX = x;
        int btnPosY = y;

        int btnxPosWidth = sprite.getPosition().x + width;
        int btnyPosHeight = sprite.getPosition().y + height;

        if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
            return true;
        }
        return false;
    }    

    static char* asctimes(const struct tm* timeptr)
    {
        static const char wday_name[][4] = {
          "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
        };
        static const char mon_name[][4] = {
          "Jan", "Feb", "Mar", "Apr", "May", "Jun",
          "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
        };
        static char result[26];
        sprintf(result, "%.3s%3d %d\n",
            mon_name[timeptr->tm_mon],
            timeptr->tm_mday,
            1900 + timeptr->tm_year);
        return result;
    }
};