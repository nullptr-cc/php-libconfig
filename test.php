<?php

$start_ts = microtime(true);

$parsed_main = lconfig_parse("config_test/main.cfg");

$ts_0 = microtime(true);

$parsed_books = lconfig_parse("config_test/books.cfg");

$ts_1 = microtime(true);

print_r($parsed_main);
print_r($parsed_books);

printf("main parse time = %.6f\n", $ts_0 - $start_ts);
printf("books parse time = %.6f\n", $ts_1 - $ts_0);
