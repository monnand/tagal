#include "db_sqlite_impl.h"
#include "db_sqlite.h"
#include "global.h"
#include <stdio.h>
#include <stdlib.h>

#define DEBUG_ERROR	1
//#define DEBUG_TRACE	1

#include "error.h"

int libtagal_sqlite(libtagal_db_t *tagal)
{
	tagal->db_init = tagal_db_sqlite_init;
	tagal->db_sql_exec = tagal_db_sqlite_sql_exec;
	tagal->db_result_new = tagal_db_sqlite_result_new;
	tagal->db_get_result = tagal_db_sqlite_get_result;
	tagal->db_release = tagal_db_sqlite_release;
	tagal->db_strerror = tagal_db_sqlite_strerror;
	return 0;
}
int tagal_db_sqlite_result_new(libtagal_db_result_t *result)
{
	result->db_next_row = tagal_db_sqlite_next_row;
	result->db_release_result = tagal_db_sqlite_release_result;
	result->db_column_int = tagal_db_sqlite_column_int;
	result->db_column_text = tagal_db_sqlite_column_text;
	TRACE(("xxx fun addr %x %x", result->db_release_result,
		tagal_db_sqlite_release_result));
	return 0;
}

int tagal_db_sqlite_init(void **lite, const char *arg)
{
	tagal_db_sqlite_t *h;
	char *str;
	int rc;
	/* XXX yes, it's not very pretty. But a compromised way to
	 * reduce nr calls to malloc. A better way is use a memory pool.
	 */
	h = (tagal_db_sqlite_t *)malloc(sizeof(tagal_db_sqlite_t) 
			+ strlen(arg) + 1);
	if(NULL == h) {
		ERROR(("Out of memory"));
		return DBERR_OUTOF_MEM;
	}
	memset(h, 0, sizeof(tagal_db_sqlite_t) + strlen(arg) + 1);

	str = (char *)h + sizeof(tagal_db_sqlite_t);
	strcpy(str, arg);
	h->filename = str;
	if(rc = sqlite3_open(arg, &(h->db))){
		ERROR(("sqlite connect error. errno: %d", rc));
		return DBERR_CONN_ERR;
	}
	h->stmt = NULL;
	*lite = h;

	TRACE(("init success. use sqlite db: %s", h->filename));
	return 0;
}

int tagal_db_sqlite_sql_exec(void *lite, const char *sql)
{
	int rc;
	const char *ptr;
	tagal_db_sqlite_t *l = (tagal_db_sqlite_t *)lite;
	assert(NULL != lite && NULL != sql && NULL != l->db);
	if(NULL != l->stmt) {
		sqlite3_finalize(l->stmt);
	}
	if(rc = sqlite3_prepare_v2(l->db, sql, 
		strlen(sql) + 1, &(l->stmt), &ptr)) {
		ERROR(("sqlite exec sql '%s' error. errno: %d", sql, rc));
		return DBERR_SQL_SYNTAX;
	}
	TRACE(("ready to exec sql %s", sql));

	return 0;
}

int tagal_db_sqlite_release(void *lite)
{
	if(NULL == lite)
		return 0;
	tagal_db_sqlite_t *l = (tagal_db_sqlite_t *)lite;
	if(NULL == l->db)
		return 0;
	if(NULL != l->stmt)  {
		sqlite3_finalize(l->stmt);
	}
	sqlite3_close(l->db);
	free(l);
	return 0;
}

int tagal_db_sqlite_get_result(void *lite, void **result)
{
	assert(NULL != lite && NULL != result);
	tagal_db_sqlite_t *l = (tagal_db_sqlite_t *)lite;
	tagal_db_sqlite_result_t *r;
	r = (tagal_db_sqlite_result_t *)malloc(
			sizeof(tagal_db_sqlite_result_t));
	if(NULL == r) {
		ERROR(("Out of memory"));
		return DBERR_OUTOF_MEM;
	}
	r->stmt = l->stmt;
	l->stmt = NULL;
	r->nr_col = sqlite3_column_count(r->stmt);
	*result = r;
	return 0;
}

int tagal_db_sqlite_next_row(void *result)
{
	tagal_db_sqlite_result_t *r = (tagal_db_sqlite_result_t *)result;
	switch(sqlite3_step(r->stmt)) {
	case SQLITE_ROW:
		return DB_MORE_DATA;
	case SQLITE_DONE:
		return 0;
	}
	ERROR(("sqlite"));
	return DBERR_ERROR;
}

int tagal_db_sqlite_release_result(void *result)
{
	tagal_db_sqlite_result_t *r = (tagal_db_sqlite_result_t *)result;
	sqlite3_finalize(r->stmt);
	return 0;
}

int tagal_db_sqlite_column_int(void *result, int col)
{
	tagal_db_sqlite_result_t *r = (tagal_db_sqlite_result_t *)result;
	if(col < 0 || col >= r->nr_col) {
		ERROR(("out of range"));
		return 0;
	}
	return sqlite3_column_int(r->stmt, col);
}

const unsigned char *tagal_db_sqlite_column_text(void *result, int col)
{
	tagal_db_sqlite_result_t *r = (tagal_db_sqlite_result_t *)result;
	if(col < 0 || col >= r->nr_col) {
		ERROR(("out of range"));
		return NULL;
	}
	return sqlite3_column_text(r->stmt, col);
}

const char *tagal_db_sqlite_strerror(void *lite)
{
	tagal_db_sqlite_t *l = (tagal_db_sqlite_t *)lite;
	return sqlite3_errmsg(l->db);
}

#if 0
int main()
{
	void *lite;
	tagal_db_sqlite_init(&lite, "test.db");
	return 0;
}
#endif

