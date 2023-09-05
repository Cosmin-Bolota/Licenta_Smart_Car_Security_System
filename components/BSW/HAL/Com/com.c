#include "BSW/HAL/Com/com.h"

#include "BSW/MCAL/WIFI/wifi.h"

static const char *TAG = "HAL COM";

extern char g_cGETBuffer[100];
extern char g_cPOSTBuffer[100];

extern bool g_bGETRequestInProcess;
extern bool g_bPOSTRequestInProcess;

/* Assign some default values to GET buffer */
COM_GET_struct g_GET_DataStructure =
{ .u8Temperature = 27, .u8Humidity = 50, .u8Comfort = 24, .bIsLocked = true,
		.bIsOccupied = false, .u8Distance = 0, .u16PhotoRes = 50};

/* Assign some default values to POST buffer */
COM_POST_struct g_POST_DataStructure =
{ .bButtonFan = false, .bButtonTrunk = false, .bButtonHeadlights = false,
		.bButtonAmbientalLights = false, .bButtonFindMyCar = false,
		.bButtonHonk = false, .bButtonSecurity = false, .bButtonDoorLock = false,
		.u8UserTemperature = 27};

/*******************************************************************************
 *  Function name    : COM_vProcessGetRequest
 *
 *  Description      : Update the GET buffer
 *
 *  List of arguments: -
 *
 *  Return value     : -
 *
 *******************************************************************************/
void COM_vProcessGetRequest(void)
{
	if (g_bGETRequestInProcess)
	{
		char dataBuffer[7];

		sprintf(dataBuffer, "%d", g_GET_DataStructure.u8Temperature);
		/* First string to be copied to buffer */
		strcpy(g_cGETBuffer, dataBuffer);
		strcat(g_cGETBuffer, "\n");

		sprintf(dataBuffer, "%d", g_GET_DataStructure.u8Humidity);
		strcat(g_cGETBuffer, dataBuffer);
		strcat(g_cGETBuffer, "\n");

		sprintf(dataBuffer, "%d", g_GET_DataStructure.u8Comfort);
		strcat(g_cGETBuffer, dataBuffer);
		strcat(g_cGETBuffer, "\n");

		sprintf(dataBuffer, "%d", g_GET_DataStructure.u16PhotoRes);
		strcat(g_cGETBuffer, dataBuffer);
		strcat(g_cGETBuffer, "\n");

		if (g_GET_DataStructure.bIsLocked)
		{
			strcat(g_cGETBuffer, "locked\n");
		}
		else
		{
			strcat(g_cGETBuffer, "unlocked\n");
		}

		if (g_GET_DataStructure.bIsOccupied)
		{
			strcat(g_cGETBuffer, "occupied\n");
		}
		else
		{
			strcat(g_cGETBuffer, "unoccupied\n");
		}

		sprintf(dataBuffer, "%d", g_GET_DataStructure.u8Distance);
		strcat(g_cGETBuffer, dataBuffer);
		strcat(g_cGETBuffer, "\n");

		g_bGETRequestInProcess = false;
	}
}

/*******************************************************************************
 *  Function name    : COM_vProcessPostRequest
 *
 *  Description      : Process the POST buffer
 *
 *  List of arguments: -
 *
 *  Return value     : -
 *
 *******************************************************************************/
void COM_vProcessPostRequest(void)
{
	if (g_bPOSTRequestInProcess)
	{
		if (strcmp(g_cPOSTBuffer, "button=Fan+On") == 0)
		{
			g_POST_DataStructure.bButtonFan = true;
			ESP_LOGI(TAG, "button=Fan+On");
		}
		else if (strcmp(g_cPOSTBuffer, "button=Fan+Off") == 0)
		{
			g_POST_DataStructure.bButtonFan = false;
			ESP_LOGI(TAG, "button=Fan+Off");
		}

		else if (strcmp(g_cPOSTBuffer, "button=Open+Trunk") == 0)
		{
			g_POST_DataStructure.bButtonTrunk = true;
			ESP_LOGI(TAG, "button=Open+Trunk");
		}
		else if (strcmp(g_cPOSTBuffer, "button=Close+Trunk") == 0)
		{
			g_POST_DataStructure.bButtonTrunk = false;
			ESP_LOGI(TAG, "button=Close+Trunk");
		}

		else if (strcmp(g_cPOSTBuffer, "button=Head+Lights+On") == 0)
		{
			g_POST_DataStructure.bButtonHeadlights = true;
			ESP_LOGI(TAG, "button=Head+Lights+On");
		}
		else if (strcmp(g_cPOSTBuffer, "button=Head+Lights+Off") == 0)
		{
			g_POST_DataStructure.bButtonHeadlights = false;
			ESP_LOGI(TAG, "button=Head+Lights+Off");
		}

		else if (strcmp(g_cPOSTBuffer, "button=Ambiental+Lights+On") == 0)
		{
			g_POST_DataStructure.bButtonAmbientalLights = true;
			ESP_LOGI(TAG, "button=Ambiental+Lights+On");
		}
		
		else if (strcmp(g_cPOSTBuffer, "button=Ambiental+Lights+Off") == 0)
		{
			g_POST_DataStructure.bButtonAmbientalLights = false;
			ESP_LOGI(TAG, "button=Ambiental+Lights+Off");
		}

		else if (strcmp(g_cPOSTBuffer, "button=Find+My+Car") == 0)
		{
			g_POST_DataStructure.bButtonFindMyCar = true;
			ESP_LOGI(TAG, "button=Find+My+Car");
		}

		else if (strcmp(g_cPOSTBuffer, "button=Stop+Find+My+Car") == 0)
		{
			g_POST_DataStructure.bButtonFindMyCar = false;
			ESP_LOGI(TAG, "button=Stop+Find+My+Car");
		}

		else if (strcmp(g_cPOSTBuffer, "button=Honk+On") == 0)
		{
			g_POST_DataStructure.bButtonHonk = true;
			ESP_LOGI(TAG, "button=Honk+On");
		}

		else if (strcmp(g_cPOSTBuffer, "button=Honk+Off") == 0)
		{
			g_POST_DataStructure.bButtonHonk = false;
			ESP_LOGI(TAG, "button=Honk+Off");
		}

		else if (strcmp(g_cPOSTBuffer, "button=Security+On") == 0)
		{
			g_POST_DataStructure.bButtonSecurity = true;
			ESP_LOGI(TAG, "button=Security+On");
		}
		else if (strcmp(g_cPOSTBuffer, "button=Security+Off") == 0)
		{
			g_POST_DataStructure.bButtonSecurity = false;
			ESP_LOGI(TAG, "button=Security+Off");
		}

		else if (strcmp(g_cPOSTBuffer, "button=Unlock+Door") == 0)
		{
			g_POST_DataStructure.bButtonDoorLock = false;
			ESP_LOGI(TAG, "button=Unlock+Door");
		}
		else if (strcmp(g_cPOSTBuffer, "button=Lock+Door") == 0)
		{
			g_POST_DataStructure.bButtonDoorLock = true;
			ESP_LOGI(TAG, "button=Lock+Door");
		}

		else if (strstr(g_cPOSTBuffer, "user-temp=") != NULL)
		{
			g_POST_DataStructure.u8UserTemperature = (g_cPOSTBuffer[10] - '0') * 10;
			g_POST_DataStructure.u8UserTemperature += g_cPOSTBuffer[11] - '0';
			ESP_LOGI(TAG, "user-temp=%c%c",g_cPOSTBuffer[10], g_cPOSTBuffer[11]);
		}

		else
		{
			ESP_LOGE(TAG, "Not known");
		}

		g_bPOSTRequestInProcess = false;
	}
}

/*******************************************************************************
 *  Function name    : COM_vTaskProcessServer
 *
 *  Description      : Process POST/GET requests
 *
 *  List of arguments: -
 *
 *  Return value     : -
 *
 *******************************************************************************/
void COM_vTaskProcessServer(void)
{
	COM_vProcessGetRequest();
	COM_vProcessPostRequest();
}
