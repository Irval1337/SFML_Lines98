#include "Textbox.hpp"

namespace sdx {
    TextBox::Text::Text(sf::String string, float x, float y) {
        font.loadFromFile("res\\arial.ttf");
        text.setFont(font);
        text.setString(string);
        text.setFillColor(sf::Color::Black);
        text.setCharacterSize(18);
        text.setPosition(sf::Vector2f(x, y));
        text.setLineSpacing(0);
        text.setOutlineThickness(0);
    }

    sf::Text TextBox::Text::get() { return text; }

    void TextBox::Text::setText(sf::String string) { text.setString(string); }

    void TextBox::Text::setPosition(float x, float y) { text.setPosition(sf::Vector2f(x, y)); }

    void TextBox::Text::setSize(unsigned int x) { text.setCharacterSize(x); }

    //Main TextBox methods start here
    TextBox::TextBox() : inpText("", 6, 5) {
        outerRect.setSize(sf::Vector2f(460, 32));
        innerRect.setSize(sf::Vector2f(456, 28));
        outerRect.setPosition(sf::Vector2f(0, 0));
        innerRect.setPosition(sf::Vector2f(2, 2));
        outerRect.setFillColor(sf::Color::Black);
        innerRect.setFillColor(sf::Color::White);

        blinker.setSize(sf::Vector2f(1, 26));
        blinker.setPosition(sf::Vector2f(4, 3));
        blinker.setFillColor(sf::Color::Black);

        time = sf::Time::Zero;
        textSize = 18;
        getPinp = "";
        txtInp = "";
        thickness = 2;
        posX = 0;
        posY = 0;
        height = 32;
        width = 460;
        focusChar = 0;
        focus = false;
        charWidth = 0;
    }
    TextBox::TextBox(float x1, float x2, float y1, float y2, float z) : inpText("", y1 + z + 2, y2 + z - 1) {
        outerRect.setSize(sf::Vector2f(x1, x2));
        innerRect.setSize(sf::Vector2f(x1 - 2 * z, x2 - 2 * z));
        outerRect.setPosition(sf::Vector2f(y1, y2));
        innerRect.setPosition(sf::Vector2f(y1 + z, y2 + z));
        outerRect.setFillColor(sf::Color::Black);
        innerRect.setFillColor(sf::Color::White);

        blinker.setSize(sf::Vector2f(1, x2 - 2 * z - 2));
        blinker.setPosition(sf::Vector2f(y1 + z + 2, y2 + z + 1));
        blinker.setFillColor(sf::Color::Black);

        time = sf::Time::Zero;
        textSize = (unsigned int)(x2 - 4 - 2 * z);
        getPinp = "";
        txtInp = "";
        thickness = z;
        posX = y1;
        posY = y2;
        height = x2;
        width = x1;
        focusChar = 0;
        focus = false;
        charWidth = 0;

        inpText.setSize(textSize);
    }

    void TextBox::setSize(float x, float y) {
        height = y;
        width = x;
        textSize = (unsigned int)(y - 4 - 2 * thickness);
        outerRect.setSize(sf::Vector2f(x, y));
        innerRect.setSize(sf::Vector2f(x - 2 * thickness, y - 2 * thickness));
        blinker.setSize(sf::Vector2f(1, y - 2 * thickness - 2));
        inpText.setSize(textSize);
        inpText.setPosition(posX + thickness + 2, posY + thickness - 1);
    }

    void TextBox::setPosition(float x, float y) {
        posX = x;
        posY = y;
        outerRect.setPosition(sf::Vector2f(x, y));
        innerRect.setPosition(sf::Vector2f(x + thickness, y + thickness));
        blinker.setPosition(sf::Vector2f(x + thickness + 2, y + thickness + 1));
        inpText.setPosition(x + thickness + 2, y + thickness - 1);
    }

    void TextBox::setBorder(float x) {
        thickness = x;
        textSize = (unsigned int)(height - 4 - 2 * x);
        innerRect.setSize(sf::Vector2f(width - 2 * x, height - 2 * x));
        inpText.setSize(textSize);
        setPosition(posX, posY);
    }

    sf::String TextBox::getCurrentText() { return getPinp; }

    sf::String TextBox::getInput() { return txtInp; }

    void TextBox::handleEvent(sf::Event& event) {
        if (event.type == sf::Event::TextEntered && focus) {
            if ((inpText.get().findCharacterPos(focusChar).x + 1.2 * textSize) < (width + posX) && 31 < int(event.text.unicode) && 256 > int(event.text.unicode)) {
                if (focusChar == getPinp.getSize()) getPinp += event.text.unicode;
                else {
                    getPinp = getPinp.substring(0, focusChar) + event.text.unicode + getPinp.substring(focusChar, getPinp.getSize() - focusChar);
                }
                focusChar++;
            }
        }
        if (event.type == sf::Event::KeyPressed && focus) {
            if (event.key.code == sf::Keyboard::BackSpace) {
                if (focusChar != 0) {
                    getPinp.erase(focusChar - 1, 1);
                    if (focusChar > 0) focusChar--;
                }
            }
            if (event.key.code == sf::Keyboard::Delete) {
                if (focusChar != getPinp.getSize()) {
                    getPinp.erase(focusChar);
                }
            }
            if (event.key.code == sf::Keyboard::Enter) {
                if (getPinp.getSize() > 0) txtInp = getPinp;
                focusChar = 0;
                getPinp.clear();
            }
            else if (event.key.code == sf::Keyboard::Left) {
                if (focusChar > 0) { focusChar--; }
            }
            else if (event.key.code == sf::Keyboard::Right) {
                if (focusChar < getPinp.getSize()) focusChar++;
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (getPinp.getSize() > 0) {
                    if (charWidth == 0) charWidth = inpText.get().findCharacterPos(1).x - inpText.get().findCharacterPos(0).x;
                    unsigned int temp = (unsigned int)((event.mouseButton.x - posX) / charWidth);
                    if (temp > getPinp.getSize()) focusChar = getPinp.getSize();
                    else focusChar = temp;
                }
                if (event.mouseButton.x > posX && event.mouseButton.x <posX + width && event.mouseButton.y>posY && event.mouseButton.y < posY + height) focus = true;
                else focus = false;
            }
        }
    }

    void TextBox::draw(sf::RenderWindow& window) {
        time += clock.restart();
        if (focus) {
            if (time.asSeconds() > 1) {
                time = sf::Time::Zero;
                blinker.setFillColor(sf::Color::Black);
            }
            else if (time.asSeconds() > 0.5) blinker.setFillColor(sf::Color::White);
        }
        else {
            blinker.setFillColor(sf::Color::White);
            if (time.asSeconds() > 300) time = sf::Time::Zero;
        }
        if (focusChar == 0) blinker.setPosition(posX + thickness + 2, posY + thickness + 1);
        else blinker.setPosition(sf::Vector2f(inpText.get().findCharacterPos(focusChar).x, posY + thickness + 1));
        inpText.setText(getPinp);
        window.draw(outerRect);
        window.draw(innerRect);
        window.draw(blinker);
        window.draw(inpText.get());
    }

    void TextBox::setText(sf::String str) {
        while (getPinp.getSize() != 0) {
            getPinp.erase(focusChar - 1, 1);
            if (focusChar > 0) focusChar--;
        }

        for (auto c : str) {
            if ((inpText.get().findCharacterPos(focusChar).x + 1.2 * textSize) < (width + posX) && 31 < int(c) && 256 > int(c)) {
                if (focusChar == getPinp.getSize()) getPinp += c;
                else {
                    getPinp = getPinp.substring(0, focusChar) + c + getPinp.substring(focusChar, getPinp.getSize() - focusChar);
                }
                focusChar++;
            }
        }
    }
}