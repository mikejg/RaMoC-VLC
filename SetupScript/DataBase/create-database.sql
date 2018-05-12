create database ramoc;
use ramoc;
GRANT ALL ON ramoc .* TO ramocuser@localhost IDENTIFIED BY 'ramoc';
GRANT ALL ON ramoc .* TO ramocuser@'%' IDENTIFIED BY 'ramoc';

FLUSH PRIVILEGES;


