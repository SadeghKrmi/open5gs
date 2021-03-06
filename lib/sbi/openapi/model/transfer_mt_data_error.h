/*
 * transfer_mt_data_error.h
 *
 *
 */

#ifndef _OpenAPI_transfer_mt_data_error_H_
#define _OpenAPI_transfer_mt_data_error_H_

#include <string.h>
#include "../external/cJSON.h"
#include "../include/list.h"
#include "../include/keyValuePair.h"
#include "../include/binary.h"
#include "invalid_param.h"
#include "problem_details.h"
#include "transfer_mt_data_add_info.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OpenAPI_transfer_mt_data_error_s OpenAPI_transfer_mt_data_error_t;
typedef struct OpenAPI_transfer_mt_data_error_s {
    char *type;
    char *title;
    int status;
    char *detail;
    char *instance;
    char *cause;
    OpenAPI_list_t *invalid_params;
    char *supported_features;
    char *target_scp;
    int max_waiting_time;
} OpenAPI_transfer_mt_data_error_t;

OpenAPI_transfer_mt_data_error_t *OpenAPI_transfer_mt_data_error_create(
    char *type,
    char *title,
    int status,
    char *detail,
    char *instance,
    char *cause,
    OpenAPI_list_t *invalid_params,
    char *supported_features,
    char *target_scp,
    int max_waiting_time
    );
void OpenAPI_transfer_mt_data_error_free(OpenAPI_transfer_mt_data_error_t *transfer_mt_data_error);
OpenAPI_transfer_mt_data_error_t *OpenAPI_transfer_mt_data_error_parseFromJSON(cJSON *transfer_mt_data_errorJSON);
cJSON *OpenAPI_transfer_mt_data_error_convertToJSON(OpenAPI_transfer_mt_data_error_t *transfer_mt_data_error);
OpenAPI_transfer_mt_data_error_t *OpenAPI_transfer_mt_data_error_copy(OpenAPI_transfer_mt_data_error_t *dst, OpenAPI_transfer_mt_data_error_t *src);

#ifdef __cplusplus
}
#endif

#endif /* _OpenAPI_transfer_mt_data_error_H_ */

