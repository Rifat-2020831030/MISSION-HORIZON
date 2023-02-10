#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <math.h>

using namespace sf;
using namespace std;

vector < pair<float, float> > bolet;
vector < pair<float, float> > eBullet;

class enemy
{

public:
    Sprite sprite;
    int HP, maxHP;

    enemy(Texture* texture)
    {
        this-> maxHP = 10;
        this->HP = this->maxHP;

        this->sprite.setTexture(*texture);

        this->sprite.setPosition(1000, rand() / (800 - this->sprite.getGlobalBounds().height));

    }
};

int main()
{
    srand(time(NULL));

    RenderWindow window(VideoMode(1100, 800), "MISSION HORIZON");   //making window
    window.setFramerateLimit(60);

    sf::Texture bulletTexture;                                      //Loading bullet
    bulletTexture.loadFromFile("image/bullet1.png");
    RectangleShape bullet(Vector2f(80.f, 20.f));
    bullet.setTexture(&bulletTexture);

    int loadTime = 21;

    Texture bgtexture;                                              //making background
    if (!bgtexture.loadFromFile("background.jpg"))
    {
        cout << "Failed to load background";
        exit(-1);
    }
    RectangleShape background(Vector2f(1100.f, 800.f));             //background 1
    background.setTexture(&bgtexture);
    background.setPosition(0.f, 0.f);

    Texture bg;                                                     //background 2
    bg.loadFromFile("image/bg2.jpg");
    RectangleShape bg2(Vector2f(1100.f, 800.f));
    bg2.setTexture(&bg);
    bg2.setPosition(1100.f , 0.f);

    
    Texture playerTexture;                                          //player loading
    if (!playerTexture.loadFromFile("image/player.jpg"))
    {
        cout << "Failed to load player";
    }
    RectangleShape player(Vector2f(100.f, 50.f));
    player.setTexture(&playerTexture);
    player.setPosition(0.f , 400.f);
    
    SoundBuffer shotBuffer;                                         //sound effect
    shotBuffer.loadFromFile("sound/laser.ogg");

    Sound shot;          
    shot.setBuffer(shotBuffer);

    Music bgmusic;                                                  //music effect
    if (!bgmusic.openFromFile("sound/space.wav"))
    {
        cout << "Failed to load music";
        exit(-1);
    }
    bgmusic.play();

    
    Texture enemyTex;                                               //Enemy loading section
    if (!enemyTex.loadFromFile("image/alien1.png"))
    {
        cout << "Failed to laod enemy1"; exit(-1);
    }
    /*
    RectangleShape alien(Vector2f(100.f, 135.f));
    alien.setTexture(&enemyTex);
    alien.setPosition(window.getSize().x, (player.getPosition().y)/400+3);
    alien.setScale(0.5f, 0.5f);

    RectangleShape ebullet(Vector2f(80.f, 20.f));
    ebullet.setTexture(&bulletTexture);

    */
    //enemy[0].push_back(make_pair(alien, eHP)); //loading first enemy in the vector        

    int enemyloadTime = 6;

    vector< enemy > alien1;


    while (window.isOpen())                                         //Game loop
    {
        Event event;

        while (window.pollEvent(event))                             //event loop
        {
            if(event.type == Event::Closed)
                window.close();

            if ( (event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Space))                 //Bullet pressed tracking
            {
                if (loadTime > 20)
                {
                    bolet.push_back(make_pair(player.getPosition().x + 100, player.getPosition().y + 25));
                    shot.play();
                    loadTime = 1;
                }
            }

        }

        if (!bolet.empty()) loadTime++;                                //bullet load time function

                                                                       //moving background effect
        background.move(-1.f, 0.f);
        bg2.move(-1.f, 0.f);
        
        if (background.getPosition().x == 0)
            bg2.setPosition(1100.f , 0.f);
        if(bg2.getPosition().x == 0)
            background.setPosition( 1100.f , 0.f);

        if (Keyboard::isKeyPressed(Keyboard::Key::A ))                //control setup
        {
            if(player.getPosition().x>0)
            player.move(-5.f, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::S ))
        {
            if(player.getPosition().y+ player.getSize().y < window.getSize().y)
            player.move(0, 5.0f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::D))
        {
            if(player.getPosition().x+player.getSize().x < window.getSize().x)
            player.move(5.f, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::W))
        {
            if(player.getPosition().y >0)
            player.move(0, -5.f);
        }               
                                                                                          //Enemy making factory
        if (enemyloadTime > 10)
        {
            alien1.push_back(&enemyTex);
            enemyloadTime = 0;
        }

        for (size_t i = 0; i < alien1.size(); i++)
        {
            if (alien1[i].sprite.getPosition().x > 1000)
                alien1[i].sprite.move(-1.f, 0.f);
        }
        enemyloadTime++;
        

       // if (enemyloadTime > 5) { eBullet.push_back(make_pair(alien.getPosition().x, alien.getPosition().y / 2)); enemyloadTime = 0; }
        
       

        window.clear();
        window.draw(background);
        window.draw(bg2);
        window.draw(player);
        
        /*
        if (!eBullet.empty() )                                                                //enemy bullet
        {
            for (size_t i = 0; i < eBullet.size(); i++)
            {
                ebullet.setPosition(eBullet[i].first, eBullet[i].second);
                ebullet.move(-1.f, 0.f);
                window.draw(ebullet);
            }
        }
        */

        if (!bolet.empty() )                                                                   //Bullet firing animation of player
        {
            for (size_t i = 0; i < bolet.size(); i++)
            {
                bolet[i].first += 2;     //position change per frame

                if(bolet[i].first < 1200)
                { 
                    bullet.setPosition(bolet[i].first, bolet[i].second);                         //bullet dynamic position changing
                    window.draw(bullet);
                }
                
            }
        }

       
        window.display();
    }

    return 0;
}
