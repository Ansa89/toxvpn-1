#ifndef VPN_H
#define VPN_H

#include "tox.h"
#include <netinet/ip.h>
#ifdef __cplusplus
extern "C" {
#endif

#define TOXVPN_SHAREID_SIZE 16
#define TOXVPN_MTU 1300 //MAX_CRYPTO_DATA_SIZE - sizeof(struct iphdr)

#define PACKET_ID_TOXVPN_LOSSLESS_PACKET 170
#define PACKET_ID_TOXVPN_LOSSY_PACKET 210

#define TOXVPN_MEMBERSHIP_ACCEPT 1
#define TOXVPN_MEMBERSHIP_DISCARD 2

#define TOXVPN_FRIENDID_INVALID UINT32_MAX
#define TOXVPN_FRIENDID_BROADCAST (UINT32_MAX - 2)
#define TOXVPN_FRIENDID_SELF (UINT32_MAX - 1)

#if 0
typedef struct ToxVPN {
    Tox *tox;
    void (*toxvpn_membership_request)(struct ToxVPN *toxvpn, int32_t, int32_t, uint8_t, void*);
    void *toxvpn_membership_request_data;
    void (*toxvpn_membership_response)(struct ToxVPN *toxvpn, int32_t, int32_t, uint8_t, void*);
    void *toxvpn_membership_response_data;

    BS_LIST toxvpn_interfaces;
} ToxVPN;
#endif

bool toxvpn_attach(Tox *tox);

/**
 * @brief toxvpn_new
 * @param tox
 * @param subnet
 * @param mask
 * @return on error value that less than 0, elsewise new toxvpn_id
 */
uint32_t toxvpn_new(struct Tox *tox, const char *subnet, uint8_t mask_cidr);

/**
 * @brief toxvpn_callback_membership_request
 * @param tox
 * @param callback
 *  @param pointer to Tox instance
 *  @param friendnumber friend number
 *  @param toxvpn_id ToxVPN id
 *  @param flags flags for feature use
 *  @param userdata userdata that should be passed
 * @param userdata userdata to pass in callback
 */
void toxvpn_callback_membership_request(Tox *tox, void (*callback)(Tox *tox, int32_t toxvpn_id, int32_t friendnumber, uint8_t flags, void *userdata), void *userdata);

/**
 * @brief toxvpn_callback_membership_response
 * @param tox
 * @param callback
 *  @param pointer to Tox instance
 *  @param friendnumber friend number
 *  @param toxvpn_id ToxVPN id
 *  @param flags flags for feature use
 *  @param userdata userdata that should be passed
 * @param userdata userdata to pass in callback
 */
void toxvpn_callback_membership_response(Tox *tox, void (*callback)(Tox *tox, int32_t toxvpn_id, int32_t friendnumber, uint8_t flags, void *userdata), void *userdata);
bool toxvpn_request_membership(Tox *tox, uint32_t toxvpn_id, uint32_t friendnumber, uint8_t flags);
bool toxvpn_response_membership(Tox *tox, uint32_t toxvpn_id, uint32_t friendnumber, uint8_t flags);

/**
 * @brief toxvpn_kill release vpn, free resources and shutdown link
 * @param tox
 * @param toxvpn_id
 * @return 0 on success, elsewise -1
 */
int toxvpn_kill(Tox *tox, uint32_t toxvpn_id);
int toxvpn_iterate(Tox *tox);

const char* toxvpn_self_get_ip(Tox *tox, uint32_t toxvpn_id);
const char* toxvpn_self_get_name(Tox *tox, uint32_t toxvpn_id);
bool toxvpn_self_get_shareid(Tox *tox, uint32_t toxvpn_id, uint8_t *share_id);

uint32_t toxvpn_friend_add(Tox *tox, uint32_t toxvpn_id, uint32_t friendnumber);
bool toxvpn_friend_get_list(Tox *tox, uint32_t toxvpn_id, uint32_t *list);
size_t toxvpn_friend_get_list_size(Tox *tox, uint32_t toxvpn_id);
const char* toxvpn_friend_get_ip(Tox *tox, uint32_t toxvpn_id, uint32_t friendnumber);

size_t toxvpn_get_list_size(Tox *tox);
bool toxvpn_get_list(Tox *tox, uint32_t *list);

char* toxvpn_settings_dump(const Tox *tox);
bool toxvpn_settings_load(Tox *tox, const uint8_t *data, size_t size);

#ifdef __cplusplus
}
#endif

#endif // VPN_H

