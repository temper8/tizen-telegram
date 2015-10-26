/*
 * tg_audio_player.h
 *
 *  Created on: Oct 22, 2015
 *      Author: sandeep
 */

#ifndef TG_AUDIO_PLAYER_H_
#define TG_AUDIO_PLAYER_H_

#include "tg_common.h"
#include <player.h>

typedef enum AUDIO_PLAYER_STATE {
	TG_AUDIO_PLAYER_STATE_NONE = 1,
	TG_AUDIO_PLAYER_STATE_INITIALIZED,
	TG_AUDIO_PLAYER_STATE_PLAYING,
	TG_AUDIO_PLAYER_STATE_INTERRUPTED,
	TG_AUDIO_PLAYER_STATE_PAUSE,
	TG_AUDIO_PLAYER_STATE_ERROR,
	TG_AUDIO_PLAYER_STATE_END
} TG_AUDIO_PLAYER_STATE;

typedef void (*tg_player_state_changed)(void* handler, TG_AUDIO_PLAYER_STATE state, void *user_data);
typedef void (*tg_player_progress_updated)(void* handler, int current, int total, void *user_data);

typedef struct tg_player_handler_s {
	player_h handler;
	tg_player_state_changed state_callback;
	tg_player_progress_updated progress_callback;
	TG_AUDIO_PLAYER_STATE state;
	void *user_data;
	Ecore_Timer *timer;
	int current_pos;
} tg_player_handler;

tg_player_handler* init_audio_player(const char *audio_file, tg_player_state_changed state_change, tg_player_progress_updated progress_update, void *user_data);

void play_audio_player(tg_player_handler *handler);

void pause_audio_player(tg_player_handler *handler);

void destroy_audio_player(tg_player_handler *handler);

#endif /* TG_AUDIO_PLAYER_H_ */
