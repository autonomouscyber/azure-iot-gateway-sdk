// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <stdio.h>

#include "gateway.h"

int main(int argc, char** argv)
{
    GATEWAY_HANDLE gateway;
    if (argc != 3)
    {
        printf("usage: dynamically_add_module_sample modulesConfigFile linksConfigFile\n");
        printf("where configFile is the name of the file that contains the Gateway configuration\n");
    }
    else
    {
        if ((gateway = Gateway_Create(NULL)) == NULL)
        {
            printf("failed to create the gateway\n");
        }
        else
        {
            printf("gateway successfully created.\n");
            printf("gateway shall run until ENTER is pressed\n");

            JSON_Value *root_value_modules;
            root_value_modules = json_parse_file(argv[1]);
            char* json_content_modules = json_serialize_to_string(root_value_modules);

            int result = Gateway_UpdateFromJson(gateway, json_content_modules);
            if (result != 0)
            {
                printf("failed to update gateway from JSON.\n");
            }
            else
            {
                JSON_Value *root_value_links;
                root_value_links = json_parse_file(argv[2]);
                char* json_content_links = json_serialize_to_string(root_value_links);

                result = Gateway_UpdateFromJson(gateway, json_content_links);
                if (result != 0)
                {
                    printf("failed to update gateway from JSON.\n");
                }
                else
                {
                    if (Gateway_Start(gateway) != GATEWAY_START_SUCCESS)
                    {
                        printf("failed to start gateway.\n");
                    }
                }
            }
            
            (void)getchar();
            Gateway_Destroy(gateway);
        }
    }
    return 0;
}

