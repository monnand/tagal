#include "dbinterface.h"
#include <stdlib.h>
#include <string.h>

//#define DEBUG_TRACE
#define DEBUG_ERROR
#include "error.h"

int libtagal_db_new(libtagal_db_t **tagal, db_new_f db_new, mempool_t *pool)
{
	assert(NULL != tagal && NULL != db_new);
	(*tagal) = (libtagal_db_t *)mempool_allocate(pool, sizeof(libtagal_db_t));
	memset(*tagal, 0, sizeof(libtagal_db_t));
	(*tagal)->pool = pool;
	return db_new(*tagal);
}

int libtagal_db_connect(libtagal_db_t *tagal, const char *arg, int if_create)
{
	assert(NULL != tagal && NULL != tagal->db_init);
	return tagal->db_init(&(tagal->db_data), arg, if_create);
}

int libtagal_db_release(libtagal_db_t *tagal)
{
	if(NULL == tagal)
		return 0;
	if(NULL == tagal->db_release)
		return 0;
	tagal->db_release(tagal->db_data);
	mempool_free(tagal->pool, tagal);
	return 0;
}

int libtagal_db_get_result(libtagal_db_t *tagal, libtagal_db_result_t **result)
{
	assert(NULL != tagal && NULL != result 
		&& NULL != tagal->db_result_new
		&& NULL != tagal->db_get_result);
	(*result) = (libtagal_db_result_t *)mempool_allocate(tagal->pool, 
			sizeof(libtagal_db_result_t));
	if(NULL == (*result)) {
		ERROR(("Out of memory"));
		return DBERR_OUTOF_MEM;
	}
	memset(*result, 0, sizeof(libtagal_db_result_t));
	(*result)->libtagal = tagal;
	(*result)->pool = tagal->pool;
	tagal->db_result_new((*result));
	return tagal->db_get_result(tagal->db_data, &((*result)->db_result));
}

int libtagal_db_exec_result(libtagal_db_t *tagal, 
		libtagal_db_result_t *result,
		const char *sql)
{
	int rc;
	if(NULL != result->db_result) {
		if(rc = result->db_release_result(result->db_result)) 
			return rc;
	}
	if(rc = tagal->db_sql_exec(tagal->db_data, sql))
		return rc;
	return tagal->db_get_result(tagal->db_data, &(result->db_result));
}

int libtagal_db_result_new(libtagal_db_t *tagal, libtagal_db_result_t **result)
{
	assert(NULL != tagal && NULL != result 
		&& NULL != tagal->db_result_new
		&& NULL != tagal->db_get_result);
	(*result) = (libtagal_db_result_t *)mempool_allocate(tagal->pool, 
			sizeof(libtagal_db_result_t));
	if(NULL == (*result)) {
		ERROR(("Out of memory"));
		return DBERR_OUTOF_MEM;
	}
	(*result)->libtagal = tagal;
	(*result)->pool = tagal->pool;
	(*result)->db_result = NULL;
	memset(*result, 0, sizeof(libtagal_db_result_t));
	return tagal->db_result_new((*result));
}

int libtagal_db_sql_exec(libtagal_db_t *tagal, const char *sql)
{
	assert(NULL != tagal && NULL != sql
		&& NULL != tagal->db_sql_exec);
	return tagal->db_sql_exec(tagal->db_data, sql);
}

int libtagal_db_result_release(libtagal_db_result_t *result)
{
	int rc;
	if(NULL == result)
		return 0;
	if(NULL == result->db_result) {
		mempool_free(result->pool, result);
		return 0;
	}
	if(rc = result->db_release_result(result->db_result)) {
		TRACE(("return %d", rc));
		return rc;
	}
	mempool_free(result->pool, result);
	return 0;
}

int libtagal_db_result_next(libtagal_db_result_t *result)
{
	return result->db_next_row(result->db_result);
}

int libtagal_db_result_column_int(libtagal_db_result_t *result, int col)
{
	return result->db_column_int(result->db_result, col);
}

const unsigned char *libtagal_db_result_column_text(
		libtagal_db_result_t *result, 
		int col)
{
	return result->db_column_text(result->db_result, col);
}

int libtagal_db_exec_noresult(libtagal_db_t *tagal, const char *sql)
{
	libtagal_db_result_t result;
	int rc;
	if(rc = tagal->db_result_new(&result))
		return rc;
	if(rc = tagal->db_sql_exec(tagal->db_data, sql))
		return rc;
	if(rc = tagal->db_get_result(tagal->db_data, &(result.db_result)))
		return rc;
	while((rc = result.db_next_row(result.db_result)) == DB_MORE_DATA);
	result.db_release_result(result.db_result);
	return rc;
}

