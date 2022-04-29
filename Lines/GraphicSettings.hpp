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
#include "Graphic_settings.hpp"

class GraphicSettings {
public:
    static void start() {
        Graphic_settings_info settings;
        if (!settings.isExists()) {
            settings.set_default();
            settings.saveConfig();
        }
        else settings.loadConfig();

        sf::RenderWindow window(sf::VideoMode(429, 245), "Graphic settings", sf::Style::Close | sf::Style::Titlebar);

        sf::Font main_font;
        main_font.loadFromFile("res\\arial.ttf"); // add log

#pragma region Textures
        sf::Texture background_texture;
        background_texture.loadFromFile("res\\graphic_settings\\background.png");

        sf::Texture checkbox_default;
        checkbox_default.loadFromFile("res\\graphic_settings\\checkbox_default.png");

        sf::Texture checkbox_clicked;
        checkbox_clicked.loadFromFile("res\\graphic_settings\\checkbox_clicked.png");

        sf::Texture checkbox_checked_default;
        checkbox_checked_default.loadFromFile("res\\graphic_settings\\checkbox_checked_default.png");

        sf::Texture checkbox_checked_clicked;
        checkbox_checked_clicked.loadFromFile("res\\graphic_settings\\checkbox_checked_clicked.png");

        sf::Texture checkbox_checked_activated;
        checkbox_checked_activated.loadFromFile("res\\graphic_settings\\checkbox_checked_activated.png");

        sf::Texture checkbox_activated;
        checkbox_activated.loadFromFile("res\\graphic_settings\\checkbox_activated.png");

        sf::Texture select_button_texture;
        select_button_texture.loadFromFile("res\\graphic_settings\\select_button.png");

        sf::Texture select_button_activated;
        select_button_activated.loadFromFile("res\\graphic_settings\\select_button_activated.png");

        sf::Texture select_button_clicked;
        select_button_clicked.loadFromFile("res\\graphic_settings\\select_button_clicked.png");

        sf::Texture save_button_texture;
        save_button_texture.loadFromFile("res\\graphic_settings\\save_button.png");

        sf::Texture save_button_activated;
        save_button_activated.loadFromFile("res\\graphic_settings\\save_button_activated.png");

        sf::Texture save_button_clicked;
        save_button_clicked.loadFromFile("res\\graphic_settings\\save_button_clicked.png");

        sf::Texture restore_button_texture;
        restore_button_texture.loadFromFile("res\\graphic_settings\\restore_button.png");

        sf::Texture restore_button_activated;
        restore_button_activated.loadFromFile("res\\graphic_settings\\restore_button_activated.png");

        sf::Texture restore_button_clicked;
        restore_button_clicked.loadFromFile("res\\graphic_settings\\restore_button_clicked.png");

        sf::Texture undo_button_texture;
        undo_button_texture.loadFromFile("res\\graphic_settings\\undo_button.png");

        sf::Texture undo_button_activated;
        undo_button_activated.loadFromFile("res\\graphic_settings\\undo_button_activated.png");

        sf::Texture undo_button_clicked;
        undo_button_clicked.loadFromFile("res\\graphic_settings\\undo_button_clicked.png");
#pragma endregion

#pragma region Background
        sf::Sprite background_sprite;
        background_sprite.setTexture(background_texture);
        background_sprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
        background_sprite.setPosition(0, 0);
#pragma endregion
        
#pragma region TextBoxes
        std::vector<sdx::TextBox*> textBoxes;

        sdx::TextBox jumpTextBox;
        jumpTextBox.setPosition(100, 37);
        jumpTextBox.setSize(75, 18);
        jumpTextBox.setBorder(1);
        jumpTextBox.setText(to_string(settings.jump));
        textBoxes.push_back(&jumpTextBox);

        sdx::TextBox explosionTextBox;
        explosionTextBox.setPosition(100, 60);
        explosionTextBox.setSize(75, 18);
        explosionTextBox.setBorder(1);
        explosionTextBox.setText(to_string(settings.explosion));
        textBoxes.push_back(&explosionTextBox);

        sdx::TextBox spawnTextBox;
        spawnTextBox.setPosition(100, 83);
        spawnTextBox.setSize(75, 18);
        spawnTextBox.setBorder(1);
        spawnTextBox.setText(to_string(settings.spawn));
        textBoxes.push_back(&spawnTextBox);

        sdx::TextBox moveTextBox;
        moveTextBox.setPosition(100, 106);
        moveTextBox.setSize(75, 18);
        moveTextBox.setBorder(1);
        moveTextBox.setText(to_string(settings.move));
        textBoxes.push_back(&moveTextBox);

        sdx::TextBox fpsTextBox;
        fpsTextBox.setPosition(100, 166);
        fpsTextBox.setSize(100, 18);
        fpsTextBox.setBorder(1);
        fpsTextBox.setText(to_string(settings.max_fps));
        textBoxes.push_back(&fpsTextBox);
#pragma endregion

#pragma region Buttons
        std::vector<Button> buttons;

        Button select_button({ 1, 1 }, select_button_texture, select_button_activated, select_button_clicked);
        select_button.setFont(main_font);
        select_button.setPosition({ 315, 37 });
        select_button.setTexture(select_button_texture);
        buttons.push_back(select_button);

        Button select_button2({ 1, 1 }, select_button_texture, select_button_activated, select_button_clicked);
        select_button2.setFont(main_font);
        select_button2.setPosition({ 315, 60 });
        select_button2.setTexture(select_button_texture);
        buttons.push_back(select_button2);

        Button select_button3({ 1, 1 }, select_button_texture, select_button_activated, select_button_clicked);
        select_button3.setFont(main_font);
        select_button3.setPosition({ 315, 83 });
        select_button3.setTexture(select_button_texture);
        buttons.push_back(select_button3);

        Button save_button({ 1, 1 }, save_button_texture, save_button_activated, save_button_clicked);
        save_button.setFont(main_font);
        save_button.setPosition({ 218, 135 });
        save_button.setTexture(save_button_texture);
        buttons.push_back(save_button);

        Button restore_button({ 1, 1 }, restore_button_texture, restore_button_activated, restore_button_clicked);
        restore_button.setFont(main_font);
        restore_button.setPosition({ 218, 164 });
        restore_button.setTexture(restore_button_texture);
        buttons.push_back(restore_button);

        Button undo_button({ 1, 1 }, undo_button_texture, undo_button_activated, undo_button_clicked);
        undo_button.setFont(main_font);
        undo_button.setPosition({ 218, 193 });
        undo_button.setTexture(undo_button_texture);
        buttons.push_back(undo_button);
#pragma endregion

        sf::Sprite checkbox;
        if (!settings.vsync)
            checkbox.setTexture(checkbox_default);
        else checkbox.setTexture(checkbox_checked_default);
        checkbox.setScale({ 1, 1 });
        checkbox.setPosition(22, 192);

        bool isChecked = settings.vsync;
        bool isCheckboxClicked = false;

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
                    if (!isCheckboxClicked) {
                        if (isMouseOver(window, checkbox, checkbox.getPosition().x, checkbox.getPosition().y, 13, 13)) {
                            if (isChecked)
                                checkbox.setTexture(checkbox_checked_activated);
                            else checkbox.setTexture(checkbox_activated);
                        }
                        else {
                            if (isChecked)
                                checkbox.setTexture(checkbox_checked_default);
                            else checkbox.setTexture(checkbox_default);
                        }
                    }
                    break;
                case sf::Event::MouseButtonPressed:
                    for (int i = 0; i < buttons.size(); i++) {
                        if (buttons[i].isMouseOver(window))
                            buttons[i].getPressed(true);
                    }

                    if (isMouseOver(window, checkbox, checkbox.getPosition().x, checkbox.getPosition().y, 13, 13)) {
                        if (isChecked)
                            checkbox.setTexture(checkbox_checked_clicked);
                        else checkbox.setTexture(checkbox_clicked);
                        isCheckboxClicked = true;
                    }

                    if (buttons[0].isMouseOver(window)) {
                        auto path = BrowseFolder(settings.balls);
                        if (path != "")
                            settings.balls = path;
                    }
                    if (buttons[1].isMouseOver(window)) {
                        auto path = BrowseFolder(settings.bombs);
                        if (path != "")
                            settings.bombs = path;
                    }
                    if (buttons[2].isMouseOver(window)) {
                        auto path = BrowseFile(settings.background);
                        if (path != "")
                            settings.background = path;
                    }

                    if (buttons[3].isMouseOver(window)) {
                        if (is_number(textBoxes[0]->getCurrentText()) && is_number(textBoxes[1]->getCurrentText()) && is_number(textBoxes[2]->getCurrentText())
                            && is_number(textBoxes[3]->getCurrentText()) && is_number(textBoxes[4]->getCurrentText())) {
                            settings.jump = atoi(textBoxes[0]->getCurrentText().toAnsiString().c_str());
                            settings.explosion = atoi(textBoxes[1]->getCurrentText().toAnsiString().c_str());
                            settings.spawn = atoi(textBoxes[2]->getCurrentText().toAnsiString().c_str());
                            settings.move = atoi(textBoxes[3]->getCurrentText().toAnsiString().c_str());

                            settings.max_fps = atoi(textBoxes[4]->getCurrentText().toAnsiString().c_str());
                            settings.vsync = isChecked;
                            settings.saveConfig();
                        }
                    }

                    if (buttons[4].isMouseOver(window)) {
                        settings.set_default();
                        settings.saveConfig();

                        jumpTextBox.setText(to_string(settings.jump));
                        explosionTextBox.setText(to_string(settings.explosion));
                        spawnTextBox.setText(to_string(settings.spawn));
                        moveTextBox.setText(to_string(settings.move));
                        fpsTextBox.setText(to_string(settings.max_fps));

                        isChecked = settings.vsync;
                        if (!settings.vsync)
                            checkbox.setTexture(checkbox_default);
                        else checkbox.setTexture(checkbox_checked_default);
                    }

                    if (buttons[5].isMouseOver(window)) {
                        settings.loadConfig();
                        jumpTextBox.setText(to_string(settings.jump));
                        explosionTextBox.setText(to_string(settings.explosion));
                        spawnTextBox.setText(to_string(settings.spawn));
                        moveTextBox.setText(to_string(settings.move));
                        fpsTextBox.setText(to_string(settings.max_fps));

                        isChecked = settings.vsync;
                        if (!settings.vsync)
                            checkbox.setTexture(checkbox_default);
                        else checkbox.setTexture(checkbox_checked_default);
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    for (int i = 0; i < buttons.size(); i++) {
                        buttons[i].getPressed(false);
                    }

                    if (isCheckboxClicked) {
                        isChecked = !isChecked;
                        if (isChecked)
                            checkbox.setTexture(checkbox_checked_default);
                        else checkbox.setTexture(checkbox_default);
                        isCheckboxClicked = false;
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

            window.draw(checkbox);

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