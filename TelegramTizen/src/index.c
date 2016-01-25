#include "index.h"

#define PRIVATE_DATA_KEY_CUR "pdkc"

void index_destroy(Evas_Object *index)
{
	if (NULL == index) {
		LOGE("index is NULL");
		return;
	}

	evas_object_data_del(index, PRIVATE_DATA_KEY_CUR);
	elm_index_item_clear(index);
	evas_object_del(index);
}



Evas_Object *index_create(Evas_Object *parent, unsigned int count)
{
	Evas_Object *index = NULL;
	register int i = 0;

	if (NULL == parent) {
		LOGE("parent is NULL");
		return NULL;
	}

	index = elm_index_add(parent);
	if (NULL == index) {
		LOGE("Fail to add the index");
		return NULL;
	}
	elm_object_style_set(index, "pagecontrol");

	elm_index_horizontal_set(index, EINA_TRUE);
	elm_index_autohide_disabled_set(index, EINA_TRUE);

	for (; i < count; i++) {
		elm_index_item_append(index, NULL, NULL, (void *) i);
	}
	elm_index_level_go(index, 0);
	evas_object_data_set(index, PRIVATE_DATA_KEY_CUR, NULL);
	evas_object_show(index);

	return index;
}



void index_update(Evas_Object *index, unsigned int count)
{
	register int i = 0;
	int cur_index = 0;

	elm_index_item_clear(index);

	for (; i < count; i++) {
		elm_index_item_append(index, NULL, NULL, (void *) i);
	}
	elm_index_level_go(index, 0);
	evas_object_show(index);

	cur_index = (int) evas_object_data_get(index, PRIVATE_DATA_KEY_CUR);
	index_bring_in(index, cur_index);
}



void index_bring_in(Evas_Object *index, int idx)
{
	Elm_Object_Item *idx_it;

	idx_it = elm_index_item_find(index, (void *) idx);
	if (NULL == idx_it) {
		LOGE("Fail to find the index item");
		return;
	}
	elm_index_item_selected_set(idx_it, EINA_TRUE);

	evas_object_data_set(index, PRIVATE_DATA_KEY_CUR, (void *) idx);
}
