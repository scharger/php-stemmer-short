# PHP Snowball Stemmer extension
(Forked from https://github.com/shabbyrobe/php-stemmer)

## Version for HHVM
https://github.com/scharger/hhvm-stemmer

## Description
This PHP extension wraps the C-language version of the stemmers provided by the
snowball project. http://snowballstem.org/

## Installation:

1. 
```shell
	make
```
	
2. add "extension=php_stemmer_short.so" -> php.ini and cli.ini

3. Restart web server


## Usage:

```php   
   <?php
   echo hh_stem("spanish", "bailando");
   // Output: bail
   ?>
```
