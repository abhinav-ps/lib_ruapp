
#ifndef __MPLANE_API__
#define __MPLANE_API__

#include <inttypes.h>

#ifndef __SUBSCRIBE__
typedef int bool;
#endif

/**
 * @brief Possible types of a data element stored in the sysrepo datastore.
 */
typedef enum notification_type_e {
    /* special types that does not contain any data */
    UNKNOWN_T,

    LIST_T,
    CONTAINER_T,
    CONTAINER_PRESENCE_T,
    LEAF_EMPTY_T,
    NOTIFICATION_T,

    /* types containing some data */
    BINARY_T,
    BITS_T,
    BOOL_T,
    DECIMAL64_T,
    ENUM_T,
    IDENTITYREF_T,
    INSTANCEID_T,
    INT8_T,
    INT16_T,
    INT32_T,
    INT64_T,
    STRING_T,
    UINT8_T,
    UINT16_T,
    UINT32_T,
    UINT64_T,
    ANYXML_T,
    ANYDATA_T
} notification_type_t;

/**
 * @brief Data of an element (if applicable), properly set according to the type.
 */
typedef union notification_data_u {
    char *binary_val;
    char *bits_val;
    bool bool_val;
    double decimal64_val;
    char *enum_val;
    char *identityref_val;
    char *instanceid_val;
    int8_t int8_val;
    int16_t int16_val;
    int32_t int32_val;
    int64_t int64_val;
    char *string_val;
    uint8_t uint8_val;
    uint16_t uint16_val;
    uint32_t uint32_val;
    uint64_t uint64_val;
    char *anyxml_val;
    char *anydata_val;
} notification_data_t;

/**
 * @brief Structure that contains value of an data element stored in the sysrepo datastore.
 */
typedef struct notification_val_s {
    /** [XPath](@ref paths) (or rather path) identifier of the data element. */
    char *xpath;

    /** Type of an element. */
    notification_type_t type;

    /**
     * Flag for node with default value (applicable only for leaves).
     * It is set to TRUE only if the value was *implicitly* set by the datastore as per
     * module schema. Explicitly set/modified data element (through the sysrepo API) always
     * has this flag unset regardless of the entered value.
     */
    bool dflt;

    /** [Origin](@ref oper_ds) of the value. */
    char *origin;

    /** Data of an element (if applicable), properly set according to the type. */
    notification_data_t data;

} notification_val_t;

/**
 * @brief Type of the operation made on an item, used by changeset retrieval in ::notification_get_change_next.
 */
typedef enum notification_change_oper_e {
    OP_CREATED,   /**< The item has been created by the change. */
    OP_MODIFIED,  /**< The value of the item has been modified by the change. */
    OP_DELETED,   /**< The item has been deleted by the change. */
    OP_MOVED      /**< The item has been moved in the subtree by the change (applicable for leaf-lists and user-ordered lists). */
} notification_change_oper_t;


typedef struct modified_data
{
    notification_val_t *old_val;
    notification_val_t *new_val;
    notification_change_oper_t oper;
} modified_data_t;


/* in and out type can be same */
enum software_pkg_opcode {
    DOWNLOAD_PKG = 0,
    INSTALL_PKG,
    ACTIVATE_PKG,

    FILE_MGMT_UPLOAD,
    START
};

typedef struct download_input {
    char *uri;
} download_input_t;

typedef struct download_output {
    int status;
    uint32_t notification_timeout;
    char *error_message;
} download_output_t;

typedef struct install_input {
    char *slot_name;
    char *file_names[];
} install_input_t;

typedef struct install_output {
    int status;
    char *error_message;
} install_output_t;

typedef struct activate_input {
    char *slot_name;
} activate_input_t;

typedef struct activate_output {
    int status;
    uint32_t notification_timeout;
    char *error_message;
} activate_output_t;

typedef struct ru_software_pkg_in{
    uint8_t type;
    union {
         download_input_t downlod_in;
         install_input_t install_in;
         activate_input_t activate_in;
    };
} ru_software_pkg_in_t;

typedef struct ru_software_pkg_out{
    uint8_t type;
    union {
         download_output_t download_out;
         install_input_t install_out;
	 activate_output_t activate_out;
    };
} ru_software_pkg_out_t;

typedef struct file_upload_input {
   char *local_logical_file_path;
   char *remote_file_path; // Format:sftp://<username>@<host>[:port]/path
} file_upload_input_t;

typedef struct file_upload_output {
   int status;
   char *reject_reason;
} file_upload_output_t;


typedef struct file_retrieve_input {
   char *logical_path; // ex :  O-RAN/log, o-RAN/PM, O-RAN/transceiver
   char *file_name_filter;
} file_retrieve_input_t;

typedef struct file_retrieve_output {
   int status;
   char *reject_reason;
   char *file_list;
} file_retrieve_output_t;

typedef struct file_download_input {
   char *local_logical_file_path;
   char *remote_file_path; // Format:sftp://<username>@<host>[:port]/path
} file_download_input_t;

typedef struct file_download_output {
   int status;
   char *reject_reason;
} file_download_output_t;

typedef struct ru_file_mgmt_in{
    uint8_t type;
    union {
         file_upload_input_t file_upload_in;
	 file_retrieve_input_t file_retrieve_in;
	 file_download_input_t file_download_in;
    };
} ru_file_mgmt_in_t;

typedef struct ru_file_mgmt_out{
    uint8_t type;
    union {
         file_upload_output_t file_upload_out;
	 file_retrieve_output_t file_retrieve_out;
	 file_download_output_t file_download_out;
    };
} ru_file_mgmt_out_t;


typedef struct mplane_start_input {
    char *status;
} mplane_start_input_t;

typedef struct mplane_start_output {
   char *status;
   char *error_message;
} mplane_start_output_t;

typedef struct mplane_switch_in{
    uint8_t type;
    union {
         mplane_start_input_t mplane_start_in;
    };
} mpane_switch_in_t;

typedef struct mplane_switch_out{
    uint8_t type;
    union {
         mplane_start_output_t mplane_start_out;
    };
} mplane_switch_out_t;


typedef enum status_code {
        SUCCESS = 0,
        FAILURE = 1

}status;


typedef struct troubleshooting_status_grouping{

        status grouping_status;
        //status_code status ;
        //enum status_code{ SUCCESS = 0, FAILURE  = 1};
        char *failure_reason;

}troubleshooting_logs_t;
typedef struct start_troubleshooting_logs{
                troubleshooting_logs_t  start_troubleshooting_logs_output ;

}start_troubleshooting_logs_t;
typedef struct stop_troubleshooting_logs{

                 troubleshooting_logs_t  stop_troubleshooting_logs_output;

}stop_troubleshooting_logs_t;


extern int software_download(ru_software_pkg_in_t *in, ru_software_pkg_out_t **out);
extern int software_install(ru_software_pkg_in_t *in, ru_software_pkg_out_t **out);
extern int software_activate(ru_software_pkg_in_t *in, ru_software_pkg_out_t **out);
extern int reset();
extern int file_upload(ru_file_mgmt_in_t *in, ru_file_mgmt_out_t **out);
extern int retrieve_file_list(ru_file_mgmt_in_t *in, ru_file_mgmt_out_t **out);
extern int file_download(ru_file_mgmt_in_t *in, ru_file_mgmt_out_t **out);
extern int start_ruapp(mpane_switch_in_t *in, mplane_switch_out_t **out);
extern int troubleshooting_start(start_troubleshooting_logs_t **out);
extern int troubleshooting_stop(stop_troubleshooting_logs_t **out);

#endif

