/* libtagal
 * A library used to tag file 
 *
 * Copyright (C) 2007 Deng Nan <monnand@gmail.com>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MONNAND_LIBTAGAL_ERRONO_H
#define MONNAND_LIBTAGAL_ERRONO_H

#define TAGAL_SUCCESS	0
#define TAGAL_OUTOFMEM	1

/* TODO more and more compatible error code */
enum libtagal_dberrno_e {
	DBERR_SUCCESS = 0,
	DBERR_OUTOF_MEM,

	DBERR_ERROR_BEGIN,
	DBERR_CONN_ERR,
	DBERR_SQL_SYNTAX,
	DBERR_OUTOF_RANGE,
	DBERR_ERROR,
	DB_MORE_DATA,
	DBERR_ERROR_END
};

enum tagaldb_errno_e {
	TAGALDB_SUCCESS,
	TAGALDB_OUTOF_MEM,
	TAGALDB_ERROR_BEGIN = 255,
	TAGALDB_TOOMUCH_TAGS,
	TAGALDB_NO_SUCH_A_FILE,
	TAGALDB_SQL_ERROR,
	TAGALDB_ERROR_END
};

#endif /* MONNAND_LIBTAGAL_ERRONO_H */
