/*
 * device_contacts_manager.h
 *
 *  Created on: Jul 7, 2015
 *      Author: sandeep
 */

#ifndef DEVICE_CONTACTS_MANAGER_H_
#define DEVICE_CONTACTS_MANAGER_H_

#include "tg_common.h"
#include <contacts.h>
#include "contacts_common.h"
#include "contacts-record-utils.h"
#include "contacts-list-utils.h"
#include "contacts-db-utils.h"

typedef struct contact_data {
	int contact_id;
	char *display_name;
	char *first_name;
	char *last_name;
	char *phone_number;
	char *pic_url;
} contact_data_s;


extern Eina_List* get_contact_list_from_device_db();
extern void free_contact_list(Eina_List *contact_data);




#endif /* DEVICE_CONTACTS_MANAGER_H_ */
