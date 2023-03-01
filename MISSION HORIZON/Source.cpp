#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include "Menu.h"

using namespace sf;
using namespace std;


int point = 0, max_score = 0;
bool p = false;
fstream file;

class enemy
{

public:
    Sprite sprite;
    int HP, maxHP;
    int eBulletLoad;

    enemy(Texture* texture)
    {
        this->maxHP = 3;
        this->HP = this->maxHP;
        this->eBulletLoad = 0;

        this->sprite.setTexture(*texture);
        this->sprite.setScale(0.5, 0.5);

        this->sprite.setPosition(1100, rand() % 800);

    }
};

class sat
{
public:
    Sprite sprite;
    int HP, maxHP;

    sat(Texture* texture)
    {
        this->maxHP = 3;
        this->HP = this->maxHP;

        this->sprite.setTexture(*texture);
        this->sprite.setScale(0.2, 0.2);
        this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 2, this->sprite.getGlobalBounds().height / 2);

        this->sprite.setPosition(1100, rand() % 800);
    }
};

class magazine
{
public:
    Sprite sprite;

    magazine(Texture* texture, Vector2f position)
    {
        this->sprite.setTexture(*texture);
        this->sprite.setScale(1.f, 0.5f);
        this->sprite.setPosition(position.x + 150.f, position.y + 50.f);
    }
};
class emagazine
{
public:
    Sprite sprite;

    emagazine(Texture* texture, Vector2f position)
    {
        this->sprite.setTexture(*texture);
        this->sprite.setScale(0.5f, 1.f);
        this->sprite.setPosition(position.x, position.y + 25.f);
    }
};

class mateor
{
public:
    Sprite sprite;
    IntRect shape;

    mateor(Texture* texture)
    {
        //(int)(1100 - this->sprite.getGlobalBounds().width)
        this->sprite.setTexture(*texture);
        this->sprite.setPosition(rand() % 1100, 0.f);
        this->sprite.setScale(0.5, 0.5);

    }
};

void pause(RenderWindow& window)
{
    Texture playbutton;
    playbutton.loadFromFile("image/play.png");

    Sprite button;
    button.setTexture(playbutton);
    button.setPosition(window.getSize().x - 70, 10);

    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Key::O)) {
            cout << " O pressed" << endl;
            p = false;
            return;
        }
        window.draw(button);
        window.display();
    }
}

void mainmenu(RenderWindow& window)
{
    Clock clock;
    Time time;

    RectangleShape loading(Vector2f(0, 10));                                          //loading section
    loading.setPosition(window.getSize().x / 2 - 200, window.getSize().y / 2 - 100);
    loading.setFillColor(Color::White);
    loading.setOutlineColor(Color::Black);

    Texture texture;                                                                   //loading background
    texture.loadFromFile("image/loading.jpg");
    RectangleShape bg(Vector2f(window.getSize().x, window.getSize().y));
    bg.setTexture(&texture);

    Font font;                                                                         //loading text
    font.loadFromFile("fonts/ModernWarfare.ttf");
    Text loadingTxt;
    loadingTxt.setFont(font);
    loadingTxt.setString("Loading...");
    loadingTxt.setCharacterSize(50);
    loadingTxt.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2 - 200);


    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        //time = clock.getElapsedTime().asSeconds;


        float temp = clock.getElapsedTime().asSeconds() * 40;

        if (temp >= 350) return;

        loading.setSize(Vector2f(temp, 10.f));

        window.clear();
        window.draw(bg);
        window.draw(loading);
        window.draw(loadingTxt);
        window.display();
    }
}

void help(RenderWindow& window)
{
    Texture t;
    t.loadFromFile("image/INSTRUCTIONS.png");

    Sprite bg;
    bg.setTexture(t);

    Font font;                                                              //return text
    font.loadFromFile("Fonts/Quarterback-6YrgD.otf");
    Text tx;
    tx.setFont(font);
    tx.setString("Press Backspace to return");
    tx.setPosition(50.f, window.getSize().y - 50);

    while (window.isOpen())
    {
        if (Keyboard::isKeyPressed(Keyboard::Key::Backspace))                                         //control setup
        {
            return;
        }
        window.draw(bg);
        window.draw(tx);
        window.display();
    }
}


void gameOver(RenderWindow& window)
{
    RectangleShape Return(Vector2f(200, 200));                                //return box
    Return.setPosition(window.getSize().x - 210, window.getSize().y - 120);
    Return.setFillColor(Color::Blue);
    Return.setOutlineColor(Color::Black);

    Font font;                                                              //return text
    font.loadFromFile("Fonts/Quarterback-6YrgD.otf");
    Text ReturnTxt;
    ReturnTxt.setFont(font);
    ReturnTxt.setString("Return");
    //ReturnTxt.setColor(Color::Black);
    ReturnTxt.setCharacterSize(30);
    ReturnTxt.setPosition(window.getSize().x - 190, window.getSize().y - 70);

    Texture texture;                                                                   //game over bg
    texture.loadFromFile("image/end.jpg");
    RectangleShape GameOver(Vector2f(window.getSize().x, window.getSize().y));
    GameOver.setTexture(&texture);

    //game over text
    Text gameoverTxt;
    gameoverTxt.setFont(font);
    gameoverTxt.setString("GAME OVER!");
    //gameoverTxt.setColor(Color::Red);
    gameoverTxt.setCharacterSize(90);
    gameoverTxt.setPosition(window.getSize().x / 2 - 400, window.getSize().y / 2 - 150);

    Text t;
    t.setFont(font);
    t.setString("Press Backspace to return");
    t.setPosition(50.f, window.getSize().y - 50);
    // t.setColor(sf::Color::Black);

    file.open("high score.txt");
    file >> max_score;
    file.close();

    Text score, hg;
    score.setFont(font);
    hg.setFont(font);
    score.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2 + 50);
    hg.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2 + score.getCharacterSize() + 50);
    score.setString("Your score : " + to_string(point));
    hg.setString("High Score : " + to_string(max_score));

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Key::Backspace))                                         //control setup
        {
            return;
        }
        window.clear();
        window.draw(GameOver);
        window.draw(Return);
        window.draw(gameoverTxt);
        window.draw(ReturnTxt);
        window.draw(score);
        window.draw(hg);
        window.draw(t);
        window.display();
    }
}

int main()                                                           //main function 
{
    //srand(time(NULL));

    RenderWindow window(VideoMode(1100, 800), "MISSION HORIZON");   //making window
    window.setFramerateLimit(60);
    //menu section
    Menu menu(window.getSize().x, window.getSize().y);

    Texture texture;
    texture.loadFromFile("image/menu.jpg");
    RectangleShape menuBackground(Vector2f(window.getSize()));
    menuBackground.setTexture(&texture);

    sf::Music menuMusic;
    menuMusic.openFromFile("menuMusic.wav");
    menuMusic.setVolume(50);
    menuMusic.setLoop(true);
    menuMusic.play();

    //score setting
    file.open("high score.txt");
    file >> max_score;
    file.close();

    Texture bgtexture;                                              //making background
    if (!bgtexture.loadFromFile("image/background.jpg"))
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
    bg2.setPosition(1100.f, 0.f);


    Texture playerTexture;                                          //player loading
    if (!playerTexture.loadFromFile("image/spaceship.png"))
    {
        cout << "Failed to load player";
    }
    RectangleShape player(Vector2f(150.f, 150.f));
    player.setTexture(&playerTexture);
    player.setPosition(0.f, 400.f);
    //player.setScale(0.5, 0.5);


    sf::Texture bulletTexture;                                      //Loading bullet
    bulletTexture.loadFromFile("image/laser.png");
    // RectangleShape bullet(Vector2f(80.f, 20.f));
     //bullet.setTexture(&bulletTexture);
    Texture ebulletTexture;
    ebulletTexture.loadFromFile("image/bullet1.png");

    Texture mateorTexture;                                          //Loading mateor
    if (!mateorTexture.loadFromFile("image/mateor.png"))
        cout << "Failed to load mateor" << endl;


    SoundBuffer shotBuffer, selects;                                         //sound and music effect
    shotBuffer.loadFromFile("sound/laser.ogg");
    Sound shot,select;
    shot.setBuffer(shotBuffer);
    shot.setVolume(5);
   
    selects.loadFromFile("button pressed.wav");
    select.setBuffer(selects);

    Music bgmusic;
    if (!bgmusic.openFromFile("sound/space.wav"))
    {
        cout << "Failed to load music";
        exit(-1);
    }
    bgmusic.setLoop(true);
    bgmusic.setVolume(10);


    Texture enemyTex, enemyTex1, enemyTex2;                                               // Enemy loading 
    //Texture enemyTex3;
    //Texture enemyTex4;
    //Texture enemyTex5;
    enemyTex.loadFromFile("image/alien.png");
    enemyTex1.loadFromFile("image/alien1.png");
    enemyTex2.loadFromFile("image/alien2.png");
    //enemyTex3.loadFromFile("image/alien3.png");
    //enemyTex4.loadFromFile("image/alien4.png");
    //enemyTex5.loadFromFile("image/alien5.png");

    Texture satelliteTex1, satelliteTex2, satelliteTex3, spacestationTex;

    satelliteTex1.loadFromFile("image/satellite.png");
    satelliteTex2.loadFromFile("image/satellite1.png");
    satelliteTex3.loadFromFile("image/satellite2.png");
    spacestationTex.loadFromFile("image/international-space-station.png");


    Font font;                                                      //Font loading
    font.loadFromFile("fonts/space.otf");

    Text score, destroy, destroycnt, pnt;                                                     //score loading
    score.setFont(font);
    score.setString("SCORE : ");
    score.setPosition(10.f, 10.f);

    pnt.setFont(font);
    pnt.setPosition(score.getGlobalBounds().width, 10);

    //play pause button
    Texture pausebutton;
    pausebutton.loadFromFile("image/pause.png");

    Sprite button;
    button.setTexture(pausebutton);
    button.setPosition(window.getSize().x - 70, 10);

    int destroyCount = 0;
    destroy.setFont(font);
    destroy.setString("Satellite destroyed : " + to_string(destroyCount));
    destroy.setPosition(10, score.getCharacterSize() + 10);

    RectangleShape HP(Vector2f(200.f, 30.f));                     //health display
    HP.setFillColor(Color::Green);
    HP.setPosition(window.getSize().x / 2 - 100.f, 10.f);

    RectangleShape HPbox(HP.getSize());
    HPbox.setOutlineColor(Color::White);
    HPbox.setOutlineThickness(3.f);
    HPbox.setFillColor(Color::Transparent);
    HPbox.setPosition(HP.getPosition());

    Text health;                     //health percentage text
    health.setFont(font);
    health.setPosition(HP.getPosition().x + 80.f, HP.getPosition().y + 0.f);
    health.setFillColor(Color::White);


    Texture explotex, fueltex;                                                //explotion section
    explotex.loadFromFile("image/type_B.png");
    IntRect shape(0, 0, 192, 192);
    Sprite explotion(explotex, shape);
    explotion.setPosition(-100, -100);
    explotion.setScale(0.5, 0.5);

    Sprite explotion1(explotex, shape);
    explotion1.setPosition(-100, -100);
    explotion1.setScale(0.5, 0.5);

    Sprite explotion2(explotex, shape);
    explotion2.setPosition(-100, -100);
    explotion2.setScale(0.5, 0.5);



    Clock clock;

    RectangleShape ebullet(Vector2f(80.f, 20.f));  //enemy bullet
    ebullet.setTexture(&ebulletTexture);

    //varibale initialization
    int enemyloadTime = 250;
    int shootTimer = 15;  //player bullet loading time
    int mateorTimer = 200;
    int time = 0;
    int temp = 0;

    bool mainMenu = true;
    bool mute = false;



    int playerHP = 50;
    vector <magazine> bullet; // player bullet vector
    vector < enemy > alien1; // Enemy vector
    vector <mateor> mateor1;
    vector <sat> satellite;
    vector <emagazine> eBullet;




    while (window.isOpen())                                                                        // GAME LOOP STARTS
    {
        Event event;

        while (window.pollEvent(event))                             //event loop
        {
            switch (event.type)                                     //menu control section
            {
            case sf::Event::KeyReleased:
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    menu.MoveUp();
                    break;

                case sf::Keyboard::Down:
                    menu.MoveDown();
                    break;

                case sf::Keyboard::Return:
                    switch (menu.GetPressed())
                    {
                    case 0:
                        mainmenu(window);
                        mainMenu = false;
                        temp = 1;
                        break;
                    case 1:
                        help(window);
                        select.play();
                        break;
                    case 2:
                        window.close();
                        break;
                    }

                    break;
                }



            }

            if (event.type == Event::Closed)
                window.close();


            if ((event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left) || Keyboard::isKeyPressed(Keyboard::Space) && mainMenu == false)               //Bullet pressed tracking
            {
                if (shootTimer > 15)
                {
                    bullet.push_back(magazine(&bulletTexture, player.getPosition()));
                    shot.play();
                    shootTimer = 1;
                }
            }


        }

        if (temp == 1) {
            menuMusic.stop();
            bgmusic.play();
            temp = 0;

        }

        //menu background randering
        if (mainMenu == true) {
            window.clear();
            window.draw(menuBackground);
            menu.draw(window);
            window.display();
            continue;
        }


        

        if ((Keyboard::isKeyPressed(Keyboard::Key::M)) && mute == false)        //mute function
        {
            cout << "m pressed" << endl;
            mute = true;
            bgmusic.pause();
        }

        /*
        if ( (Keyboard::isKeyPressed(Keyboard::Key::M)) && mute == true)
        {
            cout << "m pressed" << endl;
            mute = false;
            bgmusic.play();
        }
        */

        if (Keyboard::isKeyPressed(Keyboard::Key::P)) p = true;

        if (p == true)
        {
            pause(window);
        }


        if (clock.getElapsedTime().asSeconds() > 0.1f) {                  //animation update
            if (shape.left >= 12288)
            {
                shape.left = 0;
                explotion.setPosition(-100, -100);
                explotion1.setPosition(-100, -100);
                explotion2.setPosition(-100, -100);
            }
            else
                shape.left += 192;

            explotion.setTextureRect(shape);
            explotion1.setTextureRect(shape);
            explotion2.setTextureRect(shape);
            clock.restart();
        }


        //moving background effect
        background.move(-2.f, 0.f);
        bg2.move(-2.f, 0.f);

        if (background.getPosition().x == 0)
            bg2.setPosition(1100.f, 0.f);
        if (bg2.getPosition().x == 0)
            background.setPosition(1100.f, 0.f);



        if (Keyboard::isKeyPressed(Keyboard::Key::A))                                         //control setup
        {
            if (player.getPosition().x > 0)
                player.move(-7.f, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::S))
        {
            if (player.getPosition().y + player.getSize().y - 100 < window.getSize().y)
                player.move(0, 7.0f);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::D))
        {
            if (player.getPosition().x + player.getSize().x < window.getSize().x)
                player.move(7.f, 0);
        }
        if (Keyboard::isKeyPressed(Keyboard::Key::W))
        {
            if (player.getPosition().y > -100)
                player.move(0, -7.f);
        }

        // all variable laoding time increment
        shootTimer++;
        enemyloadTime++;
        mateorTimer++;
        time++;



        HP.setSize(Vector2f((playerHP * 200) / 50.f, 30.f)); //Health dynamic display






        if (mateorTimer > 300)                                                                  //Mateor generating factory
        {
            mateor1.push_back(&mateorTexture);
            mateorTimer = 0;
        }
        /*
        for (int i = 0; i < mateor1.size(); i++)
        {
            mateor1[i].sprite.setTexture(&mateorTexture, IntRect(0, 0, 93.75, 146));
        }
        */
        //Enemy generating factory
        if (time % 300 == 0)
        {
            if (time % 300 == 0)        alien1.push_back(&enemyTex);
            else if (time % 800 == 0)        alien1.push_back(&enemyTex1);
            else if (time % 1400 == 0)        alien1.push_back(&enemyTex2);
            //else if (time % 1100 == 0)        alien1.push_back(&enemyTex3);
            //else if (time % 1400 == 0)        alien1.push_back(&enemyTex4);
           // else if (time % 1700 == 0)        alien1.push_back(&enemyTex5);
        }


        if (time % 200 == 0)                                                                    //satellite generating factory
        {
            if (time % 400 == 0)       satellite.push_back(&satelliteTex1);
            else if (time % 700 == 0)  satellite.push_back(&satelliteTex2);
            else if (time % 1100 == 0) { satellite.push_back(&spacestationTex); }
            else                       satellite.push_back(&satelliteTex3);

        }



        //player bullet collision check
        if (!bullet.empty())
        {
            for (size_t i = 0; i < bullet.size(); i++) //for bullet
            {
                bool alreadyCollided = false;

                for (size_t j = 0; j < alien1.size(); j++) //for allien
                {

                    if (bullet[i].sprite.getGlobalBounds().intersects(alien1[j].sprite.getGlobalBounds())) // is collided with alien?
                    {

                        alien1[j].HP--;
                        alien1[j].sprite.move(10.f, 0.f); //backward force
                        bullet.erase(bullet.begin() + i);
                        alreadyCollided = true;
                        break;
                    }

                    if (alien1[j].HP <= 0)
                    {

                        point += 3;
                        explotion.setPosition(alien1[j].sprite.getPosition());
                        alien1.erase(alien1.begin() + j);
                    }

                    // if (bullet[i].sprite.getGlobalBounds() == alien1[j].sprite.getGlobalBounds() )
                    //    alien1[j].sprite.move(0.f, 5.f);


                }

                if (alreadyCollided == false)
                {
                    for (size_t k = 0; k < satellite.size(); k++)  //for satellite
                    {
                        if (bullet[i].sprite.getGlobalBounds().intersects(satellite[k].sprite.getGlobalBounds()))//is collided with satellite?
                        {

                            satellite[k].HP--;
                            satellite[k].sprite.move(10.f, 0.f); //backward force
                            bullet.erase(bullet.begin() + i);
                            break;
                        }

                        if (satellite[k].HP <= 0)
                        {
                            explotion1.setPosition(satellite[k].sprite.getPosition());
                            destroyCount++;
                            satellite.erase(satellite.begin() + k);
                            point += 3;
                        }
                    }
                }

            }
        }

        for (size_t i = 0; i < eBullet.size(); i++)                                                     //enemy bullet collision check
        {


            if (eBullet[i].sprite.getGlobalBounds().intersects(player.getGlobalBounds()))
            {
                playerHP--;
                eBullet.erase(eBullet.begin() + i);
            }
        }

        for (size_t i = 0; i < alien1.size(); i++)                                                      //alien bullet gen & collision check 
        {

            for (size_t j = 0; j < satellite.size(); j++)                                               //satellite alien overlaping check
            {
                if (alien1[i].sprite.getGlobalBounds().intersects(satellite[j].sprite.getGlobalBounds()))
                {
                    //satellite.erase(satellite.begin() + j); //if overlaped delete it
                    satellite[j].sprite.setPosition(alien1[i].sprite.getPosition().x + 200, alien1[i].sprite.getPosition().y + 200);
                }

            }

            alien1[i].eBulletLoad++;                                                                  //enemy bullet generating

            if (alien1[i].eBulletLoad > 150) //make a bullet for every alien after 300s of creation
            {
                eBullet.push_back(emagazine(&ebulletTexture, alien1[i].sprite.getPosition()));
                alien1[i].eBulletLoad = 0;
            }

            if (alien1[i].sprite.getGlobalBounds().intersects(player.getGlobalBounds()))              //alien player collision check
            {
                explotion2.setPosition(alien1[i].sprite.getPosition());
                playerHP -= 5;
                alien1.erase(alien1.begin() + i);

            }
        }

        for (size_t i = 0; i < satellite.size(); i++)
        {
            if (satellite[i].sprite.getGlobalBounds().intersects(player.getGlobalBounds())) //player satellite collision check
            {
                explotion2.setPosition(satellite[i].sprite.getPosition());
                destroyCount++;
                playerHP -= 5;
                satellite.erase(satellite.begin() + i);

            }

        }




        //Randering section
        window.clear();


        window.draw(background);
        window.draw(bg2);

        for (size_t i = 0; i < mateor1.size(); i++)          //mateor printing
        {
            mateor1[i].sprite.move(-1.f, 1.f);

            if (mateor1[i].sprite.getPosition().x > 1100)
            {
                mateor1.erase(mateor1.begin() + i); continue;
            }

            window.draw(mateor1[i].sprite);
        }

        window.draw(player);

        //alien 1 display
        for (size_t i = 0; i < alien1.size(); i++)
        {
            alien1[i].sprite.move(-4.f, 0.f);

            if (alien1[i].sprite.getPosition().x > -200) //appeared from behind effect
                window.draw(alien1[i].sprite);
            else
            {
                alien1.erase(alien1.begin() + i);
            }


        }

        //enemy bullet display
        if (!eBullet.empty())
        {
            for (size_t i = 0; i < eBullet.size(); i++)
            {
                eBullet[i].sprite.move(-7.f, 0.f);

                if (eBullet[i].sprite.getPosition().x > -100)
                {
                    window.draw(eBullet[i].sprite);
                }
                else eBullet.erase(eBullet.begin() + i);

            }
        }


        if (!bullet.empty())                                         //Bullet firing animation of player
        {
            for (size_t i = 0; i < bullet.size(); i++)
            {
                bullet[i].sprite.move(7.f, 0.f);     //position change per frame

                if (bullet[i].sprite.getPosition().x < 1200)
                {
                    //bullet.setPosition(magazine[i].first, magazine[i].second);      //bullet dynamic position changing
                    window.draw(bullet[i].sprite);
                }
                else bullet.erase(bullet.begin() + i);

            }
        }

        for (size_t i = 0; i < satellite.size(); i++)      //satellite printing
        {
            satellite[i].sprite.move(-4.f, 0.f);
            //satellite[i].sprite.rotate(2.f);

            if (satellite[i].sprite.getPosition().x < -200)
            {
                satellite.erase(satellite.begin() + i); continue;
            }

            window.draw(satellite[i].sprite);
        }


        if (playerHP <= 0)               //player HP check
        {
            explotion2.setPosition(player.getPosition());
            if (point > max_score)
            {
                file.open("high score.txt");
                file << point;
                file.close();
                cout << "You have achieved new High score : " << point;

            }
            else
            {
                cout << "High score : " << max_score << endl;
                cout << "Your score : " << point;
            }

            bgmusic.pause();          // music change;
            menuMusic.play();

            gameOver(window);
            select.play();
            //varibale initialization
            enemyloadTime = 250;
            shootTimer = 21;  //player bullet loading time
            mateorTimer = 200;
            time = 0;
            temp = 0;

            mainMenu = true;
            p = false;
            HP.setFillColor(Color::Green);

            playerHP = 50;
            point = 0;
            clock.restart();
        }


        window.draw(score);             //printing score
        pnt.setString(to_string(point));
        window.draw(pnt);
        destroy.setString("Satellite destroyed : " + to_string(destroyCount));
        window.draw(destroy);

        if (playerHP < 20) HP.setFillColor(Color::Red);     //printing Health
        window.draw(HPbox);
        window.draw(HP);
        health.setString(to_string((playerHP * 100) / 50));
        window.draw(health);

        window.draw(explotion);
        window.draw(explotion1);
        window.draw(explotion2);

        window.draw(button);

        window.display();
    }

    return 0;
}
