/*
 * index.h
 *
 *  Created on: Oct 9, 2015
 *      Author: moonkyoung
 */

#ifndef INDEX_H_
#define INDEX_H_

#include "tg_common.h"

extern void index_destroy(Evas_Object *index);
extern Evas_Object *index_create(Evas_Object *ui_manager, unsigned int count);
extern void index_update(Evas_Object *index, unsigned int count);
extern void index_bring_in(Evas_Object *index, int idx);

#endif /* INDEX_H_ */
