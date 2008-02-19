#include "tagal.h"

int main()
{
	tagal_t *tagal;
	tagal_data_iter_t *data;
	tagal_tag_iter_t *tags;

	tagal_new(&tagal, libtagal_sqlite, "tagal-test.db", 1, NULL);
	tagal_data_iter_new(tagal, &data);
	tagal_tag_iter_new(tagal, &tags);

#ifdef SELECT_TEST
	tagal_select_by_tags(tagal, data, "tag3\ntag2");

	while(tagal_data_next(data)) {
		printf("path: %s, name: %s\n",
			tagal_data_path(data), tagal_data_name(data));
	}
#endif

#ifdef DEL_TEST
	tagal_data_del_tag_by_path(tagal, "/home/32", "tag2");
	tagal_data_get_tags_by_path("/home/32", tags);
	while(tagal_tag_next(tags)) {
		printf("%s\n", tagal_tag_tag(tags));
	}

	tagal_data_del_tag_by_path(tagal, "/home/32", "tag1");

	tagal_data_get_tags_by_path("/home/32", tags);
	while(tagal_tag_next(tags)) {
		printf("%s\n", tagal_tag_tag(tags));
	}

	tagal_data_add_tag_to_path(tagal, "/home/32", "tag2");
	tagal_data_get_tags_by_path("/home/32", tags);
	while(tagal_tag_next(tags)) {
		printf("%s\n", tagal_tag_tag(tags));
	}
	tagal_tag_del_tag(tagal, "tag1");
	tagal_data_add_tag_to_path(tagal, "/home/12", "tag1");
#endif

	tagal_data_add_tags_to_path(tagal, "/home/12", "tag5\ntag8\ntag\n");

	return 0;
}

