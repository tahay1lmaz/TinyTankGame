#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include<allegro5/allegro_image.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_acodec.h>
#include<time.h>
#include<stdlib.h>
void necessary_addons()
{
	al_init_primitives_addon();
	al_install_mouse();
	al_install_audio();
	al_install_keyboard();
	al_init_image_addon();
	al_init_acodec_addon();
}
int main()
{
	al_init();
	ALLEGRO_DISPLAY* d = al_create_display(1000, 1000);
	necessary_addons();
	ALLEGRO_SAMPLE *soundEffect = al_load_sample("music.wav");
	al_reserve_samples(1);
	ALLEGRO_TIMER* t = al_create_timer(1.0 / 60);
	ALLEGRO_EVENT_QUEUE* q = al_create_event_queue();
	al_register_event_source(q, al_get_mouse_event_source());
	al_register_event_source(q, al_get_keyboard_event_source());
	al_register_event_source(q, al_get_timer_event_source(t));

	ALLEGRO_BITMAP *player = player = al_load_bitmap("bot2.png");
	ALLEGRO_BITMAP *menu = al_load_bitmap("menu.png");
	//ALLEGRO_BITMAP *background = al_load_bitmap("alan.png");
	ALLEGRO_BITMAP *end = al_load_bitmap("theend.png");
	int x = 200, y = 200, vx = 0, vy = 0, mx = 0, my = 0, x1 = 0, x2 = 0,
		px = 500, py = 500, a = 0, b = 0, count = 0;
	float theta = 0;
	bool quit = NULL;
	al_play_sample(soundEffect, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, 0);
	al_draw_bitmap(menu, 0, 0, NULL);
	al_flip_display();
	ALLEGRO_EVENT c;
	al_wait_for_event(q, &c);
	if (c.type == ALLEGRO_KEY_P) {

		bool quit = false;
	}

	al_start_timer(t);
	bool redraw = true;

	while (!quit)
	{
		//al_draw_bitmap(background, 0, 0, NULL);
		al_flip_display();
		srand(time(NULL));
		a = 1 + rand() % 5;
		b = 1 + rand() % 5;
		px = px + a;
		py = py + b;

		al_draw_bitmap(player, px, py, NULL);
		if (px > 750 || py > 750) // if bot go outside to keep it on the screen
		{
			b = -9 + rand() % 1;
			a = -9 + rand() % 1;
			al_draw_bitmap(player, px += a, py += b, NULL);
			al_flip_display();
		}
		if (200 > px || 200 > py) // if bot go outside to keep it on the screen
		{
			b = 9 + rand() % 1;
			a = 9 + rand() % 1;
			al_draw_bitmap(player, px += a, py += b, NULL);
			al_flip_display();
		}

		al_flip_display();
		ALLEGRO_EVENT e;
		al_wait_for_event(q, &e);
		switch (e.type)
		{
		case ALLEGRO_EVENT_MOUSE_AXES:
			mx = e.mouse.x;
			my = e.mouse.y;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			switch (e.keyboard.keycode)
			{

			case ALLEGRO_KEY_ESCAPE:
				quit = true;
				break;
			case ALLEGRO_KEY_D:
				vx += 3;
				break;
			case ALLEGRO_KEY_A:
				vx -= 3;
				break;
			case ALLEGRO_KEY_W:
				vy -= 3;
				break;
			case ALLEGRO_KEY_S:
				vy += 3;
				break;
			case ALLEGRO_KEY_SPACE:
				x1 = x;
				x2 = y;


				while (1000 > x1 || 1000 > x2)  // that while loop works to shoot
				{

					x1 += 10;
					x2 += 10;
					al_clear_to_color(al_map_rgb(255, 255, 51));
					al_draw_filled_circle(x1 += 0.1, x2 += 0.1, 10, al_map_rgb(0, 155, 15));
					al_flip_display();
					if (abs(x1 - px) < 56.5 && abs(x2 - py) < 67.5)
					{
						count = 1;
					}

				}
				break;

			}
			break;
		case ALLEGRO_EVENT_KEY_UP:
			switch (e.keyboard.keycode)
			{
			case ALLEGRO_KEY_D:
				vx -= 3;
				break;
			case ALLEGRO_KEY_A:
				vx += 3;
				break;
			case ALLEGRO_KEY_W:
				vy += 3;
				break;
			case ALLEGRO_KEY_S:
				vy -= 3;
				break;

			case ALLEGRO_KEY_SPACE:
				x1 = x;
				x2 = y;

				while (1000 > x1 || 1000 > x2) // that while loop works to shoot
				{
					x1 += 10;
					x2 += 10;
					al_clear_to_color(al_map_rgb(255, 255, 51));
					al_draw_filled_circle(x1 += 0.1, x2 += 0.1, 10, al_map_rgb(0, 155, 15));
					al_flip_display();
					if (abs(x1 - px) < 56.5 && abs(x2 - py) < 67.5)
					{
						count = 1;
					}
				}
				break;
			}
			break;
		case ALLEGRO_EVENT_TIMER:
			x += vx;
			y += vy;
			theta = atan2(mx - x, my - y);
			redraw = true;
			break;
		}

		if (al_is_event_queue_empty(q) && redraw)
		{
			al_clear_to_color(al_map_rgb(255, 255, 51));

			ALLEGRO_TRANSFORM trans;
			al_identity_transform(&trans);
			al_rotate_transform(&trans, theta);
			al_translate_transform(&trans, x, y);
			al_use_transform(&trans);

			al_draw_rectangle(-26, -15, 26, 15, al_map_rgb(0, 0, 255), 30.0);
			al_draw_rectangle(-10, -5, 60, 5, al_map_rgb(0, 200, 200), 10.0);

			al_identity_transform(&trans);
			al_use_transform(&trans);

			al_flip_display();
		}
		al_flip_display();
		while (count == 1)
		{
			al_draw_bitmap(end, 0, 0, NULL);
			al_flip_display();
		}
	}

	return 0;
}