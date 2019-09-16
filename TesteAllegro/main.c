#include<stdio.h>
#include<allegro5/allegro.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_color.h>
#include <math.h>

typedef struct BaseBola
{
	int x;
	int y;
	//char *bitmap;
	ALLEGRO_BITMAP* bitmap;  
}Bola;

typedef struct Botao
{
	int x;
	int y;
	//char* bitmap;
	ALLEGRO_BITMAP* bitmap;
}Botao;

typedef struct Fundo
{
	int r;
	int g;
	int b;
	//char* cor;
	//char *bitmap;
}Fundo;

Bola novaBola(int x, int y, ALLEGRO_BITMAP* bitmap)//char *bitmap
{
	Bola b;
	b.x = x;
	b.y = y;
	b.bitmap = bitmap;
	return b;
}

Botao novoBotao(int x, int y, ALLEGRO_BITMAP* bitmap)//char* bitmap
{
	Botao b;
	b.x = x;
	b.y = y;
	b.bitmap = bitmap;
	return b;
}

Fundo novoFundo(int r, int g, int b)//char* cor
{
	Fundo f;
	f.r = r;
	f.g = g;
	f.b = b;
	return f;
}

bool checaClickDentroHitBox(int xc, int yc,int raio, int xo, int yo)
{
	float dist = sqrt(pow(xo - xc,2) + pow(yo - yc, 2));
	/*printf("\n%d\n%d\n%d\n%d\n%d\n", xc, yc, raio, xo, yo);
	printf("%f\n", dist);*/
	if (dist <= raio)
		return true;
	return false;
}

////////////////////////////////////////////////////////////////////////////

int i = 0;
int main() 
{
	Fundo f1 = novoFundo(5,5,5);
	Fundo f2 = novoFundo(25,50,150);
	Fundo fundos[] = {f1,f2};

	al_init();
	ALLEGRO_DISPLAY *display;
	ALLEGRO_EVENT_QUEUE *queue;
	ALLEGRO_BITMAP *bitmap = NULL;


	display = al_create_display(1000,1000);
	queue = al_create_event_queue();

	//al_install_keyboard();
	//al_register_event_source(queue, al_get_keyboard_event_source());
	al_install_mouse();
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));

	al_init_image_addon();
	al_init_primitives_addon();

	bitmap = al_load_bitmap("ball.png");
	assert(bitmap != NULL);
	Bola b = novaBola(10, 10, bitmap);
	//Bola b = novaBola(10, 10, "ball.png"); //b.bitmap
	//bitmap = al_load_bitmap(b.bitmap);
	//assert(bitmap != NULL);

	bitmap = al_load_bitmap("setaD.png");
	assert(bitmap != NULL);
	Botao btndireita = novoBotao(al_get_display_width(display)-100,(al_get_display_height(display))/2,bitmap);

	bitmap = al_load_bitmap("setaE.png");
	assert(bitmap != NULL);
	Botao btnesquerda = novoBotao(0, (al_get_display_height(display)) / 2, bitmap);

	bool gameloop = true;
	while (gameloop != false)
	{
		ALLEGRO_EVENT event;
		ALLEGRO_MOUSE_STATE mstate;
		al_wait_for_event(queue, &event);
		al_get_mouse_state(&mstate);

		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			gameloop = false;


		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (checaClickDentroHitBox(btndireita.x, btndireita.y, 5, event.mouse.x, event.mouse.y))
			{
				i++;
			}
			if (checaClickDentroHitBox(btnesquerda.x, btnesquerda.y, 5, event.mouse.x, event.mouse.y))
			{
				i--;
			}
		}

		if (mstate.buttons & 1)
		{
			if (checaClickDentroHitBox(b.x, b.y, 5, event.mouse.x, event.mouse.y))
			{
				b.x = event.mouse.x;
				b.y = event.mouse.y;
			}
		}
	
		al_clear_to_color(al_map_rgb(fundos[i].r, fundos[i].g, fundos[i].b));

		al_draw_bitmap(b.bitmap, b.x, b.y, 0); 
		al_draw_filled_circle(b.x, b.y, 5, al_map_rgb(255, 0, 0));

		al_draw_bitmap(btndireita.bitmap, btndireita.x, btndireita.y, 0);
		al_draw_filled_circle(btndireita.x, btndireita.y, 5, al_map_rgb(255, 0, 0));
		
		al_draw_bitmap(btnesquerda.bitmap, btnesquerda.x, btnesquerda.y, 0);
		al_draw_filled_circle(btnesquerda.x, btnesquerda.y, 5, al_map_rgb(255, 0, 0));

		al_flip_display(display);
	}

	al_uninstall_mouse();
	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_destroy_bitmap(bitmap);
	//al_uninstall_keyboard();
	return 0;
}