#ifndef COMPONENTS_VITAL_BSW_MCAL_WIFI_H
#define COMPONENTS_VITAL_BSW_MCAL_WIFI_H

#include "global.h"

/*
 * OBS!
 *
 * 1 - Password for WPA2-PSK should have a minimum of 8 chars
 * 2 - Do not use a while(1) loop; Use FreeRTOS system
 * 3 - Don't forget to set the max URI length to 1024
 * */

#include "esp_http_server.h"

/*******************************************************************************
 *  Function name    : WebPageGetHandler
 *
 *  Description      : Handler for the web page GET request
 *
 *  List of arguments: *req -> Pointer for the request
 *
 *  Return value     : esp_err_t
 *
 *******************************************************************************/
esp_err_t WebPageGetHandler(httpd_req_t *req);

/*******************************************************************************
 *  Function name    : DataGetHandler
 *
 *  Description      : Handler for the data GET request
 *
 *  List of arguments: *req -> Pointer for the request
 *
 *  Return value     : esp_err_t
 *
 *******************************************************************************/
esp_err_t DataGetHandler(httpd_req_t *req);

/*******************************************************************************
 *  Function name    : WebPagePostHandler
 *
 *  Description      : Handler for the web page POST request
 *
 *  List of arguments: *req -> Pointer for the request
 *
 *  Return value     : esp_err_t
 *
 *******************************************************************************/
esp_err_t WebPagePostHandler(httpd_req_t *req);

/*******************************************************************************
 *  Function name    : WebPageStart
 *
 *  Description      : Server start function
 *
 *  List of arguments: -
 *
 *  Return value     : httpd_handle_t
 *
 *******************************************************************************/
httpd_handle_t WebPageStart(void);

/*******************************************************************************
 *  Function name    : WIFI_vInit
 *
 *  Description      : Initial configuration of MCAL WIFI
 *
 *  List of arguments: *arg -> Pointer to the server handler
 *
 *  Return value     : -
 *
 *******************************************************************************/
void WIFI_vInit(void *arg);

/* WIFI credentials */
#define ESP_SSID_AP "Coxmin"
#define ESP_PASS_AP "12345678"

#endif
