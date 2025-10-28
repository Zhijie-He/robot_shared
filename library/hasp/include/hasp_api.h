/**
 * \mainpage Sentinel Licensing API
 * \file hasp_api.h Sentinel Licensing API declarations
 *
 * Copyright (C) 2025 THALES. All rights reserved.
 */


#ifndef __HASP_API_H__
#define __HASP_API_H__

#if !defined(WITH_AKSTYPES) && !defined(WITH_OEFTYPES)
#  if defined(_MSC_VER) || defined(__WATCOMC__) || defined(__BORLANDC__)
typedef unsigned __int64 hasp_u64_t;
typedef signed __int64 hasp_s64_t;
#  else
typedef unsigned long long hasp_u64_t;
typedef signed long long hasp_s64_t;
#  endif
#  if defined(_MSC_VER)
typedef unsigned long hasp_u32_t;
typedef signed long hasp_s32_t;
#  else
typedef unsigned int hasp_u32_t;
typedef signed int hasp_s32_t;
#  endif
typedef unsigned short hasp_u16_t;
typedef signed short hasp_s16_t;
typedef signed char hasp_s8_t;
typedef unsigned char hasp_u8_t;
#endif

#if defined(_WIN32) || defined(WIN32) || defined(_MSC_VER) || defined(__BORLANDC__)
#if defined(__MINGW32__)
#  define HASP_CALLCONV __declspec(dllimport) __stdcall
#else
#  define HASP_CALLCONV __stdcall
#endif
#else
#  define HASP_CALLCONV
#endif

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup hasp_feature_ids Legacy HASP HL Run-time API: Feature ID defines
 *
 * @{
 */

/**
 * \brief Legacy HASP HL Run-time API: "Feature Type" mask
 *
 * AND-mask used to identify Feature type.
 */
#define HASP_FEATURETYPE_MASK 0xffff0000

/**
 * \brief Legacy HASP HL Run-time API: "Program Number Feature" type
 *
 * After AND-ing with HASP_FEATURETYPE_MASK the Feature type contain this value.
 */
#define HASP_PROGNUM_FEATURETYPE 0xffff0000

/**
 * \brief Legacy HASP HL Run-time API: "Program Number Mask"
 *
 * AND-mask used to extract the Program Number from a
 * "prognum" Feature ID.
 */
#define HASP_PROGNUM_MASK 0x000000ff

/**
 * \brief Legacy HASP HL Run-time API: "Program Number Options" mask
 *
 * AND-mask used to identify Program Number options:
 *   <ul>
 *     <li>HASP_PROGNUM_OPT_NO_LOCAL</li>
 *     <li>HASP_PROGNUM_OPT_NO_REMOTE</li>
 *     <li>HASP_PROGNUM_OPT_PROCESS</li>
 *     <li>HASP_PROGNUM_OPT_CLASSIC</li>
 *     <li>HASP_PROGNUM_OPT_TS</li>
 *   </ul>
 *
 * 3 bits of the mask are reserved for future extensions and currently unused.
 * Initialize them with zero.
 */
#define HASP_PROGNUM_OPT_MASK 0x0000ff00

/**
 * \brief Legacy HASP HL Run-time API: "Program Number" option
 *
 * Disables the search for local licenses.
 */
#define HASP_PROGNUM_OPT_NO_LOCAL 0x00008000

/**
 * \brief Legacy HASP HL Run-time API: "Program Number" option
 *
 * Disables the search for network licenses.
 */
#define HASP_PROGNUM_OPT_NO_REMOTE 0x00004000

/**
 * \brief Legacy HASP HL Run-time API: "Program Number" option
 *
 * Sets session count of network licenses to "per-process".
 */
#define HASP_PROGNUM_OPT_PROCESS 0x00002000

/**
 * \brief Legacy HASP HL Run-time API: "Program Number" option
 *
 * Enables the API to access "classic" (HASP4 or earlier) keys.
 */
#define HASP_PROGNUM_OPT_CLASSIC 0x00001000

/**
 * \brief Legacy HASP HL Run-time API: "Program Number" option
 *
 * Ignores the presence of terminal servers.
 */
#define HASP_PROGNUM_OPT_TS 0x00000800

/**
 * \brief The Sentinel default Feature ID
 *
 * Available in every Sentinel key.
 */
#define HASP_DEFAULT_FID 0

/**
 * \brief Legacy HASP HL Run-time API: The HASP default Feature ID
 *
 * Available in every legacy HASP hardware key.
 */
#define HASP_PROGNUM_DEFAULT_FID (HASP_DEFAULT_FID | HASP_PROGNUM_FEATURETYPE)

/**
 * @}
 */



/**
 * @defgroup hasp_file_ids Memory File ID defines
 *
 * @{
 */

/**
 * \brief Legacy HASP HL Run-time API: HASP4 memory file
 *
 * File ID for HASP4-compatible memory contents w/o FAS.
 */
#define HASP_FILEID_MAIN 0xfff0

/**
 * \brief Legacy HASP HL Run-time API: HASP4 FAS memory file
 *
 * (Dummy) File ID for the license data area of memory contents.
 */
#define HASP_FILEID_LICENSE 0xfff2

/**
 * \brief Sentinel secure writable memory file
 *
 * File ID for Sentinel secure writable memory.
 */
#define HASP_FILEID_RW 0xfff4

/**
 * \brief Sentinel secure read only memory file
 *
 * File ID for Sentinel read only memory.
 */
#define HASP_FILEID_RO 0xfff5

/**
 * \brief Sentinel dynamic memory file ID avaliable range
 *
 * File ID lower limit for Sentinel dynamic memory file.
 */
#define HASP_FILEID_DYNAMIC_FIRST 0x1

/**
 * \brief Sentinel dynamic memory file ID avaliable range
 *
 * File ID upper limit for Sentinel dynamic memory file.
 */
#define HASP_FILEID_DYNAMIC_LAST 0xffbf

/**
 * @}
 */



/**
 * @defgroup hasp_error_codes Run-time API Status Codes
 *
 * @{
 */

enum hasp_error_codes
{
    /** Request completed successfully */
    HASP_STATUS_OK = 0,

    /** Request exceeds the Sentinel protection key memory file */
    HASP_MEM_RANGE = 1,

    /** Invalid program number option */
    HASP_INV_PROGNUM_OPT = 2,

    /** The system is out of memory */
    HASP_INSUF_MEM = 3,

    /** Application has too many open login sessions */
    HASP_TMOF = 4,

    /** Access to Feature, Sentinel protection key, or functionality was denied */
    HASP_ACCESS_DENIED = 5,

    /** Legacy decryption function is not compatible with this Feature */
    HASP_INCOMPAT_FEATURE = 6,

    /** Sentinel protection key was not found */
    HASP_HASP_NOT_FOUND = 7,

    /* Deprecated - use HASP_HASP_NOT_FOUND */
    HASP_CONTAINER_NOT_FOUND = 7,

    /** Encrypted/decrypted data length is too short to execute function call */
    HASP_TOO_SHORT = 8,

    /** Invalid login handle passed to a function */
    HASP_INV_HND = 9,

    /** The specified file ID is not recognized by the API */
    HASP_INV_FILEID = 10,

    /** Installed driver or daemon is too old. Install a later Run-time Environment */
    HASP_OLD_DRIVER = 11,

    /** Real-time clock and V-Clock are not available */
    HASP_NO_TIME = 12,

    /** Generic error from host system call */
    HASP_SYS_ERR = 13,

    /** Hardware key driver was not found */
    HASP_NO_DRIVER = 14,

    /** An invalid license update or an invalid format string was passed */
    HASP_INV_FORMAT = 15,

    /** Unable to execute the function in this context; the requested
     * functionality is not supported */
    HASP_REQ_NOT_SUPP = 16,

    /** The binary data passed to the function does not contain a valid update */
    HASP_INV_UPDATE_OBJ = 17,

    /** A Sentinel protection key with the requested key ID was not found */
    HASP_KEYID_NOT_FOUND = 18,

    /** Required XML tags were not found OR contents in binary data are missing
     * or invalid */
    HASP_INV_UPDATE_DATA = 19,

    /** The update request is not supported by the Sentinel protection key */
    HASP_INV_UPDATE_NOTSUPP = 20,

    /** An update counter mismatch occurred */
    HASP_INV_UPDATE_CNTR = 21,

    /** An invalid vendor code was passed to a function */
    HASP_INV_VCODE = 22,

    /** The Sentinel protection key does not support the encryption type used.
     * You may have an obsolete key */
    HASP_ENC_NOT_SUPP = 23,

    /** The date/time value passed is outside the supported range */
    HASP_INV_TIME = 24,

    /** The battery for the HL Time key or HL NetTime key is depleted */
    HASP_NO_BATTERY_POWER = 25,

    /** Acknowledge data requested by update, but ack_data parameter
     * is NULL */
    HASP_NO_ACK_SPACE = 26,

    /** An application is running on a remote desktop (terminal server) */
    HASP_TS_DETECTED = 27,

    /** An application is running on a remote desktop (terminal server) */
    HASP_RDP_DETECTED = 27,

    /** The requested Feature type is not implemented */
    HASP_FEATURE_TYPE_NOT_IMPL = 28,

    /** An unrecognized algorithm was used in an H2R/V2C file */
    HASP_UNKNOWN_ALG = 29,

    /** Signature verification operation failed */
    HASP_INV_SIG = 30,

    /** The requested Feature was not found */
    HASP_FEATURE_NOT_FOUND = 31,

    /** Access log or trace log is not enabled */
    HASP_NO_LOG = 32,

    /** A communication error occurred between the API and the local Sentinel
     * License Manager */
    HASP_LOCAL_COMM_ERR = 33,

    /** The vendor code is not recognized by the API library */
    HASP_UNKNOWN_VCODE = 34,

    /** An invalid XML login specification was passed to a function */
    HASP_INV_SPEC = 35,

    /** XML scope is not valid */
    HASP_INV_SCOPE = 36,

    /** The scope matches too many Sentinel protection keys */
    HASP_TOO_MANY_KEYS = 37,

    /** Too many concurrent user sessions are connected */
    HASP_TOO_MANY_USERS = 38,

    /** A login session was interrupted due to certain updates */
    HASP_BROKEN_SESSION = 39,

    /** A communication error occurred between local and remote Sentinel
     * License Managers */
    HASP_REMOTE_COMM_ERR = 40,

    /** The Feature has expired */
    HASP_FEATURE_EXPIRED = 41,

    /** The existing version of the Sentinel License Manager does not support
     * the API request */
    HASP_OLD_LM = 42,

    /** Input/output error occurred in secure storage area of Sentinel SL key
     * OR a USB error occurred when communicating with a Sentinel HL key */
    HASP_DEVICE_ERR = 43,

    /** Update installation is not permitted - the update was already applied */
    HASP_UPDATE_BLOCKED = 44,

    /** System time has been tampered with */
    HASP_TIME_ERR = 45,

    /** Communication error occurred in a secure channel */
    HASP_SCHAN_ERR = 46,

    /** Secure storage area of Sentinel SL protection key is corrupted */
    HASP_STORAGE_CORRUPT = 47,

    /** The customized vendor library (haspvlib_<vendorID>.*) cannot be located */
    HASP_NO_VLIB = 48,

    /** The vendor library cannot be loaded */
    HASP_INV_VLIB = 49,

    /** Unable to locate any Features that satisfy the provided scope */
    HASP_SCOPE_RESULTS_EMPTY = 50,

    /** The license does not allow running the application on a virtual machine */
    HASP_VM_DETECTED = 51,

    /** Sentinel SL key is locked to a different machine */
    HASP_HARDWARE_MODIFIED = 52,

    /** Login is denied because of user restrictions */
    HASP_USER_DENIED = 53,

    /** Attempting to apply a V2C file that was already applied */
    HASP_UPDATE_TOO_OLD = 54,

    /** Attempting to apply V2C files for a Sentinel protection key in the wrong
     * sequence */
    HASP_UPDATE_TOO_NEW = 55,

    /** Your vendor library version is not supported by the current version
     * of the Licensing API */
    HASP_OLD_VLIB = 56,

    /** An attempt to check in a file (such as V2C or H2R) using Admin Control
     * Center failed due to invalid format */
    HASP_UPLOAD_ERROR = 57,

    /** Invalid XML "recipient" parameter */
    HASP_INV_RECIPIENT = 58,

    /** Invalid XML "action" parameter */
    HASP_INV_ACTION = 59,

    /* Deprecated - use HASP_INV_ACTION */
    HASP_INV_DETACH_ACTION = 59,

    /** The scope specified in hasp_transfer() does not identify a unique Product */
    HASP_TOO_MANY_PRODUCTS = 60,

    /** Invalid Product information */
    HASP_INV_PRODUCT = 61,

    /** The update can only be applied to the Recipient specified in hasp_transfer()
     * and not to this machine */
    HASP_UNKNOWN_RECIPIENT = 62,

    /** The duration is invalid */
    HASP_INV_DURATION = 63,

    /** Cloned Sentinel SL secure storage area was detected */
    HASP_CLONE_DETECTED = 64,

    /** The specified V2C or V2CP update was already installed in the License
     * Manager service */
    HASP_UPDATE_ALREADY_ADDED = 65,

    /** The specified key ID identifies an inactive key */
    HASP_HASP_INACTIVE = 66,

    /** No detachable Feature exists */
    HASP_NO_DETACHABLE_FEATURE = 67,

    /** No detachable Feature exists (typo kept for compatibility) */
    HASP_NO_DEATCHABLE_FEATURE = 67,

    /** Scope does not identify a unique host */
    HASP_TOO_MANY_HOSTS = 68,

    /** Rehost action is not allowed for the specified key ID */
    HASP_REHOST_NOT_ALLOWED = 69,

    /** The original license has been rehosted to another machine */
    HASP_LICENSE_REHOSTED = 70,

    /** An old rehost license cannot be applied; a rehost-counter mismatch
     * occurred */
    HASP_REHOST_ALREADY_APPLIED = 71,

    /** A V2C or V2CP file was not found or access was denied */
    HASP_CANNOT_READ_FILE = 72,

    /** The license cannot be extended because the number of detached licenses
     * is greater than the number of concurrent licenses allowed */
    HASP_EXTENSION_NOT_ALLOWED = 73,

    /** Detach of the license not allowed because the Product contains a
     * VM-disabled Feature and the host machine is a virtual machine */
    HASP_DETACH_DISABLED = 74,

    /** You cannot rehost the license to a virtual machine */
    HASP_REHOST_DISABLED = 75,

    /** The user attempted to format an SL AdminMode key or to migrate an
     * SL Legacy key to an SL AdminMode key. However, a Product is currently
     * detached from the key */
    HASP_DETACHED_LICENSE_FOUND = 76,

    /** The fingerprint of the target machine was collected using tools
     * (RUS utility or Licensing API) earlier than Sentinel LDK 7.0 */
    HASP_RECIPIENT_OLD_LM = 77,

    /** A secure storage ID mismatch occurred */
    HASP_SECURE_STORE_ID_MISMATCH = 78,

    /** The license is locked to a specific hostname; however, two or more
     * machines with this hostname were found in the network */
    HASP_DUPLICATE_HOSTNAME = 79,

    /** The Sentinel License Manager is required for this operation */
    HASP_MISSING_LM = 80,

    /** The application tried to consume or reserve multiple executions while
     * logging in to a Feature. However, the license does not contain the
     * number of executions that were requested */
    HASP_FEATURE_INSUFFICIENT_EXECUTION_COUNT = 81,

    /** Attempting to perform an operation that is not compatible with target
     * platform */
    HASP_INCOMPATIBLE_PLATFORM = 82,

    /** The protection key is disabled due to suspected tampering */
    HASP_HASP_DISABLED = 83,

    /** The protection key is not accessible due to a USB sharing violation */
    HASP_SHARING_VIOLATION = 84,

    /** The session was interrupted due a network malfunction, or the session
     * was interrupted manually from Admin Control Center */
    HASP_KILLED_SESSION = 85,

    /** The license does not allow installing the application on a virtual
     * machine */
    HASP_VS_DETECTED = 86,

    /** A client identity is required to run this application */
    HASP_IDENTITY_REQUIRED = 87,

    /** The client identity is not authenticated */
    HASP_IDENTITY_UNAUTHENTICATED = 88,

    /** The client identity is disabled */
    HASP_IDENTITY_DISABLED = 89,

    /** The client identity does not have the required permissions */
    HASP_IDENTITY_DENIED = 90,

    /** Your license is in use on a different machine */
    HASP_IDENTITY_SHARING_VIOLATION = 91,

    /** The maximum number of machines usable by the client identity was reached */
    HASP_IDENTITY_TOO_MANY_MACHINES = 92,

    /** The server is not ready to authenticate */
    HASP_IDENTITY_SERVER_NOT_READY = 93,

    /** Trying to install a V2C file with an update counter that is out of sync
     * with the update counter in the Sentinel protection key */
    HASP_UPDATE_OUT_OF_SYNC = 94,

    /** There were multiple attempts to access the protection key from a remote
     * machine using a proxy */
    HASP_REMOTE_SHARING_VIOLATION = 95,

    /** A cloud licensing session was released because the client requested the
     * seat from a different location */
    HASP_CLOUD_SESSION_OCCUPIED_REMOTELY = 96,

    /** Cloud licensing authorization is required to use this license */
    HASP_CLOUD_MISSING_AUTHORIZATION = 97,

    /** Invalid seat value in network detach. The seat count cannot be decreased
     * when modifying a detach */
    HASP_INV_NETWORK_SEATS = 98,

    /** Network detach of seats with concurrency is disabled on a Product with
     * only unlimited-concurrency Features */
    HASP_NETWORK_DETACH_DISABLED = 99,

    /** The required functionality is not supported for cloud licenses */
    HASP_CLOUD_NOT_SUPP = 100,

    /** Only trusted licenses can be installed in the trusted license storage */
    HASP_CLOUD_NOT_TRUSTED = 101,

    /** A communication error ocurred with the license storage */
    HASP_CLOUD_STORAGE_COMM_ERR = 102,

    /** Your client identity has expired */
    HASP_IDENTITY_EXPIRED = 103,

    /** The option value specified for the API function is not valid */
    HASP_INV_OPTION = 104,

    /** The license server is overloaded. Retry the operation in a few seconds */
    HASP_CLOUD_STORAGE_BUSY = 105,

    /** This machine cannot be used - the fingeprint is invalid or not accessible */
    HASP_MACHINE_DENIED = 106,

    /** The application license is not accessible because this machine is disabled */
    HASP_MACHINE_DISABLED = 107,

    /** The rate at which identity requests are received exceeded the contracted
     * limit. Try again later */
    HASP_IDENTITY_RATE_LIMIT_EXCEEDED = 108,
    
    /** The start date for the Feature has not yet arrived */
    HASP_FEATURE_START_DATE_NOT_REACHED = 109,

    /** The client identity is temporarily not accessible. Try again in a few
     * seconds */
    HASP_IDENTITY_TEMPORARILY_NOT_ACCESSIBLE = 110,

    /** You cannot use both an identity string and a JWT for the same server
     * address */
    HASP_CONFLICTING_AUTHENTICATION_METHODS = 111,

    /** The JWT or LM access token is invalid. Restart the operation */
    HASP_ACCESS_TOKEN_IS_INVALID = 112,

    /** The JWT or LM access token has expired. Restart the operation */
    HASP_ACCESS_TOKEN_EXPIRED = 113,

    /** Unable to locate the dynamic library for this vendor code */
    HASP_NO_API_DYLIB = 400,

    /** The dynamic library for this vendor code cannot be loaded, possibly
     * due to corruption */
    HASP_INV_API_DYLIB = 401,

    /** The dynamic library for this vendor code is too old and a requested
     * function was not found */
    HASP_INCOMPLETE_API_DYLIB = 402,

    /** Object was incorrectly initialized */
    HASP_INVALID_OBJECT = 500,

    /** An invalid function parameter was specified */
    HASP_INVALID_PARAMETER = 501,

    /** Attempting to log in twice to the same object */
    HASP_ALREADY_LOGGED_IN = 502,

    /** Attempting to log out twice from the same object */
    HASP_ALREADY_LOGGED_OUT = 503,

    /** Incorrect use of system or platform */
    HASP_OPERATION_FAILED = 525,

    /* An internal error occurred: No classic memory extension block is available */
    HASP_NO_EXTBLOCK = 600,

    /* An internal error occurred: Invalid port type */
    HASP_INV_PORT_TYPE = 650,

    /* An internal error occurred: Invalid port value */
    HASP_INV_PORT = 651,

    /* The .NET DLL appears to be broken */
    HASP_NET_DLL_BROKEN = 652,

    /** The requested functionality is not supported */
    HASP_NOT_IMPL = 698,

    /** An internal error ocurred in the API */
    HASP_INT_ERR = 699,

    /* Reserved for Sentinel helper libraries */
    HASP_FIRST_HELPER = 2001,

    /* Reserved for Sentinel Activation API */
    HASP_FIRST_HASP_ACT = 3001,

    HASP_NEXT_FREE_VALUES = 7001,
};

/**
 * @}
 */



/**
 * @defgroup hasp_general Sentinel typedefs and macros
 *
 * @{
 */

/** A Sentinel status code */
typedef enum hasp_error_codes hasp_status_t;

/** Sentinel size type */
typedef hasp_u32_t hasp_size_t;

/** Sentinel connection handle */
typedef hasp_u32_t hasp_handle_t;

/** Sentinel Feature ID */
typedef hasp_u32_t hasp_feature_t;

/** Sentinel File ID */
typedef hasp_u32_t hasp_fileid_t;

/** Sentinel timestamp, representing elapsed seconds since
 * Jan-01-1970 0:00:00 GMT */
typedef hasp_u64_t hasp_time_t;

/** Sentinel Vendor Code buffer */
typedef const void *hasp_vendor_code_t;


/** format to retrieve update info (C2V) */
#define HASP_UPDATEINFO     "<haspformat format=\"updateinfo\"/>"

/* format to retrieve a small update info (C2V) */
#define HASP_FASTUPDATEINFO "<haspformat format=\"fastupdateinfo\"/>"

/** format to retrieve session info */
#define HASP_SESSIONINFO    "<haspformat format=\"sessioninfo\"/>"

/** format to retrieve key/hardware info */
#define HASP_KEYINFO        "<haspformat format=\"keyinfo\"/>"

/** format to retrieve host fingerprint info */
#define HASP_FINGERPRINT    "<haspformat format=\"host_fingerprint\"/>"

/** format to retrieve recipient parameter for hasp_transfer */
#define HASP_RECIPIENT      "<haspformat root=\"location\">"             \
                            "  <license_manager>"                        \
                            "    <attribute name=\"id\" />"              \
                            "    <attribute name=\"time\" />"            \
                            "    <element name=\"hostname\" />"          \
                            "    <element name=\"version\" />"           \
                            "    <element name=\"host_fingerprint\" />"  \
                            "  </license_manager>"                       \
                            "</haspformat>"

/*
 * Invalid handle value for hasp_login() and hasp_login_scope() functions.
 */
#define HASP_INVALID_HANDLE_VALUE 0

/**
 * \brief Minimum block size for hasp_encrypt() and hasp_decrypt() functions.
 */
#define HASP_MIN_BLOCK_SIZE 16

/**
 * \brief Minimum block size for hasp_legacy_encrypt()
 *        and hasp_legacy_decrypt() legacy functions.
 */
#define HASP_MIN_BLOCK_SIZE_LEGACY 8

/**
 * @}
 */



/**
 * @defgroup hasp_basic The Basic Sentinel Licensing API
 *
 * @{
 */

/**
 * \brief Logs into a Feature and thereby establishes a session context.
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * This function establishes a context to a Sentinel protection key
 * containing a license for the requested Feature ID.
 *
 * The requisite Vendor Codes are stored in a VendorCodes folder in your
 * system. Without the correct Vendor Code, the function call cannot succeed.
 *
 * You can open up to 512 simultaneous login sessions.
 *
 * <b>Legacy HASP Remarks</b><br>
 * For local prognum Features, concurrency is not handled and each login
 * performs a decrement if it is a counting license.
 *
 * Network "prognum" features continue to use the old HASP/Sentinel LM login logic,
 * with its inherent limitations.
 *
 * There is only support for concurrent usage of <b>one</b> server (global
 * server address).
 *
 * With "Program Number" features (see \ref HASP_FEATURETYPE_MASK), 8
 * bits are reserved for legacy options (see \ref HASP_PROGNUM_OPT_MASK,
 * currently 5 bits are used):
 * <ul>
 *   <li>only local</li>
 *   <li>only remote</li>
 *   <li>login is counted per process ID</li>
 *   <li>disable terminal server check</li>
 *   <li>enable access to old (HASP3/HASP4) keys</li>
 * </ul>
 *
 * \param feature_id  Unique identifier for a specific Feature stored
 *                    in a Sentinel protection key
 * \param vendor_code Pointer to the Vendor Code
 * \param handle      Pointer to the resulting session handle
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_HASP_NOT_FOUND</li> Required Sentinel
 *                        protection key not found
 *                      <li>HASP_FEATURE_NOT_FOUND</li> Cannot find requested
 *                        Feature
 *                      <li>HASP_FEATURE_TYPE_NOT_IMPL</li> Requested Feature
 *                        type not available
 *                      <li>HASP_TMOF</li> Too many open login sessions
 *                      <li>HASP_INSUF_MEM</li> Out of memory
 *                      <li>HASP_INV_VCODE</li> Invalid Vendor Code
 *                      <li>HASP_NO_DRIVER</li> Driver not installed
 *                      <li>HASP_NO_VLIB</li> Vendor library cannot be found
 *                      <li>HASP_INV_VLIB</li> Vendor library cannot be loaded
 *                      <li>HASP_OLD_DRIVER</li> Driver too old
 *                      <li>HASP_UNKNOWN_VCODE</li> Vendor Code not recognized
 *                      <li>HASP_FEATURE_EXPIRED</li> Feature has expired
 *                      <li>HASP_TOO_MANY_USERS</li> Too many users currently
 *                        connected
 *                      <li>HASP_OLD_LM</li> Sentinel License Manager version
 *                        too old
 *                      <li>HASP_DEVICE_ERR</li> Input/Output error in Sentinel
 *                        SL/SL-AdminMode/SL-UserMode secure storage, OR in
 *                        case of a Sentinel HL key, USB communication error
 *                      <li>HASP_TIME_ERR</li> System time has been tampered
 *                        with
 *                      <li>HASP_HARDWARE_MODIFIED</li> Sentinel SL key
 *                        incompatible with machine hardware; Sentinel SL key is
 *                        locked to different hardware
 *                      <li>HASP_TS_DETECTED</li> Program is running on a
 *                        Terminal Server
 *                      <li>HASP_LOCAL_COMM_ERR</li> Communication error
 *                        between API and local Sentinel License Manager
 *                      <li>HASP_REMOTE_COMM_ERR</li> Communication error
 *                        between local and remote Sentinel License Manager
 *                      <li>HASP_OLD_VLIB</li> Vendor Library version too old
 *                      <li>HASP_CLONE_DETECTED</li> Cloned Sentinel SL storage
 *                        detected. Feature unavailable
 *                    </ul>
 *
 * \sa hasp_login_scope()
 * \sa hasp_logout()
 *
 */
hasp_status_t HASP_CALLCONV hasp_login(hasp_feature_t feature_id,
                hasp_vendor_code_t vendor_code,
                hasp_handle_t *handle);


/**
 * \brief Logs into a Feature to establish a session, according to
 * predefined search parameters.
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * This function is used to specify conditions that describe where login
 * information is to searched for.
 *
 * The requisite Vendor Codes are stored in a VendorCodes folder in your
 * system. Without the correct Vendor Code, the function call cannot succeed.
 *
 * You can open up to 512 simultaneous login sessions.
 *
 * This function does not work with legacy HASP Features.
 *
 * \param feature_id  Unique identifier for a specific Feature stored in
 *                      a Sentinel protection key
 * \param scope       Definition of the search parameters for
 *                      this Feature ID. See the additional Sentinel API
 *                      Reference documentation for more information
 *                      about Scope XML Tags
 * \param vendor_code Pointer to the vendor code
 * \param handle      Pointer to the resulting session handle
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_HASP_NOT_FOUND</li> Required Sentinel
 *                        protection key not found
 *                      <li>HASP_FEATURE_NOT_FOUND</li> Cannot find requested
 *                        Feature
 *                      <li>HASP_SCOPE_RESULTS_EMPTY</li> Unable to locate
 *                        a Feature matching the scope
 *                      <li>HASP_TMOF</li> Too many open login sessions
 *                      <li>HASP_INSUF_MEM</li> Out of memory
 *                      <li>HASP_INV_VCODE</li> Invalid Vendor Code
 *                      <li>HASP_NO_DRIVER</li> Driver not installed
 *                      <li>HASP_NO_VLIB</li> Vendor library cannot be found
 *                      <li>HASP_INV_VLIB</li> Vendor library cannot be loaded
 *                      <li>HASP_OLD_DRIVER</li> Driver too old
 *                      <li>HASP_UNKNOWN_VCODE</li> Vendor Code not recognized
 *                      <li>HASP_INVALID_PARAMETER</li> Scope string too
 *                        long (max. length 32 kb)
 *                      <li>HASP_FEATURE_EXPIRED</li> Feature has expired
 *                      <li>HASP_TOO_MANY_USERS</li> Too many users currently
 *                        connected
 *                      <li>HASP_OLD_LM</li> Sentinel License Manager version
 *                        too old
 *                      <li>HASP_DEVICE_ERR</li> Input/Output error in Sentinel
 *                        SL/SL-AdminMode/SL-UserMode secure storage, OR in
 *                        case of a Sentinel HL key, USB communication error
 *                      <li>HASP_TIME_ERR</li> System time has been tampered
 *                        with
 *                      <li>HASP_TS_DETECTED</li> Program is running on a
 *                        Terminal Server
 *                      <li>HASP_HARDWARE_MODIFIED</li> Sentinel SL key
 *                        incompatible with machine hardware; Sentinel SL key is
 *                        locked to different hardware
 *                      <li>HASP_LOCAL_COMM_ERR</li> Communication error
 *                        between API and local Sentinel License Manager
 *                      <li>HASP_REMOTE_COMM_ERR</li> Communication error
 *                        between local and remote Sentinel License Manager
 *                      <li>HASP_OLD_VLIB</li> Vendor Library version too old
 *                      <li>HASP_CLONE_DETECTED</li> Cloned Sentinel SL storage
 *                        detected. Feature unavailable
 *                    </ul>
 *
 * \sa hasp_login()
 * \sa hasp_logout()
 * \sa hasp_get_info()
 *
 */
hasp_status_t HASP_CALLCONV hasp_login_scope(hasp_feature_t feature_id,
                const char *scope,
                hasp_vendor_code_t vendor_code,
                hasp_handle_t *handle);


/**
 * \brief Logs out from a context or session.
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * Use this function to end a connection to an API session object. Once
 * logged out from a session, all memory allocated for the session is released.
 *
 * \param handle      Handle for the session being terminated
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INV_HND</li> Invalid input handle
 *                      <li>HASP_LOCAL_COMM_ERR</li> Communication error
 *                        between API and local Sentinel License Manager
 *                      <li>HASP_REMOTE_COMM_ERR</li> Communication error
 *                        between local and remote Sentinel License Manager
 *                    </ul>
 *
 * \sa hasp_login()
 * \sa hasp_login_scope()
 *
 */
hasp_status_t HASP_CALLCONV hasp_logout(hasp_handle_t handle);


/**
 * \brief Encrypts a buffer.
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * Encrypts data using the encryption engine in the Sentinel protection key.
 * The specific session handle determines which Sentinel protection key and
 * which Feature ID encrypts the data buffer. The encryption key remains
 * in the Sentinel protection key. If the encryption fails, the buffer
 * is not modified. To decrypt the data buffer, use the \ref hasp_decrypt
 * function.
 *
 * \param handle      Handle for the session
 * \param buffer      Pointer to the buffer to be encrypted
 * \param length      Size (in bytes) of the buffer to be encrypted
 *                      (16 bytes minimum)
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INV_HND</li> Invalid input handle
 *                      <li>HASP_DEVICE_ERR</li> Input/Output error in Sentinel
 *                        SL secure storage, OR in case of a Sentinel HL key,
 *                        USB communication error
 *                      <li>HASP_TIME_ERR</li> System time has been tampered
 *                        with
 *                      <li>HASP_TOO_SHORT</li> Encryption data length is
 *                        too short
 *                      <li>HASP_ENC_NOT_SUPP</li> Sentinel protection key
 *                        does not support encryption type
 *                      <li>HASP_SCHAN_ERR</li> Communication error occurred
 *                        in secure channel OR Sentinel HL Firmware too old
 *                        (update to 3.25 or later)
 *                      <li>HASP_BROKEN_SESSION</li> Session has been
 *                        interrupted
 *                      <li>HASP_LOCAL_COMM_ERR</li> Communication error
 *                        between API and local Sentinel License Manager
 *                      <li>HASP_REMOTE_COMM_ERR</li> Communication error
 *                        between local and remote Sentinel License Manager
 *                    </ul>
 *
 * \sa hasp_decrypt()
 *
 */
hasp_status_t HASP_CALLCONV hasp_encrypt(hasp_handle_t handle,
                void *buffer,
                hasp_size_t length);

/**
 * \brief Decrypts a buffer.
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * Decrypts data using the decryption engine in the Sentinel protection key
 * The specific session handle determines which Sentinel protection key and
 * which Feature ID decrypts the data buffer. The decryption key remains
 * in the Sentinel protection key. If the decryption fails, the buffer
 * is not modified. To encrypt the data buffer, use the \ref hasp_encrypt
 * function.
 *
 * \param handle      Handle for the session
 * \param buffer      Pointer to the buffer to be decrypted
 * \param length      Size (in bytes) of the buffer to be decrypted
 *                      (16 bytes minimum)
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INV_HND</li> Invalid input handle
 *                      <li>HASP_DEVICE_ERR</li> Input/Output error in Sentinel
 *                        SL/SL-AdminMode/SL-UserMode secure storage, OR in
 *                        case of a Sentinel HL key, USB communication error
 *                      <li>HASP_TIME_ERR</li> System time has been tampered
 *                        with
 *                      <li>HASP_TOO_SHORT</li> Decryption data length is
 *                        too short
 *                      <li>HASP_SCHAN_ERR</li> Communication error occurred
 *                        in secure channel OR Sentinel HL Firmware too old
 *                        (update to 3.25 or later)
 *                      <li>HASP_ENC_NOT_SUPP</li> Sentinel protection key
 *                        does not support encryption type
 *                      <li>HASP_BROKEN_SESSION</li> Session has been
 *                        interrupted
 *                      <li>HASP_LOCAL_COMM_ERR</li> Communication error
 *                        between API and local Sentinel License Manager
 *                      <li>HASP_REMOTE_COMM_ERR</li> Communication error
 *                        between local and remote Sentinel License Manager
 *                    </ul>
 *
 * \sa hasp_encrypt()
 *
 */
hasp_status_t HASP_CALLCONV hasp_decrypt(hasp_handle_t handle,
                void *buffer,
                hasp_size_t length);

/**
 * \brief Reads the memory of a Sentinel protection key.
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * Valid File IDs are \ref HASP_FILEID_RW and \ref HASP_FILEID_RO.
 * From Sentinel LDK 7.1, Sentinel HL Driverless keys support dynamic memory.
 * From Sentinel LDK 8.4, Sentinel SL keys support dynamic memory.
 * The File IDs can be from HASP_FILEID_DYNAMIC_FIRST(0x1) to HASP_FILEID_DYNAMIC_LAST(0xFFBF).
 *
 * <b>Legacy HASP Remarks</b><br>
 * Valid File IDs are \ref HASP_FILEID_LICENSE and \ref HASP_FILEID_MAIN.
 *
 * \param handle      Handle for the session
 * \param fileid      Identifier for the file that is to be read
 * \param offset      Byte offset in the file
 * \param length      Number of bytes to be read from the file
 * \param buffer      Pointer to the retrieved data
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INV_HND</li> Invalid input handle
 *                      <li>HASP_INV_FILEID</li> Unrecognized file identifier
 *                      <li>HASP_MEM_RANGE</li> Request exceeds the Sentinel
 *                        protection key memory file
 *                      <li>HASP_DEVICE_ERR</li> Input/Output error in Sentinel
 *                        SL/SL-AdminMode/SL-UserMode secure storage, OR in
 *                        case of a Sentinel HL key, USB communication error
 *                      <li>HASP_SCHAN_ERR</li> Communication error occurred
 *                        in secure channel OR Sentinel HL Firmware too old
 *                        (update to 3.25 or later)
 *                      <li>HASP_BROKEN_SESSION</li> Session has been
 *                        interrupted
 *                      <li>HASP_LOCAL_COMM_ERR</li> Communication error
 *                        between API and local Sentinel License Manager
 *                      <li>HASP_REMOTE_COMM_ERR</li> Communication error
 *                        between local and remote Sentinel License Manager
 *                    </ul>
 *
 * \remark
 * Use the \ref hasp_get_size function to determine the size of the file you
 * want to read.
 *
 * \sa hasp_write()
 * \sa hasp_get_size()
 *
 */
hasp_status_t HASP_CALLCONV hasp_read(hasp_handle_t handle,
                hasp_fileid_t fileid,
                hasp_size_t offset,
                hasp_size_t length,
                void *buffer);

/**
 * \brief Writes to the memory of a Sentinel protection key.
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * Valid File ID is \ref HASP_FILEID_RW.
 * From Sentinel LDK 7.1, Sentinel HL Driverless keys support dynamic memory.
 * From Sentinel LDK 8.4, Sentinel SL keys support dynamic memory.
 * The File IDs can be from HASP_FILEID_DYNAMIC_FIRST(0x1) to HASP_FILEID_DYNAMIC_LAST(0xFFBF).
 *
 * <b>Legacy HASP Remarks</b><br>
 * Depending on the provided session handle (either logged into the
 * default Feature or any other Feature), write access to the FAS memory
 * (\ref HASP_FILEID_LICENSE) is not permitted.
 *
 * \param handle      Handle for the session
 * \param fileid      Identifier for the file that is to be written
 * \param offset      Byte offset in the file
 * \param length      Number of bytes to be written to the file
 * \param buffer      Pointer to the data
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INV_HND</li> Invalid input handle
 *                      <li>HASP_INV_FILEID</li> Unrecognized file identifier
 *                      <li>HASP_MEM_RANGE</li> Request exceeds the Sentinel
 *                        protection key memory file
 *                      <li>HASP_DEVICE_ERR</li> Input/Output error in Sentinel
 *                        SL/SL-AdminMode/SL-UserMode secure storage, OR in
 *                        case of a Sentinel HL key, USB communication error
 *                      <li>HASP_SCHAN_ERR</li> Communication error occurred
 *                        in secure channel OR Sentinel HL Firmware too old
 *                        (update to 3.25 or later)
 *                      <li>HASP_BROKEN_SESSION</li> Session has been
 *                        interrupted
 *                      <li>HASP_LOCAL_COMM_ERR</li> Communication error
 *                        between API and local Sentinel License Manager
 *                      <li>HASP_REMOTE_COMM_ERR</li> Communication error
 *                        between local and remote Sentinel License Manager
 *                    </ul>
 *
 * \remark
 * Use the \ref hasp_get_size function to determine the size of the file you
 * want to write.
 *
 * \sa hasp_read()
 * \sa hasp_get_size()
 *
 */
hasp_status_t HASP_CALLCONV hasp_write(hasp_handle_t handle,
                hasp_fileid_t fileid,
                hasp_size_t offset,
                hasp_size_t length,
                const void *buffer);

/**
 * \brief Retrieves the byte size of a memory file from a Sentinel protection key.
 *
 * This function is used to determine the file size of a Sentinel
 * memory file.
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * From Sentinel LDK 7.1, Sentinel HL Driverless keys support dynamic memory.
 * From Sentinel LDK 8.4, Sentinel SL keys support dynamic memory.
 * The File IDs can be from HASP_FILEID_DYNAMIC_FIRST(0x1) to HASP_FILEID_DYNAMIC_LAST(0xFFBF).
 *
 * \param handle      Handle for the session
 * \param fileid      Identifier for the file that is to be queried.
 * \param size        Pointer to the resulting file size
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INV_HND</li> Invalid input handle
 *                      <li>HASP_INV_FILEID</li> Unrecognized file identifier
 *                      <li>HASP_DEVICE_ERR</li> Input/Output error in Sentinel
 *                        SL/SL-AdminMode/SL-UserMode secure storage, OR in
 *                        case of a Sentinel HL key, USB communication error
 *                      <li>HASP_BROKEN_SESSION</li> Session has been
 *                        interrupted
 *                      <li>HASP_LOCAL_COMM_ERR</li> Communication error
 *                        between API and local Sentinel License Manager
 *                      <li>HASP_REMOTE_COMM_ERR</li> Communication error
 *                        between local and remote Sentinel License Manager
 *                    </ul>
 *
 * \sa hasp_read()
 * \sa hasp_write()
 *
 */
hasp_status_t HASP_CALLCONV hasp_get_size(hasp_handle_t handle,
                hasp_fileid_t fileid,
                hasp_size_t *size);

/**
 * \brief Reads the current time.
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * Only Sentinel HL keys with a Real-time clock (rtc) and Sentinel SL keys can
 * provide the current time.
 *
 * Primarily used to obtain reliable timestamps that are independent from
 * the system clock.
 *
 * Time values are returned as the number of seconds that have elapsed
 * since Jan-01-1970 0:00:00 UTC.
 *
 * <b>Legacy HASP Remarks</b><br>
 * This request is only supported on locally accessed keys. Trying to
 * get the time from a remotely accessed key will return HASP_NO_TIME.
 *
 * \param handle      Handle for the session
 * \param time        Pointer to the current time
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INV_HND</li> Invalid input handle
 *                      <li>HASP_BROKEN_SESSION</li> Session has been
 *                        interrupted
 *                      <li>HASP_LOCAL_COMM_ERR</li> Communication error
 *                        between API and local Sentinel License Manager
 *                      <li>HASP_REMOTE_COMM_ERR</li> Communication error
 *                        between local and remote Sentinel License Manager
 *                      <li>HASP_NO_BATTERY_POWER</li> Real-time clock has
 *                        run out of power
 *                      <li>HASP_NO_TIME</li> Real-time clock is not
 *                        available
 *                    </ul>
 *
 * \sa hasp_datetime_to_hasptime()
 * \sa hasp_hasptime_to_datetime()
 *
 */
hasp_status_t HASP_CALLCONV hasp_get_rtc(hasp_handle_t handle,
                hasp_time_t *time);

/**
 * @}
 */



/**
 * @defgroup hasp_classic Legacy HASP functionality for backward compatibility
 *
 * @{
 */

/**
 * \brief Legacy HASP4 compatible encryption function.
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * This function does not work with a Sentinel login handle.
 *
 * <b>Legacy HASP Remarks</b><br>
 * The handle must have been obtained by calling \ref hasp_login() with
 * a "prognum" Feature ID.
 *
 * \param handle      Handle for the session
 * \param buffer      Pointer to the buffer to be encrypted
 * \param length      Size in bytes of the buffer (min. 8 bytes)
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INV_HND</li> Invalid input handle
 *                      <li>HASP_TOO_SHORT</li> Encryption data length is
 *                        too short
 *                      <li>HASP_ENC_NOT_SUPP</li> Sentinel protection key
 *                        does not support encryption type
 *                      <li>HASP_HASP_NOT_FOUND</li> Required Sentinel
 *                        protection key not found
 *                    </ul>
 *
 * \sa hasp_legacy_decrypt()
 * \sa hasp_encrypt()
 * \sa hasp_decrypt()
 *
 */
hasp_status_t HASP_CALLCONV hasp_legacy_encrypt(hasp_handle_t handle,
                void *buffer,
                hasp_size_t length);

/**
 * \brief Legacy HASP4 compatible decryption function.
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * This function does not work with a Sentinel login handle.
 *
 * <b>Legacy HASP Remarks</b><br>
 * The handle must have been obtained by calling \ref hasp_login() with
 * a "prognum" Feature ID.
 *
 * \param handle      Handle for the session
 * \param buffer      Pointer to the buffer to be decrypted
 * \param length      Size in bytes of the buffer (min. 8 bytes)
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INV_HND</li> Invalid input handle
 *                      <li>HASP_TOO_SHORT</li> Encryption data length is
 *                        too short
 *                      <li>HASP_ENC_NOT_SUPP</li> Sentinel protection key
 *                        does not support encryption type
 *                      <li>HASP_HASP_NOT_FOUND</li> Required Sentinel
 *                        protection key not found
 *                    </ul>
 *
 * \sa hasp_legacy_encrypt()
 * \sa hasp_decrypt()
 * \sa hasp_encrypt()
 *
 */
hasp_status_t HASP_CALLCONV hasp_legacy_decrypt(hasp_handle_t handle,
                void *buffer,
                hasp_size_t length);

/**
 * \brief Writes to HASP4-compatible real-time clock
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * This function does not work with a Sentinel login handle.
 *
 * <b>Legacy HASP Remarks</b><br>
 * The handle must have been obtained by calling \ref hasp_login() with
 * a "prognum" Feature ID.
 *
 * This request is only supported on locally accessed keys. Attempting to
 * set the time on a remotely accessed key will return HASP_NO_TIME.
 *
 * \param handle      Handle for the session
 * \param new_time    The new time value
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INV_HND</li> Invalid input handle
 *                      <li>HASP_HASP_NOT_FOUND</li> Required Sentinel
 *                        protection key not found
 *                      <li>HASP_NO_TIME</li> Real-time clock not available
 *                        OR access remote
 *                    </ul>
 *
 * \sa hasp_get_rtc()
 * \sa hasp_datetime_to_hasptime()
 * \sa hasp_hasptime_to_datetime()
 *
 */
hasp_status_t HASP_CALLCONV hasp_legacy_set_rtc(hasp_handle_t handle,
                hasp_time_t new_time);

/**
 * \brief Set the LM idle time.
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * This function does not work with a Sentinel login handle.
 *
 * <b>Legacy HASP Remarks</b><br>
 * The handle must have been obtained by calling \ref hasp_login() with
 * a "prognum" Feature ID.
 *
 * \param handle      Handle for the session
 * \param idle_time   The idle time in minutes
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INV_HND</li> Invalid input handle
 *                      <li>HASP_HASP_NOT_FOUND</li> Required Sentinel
 *                        protection key not found
 *                      <li>HASP_REQ_NOT_SUPP</li> Tried to set the idle time
 *                        for a local license
 *                    </ul>
 *
 */
hasp_status_t HASP_CALLCONV hasp_legacy_set_idletime(hasp_handle_t handle,
                hasp_u16_t idle_time);

/**
 * @}
 */



/**
 * @defgroup hasp_extended Extended Sentinel Licensing API functionality
 *
 * The extended API consists of functions that provide extended
 * functionality. This advanced functionality is sometimes necessary,
 * and addresses the "advanced" user.
 *
 * @{
 */

/**
 * \brief Retrieves information about system components, according to
 * customizable search parameters, and presents it according to
 * customizable formats.
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * You do not need to be logged in to a Sentinel Feature in order to use
 * this function.
 *
 * This function is used to specify conditions about where to search for
 * information. In addition, it enables you to specify conditions about
 * the format in which the retrieved information is presented. If
 * retrieved information is appropriately formatted, it can be used as
 * a template in the hasp_login_scope() function.
 *
 * The requisite Vendor Codes are stored in a VendorCodes folder in
 * your system. Without the correct Vendor Code, the function call
 * cannot succeed.
 *
 * This function allocates memory for the information it retrieves. To
 * release allocated memory resources, use the \ref hasp_free function.
 *
 * This function cannot be used to retrieve legacy HASP Features.
 *
 * \param scope       Definition of the data that is to be searched, in XML
 *                      format. For more information, see the accompanying
 *                      Sentinel Licensing API help documentation
 * \param format      Definition of the format in which the data is to be
 *                      displayed, in XML format. For more information, see the
 *                      accompanying Sentinel Licensing API help
 *                      documentation
 * \param vendor_code Pointer to the Vendor Code
 * \param info        Pointer to the information that is retrieved, in XML
 *                      format
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_SCOPE_RESULTS_EMPTY</li> Unable to locate
 *                        a Feature matching the scope
 *                      <li>HASP_INSUF_MEM</li> Out of memory
 *                      <li>HASP_INV_VCODE</li> Invalid Vendor Code
 *                      <li>HASP_UNKNOWN_VCODE</li> Vendor Code not recognized
 *                      <li>HASP_INVALID_PARAMETER</li> Scope or format string
 *                        too long (max. length 32 kb)
 *                      <li>HASP_DEVICE_ERR</li> Input/Output error in Sentinel
 *                        SL/SL-AdminMode/SL-UserMode secure storage, OR in
 *                        case of a Sentinel HL key, USB communication error
 *                      <li>HASP_LOCAL_COMM_ERR</li> Communication error
 *                        between API and local Sentinel License Manager
 *                      <li>HASP_REMOTE_COMM_ERR</li> Communication error
 *                        between local and remote Sentinel License Manager
 *                      <li>HASP_INV_FORMAT</li> Unrecognized format string
 *                      <li>HASP_INV_SCOPE</li> Unrecognized scope string
 *                      <li>HASP_BROKEN_SESSION</li> Session has been
 *                        interrupted
 *                      <li>HASP_TOO_MANY_KEYS</li> In case of getting C2V:
 *                        Too many Sentinel protection keys match the scope
 *                      <li>HASP_TOO_MANY_HOSTS</li> In case of getting host
 *                        fingerrpint: Too many Sentinel License Manager
 *                        match the scope
 *                      <li>HASP_HASP_INACTIVE</li> In case of getting C2V:
 *                        Inactive Sentinel SL-AdminMode/SL-UserMode key-id
 *                    </ul>
 *
 * \sa hasp_get_sessioninfo()
 * \sa hasp_free()
 *
 */
hasp_status_t HASP_CALLCONV hasp_get_info(const char *scope,
                const char *format,
                hasp_vendor_code_t vendor_code,
                char **info);

/**
 * \brief Retrieves information regarding a session context.
 *
 * Memory for the information is allocated by this function and has to
 * be freed with the \ref hasp_free function.
 *
 * \param handle      Handle for the session
 * \param format      Definition for the type of output data structure, in
 *                      XML format.
 *                    There are three format options:
 *                    <ul>
 *                      <li>HASP_KEYINFO</li> For retrieving information on
 *                        the Sentinel protection key
 *                      <li>HASP_SESSIONINFO</li> For retrieving information on
 *                        the login session
 *                      <li>HASP_UPDATEINFO</li> For retrieving information on
 *                        a license update usually contained in a C2V file.
 *                        The retrieved information includes the current
 *                        state of the key, including update counters,
 *                        license availability and memory images
 *                    </ul>
 * \param info        Pointer to the information that is retrieved as XML text
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INSUF_MEM</li> Out of memory
 *                      <li>HASP_DEVICE_ERR</li> Input/Output error in Sentinel
 *                        SL secure storage, OR in case of a Sentinel HL key,
 *                        USB communication error
 *                      <li>HASP_LOCAL_COMM_ERR</li> Communication error
 *                        between API and local Sentinel License Manager
 *                      <li>HASP_REMOTE_COMM_ERR</li> Communication error
 *                        between local and remote Sentinel License Manager
 *                      <li>HASP_INV_FORMAT</li> Unrecognized format string
 *                      <li>HASP_INV_HND</li> Invalid input handle
 *                      <li>HASP_BROKEN_SESSION</li> Session has been
 *                        interrupted
 *                      <li>HASP_TIME_ERR</li> System time has been tampered
 *                        with
 *                    </ul>
 *
 *  \sa hasp_free()
 *  \sa HASP_UPDATEINFO
 *  \sa HASP_SESSIONINFO
 *  \sa HASP_KEYINFO
 */
hasp_status_t HASP_CALLCONV hasp_get_sessioninfo(hasp_handle_t handle,
                const char *format,
                char **info);

/**
 * \brief Frees memory resources utilized by other API functions.
 *
 * Used only in C code to release memory resources allocated to storing
 * retrieved data from API calls.
 *
 * \param info         Pointer to the memory resources to be released
 *
 * \sa hasp_get_info()
 * \sa hasp_get_sessioninfo()
 * \sa hasp_update()
 *
 */
void HASP_CALLCONV hasp_free(char *info);


/**
 * \brief Updates a Sentinel protection key.
 *
 * This function writes update information. Note that the Sentinel
 * protection key must be locally connected.
 *
 * The update code contains all necessary data to perform the update on
 * a deployed Sentinel protection key including:
 * <ul>
 *   <li>The Sentinel protection key on which the updated information is
 *      to be written</li>
 *   <li>The necessary Vendor Code that is required to access the
 *      Sentinel key</li>
 *   <li>The actual update information</li>
 * </ul>
 *
 * Depending on the update data, the function returns an acknowledgement
 * code that is signed/encrypted by the key. The code is evidence that
 * an update has been applied to a license. This function allocates memory
 * for the acknowledge data. To release allocated memory resources, use
 * \a hasp_free().
 *
 * \param update_data Pointer to the complete update data.
 * \param ack_data    Pointer to a buffer to retrieve the acknowledge data.
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_KEYID_NOT_FOUND</li> The Sentinel protection
 *                        key was not found
 *                      <li>HASP_INV_UPDATE_DATA</li> Required XML tags
 *                        not found; Contents in binary data are missing
 *                        or invalid
 *                      <li>HASP_INV_UPDATE_NOTSUPP</li> Update request is
 *                        not supported by Sentinel protection key
 *                      <li>HASP_INV_UPDATE_CNTR</li> Update counter not
 *                        set correctly
 *                      <li>HASP_INSUF_MEM</li> Out of memory
 *                      <li>HASP_DEVICE_ERR</li> Input/Output error in Sentinel
 *                        SL secure storage, OR in case of a Sentinel HL key,
 *                        USB communication error
 *                      <li>HASP_LOCAL_COMM_ERR</li> Communication error
 *                        between API and local Sentinel License Manager
 *                      <li>HASP_REMOTE_COMM_ERR</li> Communication error
 *                        between local and remote Sentinel License Manager
 *                      <li>HASP_NO_ACK_SPACE</li> Acknowledge data
 *                        requested by the update, but ack_data parameter
 *                        is NULL
 *                      <li>HASP_UNKNOWN_ALG</li> Unknown algorithm used
 *                        in V2C file
 *                      <li>HASP_INV_SIG</li> Signature verification failed
 *                      <li>HASP_TOO_MANY_KEYS</li> Too many Sentinel
 *                        protection keys match the scope
 *                      <li>HASP_HARDWARE_MODIFIED</li> Conflict between
 *                        Sentinel SL key data and machine hardware data;
 *                        Sentinel SL key locked to different hardware
 *                      <li>HASP_UPDATE_TOO_OLD</li> Trying to install a
 *                        V2C file with an update counter that is out of
 *                        sequence with the update counter in the Sentinel
 *                        protection key. The values of the update counter
 *                        in the file are lower than those in the Sentinel
 *                        protection key
 *                      <li>HASP_UPDATE_TOO_NEW</li> Trying to install a
 *                        V2C file with an update counter that is out of
 *                        sequence with the update counter in the Sentinel
 *                        protection key. The first value in the file is more
 *                        than 1 greater than the value in the Sentinel
 *                        protection key
 *                      <li>HASP_UNKNOWN_RECIPIENT</li> In case of an H2R:
 *                        Update can only be applied to the Recipient
 *                        specified in hasp_detach(), not to this machine
 *                      <li>HASP_HASP_INACTIVE</li> Inactive Sentinel
 *                        SL-AdminMode/SL-UserMode key-id
 *                      <li>HASP_UPDATE_ALREADY_ADDED</li> Sentinel
 *                        SL-AdminMode/SL-UserMode V2C update(s) already applied
 *                      <li>HASP_REHOST_ALREADY_APPLIED</li> In case of SL-AdminMode
 *                       /SL-UserMode H2H: Specified H2H already applied
 *                      <li>HASP_LICENSE_REHOSTED</li> In case of SL-AdminMode
 *                       /SL-UserMode V2C: Specified V2C already rehosted to another
 *                       host
 *                    </ul>
 *
 * \sa hasp_free()
 *
 */
hasp_status_t HASP_CALLCONV hasp_update(const char *update_data,
                char **ack_data);


/**
 * \brief Detaches or cancels an attached license, according to customizable
 * parameters.
 *
 * Starting from Sentinel LDK version 6.0, the "hasp_detach" API has been deprecated.
 * Thales recommends that user should use the "hasp_transfer" API to perform
 * the detach/cancel actions.This API has been retained for backward compatibility.
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * You do not need to be logged in to a  Sentinel Feature in order to use
 * this function.
 *
 * This function is used to detach a license for a Product (i.e. all Sentinel
 * Features and Memory files which belong to this Product) from a Sentinel
 * SL Protection key. The function returns a H2R file which must then be
 * applied on the recipient machine using hasp_update() or the ACC.
 *
 * This function only works with Sentinel SL Protection Keys; Sentinel HL
 * Protection Keys are ignored.
 *
 * This function can also be used on the recipient machine to cancel an
 * attached license. In this case, the recipient parameter is ignored and
 * should be set to NULL. For cancelling, the function returns a R2H file
 * which must be applied on the host machine using hasp_update() or the
 * ACC. If the detached Product is already expired, no R2H file will be
 * returned.
 *
 * The required Vendor Codes are stored in a VendorCodes folder in
 * your system. Without the correct Vendor Code, the function call
 * cannot succeed.
 *
 * \param detach_action Parameters for the operation, in XML format. For
 *                      more information, see the accompanying
 *                      Sentinel Licensing API help documentation.
 * \param scope       Search parameters for the Product that is to be
 *                      detached
 * \param vendor_code Pointer to the Vendor Code
 * \param recipient   Definition in XML format of the recipient computer,
 *                      on which the detached Product will be installed.
 *                      This information can be retrieved using either
 *                      @a hasp_get_info or @a hasp_get_sessioninfo
 *                      together with the format specifier
 *                      @a HASP_RECIPIENT.
 *                      Set to NULL if an attached protection key is cancelled.
 * \param info        Pointer to the information that is retrieved, in
 *                      XML format. This information is a V2C, which can
 *                      then be installed on the recipient computer
 *                      via @a hasp_update. Use @a hasp_free to release this
 *                      pointer after use.
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INV_DETACH_ACTION</li> Invalid XML
 *                        "detach_action" parameter
 *                      <li>HASP_INV_RECIPIENT</li> Invalid XML "recipient"
 *                        parameter
 *                      <li>HASP_TOO_MANY_PRODUCTS</li> Scope for hasp_detach
 *                        does not specify a unique Parameter
 *                      <li>HASP_TOO_MANY_USERS</li> Too many users currently
 *                        connected, or: at least one detachable Feature
 *                        does not have enough network seats available
 *                      <li>HASP_ACCESS_DENIED</li> Request cannot be
 *                        processed due to ACC restrictions
 *                      <li>HASP_FEATURE_EXPIRED</li> All detachable
 *                        Features are expired
 *                      <li>HASP_INV_PRODUCT</li> Invalid Product information
 *                      <li>HASP_INV_DURATION</li> In the case of a new
 *                        detachable license, duration exceeds maximum allowed
 *                        OR, in the case of a detachable license extension,
 *                        expiration date earlier than original date
 *                        or too short (if an existing detached Product is
 *                        extended, and the new expiration date is earlier
 *                        than the original expiration date)
 *                      <li>HASP_INSUF_MEM</li> Out of memory
 *                      <li>HASP_DEVICE_ERR</li> Input/Output error in Sentinel
 *                        SL secure storage, OR in case of a Sentinel HL key,
 *                        USB communication error
 *                      <li>HASP_LOCAL_COMM_ERR</li> Communication error
 *                        between API and local Sentinel License Manager
 *                      <li>HASP_REMOTE_COMM_ERR</li> Communication error
 *                        between local and remote Sentinel License Manager
 *                    </ul>
 *
 * \sa hasp_get_info()
 * \sa hasp_update()
 * \sa hasp_free()
 */
#if (_MSC_VER >= 1400)
__declspec(deprecated)hasp_status_t HASP_CALLCONV hasp_detach(const char *detach_action,
                const char *scope,
                hasp_vendor_code_t vendor_code,
                const char *recipient,
                char **info);
#elif defined(__GNUC__)
hasp_status_t HASP_CALLCONV hasp_detach(const char *detach_action,
                const char *scope,
                hasp_vendor_code_t vendor_code,
                const char *recipient,
                char **info)__attribute__ ((deprecated));
#else
hasp_status_t HASP_CALLCONV hasp_detach(const char *detach_action,
                const char *scope,
                hasp_vendor_code_t vendor_code,
                const char *recipient,
                char **info);
#endif

/**
 * \brief: Deprecate the above API "hasp_detach()" , This API performs
 * same functionalities as "hasp_detach()" does. Along with this,
 * "hasp_transfer()" API is used to rehost the SL-AdminMode/SL-UserMode
 * V2C from one machine to another machine.
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * You do not need to be logged in to a Sentinel Feature in
 * order to use this function.
 *
 * This function is used to perform the following task as per its
 * "action" parameter.
 * for "detach" action: detach a license for a Product (i.e. all
 *                      Sentinel Features and Memory files which
 *                      belong to this Product) from a Sentinel
 *                      SL/SL-AdminMode/SL-UserMode key. The function
 *                      returns a bufferwhich should be saved as H2R file.
 *
 * for "cancel" action: This action runs on the recipient machine to
 *                      cancel an attached license. In this case, the
 *                      recipient parameter is ignored and  should be
 *                      set to NULL. For cancelling, the function returns
 *                      a buffer which must be applied on the host machine
 *                      using hasp_update() or ACC If the detached Product
 *                      is already expired, no buffer will be returned.
 *
 * for "rehost" action: create a tranferable a license for given container
 *                      (i.e. all Sentinel Features and Memory files
 *                      which belong to this container) from SL-AdminMode/
 *                      SL-UserMode Protection key. The function returns
 *                      buffer on success which must be saved as V2C file.
 *                      hasp_update() or ACC is used to apply this on
 *                      destination machine.
 *
 * This function only works with Sentinel SL/SL-AdminMode/SL-UserMode
 * Protection Keys; Sentinel HL Protection Keys are ignored.
 *
 * The required Vendor Codes are stored in a VendorCodes folder in
 * your system. Without the correct Vendor Code, the function call
 * cannot succeed.
 *
 * \param action      Parameters for the operation, in XML format. For
 *                      more information, see the accompanying
 *                      Sentinel Licensing API help documentation.
 * \param scope       Search parameters for the conatiner-id that is to be
 *                      re-hosted. For more information, see the accompanying
 *                      Sentinel Licensing API help documentation.
 * \param vendor_code Pointer to the Vendor Code
 * \param recipient   Definition in XML format of the recipient computer,
 *                      on which the detached Product will be installed.
 *                      This information can be retrieved using either
 *                      @a hasp_get_info or @a hasp_get_sessioninfo
 *                      together with the format specifier
 *                      @a HASP_RECIPIENT.
 * \param info        Pointer to the information that is retrieved, in
 *                      XML format. This information is a V2C, which can
 *                      then be installed on the destination computer
 *                      via @a hasp_update. Use @a hasp_free to release this
 *                      pointer after use.
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INV_ACTION</li> Invalid XML
 *                        "action" parameter
 *                      <li>HASP_INV_RECIPIENT</li> Invalid XML "recipient"
 *                        parameter
 *                      <li>HASP_TOO_MANY_PRODUCTS</li> Scope for hasp_transfer
 *                        for detach action does not specify a unique Parameter
 *                      <li>HASP_TOO_MANY_USERS</li> Too many users currently
 *                        connected, or: at least one detachable Feature
 *                        does not have enough network seats available
 *                      <li>HASP_ACCESS_DENIED</li> Request cannot be
 *                        processed due to ACC restrictions
 *                      <li>HASP_FEATURE_EXPIRED</li> All detachable
 *                        Features are expired
 *                      <li>HASP_INV_PRODUCT</li> Invalid Product information
 *                      <li>HASP_INV_DURATION</li> In the case of a new
 *                        detachable license, duration exceeds maximum allowed
 *                        OR, in the case of a detachable license extension,
 *                        expiration date earlier than original date
 *                        or too short (if an existing detached Product is
 *                        extended, and the new expiration date is earlier
 *                        than the original expiration date)
 *                      <li>HASP_TOO_MANY_KEYS</li> Scope for hasp_transfer
 *                        does not specify a unique Parameter
 *                      <li>HASP_ACCESS_DENIED</li> Request cannot be
 *                        processed due to ACC restrictions
 *                      <li>HASP_INSUF_MEM</li> Out of memory
 *                      <li>HASP_DEVICE_ERR</li> Input/Output error in Sentinel
 *                        SL/SL-AdminMode/SL-UserMode secure storage, OR in
 *                        case of a Sentinel HL key, USB communication error
 *                      <li>HASP_LOCAL_COMM_ERR</li> Communication error
 *                        between API and local Sentinel License Manager
 *                      <li>HASP_NO_DEATCHABLE_FEATURE</li> In case of H2R:
 *                        No detachable feature found in specified product
 *                      <li><HASP_OLD_LM></li> Sentinel License Manager is
 *                        not supported to SL-AdminMode/ SL-UserMode
 *                      <li><HASP_HASP_INACTIVE></li> SL-AdminMode/
 *                        SL-UserMode container is inactive
 *                      <li><HASP_REHOST_NOT_ALLOWED></li> Specified
 *                        SL-AdminMode/SL-UserMode container is not
 *                        allowed for rehost
 *                    </ul>
 *
 * \sa hasp_get_info()
 * \sa hasp_update()
 * \sa hasp_free()
 */
hasp_status_t HASP_CALLCONV hasp_transfer(const char *action,
                const char *scope,
                hasp_vendor_code_t vendor_code,
                const char *recipient,
                char **info);

/**
 * @}
 */



/**
 * @defgroup hasp_util Utility functions
 *
 * @{
 */

/**
 * \brief Retrieves version and build number of the Sentinel library
 *
 * \param major_version Pointer to retrieve the major version number
 * \param minor_version Pointer to retrieve the minor version number
 * \param generation_version  Pointer to retrieve the generation version number
 * \param build_number  Pointer to retrieve the build number
 * \param vendor_code   Pointer to the Vendor Code
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                    </ul>
 *
 * \remark Any pointer other than the vendor_code can be NULL if its
 * information is not required.
 *
 */
hasp_status_t HASP_CALLCONV hasp_get_version(unsigned int *major_version,
                unsigned int *minor_version,
                unsigned int *generation_version,
                unsigned int *build_number,
                hasp_vendor_code_t vendor_code);

/**
 * \brief Converts a date and time value to hasptime (the number of
 * elapsed seconds since January 1 1970).
 *
 * \param day         Input for day value (range 1-31)
 * \param month       Input for month value (range 1-12)
 * \param year        Input for year value (range 1970+)
 * \param hour        Input for hour value (range 0-23)
 * \param minute      Input for minute value (range 0-59)
 * \param second      Input for second value (range 0-59)
 * \param time        Pointer to the resulting time value
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INV_TIME</li> Passed time value is outside
 *                        the supported value range
 *                    </ul>
 *
 * \remark Time values are in UTC.
 *
 * \sa hasp_hasptime_to_datetime()
 *
 */
hasp_status_t HASP_CALLCONV hasp_datetime_to_hasptime(unsigned int day,
                unsigned int month,
                unsigned int year,
                unsigned int hour,
                unsigned int minute,
                unsigned int second,
                hasp_time_t *time);

/**
 * \brief Converts a time value (elapsed seconds since January 1 1970)
 * into a date and time
 *
 * \param time        The input time value
 * \param day         Pointer to the day value
 * \param month       Pointer to the month value
 * \param year        Pointer to the year value
 * \param hour        Pointer to the hour value
 * \param minute      Pointer to the minute value
 * \param second      Pointer to the second value
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully
 *                        completed
 *                      <li>HASP_INV_TIME</li> Passed time value outside
 *                        of supported value range
 *                    </ul>
 *
 * \remark Time values are in UTC.
 *
 * \sa hasp_datetime_to_hasptime()
 *
 */
hasp_status_t HASP_CALLCONV hasp_hasptime_to_datetime(hasp_time_t time,
                unsigned int *day,
                unsigned int *month,
                unsigned int *year,
                unsigned int *hour,
                unsigned int *minute,
                unsigned int *second);

/**
 * \brief Update information regarding a login session for a Sentinel protection key
 *
 * The information that can currently be updated is the number of executions to
 * consume from the license for a single login session.
 *
 * \param handle Handle for the session
 * \param option Pointer to the XML code that defines the data to be updated by
 *                 the function
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully completed
 *                      <li>HASP_INV_OPTION</li> Option string has an invalid format or content
 *                      <li>HASP_BROKEN_SESSION</li> Session has been interrupted
 *                    </ul>
 * \sa hasp_get_sessioninfo()
 *
 */
hasp_status_t HASP_CALLCONV hasp_update_session(hasp_handle_t handle,
                const char *option);

/**
 * \brief Configure the behavior of the Licensing API for a specific application run-time session
 *
 * <b>Sentinel Licensing API Usage Notes</b><br>
 * This function should be called before you call the hasp_login or hasp_login_scope function.
 * The configuration defined by the function remains active for the duration of the application run-time session.
 *
 *
 * \param config       Parameters for the various configuration operations to be performed, in XML format.
 *                     For more information, see the accompanying Sentinel Licensing API help documentation.
 * \param vendor_code  Pointer to the vendor code
 *
 *
 * \return            <ul>
 *                      <li>HASP_STATUS_OK</li> Request was successfully completed
 *                      <li>HASP_INVALID_PARAMETER</li> Invalid function parameter
 *                      <li>HASP_INV_FORMAT</li> Unrecognized format string
 *                      <li>HASP_INSUF_MEM</li> Out of memory
 *                      <li>HASP_INT_ERR</li> Internal error occurred in API
 *                    </ul>
 *
 */
hasp_status_t HASP_CALLCONV hasp_config(const char *config,
                hasp_vendor_code_t vendor_code);

/**
 * @}
 */

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* __HASP_API_H__ */

