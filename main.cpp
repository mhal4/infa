#include <SFML/Graphics.hpp>
#include "map.h"
#include "view.h"
#include <iostream>
#include <math.h>
using namespace std;
using namespace sf;


class Player{
    private: float x,y;
    public:
        float w,h,dx,dy,speed = 0;
        bool on_ground,life;
        int score,health;
        enum stateObject {jump, down_ground, down_air, stay};
        stateObject state;
        String file;
        Image img;
        Texture tex;
        Sprite spr;

        Player (String F, int X, int Y, float W, float H){
            dx = 0; dy = 0; speed = 0; score = 1; health = 1;
            file = F; on_ground = false; state = stay; life = true;
            w = W; h = H;
            img.loadFromFile("images/" + file);
            tex.loadFromImage(img);
            spr.setTexture(tex);
            x = X; y = Y;
            spr.setTextureRect(IntRect(0,0,w,h));
        }

        void control(){
            bool f1 = true,f2 = true;
            if ((Keyboard::isKeyPressed(Keyboard::Up)||Keyboard::isKeyPressed(Keyboard::Space)) && (on_ground)) { 
                state = jump;  on_ground = false; 
                f1 = false;
                
            }

            if (Keyboard::isKeyPressed(Keyboard::Down)) { 
                if(on_ground){
                    state = down_ground; 
                } else {
                    state = down_air;
                }
                f2 = false;
                
            }
            
            speed = 0.1;
            if (f1&&f2) {
                state = stay; speed = 0.1;    
            }
            spr.setTextureRect(IntRect(0,0,240,240));

        }

        void checkCollisionWithMap(float Dx, float Dy)//ф ция проверки столкновений с картой
	   {
		   for (int i = y / 32; i < (y + h) / 32; i++)//проходимся по элементам карты
		   for (int j = x / 32; j<(x + w) / 32; j++)
		   {
			   if (TileMap[i][j] == '0'){if (Dy>0) y = i * 32 - h;  dy = 0; on_ground = true; }
               if (TileMap[i][j] == 'C'){if (Dx>0) x = j * 32 + 32; health = 0;}// с левым краем карты
			}
	   }
       
        void update(float time){
            control();
            switch(state){
                case jump:  dy = -0.7; break;
                case down_air: dy += 0.8; break;
                case down_ground: dy = 0; spr.setTextureRect(IntRect(240,0,240,240)); break; //spr.setTextureRect()
                //case stay: dx = speed; dy = 0;
            }

            speed += sqrt(score/(float)100);
            speed = int(speed)/(float)40;
            x += (speed+0.1)*time;
            score = x;
            cout << score << ' ' << speed <<'\n';
		    checkCollisionWithMap(dx, 0);//обрабатываем столкновение по Х
		    y += dy*time;
		    checkCollisionWithMap(0, dy);//обрабатываем столкновение по Y
            spr.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		    if (health <= 0){ life = false; }
		    if (!on_ground) { dy = dy + 0.001*time; spr.setTextureRect(IntRect(480,0,240,240));}//убираем и будем всегда притягивать к земле
            if (on_ground) dy = 0;
            spr.setPosition(x,y);
        }
        
        float getx(){return x;}
        float gety(){return y;}

        
};


int main()
{
    RenderWindow window(VideoMode(1000, 1000), "SFML works!");
    view.reset(FloatRect(0,0,1080,720));
    view.setViewport(FloatRect(0,0,1.f,0.5f));

    Image map_image;
    map_image.loadFromFile("images/map.png");
    Texture map;
    map.loadFromImage(map_image);
    Sprite s_map;
    s_map.setTexture(map);

    Player p1("fopfall.png" , 250, 250, 240.0, 240.0);

    Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        
        p1.update(time);
        window.setView(view);
        window.clear();

        for (int i = 0; i < HEIGHT_MAP; i++){
            for (int j = 0; j < WIDTH_MAP; j++){
                if (TileMap[i][j] == ' ') s_map.setTextureRect(IntRect(0,0,32,32));
                if (TileMap[i][j] == 's') s_map.setTextureRect(IntRect(32,0,32,32));
                if (TileMap[i][j] == '0') s_map.setTextureRect(IntRect(64,0,32,32));

                s_map.setPosition(j*32, i*32);

                window.draw(s_map);
            }
        }
        getview(p1.getx(),p1.gety());
        window.draw(p1.spr);
        window.display();
    }

    return 0;
}

