#include "tagal.h"
#include "tagaldb.h"
#include "dbinterface.h"
#include "global.h"
#include <string.h>
#include <stdlib.h>

//#define DEBUG_TRACE	1
#define DEBUG_ERROR	1
#include "error.h"

#define DEFAULT_BUFSZ	1024

#define FREE_COND(str, buf)	do {	\
	if((str) != (buf) && NULL != (str))	\
		free(str);	\
} while(0)

/* TODO here really needs some buffer staff, 
 * rather than a singl pointer, doing nothing but making memory fragment
 */
struct tagal_t {
	libtagal_db_t *db;
	mempool_t *pool;
};

struct tagal_data_iter_t {
	tagal_t *tagal;
	mempool_t *pool;
	libtagal_db_result_t *result;
};

struct tagal_tag_iter_t {
	tagal_t *tagal;
	mempool_t *pool;
	libtagal_db_result_t *result;
};

static char *trans_str(const char *str, char *buf, int size)
{
	char *ret;
	char *ptr;
	int nr_t;
	nr_t = 0;
	if(strlen(str) >= size) {
		ret = (char *)malloc(strlen(str) << 1 + 1);
		if(NULL == ret) {
			ERROR(("Out of memory"));
			return NULL;
		}
	} else {
		for(ptr = (char *)str; 0 != *ptr; ++ptr) {
			if('\'' == *ptr) {
				nr_t++;
			}
		}
		if(strlen(str) + nr_t + 1 > size) {
			ret = (char *)malloc(strlen(str) + nr_t  + 1);
			if(NULL == ret) {
				ERROR(("Out of memory"));
				return NULL;
			}
		} else {
			ret = buf;
		}
	}
	*ret = 0;
	for(ptr = ret; 0 != *str; str++) {
		switch(*str) {
		case '\'':
			*ptr = '\'';
			*(++ptr) = '\'';
			++ptr;
			*ptr = 0;
			break;
		default:
			*ptr = *str;
			*(++ptr) = 0;
			break;
		}
	}
	return ret;
}

int tagal_new(tagal_t **tagal, db_new_f db_new, 
	const char *arg, int if_create, mempool_t *pool)
{
	int rc;
	assert(NULL != tagal);
	(*tagal) = (tagal_t *)mempool_allocate(pool, sizeof(tagal_t));
	if(NULL == (*tagal)) {
		ERROR(("Out of memory"));
		return TAGAL_OUTOFMEM;
	}
	(*tagal)->pool = pool;
	(*tagal)->db = NULL;
	if(rc = libtagal_db_new(&((*tagal)->db), db_new, pool))
		return rc;
	return libtagal_db_connect((*tagal)->db, arg, if_create);
}

int tagal_release(tagal_t *tagal)
{
	if(NULL == tagal)
		return 0;
	if(NULL != tagal->db)
		libtagal_db_release(tagal->db);
	mempool_free(tagal->pool, tagal);
	return 0;
}

int tagal_data_iter_new(tagal_t *tagal, tagal_data_iter_t **iter) 
{
	assert(NULL != tagal && NULL != iter);
	(*iter) = (tagal_data_iter_t *)mempool_allocate(tagal->pool, 
		sizeof(tagal_data_iter_t));
	if(NULL == (*iter)) {
		ERROR(("Out of memory"));
		return TAGAL_OUTOFMEM;
	}
	memset((*iter), 0, sizeof(tagal_data_iter_t));
	(*iter)->tagal = tagal;
	(*iter)->pool= tagal->pool;
	return libtagal_db_result_new(tagal->db, &((*iter)->result));
}

int tagal_tag_iter_new(tagal_t *tagal, tagal_tag_iter_t **iter) 
{
	assert(NULL != tagal && NULL != iter);
	(*iter) = (tagal_tag_iter_t *)mempool_allocate(tagal->pool, 
		sizeof(tagal_tag_iter_t));
	if(NULL == (*iter)) {
		ERROR(("Out of memory"));
		return TAGAL_OUTOFMEM;
	}
	memset(*iter, 0, sizeof(tagal_tag_iter_t));
	(*iter)->tagal = tagal;
	(*iter)->pool= tagal->pool;
	return libtagal_db_result_new(tagal->db, &((*iter)->result));
}

int tagal_data_iter_release(tagal_data_iter_t *iter)
{
	if(NULL == iter)
		return 0;
	if(NULL != iter->result)
		libtagal_db_result_release(iter->result);
	mempool_free(iter->pool, iter);
	return 0;
}

int tagal_tag_iter_release(tagal_tag_iter_t *iter)
{
	if(NULL == iter)
		return 0;
	if(NULL != iter->result)
		libtagal_db_result_release(iter->result);
	mempool_free(iter->pool, iter);
	return 0;
}

int tagal_select_by_tags(tagal_t *tagal, 
		tagal_data_iter_t *data, 
		const char *tags)
{
	assert(NULL != tagal && NULL != data);
	char *t;
	int rc;
	char buf[DEFAULT_BUFSZ];
	t = trans_str(tags, buf, sizeof(buf));
	if(NULL == t) {
		return TAGAL_OUTOFMEM;
	}
	rc = tagaldb_select_by_tags(tagal->db, data->result, t);
	FREE_COND(t, buf);
	return rc;
}

int tagal_select_by_path(tagal_t *tagal, 
		tagal_data_iter_t *data, 
		const char *path)
{
	assert(NULL != tagal && NULL != data);
	char *t;
	int rc;
	char buf[DEFAULT_BUFSZ];
	t = trans_str(path, buf, sizeof(buf));
	if(NULL == t) {
		return TAGAL_OUTOFMEM;
	}
	rc = tagaldb_select_by_path(tagal->db, data->result, t);
	FREE_COND(t, buf);
	return rc;
}

const char *tagal_data_path(tagal_data_iter_t *data)
{
	assert(NULL != data);
	if(NULL == data->result)
		return NULL;
	return tagaldb_get_path(data->result);
}

const char *tagal_data_name(tagal_data_iter_t *data)
{
	assert(NULL != data);
	if(NULL == data->result)
		return NULL;
	return tagaldb_get_name(data->result);
}

const char *tagal_tag_tag(tagal_tag_iter_t *tag)
{
	assert(NULL != tag);
	if(NULL == tag->result)
		return NULL;
	return tagaldb_get_tag(tag->result);
}

int tagal_tag_del_tag(tagal_t *tagal, const char *tag)
{
	char *t;
	int rc;
	char buf[DEFAULT_BUFSZ];
	assert(NULL != tagal);
	if(NULL == tag)
		return 0;
	t = trans_str(tag, buf, sizeof(buf));
	if(NULL == t)
		return TAGAL_OUTOFMEM;
	rc = tagaldb_del_tag(tagal->db, t);
	FREE_COND(t, buf);
	return rc;
}

int tagal_data_next(tagal_data_iter_t *data)
{
	assert(NULL != data);
	if(NULL == data->result)
		return 0;
	return libtagal_db_result_next(data->result);
}

int tagal_tag_next(tagal_tag_iter_t *tag)
{
	assert(NULL != tag);
	if(NULL == tag->result)
		return 0;
	return libtagal_db_result_next(tag->result);
}

int tagal_data_get_tags(tagal_data_iter_t *data, tagal_tag_iter_t *tags)
{
	assert(NULL != data && NULL != tags);
	if(NULL == data->result || NULL == data->tagal->db 
		|| NULL == tags->result)
		return 0;
	return tagaldb_get_tags_by_fid(data->tagal->db,
			tags->result, 
			tagaldb_get_fid(data->result));

}

int tagal_data_get_tags_by_path(const char *path, tagal_tag_iter_t *tags)
{
	char *t;
	int rc;
	char buf[DEFAULT_BUFSZ];

	assert(NULL != tags && NULL != tags->result 
		&& NULL != tags->tagal && NULL != tags->tagal->db);
	if(NULL == path)
		return 0;
	t = trans_str(path, buf, sizeof(buf));
	if(NULL == t)
		return TAGAL_OUTOFMEM;
	rc = tagaldb_get_tags_by_path(tags->tagal->db, tags->result, t);
	FREE_COND(t, buf);
	return rc;
}

int tagal_data_add_tag(tagal_data_iter_t *data, const char *tag)
{
	char *t;
	int rc;
	char buf[DEFAULT_BUFSZ];
	assert(NULL != data && NULL != data->result 
		&& NULL != data->tagal && NULL != data->tagal->db);
	if(NULL == tag)
		return 0;
	t = trans_str(tag, buf, sizeof(buf));
	if(NULL == t)
		return TAGAL_OUTOFMEM;
	rc = tagaldb_add_tag_to_fid(data->tagal->db,
			tagaldb_get_fid(data->result), t);
	FREE_COND(t, buf);
	return rc;
}

int tagal_data_add_tag_to_path(tagal_t *tagal, const char *path, 
	const char *tag)
{
	char *t_path, *t_tag;
	char buf1[DEFAULT_BUFSZ];
	char buf2[DEFAULT_BUFSZ];
	int rc;
	assert(NULL != tagal && NULL != tagal->db);
	if(NULL == tag || NULL == path)
		return 0;
	t_path = trans_str(path, buf1, sizeof(buf1));
	t_tag = trans_str(tag, buf2, sizeof(buf2));
	if(NULL == t_tag || NULL == t_path)
		return TAGAL_OUTOFMEM;
	rc = tagaldb_add_tag_to_path(tagal->db, t_path, t_tag);
	FREE_COND(t_path, buf1);
	FREE_COND(t_tag, buf2);
	return rc;
}

int tagal_data_add_tags_to_path(tagal_t *tagal, const char *path, 
	const char *tag)
{
	char *t_path, *t_tag;
	char buf1[DEFAULT_BUFSZ];
	char buf2[DEFAULT_BUFSZ];
	char *ptr, *str;
	int rc;

	assert(NULL != tagal && NULL != tagal->db);
	if(NULL == tag || NULL == path)
		return 0;
	t_path = trans_str(path, buf1, sizeof(buf1));
	t_tag = trans_str(tag, buf2, sizeof(buf2));
	if(NULL == t_tag || NULL == t_path)
		return TAGAL_OUTOFMEM;

	ptr = t_tag;
	do {
		str = ptr;
		ptr = strchr(str, '\n');
		if(NULL != ptr) {
			*ptr = 0;
			for(ptr++; '\n' == *ptr && 0 != *ptr; ptr++);
		}

		TRACE(("add %s to %s", t_path, str));
		rc = tagaldb_add_tag_to_path(tagal->db, t_path, str);
	} while(NULL != ptr && 0 != *ptr);

	FREE_COND(t_path, buf1);
	FREE_COND(t_tag, buf2);
}

int tagal_data_del_tag(tagal_data_iter_t *data, const char *tag)
{
	char *t;
	int rc;
	char buf[DEFAULT_BUFSZ];
	assert(NULL != data && NULL != data->result
		&& NULL != data->tagal && NULL != data->tagal->db);
	if(NULL == tag)
		return 0;
	t = trans_str(tag, buf, sizeof(buf));
	if(NULL == t)
		return TAGAL_OUTOFMEM;
	rc = tagaldb_del_tag_to_fid(data->tagal->db, 
		tagaldb_get_fid(data->result),
		t);
	FREE_COND(t, buf);
	return rc;
}

int tagal_data_del_tag_by_path(tagal_t *tagal, const char *path, 
	const char *tag)
{
	char *t_path, *t_tag;
	int rc;
	char buf1[DEFAULT_BUFSZ];
	char buf2[DEFAULT_BUFSZ];
	assert(NULL != tagal && NULL != tagal->db);
	if(NULL == path || NULL == tag)
		return 0;
	t_path = trans_str(path, buf1, sizeof(buf1));
	t_tag = trans_str(tag, buf2, sizeof(buf2));
	if(NULL == t_tag || NULL == t_path)
		return TAGAL_OUTOFMEM;
	rc = tagaldb_del_tag_to_path(tagal->db, t_path, t_tag);
	FREE_COND(t_path, buf1);
	FREE_COND(t_tag, buf2);
	return rc;
}

int tagal_data_del_data(tagal_data_iter_t *data)
{
	assert(NULL != data && NULL != data->result
		&& NULL != data->tagal && NULL != data->tagal->db);
	return tagaldb_del_file_by_fid(data->tagal->db,
		tagaldb_get_fid(data->result));
}

int tagal_data_del_by_path(tagal_t *tagal, const char *path)
{
	char *t;
	char buf[DEFAULT_BUFSZ];
	int rc;
	assert(NULL != tagal && NULL != tagal->db);
	if(NULL == path)
		return 0;
	t = trans_str(path, buf, sizeof(buf));
	if(NULL == t)
		return TAGAL_OUTOFMEM;
	rc = tagaldb_del_file_by_path(tagal->db, t);
	FREE_COND(t, buf);
	return rc;
}

int tagal_add_data(tagal_t *tagal, const char *path, const char *name)
{
	char *t_path, *t_name;
	int rc;
	char buf1[DEFAULT_BUFSZ];
	char buf2[DEFAULT_BUFSZ];
	assert(NULL != tagal && NULL != tagal->db);
	t_path = trans_str(path, buf1, sizeof(buf1));
	t_name = trans_str(name, buf2, sizeof(buf2));
	if(NULL == t_path || NULL == t_name)
		return TAGAL_OUTOFMEM;
	rc = tagaldb_add_file(tagal->db, t_path, t_name);
	FREE_COND(t_path, buf1);
	FREE_COND(t_name, buf2);
	return rc;
}

int tagal_get_all_data(tagal_t *tagal, tagal_data_iter_t *iter)
{
	assert(NULL != tagal && NULL != tagal->db 
		&& NULL != iter && NULL != iter->result);
	return tagaldb_get_all_files(tagal->db, iter->result);
}

int tagal_get_all_tags(tagal_t *tagal, tagal_tag_iter_t *iter)
{
	assert(NULL != tagal && NULL != tagal->db 
		&& NULL != iter && NULL != iter->result);
	return tagaldb_get_all_tags(tagal->db, iter->result);
}

int tagal_data_set_name(tagal_data_iter_t *data, const char *name)
{
	char *t;
	char buf[DEFAULT_BUFSZ];
	int rc;
	assert(NULL != data && NULL != data->result
		&& NULL != data->tagal && NULL != data->tagal->db);
	t = trans_str(name, buf, sizeof(buf));
	if(NULL == t)
		return TAGAL_OUTOFMEM;
	
	rc = tagaldb_rename(data->tagal->db,
		tagaldb_get_fid(data->result), t);
	FREE_COND(t, buf);
	return rc;
}

int tagal_data_set_path(tagal_data_iter_t *data, const char *path)
{
	char *t;
	char buf[DEFAULT_BUFSZ];
	int rc;
	assert(NULL != data && NULL != data->result
		&& NULL != data->tagal && NULL != data->tagal->db);
	t = trans_str(path, buf, sizeof(buf));
	rc = tagaldb_repath(data->tagal->db,
		tagaldb_get_fid(data->result), t);
	FREE_COND(t, buf);
	return rc;
}

