/*
 * server_requests.h
 *
 *  Created on: Jun 26, 2015
 *      Author: sandeep
 */

#ifndef SERVER_REQUESTS_H_
#define SERVER_REQUESTS_H_

#include "tg_common.h"

void send_request_for_registration(service_client* service_client, const char* phone_number, Eina_Bool through_sms);
void send_request_for_profile_registration(service_client* service_client, const char* first_name, const char* last_name);
void send_request_for_validation(service_client* service_client, const char* sms_code);
// type_of_chat 0-buddy, 1-group_chat 2-encrpted_chat
void send_request_for_message_transport(service_client* service_client, const int buddy_id, const int msg_type, const char* data, const int type_of_chat);
void send_request_for_image_downloading(service_client* service_client, const int buddy_id, const long long media_id);
void send_request_for_media_transport(service_client* service_client, const int buddy_id, const int msg_type, const char* file_path);
void send_contacts_list_to_server(service_client* service_client, Eina_List* contacts_list);
void send_group_creation_request_to_server(service_client* service_client, Eina_List* buddy_list, const char* group_name, const char* group_image);

#endif /* SERVER_REQUESTS_H_ */
