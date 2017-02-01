#include "mycalc.h"
#include "cview.h"
#include <xcb/xcb.h>
#include <iostream>
#include <cstring>
#include <string>
#define TYPE int

#define HEIGHT 20
#define WIDTH 100

cview::cview(mycalc *mc): m(mc)
{
	this->c = xcb_connect(NULL,NULL);
	std::cout<<"x-server connected"<<std::endl;
	setup();
}
cview::~cview()
{
	xcb_disconnect(this->c);
	std::cout<<"x-server disconnected"<<std::endl;
}

xcb_gcontext_t cview::gc_font_get(xcb_connection_t *c,
                            xcb_screen_t *screen,
			    xcb_window_t window,
			    const char *font_name)
{
	uint32_t value_list[3];
	xcb_void_cookie_t cookie_font;
	xcb_void_cookie_t cookie_gc;
	xcb_generic_error_t *error;
	xcb_font_t font;
	xcb_gcontext_t gc;
	uint32_t mask;

	font = xcb_generate_id(c);
	cookie_font = xcb_open_font_checked(c, font, strlen(font_name), font_name);

	error = xcb_request_check(c, cookie_font);
	if(error) { std::cout<<"ERROR: can't open font : "<<error->error_code<<std::endl; xcb_disconnect(c); exit(-1); }

	gc = xcb_generate_id(c);
	mask = XCB_GC_FOREGROUND | XCB_GC_BACKGROUND | XCB_GC_FONT;
	value_list[0] = screen->black_pixel;
	value_list[1] = screen->white_pixel;
	value_list[2] = font;
	cookie_gc = xcb_create_gc_checked(c, gc, window, mask, value_list);
	error = xcb_request_check(c, cookie_gc);
	if(error) { std::cout<<"ERROR: can't create gc : "<<error->error_code<<std::endl; xcb_disconnect(c); exit(-1); }

	cookie_font = xcb_close_font_checked(c, font);
	error = xcb_request_check(c, cookie_font);
	if(error) { std::cout<<"ERROR: can't close font : "<<error->error_code<<std::endl; xcb_disconnect(c); exit(-1); }

	return gc;
}

void cview::text_draw(xcb_connection_t *c,
                      xcb_screen_t *screen,
		      xcb_window_t window,
		      int16_t x1,
		      int16_t y1,
		      const char* label)
{
	xcb_void_cookie_t cookie_gc;
	xcb_void_cookie_t cookie_text;
	xcb_generic_error_t *error;
	xcb_gcontext_t gc;
	uint8_t length;

	length = strlen(label);

	gc = gc_font_get(c, screen, window, "7x13");

	cookie_text = xcb_image_text_8_checked(c, length, window, gc, x1, y1, label);

	error = xcb_request_check(c, cookie_text);
	if(error) { std::cout<<"ERROR "<<error->error_code<<" on line "<<__LINE__<<std::endl; xcb_disconnect(c); exit(-1); }

	cookie_gc = xcb_free_gc(c, gc);
	error = xcb_request_check(c, cookie_gc);
	if(error) { std::cout<<"ERROR "<<__LINE__<<std::endl; xcb_disconnect(c); exit(-1); }
}

void cview::setup()
{
	this->screen = xcb_setup_roots_iterator(xcb_get_setup(this->c)).data; //Screen
	//Window stuff
	this->win = xcb_generate_id(this->c);

	xcb_generic_event_t *e;
	xcb_generic_error_t *error;
	xcb_void_cookie_t cookie_window;
	xcb_void_cookie_t cookie_map;
	uint32_t mask;
	uint32_t values[2];

	this->display = "888";

	mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;
	values[0] = this->screen->white_pixel;
	values[1] = XCB_EVENT_MASK_KEY_RELEASE | XCB_EVENT_MASK_EXPOSURE;

	cookie_window = xcb_create_window_checked(this->c,                        //Connection
	                                          this->screen->root_depth,       //depth
	                                          this->win,                      //window ID
	                                          this->screen->root,             //parent window
	                                          0, 0,                           //x, y
	                                          WIDTH, HEIGHT,                  //width,height
	                                          10,                             //border
	                                          XCB_WINDOW_CLASS_INPUT_OUTPUT,  //class
	                                          this->screen->root_visual,      //visual
	                                          mask, values);                  //masks
	
	cookie_map = xcb_map_window_checked(this->c, this->win);

	// Error managing
	error = xcb_request_check(this->c, cookie_window);
	if(error) { std::cout<<"ERROR: can't create window : "<<error->error_code<<std::endl; xcb_disconnect(this->c); exit(-1); }

	error = xcb_request_check(this->c, cookie_map);
	if(error) { std::cout<<"ERROR: can't map window : "<<error->error_code<<std::endl; xcb_disconnect(this->c); exit(-1); }
	// // //

	xcb_flush(this->c);

	int16_t textpos_x = 10;
	int16_t textpos_y = 10;
	const char* clear = "             ";
	TYPE buf;

	bool run = true;

	while((e = xcb_wait_for_event(this->c)) && run)
	{
		switch(e->response_type & ~0x80)
		{
		case XCB_KEY_RELEASE:
			buf = 0;
			switch((int)((char)((xcb_key_press_event_t *)e)->detail))
			{
			case 81:
				buf++;
			case 80:
				buf++;
			case 79:
				buf++;
			case 85:
				buf++;
			case 84:
				buf++;
			case 83:
				buf++;
			case 89:
				buf++;
			case 88:
				buf++;
			case 87:
				buf++;
			case 90:
				bufnum *= 10;
				bufnum += buf;
				break;
			case 108: //enter
				std::cout<<std::to_string(bufnum)<<std::endl;
				m->c_push(bufnum);
				bufnum = 0;
				break;
			case 86: //plus
				if(bufnum)
				{
					m->add(bufnum);
					bufnum = 0;
				} else {
					m->add();
				}
				break;
			case 82: //minus
				if(bufnum)
				{
					m->sub(bufnum);
					bufnum = 0;
				} else {
					m->sub();
				}
				break;
			case 63: //mul
				if(bufnum)
				{
					m->mul(bufnum);
					bufnum = 0;
				} else {
					m->mul();
				}
				break;
			case 112: //div
				if(bufnum)
				{
					m->div(bufnum);
					bufnum = 0;
				} else {
					m->div();
				}
				break;
			case 24: // q
			case 9:  // ESC
				free(e);
				return;
			}
		case XCB_EXPOSE:
			display = &m->get_display()[0];
			text_draw(this->c, this->screen, this->win, textpos_x, textpos_y, clear);
			text_draw(this->c, this->screen, this->win, textpos_x, textpos_y, display);
			xcb_flush(this->c);
			break;
		default:
			std::cout<<"Unknown: "<<e->response_type<<std::endl;
			break;
		}
		free(e);
	}
}
