

/**
 * Securing PII information
 *
 * The best security is a lack of access. This module depends on correct privleges being set for the database users. In this case, proper Drupal Database security uses one DB user for the public-facing site and another DB user for the private-facing site.

  * DATABASE & DRUPAL CONFIG (NOT HANDLED BY THIS MODULE)

   ** The public-facing user has global privleges on the database for everything except 'SELECT' on all tables. Then, this user is granted 'SELECT' privileges on all tables except for those with prefix 'private_'.

   ** The private-facing user has ALL global mysql privleges. For the Drupal configuration, the prefix 'private_' will be added to the database settings in 'settings.php' for the PII tables/fields.

   ** Set an 'environment variable' (refered to henceforth as 'ENV') to identify each site/server to Drupal (ie. prod, test, dev, etc.).


  * WHAT THIS MODULE DOES

    ** On the public-facing side -- Using this module, if 'ENV' indicates a public-facing site then in hook_node_insert/update then we will use the MySQL insert-only privileges to insert the PII data into the 'private_' tables with a special query. Then, also, the PII values will be unset and reset as '***' or '000' and insert/updated as the node information for the public-facing website.

    ** On the private-facing side -- If the 'ENV' variable indicates private-0facing then the insert/update action allows hook_node_insert/update to work as normal and then also insert/updates the same records with mock information (ie. '***' or '000') in the NON-'private_' tables to be used by the public-facing Drupal.

 *
 */

 INSTALL user in Mysql

> CREATE USER 'pubuser'@'localhost' IDENTIFIED BY  '***';
> GRANT USAGE ON * . * TO  'pubuser'@'localhost' IDENTIFIED BY  '***' WITH MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0 ;
> GRANT CREATE , CREATE TEMPORARY TABLES , LOCK TABLES ON  `emergingfirms\_start` . * TO  'pubuser'@'localhost';

** REPEAT FOR ALL TABLES
[SELECT, INSERT, UPDATE, DELETE, DROP, REFERENCES, INDEX, ALTER]
GRANT SELECT ON emergingfirms_start.trigger_assignments to 'pubuser'@'localhost';
GRANT INSERT ON emergingfirms_start.trigger_assignments to 'pubuser'@'localhost';
GRANT UPDATE ON emergingfirms_start.trigger_assignments to 'pubuser'@'localhost';
GRANT DELETE ON emergingfirms_start.trigger_assignments to 'pubuser'@'localhost';
GRANT DROP ON emergingfirms_start.trigger_assignments to 'pubuser'@'localhost';
GRANT REFERENCES ON emergingfirms_start.trigger_assignments to 'pubuser'@'localhost';
GRANT INDEX ON emergingfirms_start.trigger_assignments to 'pubuser'@'localhost';
GRANT ALTER ON emergingfirms_start.trigger_assignments to 'pubuser'@'localhost';
