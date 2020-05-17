/*
   +----------------------------------------------------------------------+
   | Stemmer for HHVM                                                     |
   +----------------------------------------------------------------------+
   | 									 								  |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"

#include "ext_php_stemmer_short.h"
#include "libstemmer_c/include/libstemmer.h"

const zend_function_entry php_stemmer_short_functions[] = {
	PHP_FE(hh_stem,			NULL)
	PHP_FE(stemmer_list,	NULL)
	PHP_FE_END
};

zend_module_entry php_stemmer_short_module_entry = {
	STANDARD_MODULE_HEADER,
	"php_stemmer_short",
	php_stemmer_short_functions,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	"0.1",
	STANDARD_MODULE_PROPERTIES
};

PHP_FUNCTION(hh_stem) {
    int argc = ZEND_NUM_ARGS();
	zend_string *language = NULL;
	zend_string *word;
	zend_string *enc = NULL;
    if (zend_parse_parameters(argc, "S|S|S", &language, &word, &enc) == FAILURE) {
        return;
    }

	char *enc_v = NULL;
	if (argc == 3) {
		enc_v = enc->val;
	}

	struct sb_stemmer *sb = sb_stemmer_new(language->val, enc_v);
	if (sb == NULL) {
		sb_stemmer_delete(sb);
		RETVAL_FALSE;
	}

	const sb_symbol *result = sb_stemmer_stem(sb, (unsigned char *)word->val, word->len);
	if (result == NULL) {
		php_error_docref(NULL, E_WARNING, "stemmer failed");
		sb_stemmer_delete(sb);
		RETVAL_FALSE;
	}
	
	sb_stemmer_delete(sb);

    ZVAL_STRING(return_value, (char *)result);
}

PHP_FUNCTION(stemmer_list) {
	array_init(return_value);

	const char **list = sb_stemmer_list();
	for (const char **cur = list; *cur != NULL; cur++) {
		add_next_index_string(return_value, *cur);
	}
	return;
}


ZEND_GET_MODULE(php_stemmer_short);