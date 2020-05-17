PHP_ARG_ENABLE(php_stemmer_short, enable php_stemmer_short extension,  
[  --enable-php_stemmer_short           Enable php_stemmer_short extension])

PHP_REQUIRE_CXX()
PHP_NEW_EXTENSION(php_stemmer_short, ext_php_stemmer_short.cpp, $ext_shared)
EXTRA_LDFLAGS=libstemmer.o
PHP_SUBST(COUNTER_SHARED_LIBADD)