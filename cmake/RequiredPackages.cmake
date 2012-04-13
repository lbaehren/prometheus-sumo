
## ==============================================================================
##
##  Apache configuration
##
## ==============================================================================

add_custom_target (apache_enable_modes
  COMMAND a2enmod rewrite
  COMMAND a2enmod proxy_balancer
  COMMAND a2enmod proxy_http
  COMMAND /etc/init.d/apache2 restart
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
  COMMENT "Enabling Apache modes ..."
  )
