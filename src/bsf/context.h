/*
 * Copyright (C) 2019 by Sukchan Lee <acetcom@gmail.com>
 *
 * This file is part of Open5GS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef BSF_CONTEXT_H
#define BSF_CONTEXT_H

#include "ogs-sbi.h"
#include "ogs-app.h"

#include "timer.h"
#include "bsf-sm.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int __bsf_log_domain;

#undef OGS_LOG_DOMAIN
#define OGS_LOG_DOMAIN __bsf_log_domain

typedef struct bsf_context_s {
    OpenAPI_nf_type_e   nf_type;

    ogs_hash_t      *supi_hash;     /* hash table (SUPI) */
    ogs_hash_t      *ipv4_hash;     /* hash table (IPv4 Address) */
    ogs_hash_t      *ipv6_hash;     /* hash table (IPv6 Address) */

    ogs_list_t      sess_list;
} bsf_context_t;

#define BSF_NF_INSTANCE_CLEAR(_cAUSE, _nFInstance) \
    do { \
        ogs_assert(_nFInstance); \
        if ((_nFInstance)->reference_count == 1) { \
            ogs_info("[%s] (%s) NF removed", (_nFInstance)->id, (_cAUSE)); \
            bsf_nf_fsm_fini((_nFInstance)); \
        } else { \
            /* There is an assocation with other context */ \
            ogs_info("[%s:%d] (%s) NF suspended", \
                    _nFInstance->id, _nFInstance->reference_count, (_cAUSE)); \
            OGS_FSM_TRAN(&_nFInstance->sm, bsf_nf_state_de_registered); \
            ogs_fsm_dispatch(&_nFInstance->sm, NULL); \
        } \
        ogs_sbi_nf_instance_remove(_nFInstance); \
    } while(0)

typedef struct bsf_sess_s bsf_sess_t;

typedef struct bsf_sess_s {
    ogs_sbi_object_t sbi;

    char *binding_id;

    ogs_s_nssai_t s_nssai;
    char *dnn;

} bsf_sess_t;

void bsf_context_init(void);
void bsf_context_final(void);
bsf_context_t *bsf_self(void);

int bsf_context_parse_config(void);

bsf_sess_t *bsf_sess_add_by_snssai_and_dnn(ogs_s_nssai_t *s_nssai, char *dnn);
void bsf_sess_remove(bsf_sess_t *sess);
void bsf_sess_remove_all(void);

bsf_sess_t *bsf_sess_find_by_snssai_and_dnn(ogs_s_nssai_t *s_nssai, char *dnn);
bsf_sess_t *bsf_sess_find_by_binding_id(char *binding_id);

void bsf_sess_select_nf(bsf_sess_t *sess, OpenAPI_nf_type_e nf_type);

#ifdef __cplusplus
}
#endif

#endif /* BSF_CONTEXT_H */
