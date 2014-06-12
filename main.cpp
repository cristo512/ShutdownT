#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <windows.h>
#include <conio.h>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdlib>

std::string custom;
sf::Text custom_text;
sf::Sprite field[9],quit_sprite;
sf::RectangleShape prostokat(sf::Vector2f(405,60));
sf::RectangleShape unitFrame[3];
int delay[8];
char timeUnit='s';

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

void setShutdown(int currentTime, char Unit)
{
    int power;
    if(Unit=='s')
        power=0;
    else if(Unit=='m')
        power=1;
    else if(Unit=='h')
        power=2;
    std::string command;
    command = "shutdown /s /t ";
    std::stringstream ss;
    ss << currentTime*pow(60,power);
    command += ss.str();
    const char* temp;
    temp = command.c_str();
    system(temp);
}

void checkEvent(sf::Event &event, sf::RenderWindow &window, sf::Mouse &mouse)
{
    if(event.type==sf::Event::Closed)
        window.close();
    for(int i=0;i<9;i++)
    {
        if(i==7)
            continue;
        if(mouse.getPosition(window).x>field[i].getPosition().x
    &&mouse.getPosition(window).x<field[i].getPosition().x+field[i].getGlobalBounds().width
    &&mouse.getPosition(window).y>field[i].getPosition().y
    &&mouse.getPosition(window).y<field[i].getPosition().y+field[i].getGlobalBounds().height)
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
    for(int i=0;i<3;i++)
    {
        if(mouse.getPosition(window).x>unitFrame[i].getPosition().x
        &&mouse.getPosition(window).x<unitFrame[i].getPosition().x+unitFrame[i].getGlobalBounds().width
        &&mouse.getPosition(window).y>unitFrame[i].getPosition().y
        &&mouse.getPosition(window).y<unitFrame[i].getPosition().y+unitFrame[i].getGlobalBounds().height)
            {
                if(event.type==sf::Event::MouseButtonPressed)
                {
                    if(i==0)
                        timeUnit='s';
                    if(i==1)
                        timeUnit='m';
                    if(i==2)
                        timeUnit='h';
                }

            }
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

    if(mouse.getPosition(window).x>prostokat.getPosition().x
    &&mouse.getPosition(window).x<prostokat.getPosition().x+prostokat.getGlobalBounds().width
    &&mouse.getPosition(window).y>prostokat.getPosition().y
    &&mouse.getPosition(window).y<prostokat.getPosition().y+prostokat.getGlobalBounds().height)
    {
        prostokat.setFillColor(sf::Color::Green);
        if(event.type==sf::Event::MouseButtonPressed)
        {
            int custom_time=atoi(custom.c_str());
            setShutdown(custom_time, timeUnit);
        }
    }
    else
        prostokat.setFillColor(sf::Color::White);

    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code >= sf::Keyboard::Num0 && event.key.code <= sf::Keyboard::Num9 && custom.length()<7)
        {
            std::stringstream ss;
            ss << 'A' + char(event.key.code) - 91;
            custom += ss.str();
            custom_text.setString(custom);
            custom_text.setPosition( prostokat.getPosition().x+ (prostokat.getGlobalBounds().width - custom_text.getGlobalBounds().width)/2 ,
                                    prostokat.getPosition().y+ (prostokat.getGlobalBounds().height - custom_text.getGlobalBounds().height)/2 );
        }

        else if(event.key.code == sf::Keyboard::BackSpace && !custom.empty())
        {
            custom.erase(custom.end()-1);
            custom_text.setString(custom);
            custom_text.setPosition( prostokat.getPosition().x+ (prostokat.getGlobalBounds().width - custom_text.getGlobalBounds().width)/2 ,
                                    prostokat.getPosition().y+ (prostokat.getGlobalBounds().height - custom_text.getGlobalBounds().height)/2 );
        }

        else if(event.key.code == sf::Keyboard::Escape)
        {
            window.close();
        }
        else if(event.key.code == sf::Keyboard::Return)
        {
            int custom_time=atoi(custom.c_str());
            setShutdown(custom_time, timeUnit);
        }
        else if(event.key.code == sf::Keyboard::S)
        {
            timeUnit='s';
        }
        else if(event.key.code == sf::Keyboard::M)
        {
            timeUnit='m';
        }
        else if(event.key.code == sf::Keyboard::H)
        {
            timeUnit='h';
        }
    }
}


int main()
{
    delay[0] = 1800;
    delay[1] = 2400;
    delay[2] = 3000;
    delay[3] = 3600;
    delay[4] = 7200;
    delay[5] = 14400;
    delay[6] = 18000;
    delay[8] = 36000;

    sf::RenderWindow window(sf::VideoMode(800,600), "Shutdown");
    sf::Texture shutdown_texture;
    if(!shutdown_texture.loadFromFile("blok.png"))
       return -1;
    sf::Font czcionka;
    if(!czcionka.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
        return -2;
    sf::Text s[9],q, unit_text[3];
    s[0].setString("30 min");
    s[1].setString("40 min");
    s[2].setString("50 min");
    s[3].setString("1 h");
    s[4].setString("2 h");
    s[5].setString("4 h");
    s[6].setString("5 h");
    s[7].setString(L"Wyłącz");
    s[8].setString("10 h");
    q.setString(L"Wyjdź");
    unit_text[0].setString("S");
    unit_text[1].setString("M");
    unit_text[2].setString("H");

    custom_text.setFont(czcionka);
    custom_text.setColor(sf::Color::Blue);
    custom_text.setScale(1.4,1.4);

    prostokat.setPosition(150, 30);
    for (int i=0;i<9;i++)
    {
        field[i].setTexture(shutdown_texture);
        field[i].setPosition(150+(i%3)*140 , 200+(i/3)*117);
        s[i].setFont(czcionka);
        s[i].setPosition( field[i].getPosition().x+ (field[i].getGlobalBounds().width - s[i].getGlobalBounds().width)/2 ,
                        field[i].getPosition().y+ (field[i].getGlobalBounds().height - s[i].getGlobalBounds().height)/2 );
        s[i].setColor(sf::Color::Blue);
    }
    for(int i=0;i<3;i++)
    {
        unitFrame[i].setFillColor(sf::Color::White);
        unitFrame[i].setSize(sf::Vector2f(40,50));
        unitFrame[i].setPosition( (prostokat.getPosition().x + (prostokat.getGlobalBounds().width - 165)/2) + (i%3)*55, 110);
        unit_text[i].setFont(czcionka);
        unit_text[i].setColor(sf::Color::Blue);
        unit_text[i].setPosition( unitFrame[i].getPosition().x+ (unitFrame[i].getGlobalBounds().width - unit_text[i].getGlobalBounds().width)/2 ,
                        unitFrame[i].getPosition().y+ (unitFrame[i].getGlobalBounds().height - unit_text[i].getGlobalBounds().height)/2 );


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
            checkEvent(event, window, mouse);
        }
        if(timeUnit=='s')
            unitFrame[0].setFillColor(sf::Color::Green);
        else
            unitFrame[0].setFillColor(sf::Color::White);
        if(timeUnit=='m')
            unitFrame[1].setFillColor(sf::Color::Green);
        else
            unitFrame[1].setFillColor(sf::Color::White);
        if(timeUnit=='h')
            unitFrame[2].setFillColor(sf::Color::Green);
        else
            unitFrame[2].setFillColor(sf::Color::White);

        window.draw(prostokat);
        for(int i=0;i<9;i++)
        {
            window.draw(field[i]);
            window.draw(s[i]);
        }
        for(int i=0;i<3;i++)
        {
            window.draw(unitFrame[i]);
            window.draw(unit_text[i]);
        }
        window.draw(custom_text);
        window.draw(quit_sprite);
        window.draw(q);
        window.display();

    }
    return 0;
}
