#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public:
	Button(sf::Vector2f factors, sf::Texture bgTexture, sf::Texture activatedTexture, sf::Texture pressedTexture) {
		button.setTexture(bgTexture);
		button.setScale(factors);

		btnWidth = bgTexture.getSize().x * factors.x;
		btnHeight = bgTexture.getSize().y * factors.y;

		// text.setString(btnText);
		// text.setCharacterSize(charSize);
		// text.setFillColor(textColor);

		this->normalTexture = bgTexture;
		this->activatedTexture = activatedTexture;
		this->pressedTexture = pressedTexture;
	}

	void setFont(sf::Font& fonts) {
		text.setFont(fonts);
	}

	void setTexture(sf::Texture& texture) {
		button.setTexture(texture);
	}

	void getPressed(bool value) {
		if (this->pressed != value) {
			if (value) setTexture(pressedTexture);
			else setTexture(normalTexture);
			this->pressed = value;
		}
	}

	void autoSetTexture(sf::RenderWindow& window) {
		if (this->pressed) return;
		if (this->isMouseOver(window)) {
			this->setTexture(this->activatedTexture);
		}
		else {
			this->setTexture(this->normalTexture);
		}
	}

	void setTextColor(sf::Color color) {
		text.setFillColor(color);
	}

	void setPosition(sf::Vector2f point) {
		button.setPosition(point);

		// float xPos = (point.x + btnWidth / 2) - (text.getLocalBounds().width / 2);
		// float yPos = (point.y + btnHeight / 2.2) - (text.getLocalBounds().height / 2);
		// text.setPosition(xPos, yPos);
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(button);
		// window.draw(text);
	}

	bool isMouseOver(sf::RenderWindow& window) {
		int mouseX = sf::Mouse::getPosition(window).x;
		int mouseY = sf::Mouse::getPosition(window).y;

		int btnPosX = button.getPosition().x;
		int btnPosY = button.getPosition().y;

		int btnxPosWidth = button.getPosition().x + btnWidth;
		int btnyPosHeight = button.getPosition().y + btnHeight;

		if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
			return true;
		}
		return false;
	}
private:
	sf::Sprite button;
	sf::Text text;

	int btnWidth;
	int btnHeight;

	bool pressed = false;

	sf::Texture normalTexture, activatedTexture, pressedTexture;
};

class ButtonWithColor {
public:
	ButtonWithColor(std::string btnText, int charSize, sf::Color textColor, sf::Vector2f factors, sf::Color bgColor, 
			sf::Color activatedColor, sf::Color borderActivatedColor, sf::Color pressedColor, sf::Color borderPressedColor) {
		button.setSize(factors);
		button.setFillColor(bgColor);

		border_rect.setSize(sf::Vector2f(factors.x + 2, factors.y + 2));

		btnWidth = factors.x;
		btnHeight = factors.y;

		text.setString(btnText);
		text.setCharacterSize(charSize);
		text.setFillColor(textColor);

		this->normalColor = bgColor;
		this->activatedColor = activatedColor;
		this->pressedColor = pressedColor;
		this->borderActivatedColor = borderActivatedColor;
		this->borderPressedColor = borderPressedColor;
	}

	void setFont(sf::Font& fonts) {
		text.setFont(fonts);
	}

	void setBackColor(sf::Color color) {
		button.setFillColor(color);
	}

	void setBorderColor(sf::Color color) {
		border_rect.setFillColor(color);
	}

	void getPressed(bool value) {
		if (this->pressed != value) {
			if (value) {
				setBackColor(pressedColor);
				setBorderColor(borderPressedColor);
				needBorder = true;
			}
			else {
				setBackColor(normalColor);
				needBorder = false;
				setBorderColor(sf::Color::Transparent);
			}
			this->pressed = value;
		}
	}

	void autoSetColor(sf::RenderWindow& window) {
		if (this->pressed) return;
		if (this->isMouseOver(window)) {
			this->setBackColor(this->activatedColor);
			setBorderColor(borderActivatedColor);
			needBorder = true;
		}
		else {
			this->setBackColor(this->normalColor);
			setBorderColor(sf::Color::Transparent);
			needBorder = false;
		}
	}

	void setTextColor(sf::Color color) {
		text.setFillColor(color);
	}

	void setPosition(sf::Vector2f point) {
		button.setPosition(point);
		border_rect.setPosition(sf::Vector2f(point.x - 1, point.y - 1));

		int xPos = (point.x + btnWidth / 2) - (text.getLocalBounds().width / 2);
		int yPos = (point.y + btnHeight / 2.2) - (text.getLocalBounds().height / 2);
		text.setPosition(xPos, yPos);
	}

	void drawTo(sf::RenderWindow& window) {
		if (needBorder) window.draw(border_rect);
		window.draw(button);
		window.draw(text);
	}

	bool isMouseOver(sf::RenderWindow& window) {
		int mouseX = sf::Mouse::getPosition(window).x;
		int mouseY = sf::Mouse::getPosition(window).y;

		int btnPosX = button.getPosition().x;
		int btnPosY = button.getPosition().y;

		int btnxPosWidth = button.getPosition().x + btnWidth;
		int btnyPosHeight = button.getPosition().y + btnHeight;

		if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
			return true;
		}
		return false;
	}
private:
	sf::RectangleShape button, border_rect;
	sf::Text text;

	int btnWidth;
	int btnHeight;

	bool pressed = false;
	bool needBorder = false;

	sf::Color normalColor, activatedColor, pressedColor;
	sf::Color borderActivatedColor, borderPressedColor;
};