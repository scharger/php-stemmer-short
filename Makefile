.PHONY: php_stemmer_short

php_stemmer_short:
	cd php/libstemmer_c/ && make && mv libstemmer.o ../libstemmer.o && cd .. && phpize && ./configure --enable-php_stemmer_short && make && make install && php tests/001.php