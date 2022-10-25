#include "list.h"
#include <cli/cli.h>
#include <stdlib.h>
#include "../../../list/list.h"
#include "../../../../types/token_info.h"
#include "../../../config/constants.h"
#include "../../cli_common_helpers.h"

static char* get_algo_as_cstr(TokenHashAlgo algo) {
    switch(algo) {
    case SHA1:
        return TOTP_CONFIG_TOKEN_ALGO_SHA1_NAME;
    case SHA256:
        return TOTP_CONFIG_TOKEN_ALGO_SHA256_NAME;
    case SHA512:
        return TOTP_CONFIG_TOKEN_ALGO_SHA512_NAME;
    }

    return "UNKNOWN";
}

static uint8_t get_digits_as_int(TokenDigitsCount digits) {
    switch(digits) {
    case TOTP_6_DIGITS:
        return 6;
    case TOTP_8_DIGITS:
        return 8;
    }

    return 6;
}

void totp_cli_command_list_print_help() {
    TOTP_CLI_PRINTF("\t" TOTP_CLI_COMMAND_LIST " - list all tokens\r\n\r\n");
}

void totp_cli_command_list_handle(PluginState* plugin_state) {
    if (plugin_state->tokens_list == NULL) {
        TOTP_CLI_PRINTF("There are no tokens");
        return;
    }

    ListNode* node = plugin_state->tokens_list;

    TOTP_CLI_PRINTF("+-----+-----------------------------+--------+--------+\r\n");
    TOTP_CLI_PRINTF("| %-*s | %-*s | %-*s | %-s |\r\n", 3, "#", 27, "Name", 6, "Algo", "Digits");
    TOTP_CLI_PRINTF("+-----+-----------------------------+--------+--------+\r\n");
    uint16_t index = 1;
    while(node != NULL) {
        TokenInfo* token_info = (TokenInfo* )node->data;
        token_info_get_digits_count(token_info);
        TOTP_CLI_PRINTF("| %-3" PRIu16 " | %-27.27s | %-6s | %-6" PRIu8 " |\r\n", index, token_info->name, get_algo_as_cstr(token_info->algo), get_digits_as_int(token_info->digits));
        node = node->next;
        index++;
    }
    TOTP_CLI_PRINTF("+-----+-----------------------------+--------+--------+\r\n");
}