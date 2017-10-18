#include "Characters.h"
#include "Textures.h"

Hero::Hero(int x, int y)
{
	this->x = x;
	this->y = y;
	this->ground = true;
	this->jump = false;
	this->p_y = SCREEN_H;
	this->lewo = true;
	this->prawo = true;
	this->anim = false;
	this->acceleration = 1;
	BMP =  load_bitmap("BMP/hero.bmp",NULL);
}

void Hero::draw(BITMAP* buffor,int timer)
{
    if(!ground&&!anim)
    {
        if(p_y<y&&prawo)
            masked_blit(this->BMP, buffor, 50, 0, x, y, BMP->w/3, BMP->h/5);
        else if(p_y>y&&prawo)
           masked_blit(this->BMP, buffor, 100, 0, x, y, BMP->w/3, BMP->h/5);
        else if(p_y<y&&lewo)
           masked_blit(this->BMP, buffor, 50, 240, x, y, BMP->w/3, BMP->h/5);
        else
            masked_blit(this->BMP, buffor, 100, 240, x, y, BMP->w/3, BMP->h/5);
    }
	else if(!anim){
        if(prawo)
            masked_blit(this->BMP, buffor,klatka, 80, x, y, BMP->w/3, BMP->h/5);
        else if(lewo)
            masked_blit(this->BMP, buffor, klatka, 160, x, y, BMP->w/3, BMP->h/5);
        else
            masked_blit(this->BMP, buffor, 0, 0, x, y, BMP->w/3, BMP->h/5);
	}
	else
    {
        masked_blit(this->BMP, buffor, klatka, 320, x, y, BMP->w/3, BMP->h/5);
    }
    if(key[KEY_E])
    {
        //textprintf_centre_ex(screen, font, 500, 500, makecol(255, 255, 255), -1, "%d", mx);
        //textprintf_centre_ex(screen, font, 500, 500, makecol(255, 255, 255), -1, "%d", hero->x);
           // putpixel(buffor,((x+40)+i*(x-mx)),(y+40)+i*(y-my),makecol(255,0,0));
            if (x >= CAMERA_OFFSET && x <= 2100 - SCREEN_W + CAMERA_OFFSET)
                line(buffor,x+40,y+40,mouse_x+x-CAMERA_OFFSET,mouse_y,makecol(255,35,0));
            else if (x <= CAMERA_OFFSET)                                              //LEWA STRONA PLANSZY
                line(buffor,x+40,y+40,mouse_x,mouse_y,makecol(255,35,0));
            else
            {
                for(int i=0;i<20;i++)
                    line(buffor,x+40,y+40,mouse_x+x+(i*5)-CAMERA_OFFSET,mouse_y,makecol(255,35,0));
            }
            poll_mouse();
    }
}

void Hero::move(int jump_height,int timer,bool &end)
{
//    if(!key[KEY_A]&&!key[KEY_D]&&!jump)
//    {
//        lewo = false;
//        prawo = false;
//    }
	if (key[KEY_A]){
		x--;
        lewo = true;
        prawo = false;
        klatka = timer*50;
		}
	if (key[KEY_D]){
		x++;
        prawo = true;
        lewo = false;
        klatka = timer*50;
	}
	if (key[KEY_W] && !jump && ground)
	{
	    acceleration = 1;
		jump = true;
		ground = false;
		p_y = y - jump_height;
		if (p_y<0)
			p_y = 0;
	}
	if(key[KEY_S]){
        ground = false;
	}

	if(key[KEY_Q])
    {
        anim = true;
        klatka = timer*50;
    }
    if(anim&&!key[KEY_Q])
    {
        if(timer>1)
            anim = false;
    }
	if (jump)
	{
	    if(acceleration<3)
            acceleration+=0.01;
		if (y >= p_y)
			y-=acceleration;
		else
		{
			jump = false;
			p_y = SCREEN_H;
		}
	}
	if (!ground && !jump)
    {
		y+=acceleration;
		acceleration+=0.01;
    }
	if (key[KEY_R])
	{
		x = 50;
		y = -50;
		acceleration = 1;
	}
	if(y > SCREEN_H)
        end = true;
	Ground::gravity_blocks = 0;
}
void Hero::attack(std::vector <Bullet> &bullets, volatile int &rest)
{
    if(key[KEY_SPACE]&&rest>5){
        Bullet *tmp  = new Bullet(this->x,this->y,this->lewo);
        bullets.push_back(*tmp);
        std::cout<<"d"<<std::endl;
        rest = 0;
    }
}
//************************
Bullet::Bullet(int x,int y,bool direction)
{
    this->direction = direction;
    if(direction)
        this->x = x;
    else
        this->x = x+40;
        this->y = y+30;
    this->range = x+350;
}

void Bullet::draw(BITMAP *buffor)
{
    circlefill(buffor,x,y,5,makecol(255,255,0));
}
void Bullet::move()
{
    if(direction)
        x-=2;
    else
        x+=2;
}
int Bullet::del()
{
    if(x>range  || x<range-700)
        return 1;
    return 0;
}
//************************
Enemy::Enemy(int x, int y,int xmin, int xmax)
{
    this->x = x;
    this->y = y;
    this->ymax = y-81;
    this->ymin = y+81;
    this->xmin = xmin;
    this->xmax = xmax;
    this->dest = false;
    BMP = load_bitmap("BMP/enemy.bmp",NULL);
    init = false;
    all = false;
    this->direction = true;
}

void Enemy::draw(BITMAP* buffor){
    if(init)
        masked_blit(this->BMP, buffor, 0, 0, x, y, BMP->w, BMP->h);
}

void Enemy::ini(int x)
{
    if(x>this->x-250)
        init = true;
}

void Enemy::move()
{
    if(init && !all){
        y--;
        if(y <= ymax)
            all = true;
    }
    else if(all)
    {
        if(!direction)
        {
            x--;
            if(xmin>x){
                    swap_bmp();
                direction = true;
            }
        }
        else if(direction)
        {
            x++;
            if(xmax<x){
                    swap_bmp();
                direction = false;
            }
        }
    }
}

void Enemy::swap_bmp(){
    BITMAP *tmp = create_bitmap(this->BMP->w,this->BMP->h);
    clear_to_color(tmp, makecol(255,0,255));
    for(int i=0; i<=this->BMP->w-1;i++)
    {
        for(int j=0; j<=this->BMP->h-1;j++)
        {
            putpixel(tmp,this->BMP->w-i,j, getpixel(BMP,i,j));
        }
    }
    this->BMP = tmp;
}

int Enemy::check_bullet(std::vector<Bullet> &bullets)
{
    for (std::vector<Bullet>::iterator it = bullets.begin() ; it != bullets.end();)
        {
            if(it->x >x && it->x < x  + BMP->w  && it->y > y && it->y < y +BMP->h){
                it = bullets.erase(it);
                return 1;
                }
            else
                ++it;
        }
        return 0;
}

int Enemy::movedead()
{
    y++;
    if(y>ymin)
        return 1;
    return 0;
}

int Enemy::check_hero(BITMAP* buffor, Hero &h)
{
    if(x < h.x+(h.BMP->w/3)-30 && x + BMP->w > h.x+30  && y <h.y + (h.BMP->h/5)-30 && y + BMP->h >h.y)
    {
        for(int i=0;i<BMP->w;i++)
        {
            for(int j=0;j<BMP->h;j++)
            {
                int p =  getpixel(h.BMP,x+i,y+j);
                int x =  getpixel(BMP,i,j);
                if(p!=x && p != makecol(255,0,255))
                    return 1;
            }
        }
    }
    return 0;
}

Boss::Boss(int x,int y)
{
    this->x = x;
    this->y = y;
    this->hp = 25;
    this->xmin = x-100;
    this->xmax = SCREEN_W-100;
    this->init = true;
    this->direction = false;
    this->BMP = load_bitmap("BMP/boss1.bmp",NULL);
}

void Boss::draw(BITMAP* buffor)
{
    masked_blit(BMP,buffor,0,0,x,y,BMP->w,BMP->h);
    rect(buffor,200,100,600,150,makecol(255,255,255));
    for(int i=0;i<=hp;i++)
        rectfill(buffor,200,100,200+(16*i),150,makecol(255,127,127));
}

void Boss::move()
{
    if(direction)
    {
        x--;
        if(x<=xmin)
            this->direction = false;
    }
    else
    {
        x++;
        if(x>=xmax){
            this->direction = true;
        }
    }
}

void Boss::attack(std::vector<Enemy> &enemies){
    if(hp==23&&init)
    {
        for(int i=0;i<5;i++)
        {
            Enemy *en  = new Enemy(0-(i*200),470,0,SCREEN_W);
            enemies.push_back(*en);
        }
        init = false;
    }
    if(hp==20&&init)
    {
        for(int i=0;i<5;i++)
        {
            Enemy *en  = new Enemy(SCREEN_W+(i*200),470,0,SCREEN_W+(i*200)+1);
            en->init = true;
            enemies.push_back(*en);
        }
        init = false;
    }
    if(hp==15&&init)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                Enemy *en = new Enemy(0-(i*50)-(400*j),470,0,SCREEN_W);
                en->init = true;
                enemies.push_back(*en);
            }
        }
        init = false;
    }
    if(hp==10&&init)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<4;j++)
            {
            Enemy *en  = new Enemy(SCREEN_W+(i*50)+(400*j),470,0,(SCREEN_W+(i*200)+(400*j)));
            en->init = true;
                enemies.push_back(*en);
            }
        }
        init = false;
    }
    if(hp==5&&init)
    {
        for(int i=0;i<5;i++){
            Enemy *en  = new Enemy(0-(i*200),470,0,SCREEN_W);
            en->init = true;
                enemies.push_back(*en);
        }
        for(int i=0;i<5;i++){
            Enemy *en  = new Enemy(SCREEN_W+(i*200),470,0,SCREEN_W+(i*200)+1);
            en->init = true;
                enemies.push_back(*en);
        }
        init = false;
    }
    if(hp!= 23 && hp!=20 && hp != 15 && hp!= 10 && hp!=5)
    {
        init = true;
    }
}
