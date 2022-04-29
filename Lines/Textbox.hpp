#include<SFML/Graphics.hpp>
#ifndef SDX_TEXTBOX
#define SDX_TEXTBOX

namespace sdx {
    class TextBox {
    private:
        sf::RectangleShape outerRect;
        sf::RectangleShape innerRect;
        sf::RectangleShape blinker;
        sf::String getPinp;
        sf::String txtInp;
        sf::Clock clock;
        sf::Time time;
        //sf::Cursor cursor;
        unsigned int textSize;
        unsigned int focusChar;
        float charWidth;
        float thickness;
        float posX;
        float posY;
        float height;
        float width;
        bool focus;
    public:
        class Text {
        private:
            sf::Font font;
            sf::Text text;
        public:
            Text(sf::String, float, float); //constructior, first parameter is text string, second is x position, third y position.
            sf::Text get(); //returns the drawable sf::Text class
            void setText(sf::String); //update the text
            void setPosition(float, float); //update text position
            void setSize(unsigned int); //update text size
        };
        TextBox();  //constructor
        TextBox(float, float, float, float, float); //first two parameter for size, second two for position and the last one for thickness.
        void draw(sf::RenderWindow&);  //it'll go to the main event loop, after event handler, it draws in the window.
        void handleEvent(sf::Event&); //handles text input and press enter evernt. place it inside pollEvent loop inside the main event loop.
        sf::String getCurrentText();  //get what is written in the text box right now
        sf::String getInput();  //updates last text after pressing enter.
        void setText(sf::String);
    public:
        void setSize(float, float);  //update box size first parameter for x, second for y.
        void setPosition(float, float); //update (x,y) position of top-left corner
        void setBorder(float);  //update border thickness.
    private:
        Text inpText;
    };
}
#endif