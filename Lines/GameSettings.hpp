#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <SFML/Graphics.hpp>
#include "Textbox.hpp"
#include "Button.hpp"
#include <windows.h>
#include <sstream>
#include <shlobj.h>
#include "Game_settings.hpp"

class GameSettings {
public:
    static void start() {
        Game_settings_info settings;
        if (!settings.isExists()) {
            settings.set_default();
            settings.saveConfig();
        }
        else settings.loadConfig();

        sf::RenderWindow window(sf::VideoMode(441, 232), "Game Mode settings", sf::Style::Close | sf::Style::Titlebar);

        sf::Font main_font;
        main_font.loadFromFile("res\\arial.ttf"); // add log

#pragma region Textures
        sf::Texture background_texture;
        background_texture.loadFromFile("res\\game_settings\\background.png");

        sf::Texture checkbox_default;
        checkbox_default.loadFromFile("res\\game_settings\\checkbox_default.png");

        sf::Texture checkbox_clicked;
        checkbox_clicked.loadFromFile("res\\game_settings\\checkbox_clicked.png");

        sf::Texture checkbox_activated;
        checkbox_activated.loadFromFile("res\\game_settings\\checkbox_activated.png");

        sf::Texture checkbox_checked_default;
        checkbox_checked_default.loadFromFile("res\\game_settings\\checkbox_checked_default.png");

        sf::Texture checkbox_checked_clicked;
        checkbox_checked_clicked.loadFromFile("res\\game_settings\\checkbox_checked_clicked.png");

        sf::Texture checkbox_checked_activated;
        checkbox_checked_activated.loadFromFile("res\\game_settings\\checkbox_checked_activated.png");

        sf::Texture save_button_texture;
        save_button_texture.loadFromFile("res\\game_settings\\button_save.png");

        sf::Texture save_button_activated;
        save_button_activated.loadFromFile("res\\game_settings\\button_save_activated.png");

        sf::Texture save_button_clicked;
        save_button_clicked.loadFromFile("res\\game_settings\\button_save_clicked.png");

        sf::Texture restore_button_texture;
        restore_button_texture.loadFromFile("res\\game_settings\\button_restore.png");

        sf::Texture restore_button_activated;
        restore_button_activated.loadFromFile("res\\game_settings\\button_restore_activated.png");

        sf::Texture restore_button_clicked;
        restore_button_clicked.loadFromFile("res\\game_settings\\button_restore_clicked.png");
#pragma endregion

#pragma region Background
        sf::Sprite background_sprite;
        background_sprite.setTexture(background_texture);
        background_sprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
        background_sprite.setPosition(0, 0);
#pragma endregion

#pragma region TextBoxes
        std::vector<sdx::TextBox*> textBoxes;

        sdx::TextBox fieldTextBox;
        fieldTextBox.setPosition(153, 37);
        fieldTextBox.setSize(50, 18);
        fieldTextBox.setBorder(1);
        fieldTextBox.setText(std::to_string(settings.field_size));
        textBoxes.push_back(&fieldTextBox);

        sdx::TextBox colorTextBox;
        colorTextBox.setPosition(153, 60);
        colorTextBox.setSize(50, 18);
        colorTextBox.setBorder(1);
        colorTextBox.setText(std::to_string(settings.color_count));
        textBoxes.push_back(&colorTextBox);

        sdx::TextBox ballsTextBox;
        ballsTextBox.setPosition(153, 83);
        ballsTextBox.setSize(50, 18);
        ballsTextBox.setBorder(1);
        ballsTextBox.setText(to_string(settings.new_balls_count));
        textBoxes.push_back(&ballsTextBox);

        sdx::TextBox multicolorTextBox;
        multicolorTextBox.setPosition(325, 37);
        multicolorTextBox.setSize(70, 18);
        multicolorTextBox.setBorder(1);
        multicolorTextBox.setText(std::to_string(settings.prop_multi));
        textBoxes.push_back(&multicolorTextBox);

        sdx::TextBox zoneTextBox;
        zoneTextBox.setPosition(325, 60);
        zoneTextBox.setSize(70, 18);
        zoneTextBox.setBorder(1);
        zoneTextBox.setText(std::to_string(settings.prop_zone));
        textBoxes.push_back(&zoneTextBox);

        sdx::TextBox v_h_TextBox;
        v_h_TextBox.setPosition(325, 83);
        v_h_TextBox.setSize(70, 18);
        v_h_TextBox.setBorder(1);
        v_h_TextBox.setText(to_string(settings.prop_v_h));
        textBoxes.push_back(&v_h_TextBox);
#pragma endregion

#pragma region Buttons
        std::vector<Button> buttons;

        Button save_button({ 1, 1 }, save_button_texture, save_button_activated, save_button_clicked);
        save_button.setFont(main_font);
        save_button.setPosition({ 216, 167 });
        save_button.setTexture(save_button_texture);
        buttons.push_back(save_button);

        Button restore_button({ 1, 1 }, restore_button_texture, restore_button_activated, restore_button_clicked);
        restore_button.setFont(main_font);
        restore_button.setPosition({ 216, 196 });
        restore_button.setTexture(restore_button_texture);
        buttons.push_back(restore_button);
#pragma endregion

        sf::Text hash_label;
        hash_label.setFont(main_font);
        hash_label.setCharacterSize(13);
        hash_label.setFillColor(sf::Color::Black);
        hash_label.setStyle(sf::Text::Regular);
        hash_label.setString("Code:" + std::to_string(settings.getHash()));
        hash_label.setPosition(216, 145);

        sf::Sprite checkbox_multicolor;
        if (!settings.multicolor)
            checkbox_multicolor.setTexture(checkbox_default);
        else checkbox_multicolor.setTexture(checkbox_checked_default);
        checkbox_multicolor.setScale({ 1, 1 });
        checkbox_multicolor.setPosition(22, 145);

        bool checkbox_multicolor_isChecked = settings.multicolor;
        bool checkbox_multicolor_isCheckboxClicked = false;

        sf::Sprite checkbox_zone;
        if (!settings.zone_bomb)
            checkbox_zone.setTexture(checkbox_default);
        else checkbox_zone.setTexture(checkbox_checked_default);
        checkbox_zone.setScale({ 1, 1 });
        checkbox_zone.setPosition(22, 168);

        bool checkbox_zone_isChecked = settings.zone_bomb;
        bool checkbox_zone_isCheckboxClicked = false;

        sf::Sprite checkbox_h_v;
        if (!settings.v_h_bomb)
            checkbox_h_v.setTexture(checkbox_default);
        else checkbox_h_v.setTexture(checkbox_checked_default);
        checkbox_h_v.setScale({ 1, 1 });
        checkbox_h_v.setPosition(22, 191);

        bool checkbox_h_v_isChecked = settings.v_h_bomb;
        bool checkbox_h_v_isCheckboxClicked = false;

        while (true) {
            sf::Event event;
            bool isHand = false;

            while (window.pollEvent(event))
            {
                for (auto tb : textBoxes)
                    tb->handleEvent(event);

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
                    if (!checkbox_multicolor_isCheckboxClicked) {
                        if (isMouseOver(window, checkbox_multicolor, checkbox_multicolor.getPosition().x, checkbox_multicolor.getPosition().y, 13, 13)) {
                            if (checkbox_multicolor_isChecked)
                                checkbox_multicolor.setTexture(checkbox_checked_activated);
                            else checkbox_multicolor.setTexture(checkbox_activated);
                        }
                        else {
                            if (checkbox_multicolor_isChecked)
                                checkbox_multicolor.setTexture(checkbox_checked_default);
                            else checkbox_multicolor.setTexture(checkbox_default);
                        }
                    }

                    if (!checkbox_zone_isCheckboxClicked) {
                        if (isMouseOver(window, checkbox_zone, checkbox_zone.getPosition().x, checkbox_zone.getPosition().y, 13, 13)) {
                            if (checkbox_zone_isChecked)
                                checkbox_zone.setTexture(checkbox_checked_activated);
                            else checkbox_zone.setTexture(checkbox_activated);
                        }
                        else {
                            if (checkbox_zone_isChecked)
                                checkbox_zone.setTexture(checkbox_checked_default);
                            else checkbox_zone.setTexture(checkbox_default);
                        }
                    }

                    if (!checkbox_h_v_isCheckboxClicked) {
                        if (isMouseOver(window, checkbox_h_v, checkbox_h_v.getPosition().x, checkbox_h_v.getPosition().y, 13, 13)) {
                            if (checkbox_h_v_isChecked)
                                checkbox_h_v.setTexture(checkbox_checked_activated);
                            else checkbox_h_v.setTexture(checkbox_activated);
                        }
                        else {
                            if (checkbox_h_v_isChecked)
                                checkbox_h_v.setTexture(checkbox_checked_default);
                            else checkbox_h_v.setTexture(checkbox_default);
                        }
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    for (int i = 0; i < buttons.size(); i++) {
                        if (buttons[i].isMouseOver(window))
                            buttons[i].getPressed(true);
                    }

                    if (isMouseOver(window, checkbox_multicolor, checkbox_multicolor.getPosition().x, checkbox_multicolor.getPosition().y, 13, 13)) {
                        if (checkbox_multicolor_isChecked)
                            checkbox_multicolor.setTexture(checkbox_checked_clicked);
                        else checkbox_multicolor.setTexture(checkbox_clicked);
                        checkbox_multicolor_isCheckboxClicked = true;
                    }
                    if (isMouseOver(window, checkbox_zone, checkbox_zone.getPosition().x, checkbox_zone.getPosition().y, 13, 13)) {
                        if (checkbox_zone_isChecked)
                            checkbox_zone.setTexture(checkbox_checked_clicked);
                        else checkbox_zone.setTexture(checkbox_clicked);
                        checkbox_zone_isCheckboxClicked = true;
                    }
                    if (isMouseOver(window, checkbox_h_v, checkbox_h_v.getPosition().x, checkbox_h_v.getPosition().y, 13, 13)) {
                        if (checkbox_h_v_isChecked)
                            checkbox_h_v.setTexture(checkbox_checked_clicked);
                        else checkbox_h_v.setTexture(checkbox_clicked);
                        checkbox_h_v_isCheckboxClicked = true;
                    }

                    if (buttons[0].isMouseOver(window)) {
                        if (!is_number(fieldTextBox.getCurrentText())) break;
                        int new_size = atoi(fieldTextBox.getCurrentText().toAnsiString().c_str());
                        if (new_size < 9 || new_size > 16) break;
                        
                        if (!is_number(colorTextBox.getCurrentText())) break;
                        int new_color = atoi(colorTextBox.getCurrentText().toAnsiString().c_str());
                        if (new_color < 2 || new_color > 7) break;

                        if (!is_number(ballsTextBox.getCurrentText())) break;
                        int new_balls = atoi(ballsTextBox.getCurrentText().toAnsiString().c_str());
                        if (new_balls < 0 || new_balls > 5) break;

                        if (!is_number(multicolorTextBox.getCurrentText())) break;
                        int new_multicolor = atoi(multicolorTextBox.getCurrentText().toAnsiString().c_str());
                        if (new_multicolor < 0 || new_multicolor > 100) break;

                        if (!is_number(zoneTextBox.getCurrentText())) break;
                        int new_zone = atoi(zoneTextBox.getCurrentText().toAnsiString().c_str());
                        if (new_zone < 0 || new_zone > 100) break;

                        if (!is_number(v_h_TextBox.getCurrentText())) break;
                        int new_v_h = atoi(v_h_TextBox.getCurrentText().toAnsiString().c_str());
                        if (new_v_h < 0 || new_v_h > 100) break;

                        if (new_v_h + new_zone + new_multicolor > 100) break;

                        settings.field_size = new_size;
                        settings.color_count = new_color;
                        settings.new_balls_count = new_balls;
                        settings.multicolor = checkbox_multicolor_isChecked;
                        settings.zone_bomb = checkbox_zone_isChecked;
                        settings.v_h_bomb = checkbox_h_v_isChecked;
                        settings.prop_multi = new_multicolor;
                        settings.prop_zone = new_zone;
                        settings.prop_v_h = new_v_h;

                        settings.saveConfig();
                        hash_label.setString("Code:" + std::to_string(settings.getHash()));
                    }
                    
                    if (buttons[1].isMouseOver(window)) {
                        settings.set_default();
                        settings.saveConfig();

                        hash_label.setString("Code:" + std::to_string(settings.getHash()));
                        fieldTextBox.setText(std::to_string(settings.field_size));
                        colorTextBox.setText(std::to_string(settings.color_count));
                        ballsTextBox.setText(to_string(settings.new_balls_count));
                        multicolorTextBox.setText(std::to_string(settings.prop_multi));
                        zoneTextBox.setText(std::to_string(settings.prop_zone));
                        v_h_TextBox.setText(to_string(settings.v_h_bomb));

                        if (!settings.multicolor)
                            checkbox_multicolor.setTexture(checkbox_default);
                        else checkbox_multicolor.setTexture(checkbox_checked_default);

                        checkbox_multicolor_isChecked = settings.multicolor;

                        if (!settings.zone_bomb)
                            checkbox_zone.setTexture(checkbox_default);
                        else checkbox_zone.setTexture(checkbox_checked_default);

                        checkbox_zone_isChecked = settings.zone_bomb;

                        if (!settings.v_h_bomb)
                            checkbox_h_v.setTexture(checkbox_default);
                        else checkbox_h_v.setTexture(checkbox_checked_default);

                        checkbox_h_v_isChecked = settings.v_h_bomb;
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    for (int i = 0; i < buttons.size(); i++) {
                        buttons[i].getPressed(false);
                    }

                    if (checkbox_multicolor_isCheckboxClicked) {
                        checkbox_multicolor_isChecked = !checkbox_multicolor_isChecked;
                        if (checkbox_multicolor_isChecked)
                            checkbox_multicolor.setTexture(checkbox_checked_default);
                        else checkbox_multicolor.setTexture(checkbox_default);
                        checkbox_multicolor_isCheckboxClicked = false;
                    }
                    if (checkbox_zone_isCheckboxClicked) {
                        checkbox_zone_isChecked = !checkbox_zone_isChecked;
                        if (checkbox_zone_isChecked)
                            checkbox_zone.setTexture(checkbox_checked_default);
                        else checkbox_zone.setTexture(checkbox_default);
                        checkbox_zone_isCheckboxClicked = false;
                    }
                    if (checkbox_h_v_isCheckboxClicked) {
                        checkbox_h_v_isChecked = !checkbox_h_v_isChecked;
                        if (checkbox_h_v_isChecked)
                            checkbox_h_v.setTexture(checkbox_checked_default);
                        else checkbox_h_v.setTexture(checkbox_default);
                        checkbox_h_v_isCheckboxClicked = false;
                    }
                    break;
                }
            }

            window.clear();

            window.draw(background_sprite);

            for (auto tb : textBoxes)
                tb->draw(window);

            for (auto button : buttons)
                button.drawTo(window);

            window.draw(checkbox_multicolor);
            window.draw(checkbox_zone);
            window.draw(checkbox_h_v);
            window.draw(hash_label);

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

    static int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
    {

        if (uMsg == BFFM_INITIALIZED)
        {
            std::string tmp = (const char*)lpData;
            SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);
        }

        return 0;
    }

    static std::string BrowseFolder(std::string saved_path)
    {
        TCHAR path[MAX_PATH];

        const char* path_param = saved_path.c_str();

        BROWSEINFO bi = { 0 };
        bi.lpszTitle = ("Browse for folder...");
        bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
        bi.lpfn = BrowseCallbackProc;
        bi.lParam = (LPARAM)path_param;

        LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

        if (pidl != 0)
        {
            //get the name of the folder and put it in path
            SHGetPathFromIDList(pidl, path);

            //free memory used
            IMalloc* imalloc = 0;
            if (SUCCEEDED(SHGetMalloc(&imalloc)))
            {
                imalloc->Free(pidl);
                imalloc->Release();
            }

            return path;
        }

        return "";
    }

    static std::string BrowseFile(std::string saved_path) {
        char filename[MAX_PATH];

        OPENFILENAME ofn;
        ZeroMemory(&filename, sizeof(filename));
        ZeroMemory(&ofn, sizeof(ofn));
        ofn.lStructSize = sizeof(ofn);
        ofn.hwndOwner = NULL;
        ofn.lpstrFilter = "Image Files\0*.png;*.jpg;*jpeg\0Any File\0*.*\0";
        ofn.lpstrFile = filename;
        ofn.nMaxFile = MAX_PATH;
        ofn.lpstrTitle = "Browse for file...";
        ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
        ofn.lpstrFile = (LPSTR)saved_path.c_str();

        if (GetOpenFileName(&ofn))
            return filename;
        return "";
    }

    static bool is_number(const std::string& s)
    {
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }
};