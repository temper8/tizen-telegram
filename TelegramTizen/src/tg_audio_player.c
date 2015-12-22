/*
 * tg_audio_player.c
 *
 *  Created on: Oct 22, 2015
 *      Author: sandeep
 */


#include "tg_audio_player.h"

static void _player_interrupted_cb(player_interrupted_code_e code, void *data)
{
	tg_player_handler *player = data;

	if (!player)
		return;

	player_state_e state;
	player_get_state(player->handler, &state);
	player->state = TG_AUDIO_PLAYER_STATE_INTERRUPTED;
	player->state_callback(player, player->state, player->user_data);
	return;
}

static void _player_completed_cb(void *data)
{
	tg_player_handler *player = data;

	if (!player)
		return;

	player->state = TG_AUDIO_PLAYER_STATE_END;
	player->state_callback(player, player->state, player->user_data);
	return;
}

static void _player_error_cb(int error_code, void *user_data)
{
	tg_player_handler *player = user_data;

	if (!player)
		return;

	player->state = TG_AUDIO_PLAYER_STATE_ERROR;
	player->state_callback(player, player->state, player->user_data);
	return;
}

tg_player_handler* init_audio_player(const char *audio_file, tg_player_state_changed state_change, tg_player_progress_updated progress_update, void *user_data)
{
	if (!audio_file)
		return NULL;
	tg_player_handler *player = NULL;
	if (access(audio_file, F_OK) != -1) {
		player = (tg_player_handler*)malloc(sizeof(tg_player_handler));
		if (player) {
			player->timer = NULL;
			player->current_pos = 0;
			player->state = TG_AUDIO_PLAYER_STATE_NONE;
			player->progress_callback = progress_update;
			player->state_callback = state_change;
			player->user_data = user_data;

			int error_code = 0;
			error_code = player_create(&player->handler);
			if (error_code == PLAYER_ERROR_NONE) {
				player_set_sound_type(player->handler, SOUND_TYPE_MEDIA);
				player_set_volume(player->handler, 1.0, 1.0);
				player_set_looping(player->handler, false);
			}
			error_code = player_set_interrupted_cb(player->handler, _player_interrupted_cb, player);
			if (error_code != PLAYER_ERROR_NONE) {
				free(player);
				return NULL;
			}
			error_code = player_set_completed_cb(player->handler, _player_completed_cb, player);
			if (error_code != PLAYER_ERROR_NONE) {
				free(player);
				return NULL;
			}
			error_code = player_set_error_cb(player->handler, _player_error_cb, NULL);
			if (error_code != PLAYER_ERROR_NONE) {
				free(player);
				return NULL;
			}
			error_code = player_set_uri(player->handler, audio_file);
			if (error_code != PLAYER_ERROR_NONE) {
				free(player);
				return NULL;
			}
			error_code = player_prepare(player->handler);
			if (error_code == PLAYER_ERROR_NONE) {
				usleep(1000);
				player->state = TG_AUDIO_PLAYER_STATE_INITIALIZED;
				player->state_callback(player, player->state, user_data);
			} else {
				//failed to create player, free all items.
				free(player);
				return NULL;
			}

		}
	}
	return player;
}


static Eina_Bool audio_progress_updated(void *data)
{
	tg_player_handler *player = data;

	if (!player) {
		return ECORE_CALLBACK_CANCEL;
	}

	int total_duration = 0;
	player_get_duration(player->handler, &total_duration);

	int cur_pos = 0;
	player_get_play_position(player->handler, &cur_pos);

	player->progress_callback(player, cur_pos, total_duration, player->user_data);

	return ECORE_CALLBACK_RENEW;
}
void play_audio_player(tg_player_handler *player)
{
	if (!player)
		return;
	int error_code = 0;
	if (player->state == TG_AUDIO_PLAYER_STATE_INITIALIZED || player->state == TG_AUDIO_PLAYER_STATE_INTERRUPTED || player->state == TG_AUDIO_PLAYER_STATE_PAUSE) {
		error_code = player_start(player->handler);
		if (error_code == PLAYER_ERROR_NONE) {
			player->state = TG_AUDIO_PLAYER_STATE_PLAYING;

			if (player->timer) {
				ecore_timer_del(player->timer);
				player->timer = NULL;
			}
			player->timer = ecore_timer_add(0.001, audio_progress_updated, player);
			player->state_callback(player, player->state, player->user_data);
		}
	}
}

void pause_audio_player(tg_player_handler *player)
{
	if (!player)
		return;
	int error_code = 0;
	if (player->state == TG_AUDIO_PLAYER_STATE_PLAYING) {
		error_code = player_pause(player->handler);
		if (error_code == PLAYER_ERROR_NONE) {
			player->state = TG_AUDIO_PLAYER_STATE_PAUSE;
			if (player->timer) {
				ecore_timer_del(player->timer);
				player->timer = NULL;
			}
			player->state_callback(player, player->state, player->user_data);
		}
	}
}

void destroy_audio_player(tg_player_handler *player)
{
	if (!player)
		return;
	int error_code = 0;

	error_code = player_stop(player->handler);
	if (error_code == PLAYER_ERROR_NONE) {

	}

	error_code = player_unprepare(player->handler);
	if (error_code == PLAYER_ERROR_NONE) {
		if (player->timer) {
			ecore_timer_del(player->timer);
			player->timer = NULL;
		}
	}
	player_destroy(player->handler);
	player->state = TG_AUDIO_PLAYER_STATE_NONE;
}

