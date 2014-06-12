#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <windows.h>
#include <conio.h>
#include <sstream>

sf::Sprite field[9],quit_sprite;
int delay[6];

void setShutdown(int currentTime)
{
    std::string command;
    command = "shutdown /s /t ";
    std::stringstream ss;
    ss << currentTime;
    command += ss.str();
    const char* temp;
    temp = command.c_str();
    system(temp);
}

int checkEvent(sf::Event &event, sf::Mouse &mouse, sf::RenderWindow &window)
{
    if(event.type==sf::Event::Closed)
        window.close();
    for(int i=0;i<7;i++)
    {
        if(mouse.getPosition(window).x>150+(i%3)*135
        &&mouse.getPosition(window).x<150+(i%3)*135+field[i].getGlobalBounds().width
        &&mouse.getPosition(window).y>150+(i/3)*112
        &&mouse.getPosition(window).y<150+(i/3)*112+field[i].getGlobalBounds().height)
        {
            field[i].setColor(sf::Color::Green);
            if(event.type==sf::Event::MouseButtonPressed)
            {
                setShutdown(delay[i]);
            }

        }
        else
            field[i].setColor(sf::Color::White);
    }
    if(mouse.getPosition(window).x>field[7].getPosition().x
    &&mouse.getPosition(window).x<field[7].getPosition().x+field[6].getGlobalBounds().width
    &&mouse.getPosition(window).y>field[7].getPosition().y
    &&mouse.getPosition(window).y<field[7].getPosition().y+field[6].getGlobalBounds().height)
    {
        field[7].setColor(sf::Color::Green);
        if(event.type==sf::Event::MouseButtonPressed)
        {
            system("shutdown /a");
        }
    }
    else
        field[7].setColor(sf::Color::White);
    if(mouse.getPosition(window).x>quit_sprite.getPosition().x
    &&mouse.getPosition(window).x<quit_sprite.getPosition().x+quit_sprite.getGlobalBounds().width
    &&mouse.getPosition(window).y>quit_sprite.getPosition().y
    &&mouse.getPosition(window).y<quit_sprite.getPosition().y+quit_sprite.getGlobalBounds().height)
    {
        quit_sprite.setColor(sf::Color::Green);
        if(event.type==sf::Event::MouseButtonPressed)
        {
            window.close();
        }
    }
    else
        quit_sprite.setColor(sf::Color::White);
}


int main()
{
    std::string sdown[7];
    delay[0] = 1800;
    delay[1] = 2400;
    delay[2] = 3000;
    delay[3] = 3600;
    delay[4] = 7200;
    delay[5] = 14400;
    delay[6] = 36000;

    sf::RenderWindow window(sf::VideoMode(800,600), "Shutdown");
    sf::Texture shutdown_texture;
    if(!shutdown_texture.loadFromFile("blok.png"))
       return -1;
    sf::Sprite field[9],quit_sprite;
    sf::Font czcionka;
    if(!czcionka.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
        return -2;
    sf::Text s[8],q;
    s[0].setString("30min");
    s[1].setString("40min");
    s[2].setString("50min");
    s[3].setString("1 h");
    s[4].setString("2 h");
    s[5].setString("4 h");
    s[6].setString("10 h");
    s[7].setString("Wylacz");
    q.setString("Wyjdz");

    for (int i=0;i<9;i++)
    {
        field[i].setTexture(shutdown_texture);
        field[i].setPosition(150+(i%3)*140 , 150+(i/3)*117);
        if(i==8)
            break;
        s[i].setFont(czcionka);
        s[i].setPosition( field[i].getPosition().x+ (field[i].getGlobalBounds().width - s[i].getGlobalBounds().width)/2 ,
                         field[i].getPosition().y+ (field[i].getGlobalBounds().height - s[i].getGlobalBounds().height)/2 );
        s[i].setColor(sf::Color::Blue);
    }
    quit_sprite.setTexture(shutdown_texture);
    quit_sprite.setPosition(600,450);
    q.setColor(sf::Color::Blue);
    q.setFont(czcionka);
    q.setPosition(quit_sprite.getPosition().x+(quit_sprite.getGlobalBounds().width-q.getGlobalBounds().width)/2 ,
                  quit_sprite.getPosition().y+(quit_sprite.getGlobalBounds().height-q.getGlobalBounds().height)/2);

    sf::Event event;
    sf::Mouse mouse;
    window.setFramerateLimit(60);
    while(window.isOpen())
    {
        window.clear();
        while(window.pollEvent(event))
        {
            checkEvent(event, mouse, window);
        }
        for(int i=0;i<9;i++)
        {
            window.draw(field[i]);
            window.draw(s[i]);
        }
        window.draw(quit_sprite);
        window.draw(q);
        window.display();

    }
    return 0;
}
