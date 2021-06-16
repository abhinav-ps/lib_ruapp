#include <stdio.h>
#include "mplane_api.h"

/**
 * @This is a temp function, just to validate values
 */
void
print_val(const notification_val_t *value)
{
    if (NULL == value) {
        return;
    }

    printf("%s ", value->xpath);

    switch (value->type) {
    case CONTAINER_T:
    case CONTAINER_PRESENCE_T:
        printf("(container)");
        break;
    case LIST_T:
        printf("(list instance)");
        break;
    case STRING_T:
        printf("= %s", value->data.string_val);
        break;
    case BOOL_T:
        printf("= %s", value->data.bool_val ? "true" : "false");
        break;
    case DECIMAL64_T:
        printf("= %g", value->data.decimal64_val);
        break;
    case INT8_T:
        printf("= %" PRId8, value->data.int8_val);
        break;
    case INT16_T:
        printf("= %" PRId16, value->data.int16_val);
        break;
    case INT32_T:
        printf("= %" PRId32, value->data.int32_val);
        break;
    case INT64_T:
        printf("= %" PRId64, value->data.int64_val);
        break;
    case UINT8_T:
        printf("= %" PRIu8, value->data.uint8_val);
        break;
    case UINT16_T:
        printf("= %" PRIu16, value->data.uint16_val);
        break;
    case UINT32_T:
        printf("= %" PRIu32, value->data.uint32_val);
        break;
    case UINT64_T:
        printf("= %" PRIu64, value->data.uint64_val);
        break;
    case IDENTITYREF_T:
        printf("= %s", value->data.identityref_val);
        break;
    case INSTANCEID_T:
        printf("= %s", value->data.instanceid_val);
        break;
    case BITS_T:
        printf("= %s", value->data.bits_val);
        break;
    case BINARY_T:
        printf("= %s", value->data.binary_val);
        break;
    case ENUM_T:
        printf("= %s", value->data.enum_val);
        break;
    case LEAF_EMPTY_T:
        printf("(empty leaf)");
        break;
    default:
        printf("(unprintable)");
        break;
    }

    switch (value->type) {
    case UNKNOWN_T:
    case CONTAINER_T:
    case CONTAINER_PRESENCE_T:
    case LIST_T:
    case LEAF_EMPTY_T:
        printf("\n");
        break;
    default:
        printf("%s\n", value->dflt ? " [default]" : "");
        break;
    }
}

/**
 * @This is a temp function, just to validate values
 */
void
print_change(notification_change_oper_t op,
             notification_val_t *old_val,
             notification_val_t *new_val)
{
    switch (op) {
    case OP_CREATED:
        printf("CREATED: ");
        print_val(new_val);
        break;
    case OP_DELETED:
        printf("DELETED: ");
        print_val(old_val);
        break;
    case OP_MODIFIED:
        printf("MODIFIED: ");
        print_val(old_val);
        printf("to ");
        print_val(new_val);
        break;
    case OP_MOVED:
        printf("MOVED: %s\n", new_val->xpath);
        break;
    }
}


int
change_notification(modified_data_t *in, int count)
{
    int i = 0;
    printf("Count: %d\n", count);
    for(i = 0; i < count; i++)
    {
        print_change(in[i].oper, in[i].old_val, in[i].new_val);
    }
    return 0;
}

int
software_download(ru_software_pkg_in_t *in,
                  ru_software_pkg_out_t **out)
{
    printf("URI: %s\n", in->downlod_in.uri);
    return 0;
}

int software_install(ru_software_pkg_in_t *in,
                     ru_software_pkg_out_t **out)
{
    printf("Install from slot: %s\n", in->install_in.slot_name);
    return 0;
}

int
software_activate(ru_software_pkg_in_t *in,
                  ru_software_pkg_out_t **out)
{
    printf("Slot-name: %s\n", in->activate_in.slot_name);
    return 0;
}

int
file_upload(ru_file_mgmt_in_t *in,
            ru_file_mgmt_out_t **out)
{
    printf("Local PATH: %s\n", in->file_upload_in.local_logical_file_path);
    printf("Remote PATH: %s\n", in->file_upload_in.remote_file_path);
    return 0;
}

int
retrieve_file_list(ru_file_mgmt_in_t *in,
                   ru_file_mgmt_out_t **out)
{
    printf("Logical PATH: %s\n", in->file_retrieve_in.logical_path);
    printf("File Filter: %s\n", in->file_retrieve_in.file_name_filter);
    return 0;
}

int
file_download(ru_file_mgmt_in_t *in,
              ru_file_mgmt_out_t **out)
{
    printf("file-download rpc hit\n");
    printf("Local PATH: %s\n", in->file_download_in.local_logical_file_path);
    printf("Remote PATH: %s\n", in->file_download_in.remote_file_path);
    return 0;
}

int
start_ruapp(mpane_switch_in_t *in,
            mplane_switch_out_t **out)
{
    printf("Command Type: %d\n", in->type);
    printf("Status: %s\n", in->mplane_start_in.status);
    return 0;
}
