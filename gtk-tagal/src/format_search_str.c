#include "format_search_str.h"
#include <string.h>
#include <stdlib.h>

GString *format_search_str(const gchar *str)
{
	GString *fstr;
	fstr = g_string_sized_new(strlen(str) + strlen(str) >> 2);
	int is_in_qu;
	int is_trans;
	int just_a_newline;
	is_in_qu = 0;
	is_trans = 0;
	just_a_newline = 1;
	while(*str) {
		switch(*str) {
		case '\\':
			if(is_trans) {
				g_string_append_c(fstr, '\\');
				is_trans = 0;
				just_a_newline = 0;
			} else {
				is_trans = 1;
			}
			break;
		case '"':
			if(is_in_qu && is_trans) {
				g_string_append_c(fstr, '"');
				is_trans = 0;
				just_a_newline = 0;
			} else {
				if(is_in_qu) {
					is_in_qu = 0;
					g_string_append_c(fstr, '\n');
					just_a_newline = 1;
				} else if(!just_a_newline) {
					g_string_append_c(fstr, '\n');
					just_a_newline = 1;
					is_in_qu = 1;
				} else {
					is_in_qu = 1;
				}
			}
			break;
		case ' ': case '\t': case '\r': case '\n':
			if(is_in_qu) {
				g_string_append_c(fstr, *str);
				just_a_newline = 0;
			} else {
				if(!just_a_newline) {
					g_string_append_c(fstr, '\n');
					just_a_newline = 1;
				}
			}
			break;
			/*
		case '\'':
			g_string_append(fstr, "''");
			just_a_newline = 0;
			break;
			*/
		default:
			g_string_append_c(fstr, *str);
			just_a_newline = 0;
			break;
		}
		str++;
	}
	if(!just_a_newline) {
		g_string_append_c(fstr, '\n');
	}
	return fstr;
}

