#include "dbinterface.h"
#include "tagaldb.h"

#define DEBUG_ERROR
//#define DEBUG_TRACE

#include "error.h"
#include <string.h>
#include <stdlib.h>

int tagaldb_select_by_tags(libtagal_db_t *db, 
		libtagal_db_result_t *result,
		const char *tags)
{
	const char *end;
	const char *start;
	char sql[4096];
	char *sql_ptr;
	int max_len;
	int len;
	int nr_tags;

	if(NULL == tags || 0 == strlen(tags) 
		|| ('\n' == *tags && 0 == (*(tags + 1))))
		return 0;

	if(strlen(tags) > sizeof(sql) >> 2) {
		max_len = strlen(tags) + strlen(tags) >> 2;
		sql_ptr = mempool_allocate(db->pool, max_len);
	} else {
		max_len = sizeof(sql);
		sql_ptr = sql;
	}
	memset(sql_ptr, 0, max_len);

	max_len -= 20;

	len = 0;
	
	/* XXX any better sql statement ? */
	strcpy(sql_ptr, "select distinct f.id,f.name,f.path "
			"from files as f,tag_file_map as map "
			"where f.id=map.fid and "
			"(select count(tid) from "
			"tag_file_map, tags "
			"where tid=tags.id and fid=map.fid and (");
	len = strlen(sql_ptr);
	start = tags;
	nr_tags = 0;
	do {
		end = strchr(start, '\n');
		if(NULL == end) {
			if(0 != strlen(start)) {
				if(0 == nr_tags) {
					snprintf(sql_ptr + len, 
						max_len - len - 2, 
						"tag='%s'", start);
					len = strlen(sql_ptr);
					nr_tags++;
					break;
				}
				snprintf(sql_ptr + len, max_len - len - 2, 
					" or tag='%s'", start);
				len = strlen(sql_ptr);
				nr_tags++;
			}
			break;
		}
		if(1 == (end - start)) {
			start = end + 1;
			continue;
		}
		if(0 == nr_tags) {
			snprintf(sql_ptr + len, 
				MIN(max_len - len - 3, 
					strlen("tag='") + end - start + 1), 
			"tag='%s", start);
			strcat(sql_ptr, "'");
			len = strlen(sql_ptr);
			start = end + 1;
			nr_tags++;
			continue;
		}
		snprintf(sql_ptr + len, 
			MIN(max_len - len - 3, 
				strlen(" or tag='") + end - start + 1), 
			" or tag='%s", start);
		strcat(sql_ptr, "'");
		len = strlen(sql_ptr);
		start = end + 1;
		nr_tags++;
	} while(NULL != end);
	if(len >= max_len - 1)
		return TAGALDB_TOOMUCH_TAGS;
	snprintf(sql_ptr + len, 20, "))=%d order by f.name;", nr_tags);

	TRACE(("ready to exec sql: %s", sql_ptr));

	if(len = libtagal_db_exec_result(db, result, sql_ptr)) {
		if(sql_ptr != sql)
			mempool_free(db->pool, sql_ptr);
		return len;
	}
	if(sql_ptr != sql)
		mempool_free(db->pool, sql_ptr);
	return 0;
}

int tagaldb_select_by_path(libtagal_db_t *db,
		libtagal_db_result_t *result,
		const char *path)
{
	char sql[4096];
	char *sql_ptr;
	int max_len;
	
	if(NULL == path || 0 == strlen(path))
		return 0;
	if(strlen(path) >= sizeof(sql) >> 1) {
		max_len = strlen(path) + strlen(path) >> 1;
		sql_ptr = mempool_allocate(db->pool, max_len);
	} else {
		max_len = sizeof(sql);
		sql_ptr = sql;
	}

	snprintf(sql_ptr, max_len, 
		"select id, name, path from files where path='%s'", path);
	if(max_len = libtagal_db_exec_result(db, result, sql_ptr)) {
		if(sql_ptr != sql)
			mempool_free(db->pool, sql_ptr);
		return max_len;
	}
	if(sql_ptr != sql)
		mempool_free(db->pool, sql_ptr);
	return 0;
}

int tagaldb_get_fid(libtagal_db_result_t *result)
{
	return libtagal_db_result_column_int(result, 0);
}

const char *tagaldb_get_name(libtagal_db_result_t *result)
{
	return libtagal_db_result_column_text(result, 1);
}

const char *tagaldb_get_path(libtagal_db_result_t *result)
{
	return libtagal_db_result_column_text(result, 2);
}

int tagaldb_get_tags_by_fid(libtagal_db_t *db, 
	libtagal_db_result_t *result, const int id)
{
	char sql[1024];
	snprintf(sql, sizeof(sql), "select m.tid,t.tag "
		"from tag_file_map as m, tags as t "
		"where m.tid=t.id and m.fid=%d;", id);
	TRACE(("ready to exec sql: %s", sql));
	return libtagal_db_exec_result(db, result, sql);
}

int tagaldb_get_tags_by_path(libtagal_db_t *db, 
		libtagal_db_result_t *result, const char *path)
{
	char sql[1024];
	snprintf(sql, sizeof(sql), "select m.tid,t.tag "
		"from tag_file_map as m, tags as t, files as f "
		"where m.tid=t.id and m.fid=f.id and f.path='%s' "
		"order by t.tag;", path);
	TRACE(("ready to exec sql: %s", sql));
	return libtagal_db_exec_result(db, result, sql);
}

int tagaldb_get_tid(libtagal_db_result_t *result)
{
	return libtagal_db_result_column_int(result, 0);
}

const char *tagaldb_get_tag(libtagal_db_result_t *result)
{
	return libtagal_db_result_column_text(result, 1);
}

int tagaldb_add_tag_to_fid(libtagal_db_t *db, const int id, const char *tag)
{
	char sql[1024];
	libtagal_db_result_t *result;
	int rc;
	memset(sql, 0, sizeof(sql));

	/* If has this file */
	snprintf(sql, sizeof(sql), "select id from files where id=%d", id);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_sql_exec(db, sql))
		return rc;
	if(rc = libtagal_db_get_result(db, &result))
		return rc;
	if((rc = libtagal_db_result_next(result)) != DB_MORE_DATA)
		return TAGALDB_NO_SUCH_A_FILE;

	/* Insert this tag if it doesn't exist */
	snprintf(sql, sizeof(sql), "insert or ignore into tags "
		"(tag) values ('%s');", tag);
	
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_result(db, result, sql))
		return rc;
	while((rc = libtagal_db_result_next(result)) == DB_MORE_DATA);
	if(rc)
		return rc;

	/* Test if this tag has connected with this file */
	snprintf(sql, sizeof(sql), "select m.id from tag_file_map as m, "
		"tags as t where m.fid=%d and m.tid=t.id and t.tag='%s';",
		id, tag);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_result(db, result, sql))
		return rc;
	if((rc = libtagal_db_result_next(result)) == DB_MORE_DATA) {
		TRACE(("THIS PAIR AREADY EXIST!"));
		return 0;
	}
	if(rc)
		return rc;

	/* Insert this pair into tag file map */
	snprintf(sql, sizeof(sql), "insert or ignore into tag_file_map "
		"(fid, tid) select f.id, t.id from files as f, tags as t "
		"where f.id=%d and t.tag='%s';", id, tag);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_result(db, result, sql))
		return rc;
	while((rc = libtagal_db_result_next(result)) == DB_MORE_DATA);
	if(rc)
		return rc;

	/* Updata the nr reference to this tag */
	snprintf(sql, sizeof(sql), "update tags set nr_ref=nr_ref+1 "
			"where tag='%s'", tag); 
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_result(db, result, sql))
		return rc;
	while((rc = libtagal_db_result_next(result)) == DB_MORE_DATA);
	if(rc)
		return rc;

	return libtagal_db_result_release(result);
}

int tagaldb_add_tag_to_path(libtagal_db_t *db, 
		const char *path, 
		const char *tag)
{
	char sql[1024];
	libtagal_db_result_t *result;
	int rc;
	int id;
	memset(sql, 0, sizeof(sql));

	/* If has this file */
	snprintf(sql, sizeof(sql), "select id from files "
		"where path='%s'", path);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_sql_exec(db, sql))
		return rc;
	if(rc = libtagal_db_get_result(db, &result))
		return rc;
	if((rc = libtagal_db_result_next(result)) != DB_MORE_DATA)
		return rc;
	id = libtagal_db_result_column_int(result, 0);

	/* Insert this tag if it doesn't exist */
	snprintf(sql, sizeof(sql), "insert or ignore into tags "
		"(tag) values ('%s');", tag);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_result(db, result, sql))
		return rc;
	while((rc = libtagal_db_result_next(result)) == DB_MORE_DATA);
	if(rc)
		return rc;

	/* Test if this tag has connected with this file */
	snprintf(sql, sizeof(sql), "select m.id from tag_file_map as m, "
		"tags as t where m.fid=%d and m.tid=t.id and t.tag='%s';",
		id, tag);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_result(db, result, sql))
		return rc;
	if((rc = libtagal_db_result_next(result)) == DB_MORE_DATA) {
		TRACE(("THIS PAIR AREADY EXIST!"));
		return 0;
	}
	if(rc)
		return rc;

	/* Insert this pair into tag file map */
	snprintf(sql, sizeof(sql), "insert or ignore into tag_file_map "
		"(fid, tid) select f.id, t.id from files as f, tags as t "
		"where f.id=%d and t.tag='%s';", id, tag);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_result(db, result, sql))
		return rc;
	while((rc = libtagal_db_result_next(result)) == DB_MORE_DATA);
	if(rc)
		return rc;

	/* Updata the nr reference to this tag */
	snprintf(sql, sizeof(sql), "update tags set nr_ref=nr_ref+1 "
			"where tag='%s'", tag); 
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_noresult(db, sql))
		return rc;

	return libtagal_db_result_release(result);
}

int tagaldb_del_tag_to_fid(libtagal_db_t *db, const int fid, const char *tag)
{
	char sql[1024];
	int tid, id;
	int rc;
	libtagal_db_result_t *result;
	
	/* If this tag has connected with this fid */
	snprintf(sql, sizeof(sql), "select m.id,m.tid from "
		"tag_file_map as m,tags as t "
		"where m.fid=%d and m.tid=t.id and t.tag='%s';",
		fid, tag);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_sql_exec(db, sql))
		return rc;
	if(rc = libtagal_db_get_result(db, &result))
		return rc;
	if((rc = libtagal_db_result_next(result)) != DB_MORE_DATA)
		return rc;
	id = libtagal_db_result_column_int(result, 0);
	tid = libtagal_db_result_column_int(result, 1);

	/* delete this map from tag_file_map */
	snprintf(sql, sizeof(sql), "delete from tag_file_map where id=%d;", id);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_noresult(db, sql))
		return rc;

	/* refresh nr reference */
	snprintf(sql, sizeof(sql), "update tags set nr_ref=nr_ref-1 "
		"where id=%d;", tid);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_noresult(db, sql))
		return rc;

	/* delete the unrefered tags */
	snprintf(sql, sizeof(sql), "delete from tags where nr_ref <= 0");
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_noresult(db, sql))
		return rc;
	return libtagal_db_result_release(result);
}

int tagaldb_del_tag_to_path(libtagal_db_t *db, 
		const char *path, 
		const char *tag)
{
	char sql[1024];
	int tid, id;
	int rc;
	libtagal_db_result_t *result;
	
	/* If this tag has connected with this fid */
	snprintf(sql, sizeof(sql), "select m.id,m.tid from "
		"tag_file_map as m,tags as t,files as f "
		"where m.fid=f.id and m.tid=t.id and "
		"f.path='%s' and t.tag='%s';",
		path, tag);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_sql_exec(db, sql))
		return rc;
	if(rc = libtagal_db_get_result(db, &result))
		return rc;
	if((rc = libtagal_db_result_next(result)) != DB_MORE_DATA)
		return rc;
	id = libtagal_db_result_column_int(result, 0);
	tid = libtagal_db_result_column_int(result, 1);

	/* delete this map from tag_file_map */
	snprintf(sql, sizeof(sql), "delete from tag_file_map where id=%d;", id);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_noresult(db, sql))
		return rc;

	/* refresh nr reference */
	snprintf(sql, sizeof(sql), "update tags set nr_ref=nr_ref-1 "
		"where id=%d;", tid);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_noresult(db, sql))
		return rc;

	/* delete the unrefered tags */
	snprintf(sql, sizeof(sql), "delete from tags where nr_ref <= 0");
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_noresult(db, sql))
		return rc;
	return libtagal_db_result_release(result);
}

int tagaldb_del_tag(libtagal_db_t *db, const char *tag)
{
	char sql[1024];
	libtagal_db_result_t *result;
	int tid, rc;

	snprintf(sql, sizeof(sql), "select id from tags "
		"where tag='%s';", tag);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_sql_exec(db, sql))
		return rc;
	if(rc = libtagal_db_get_result(db, &result))
		return rc;
	if((rc = libtagal_db_result_next(result)) != DB_MORE_DATA)
		return rc;
	tid = libtagal_db_result_column_int(result, 0);
	libtagal_db_result_release(result);

	snprintf(sql, sizeof(sql), "delete from tag_file_map "
		"where tid=%d;", tid);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_noresult(db, sql))
		return rc;

	snprintf(sql, sizeof(sql), "delete from tags "
		"where id=%d;", tid);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_noresult(db, sql))
		return rc;
	return 0;
}

int tagaldb_add_file(libtagal_db_t *db, const char *path, const char *name)
{
	char sql[1024];
	snprintf(sql, sizeof(sql), "insert or ignore into files "
		"(path, name) values ('%s', '%s')", path, name);
	TRACE(("ready to exec sql: %s", sql));
	return libtagal_db_exec_noresult(db, sql);
}

int tagaldb_del_file_by_fid(libtagal_db_t *db, const int id)
{
	char sql[1024];
	int rc;

	/* decrease the counter of each tag connected with this file */
	snprintf(sql, sizeof(sql), "update tags set nr_ref=nr_ref-1 "
		"where id in (select t.id from tags as t, "
		"tag_file_map as m where m.fid=%d and t.id=m.tid);",
		id);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_noresult(db, sql))
		return rc;

	/* delete this file */
	snprintf(sql, sizeof(sql), "delete from files where id=%d", id);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_noresult(db, sql))
		return rc;

	/* delete all connections */
	snprintf(sql, sizeof(sql), "delete from tag_file_map "
		"where fid=%d", id);
	TRACE(("ready to exec sql: %s", sql));
	if(rc = libtagal_db_exec_noresult(db, sql))
		return rc;

	/* delete all unused tags */
	snprintf(sql, sizeof(sql), "delete from tags where nr_ref <= 0");
	TRACE(("ready to exec sql: %s", sql));
	return libtagal_db_exec_noresult(db, sql);
}

int tagaldb_del_file_by_path(libtagal_db_t *db, const char *path)
{
	char sql[1024];
	int rc;

	/* decrease the counter of each tag connected with this file */
	snprintf(sql, sizeof(sql), "update tags set nr_ref=nr_ref-1 "
		"where id in (select t.id from tags as t, files as f, "
		"tag_file_map as m where f.id=m.fid and "
		"f.path='%s' and t.id=m.tid);", path);
	if(rc = libtagal_db_exec_noresult(db, sql))
		return rc;

	/* delete all connections */
	snprintf(sql, sizeof(sql), "delete from tag_file_map "
		"where fid in (select id from files where path='%s')", path);
	if(rc = libtagal_db_exec_noresult(db, sql))
		return rc;

	/* delete this file */
	snprintf(sql, sizeof(sql), "delete from files where path='%s'", path);
	if(rc = libtagal_db_exec_noresult(db, sql))
		return rc;
	/* delete all unused tags */
	snprintf(sql, sizeof(sql), "delete from tags where nr_ref <= 0;");
	return libtagal_db_exec_noresult(db, sql);
}

int tagaldb_rename(libtagal_db_t *db, const int id, const char *name)
{
	char sql[1024];
	snprintf(sql, sizeof(sql), "updata files set name='%s' where id=%d;", 
		name, id);
	return libtagal_db_exec_noresult(db, sql);
}

int tagaldb_repath(libtagal_db_t *db, const int id, const char *path)
{
	char sql[1024];
	snprintf(sql, sizeof(sql), "updata files set path='%s' where id=%d;", 
		path, id);
	return libtagal_db_exec_noresult(db, sql);
}

int tagaldb_get_all_tags(libtagal_db_t *db, libtagal_db_result_t *result)
{
	return libtagal_db_exec_result(db, result, 
		"select id, tag from tags order by tag;");
}

int tagaldb_get_all_files(libtagal_db_t *db, libtagal_db_result_t *result)
{
	return libtagal_db_exec_result(db, result, 
		"select id, name, path from files order by name;");
}
