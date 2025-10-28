// Copyright (C) 2025 THALES. All rights reserved.

#include "hasp_api_cpp.h"
#include "errorprinter.h"
#include <iostream>

using namespace std;

ErrorPrinter::ErrorPrinter()
{
    errorMap.insert(StatusMap::value_type(HASP_STATUS_OK, "Request completed successfully"));
    errorMap.insert(StatusMap::value_type(HASP_MEM_RANGE, "Request exceeds the Sentinel protection key memory file"));
    errorMap.insert(StatusMap::value_type(HASP_INV_PROGNUM_OPT, "Invalid program number option"));
    errorMap.insert(StatusMap::value_type(HASP_INSUF_MEM, "The system is out of memory"));
    errorMap.insert(StatusMap::value_type(HASP_TMOF, "Application has too many open login sessions"));
    errorMap.insert(StatusMap::value_type(HASP_ACCESS_DENIED, "Access to Feature, Sentinel protection key, or functionality was denied"));
    errorMap.insert(StatusMap::value_type(HASP_INCOMPAT_FEATURE, "Legacy decryption function is not compatible with this Feature"));
    errorMap.insert(StatusMap::value_type(HASP_HASP_NOT_FOUND, "Sentinel protection key was not found"));
    errorMap.insert(StatusMap::value_type(HASP_TOO_SHORT, "Encrypted/decrypted data length is too short to execute function call"));
    errorMap.insert(StatusMap::value_type(HASP_INV_HND, "Invalid login handle passed to a function"));
    errorMap.insert(StatusMap::value_type(HASP_INV_FILEID, "The specified file ID is not recognized by the API"));
    errorMap.insert(StatusMap::value_type(HASP_OLD_DRIVER, "Installed driver or daemon is too old. Install a later Run-time Environment"));
    errorMap.insert(StatusMap::value_type(HASP_NO_TIME, "Real-time clock and V-Clock are not available"));
    errorMap.insert(StatusMap::value_type(HASP_SYS_ERR, "Generic error from host system call"));
    errorMap.insert(StatusMap::value_type(HASP_NO_DRIVER, "Hardware key driver was not found"));
    errorMap.insert(StatusMap::value_type(HASP_INV_FORMAT, "An invalid license update or an invalid format string was passed"));
    errorMap.insert(StatusMap::value_type(HASP_REQ_NOT_SUPP, "Unable to execute the function in this context; the requested functionality is not supported"));
    errorMap.insert(StatusMap::value_type(HASP_INV_UPDATE_OBJ, "The binary data passed to the function does not contain a valid update"));
    errorMap.insert(StatusMap::value_type(HASP_KEYID_NOT_FOUND, "A Sentinel protection key with the requested key ID was not found"));
    errorMap.insert(StatusMap::value_type(HASP_INV_UPDATE_DATA, "Required XML tags were not found OR contents in binary data are missing or invalid"));
    errorMap.insert(StatusMap::value_type(HASP_INV_UPDATE_NOTSUPP, "The update request is not supported by the Sentinel protection key"));
    errorMap.insert(StatusMap::value_type(HASP_INV_UPDATE_CNTR, "An update counter mismatch occurred"));
    errorMap.insert(StatusMap::value_type(HASP_INV_VCODE, "An invalid vendor code was passed to a function"));
    errorMap.insert(StatusMap::value_type(HASP_ENC_NOT_SUPP, "The Sentinel protection key does not support the encryption type used. You may have an obsolete key"));
    errorMap.insert(StatusMap::value_type(HASP_INV_TIME, "The date/time value passed is outside the supported range"));
    errorMap.insert(StatusMap::value_type(HASP_NO_BATTERY_POWER, "The battery for the HL Time key or HL NetTime key is depleted"));
    errorMap.insert(StatusMap::value_type(HASP_NO_ACK_SPACE, "Acknowledge data requested by update, but ack_data parameter is NULL"));
    errorMap.insert(StatusMap::value_type(HASP_TS_DETECTED, "An application is running on a remote desktop (terminal server)"));
    errorMap.insert(StatusMap::value_type(HASP_FEATURE_TYPE_NOT_IMPL, "The requested Feature type is not implemented"));
    errorMap.insert(StatusMap::value_type(HASP_UNKNOWN_ALG, "An unrecognized algorithm was used in an H2R/V2C file"));
    errorMap.insert(StatusMap::value_type(HASP_INV_SIG, "Signature verification operation failed"));
    errorMap.insert(StatusMap::value_type(HASP_FEATURE_NOT_FOUND, "The requested Feature was not found"));
    errorMap.insert(StatusMap::value_type(HASP_NO_LOG, "Access log or trace log is not enabled"));
    errorMap.insert(StatusMap::value_type(HASP_LOCAL_COMM_ERR, "A communication error occurred between the API and the local Sentinel License Manager"));
    errorMap.insert(StatusMap::value_type(HASP_UNKNOWN_VCODE, "The vendor code is not recognized by the API library"));
    errorMap.insert(StatusMap::value_type(HASP_INV_SPEC, "An invalid XML login specification was passed to a function"));
    errorMap.insert(StatusMap::value_type(HASP_INV_SCOPE, "XML scope is not valid"));
    errorMap.insert(StatusMap::value_type(HASP_TOO_MANY_KEYS, "The scope matches too many Sentinel protection keys"));
    errorMap.insert(StatusMap::value_type(HASP_TOO_MANY_USERS, "Too many concurrent user sessions are connected"));
    errorMap.insert(StatusMap::value_type(HASP_BROKEN_SESSION, "A login session was interrupted due to certain updates"));
    errorMap.insert(StatusMap::value_type(HASP_REMOTE_COMM_ERR, "A communication error occurred between local and remote Sentinel License Managers"));
    errorMap.insert(StatusMap::value_type(HASP_FEATURE_EXPIRED, "The Feature has expired" ));
    errorMap.insert(StatusMap::value_type(HASP_OLD_LM, "The existing version of the Sentinel License Manager does not support the API request" ));
    errorMap.insert(StatusMap::value_type(HASP_DEVICE_ERR, "Input/output error occurred in secure storage area of Sentinel SL key OR a USB error occurred when communicating with a Sentinel HL key" ));
    errorMap.insert(StatusMap::value_type(HASP_UPDATE_BLOCKED, "Update installation is not permitted - the update was already applied" ));
    errorMap.insert(StatusMap::value_type(HASP_TIME_ERR, "System time has been tampered with" ));
    errorMap.insert(StatusMap::value_type(HASP_SCHAN_ERR, "Communication error occurred in a secure channel" ));
    errorMap.insert(StatusMap::value_type(HASP_STORAGE_CORRUPT, "Secure storage area of Sentinel SL protection key is corrupted" ));
    errorMap.insert(StatusMap::value_type(HASP_NO_VLIB, "The customized vendor library (haspvlib_<vendorID>.*) cannot be located" ));
    errorMap.insert(StatusMap::value_type(HASP_INV_VLIB, "The vendor library cannot be loaded" ));
    errorMap.insert(StatusMap::value_type(HASP_SCOPE_RESULTS_EMPTY, "Unable to locate any Features that satisfy the provided scope" ));
    errorMap.insert(StatusMap::value_type(HASP_VM_DETECTED, "The license does not allow running the application on a virtual machine" ));
    errorMap.insert(StatusMap::value_type(HASP_HARDWARE_MODIFIED, "Sentinel SL key is locked to a different machine" ));
    errorMap.insert(StatusMap::value_type(HASP_USER_DENIED, "Login is denied because of user restrictions" ));
    errorMap.insert(StatusMap::value_type(HASP_UPDATE_TOO_OLD, "Attempting to apply a V2C file that was already applied" ));
    errorMap.insert(StatusMap::value_type(HASP_UPDATE_TOO_NEW, "Attempting to apply V2C files for a Sentinel protection key in the wrong sequence" ));
    errorMap.insert(StatusMap::value_type(HASP_OLD_VLIB, "Your vendor library version is not supported by the current version of the Licensing API" ));
    errorMap.insert(StatusMap::value_type(HASP_UPLOAD_ERROR, "An attempt to check in a file (such as V2C or H2R) using Admin Control Center failed due to invalid format" ));
    errorMap.insert(StatusMap::value_type(HASP_INV_RECIPIENT, "Invalid XML \"recipient\" parameter" ));
    errorMap.insert(StatusMap::value_type(HASP_INV_DETACH_ACTION, "Invalid XML \"action\" parameter" ));
    errorMap.insert(StatusMap::value_type(HASP_TOO_MANY_PRODUCTS, "The scope specified in hasp_transfer() does not identify a unique Product" ));
    errorMap.insert(StatusMap::value_type(HASP_INV_PRODUCT, "Invalid Product information" ));
    errorMap.insert(StatusMap::value_type(HASP_UNKNOWN_RECIPIENT, "The update can only be applied to the Recipient specified in hasp_transfer() and not to this machine" ));
    errorMap.insert(StatusMap::value_type(HASP_INV_DURATION, "The duration is invalid" ));
    errorMap.insert(StatusMap::value_type(HASP_CLONE_DETECTED, "Cloned Sentinel SL secure storage area was detected" ));
	errorMap.insert(StatusMap::value_type(HASP_UPDATE_ALREADY_ADDED, "The specified V2C or V2CP update was already installed in the License Manager service" ));
	errorMap.insert(StatusMap::value_type(HASP_HASP_INACTIVE, "The specified key ID identifies an inactive key" ));
	errorMap.insert(StatusMap::value_type(HASP_NO_DETACHABLE_FEATURE, "No detachable Feature exists" ));
	errorMap.insert(StatusMap::value_type(HASP_TOO_MANY_HOSTS, "Scope does not identify a unique host" ));
	errorMap.insert(StatusMap::value_type(HASP_REHOST_NOT_ALLOWED, "Rehost action is not allowed for the specified key ID" ));
	errorMap.insert(StatusMap::value_type(HASP_LICENSE_REHOSTED, "The original license has been rehosted to another machine" ));
	errorMap.insert(StatusMap::value_type(HASP_REHOST_ALREADY_APPLIED, "An old rehost license cannot be applied; a rehost-counter mismatch occurred" ));
	errorMap.insert(StatusMap::value_type(HASP_CANNOT_READ_FILE, "A V2C or V2CP file was not found or access was denied" ));
	errorMap.insert(StatusMap::value_type(HASP_EXTENSION_NOT_ALLOWED, "The license cannot be extended because the number of detached licenses is greater than the number of concurrent licenses allowed" ));
	errorMap.insert(StatusMap::value_type(HASP_DETACH_DISABLED, "Detach of the license not allowed because the Product contains a VM-disabled Feature and the host machine is a virtual machine" ));
	errorMap.insert(StatusMap::value_type(HASP_REHOST_DISABLED, "You cannot rehost the license to a virtual machine" ));
	errorMap.insert(StatusMap::value_type(HASP_DETACHED_LICENSE_FOUND, "The user attempted to format an SL AdminMode key or to migrate an SL Legacy key to an SL AdminMode key. However, a Product is currently detached from the key" ));
	errorMap.insert(StatusMap::value_type(HASP_RECIPIENT_OLD_LM, "The fingerprint of the target machine was collected using tools (RUS utility or Licensing API) earlier than Sentinel LDK 7.0" ));
	errorMap.insert(StatusMap::value_type(HASP_SECURE_STORE_ID_MISMATCH, "A secure storage ID mismatch occurred" ));
	errorMap.insert(StatusMap::value_type(HASP_DUPLICATE_HOSTNAME, "The license is locked to a specific hostname; however, two or more machines with this hostname were found in the network" ));
	errorMap.insert(StatusMap::value_type(HASP_MISSING_LM, "The Sentinel License Manager is required for this operation" ));
	errorMap.insert(StatusMap::value_type(HASP_FEATURE_INSUFFICIENT_EXECUTION_COUNT, "The application tried to consume or reserve multiple executions while logging in to a Feature. However, the license does not contain the number of executions that were requested" ));
	errorMap.insert(StatusMap::value_type(HASP_INCOMPATIBLE_PLATFORM, "Attempting to perform an operation that is not compatible with target platform" ));
	errorMap.insert(StatusMap::value_type(HASP_HASP_DISABLED, "The protection key is disabled due to suspected tampering" ));
	errorMap.insert(StatusMap::value_type(HASP_SHARING_VIOLATION, "The protection key is not accessible due to a USB sharing violation" ));
	errorMap.insert(StatusMap::value_type(HASP_KILLED_SESSION, "The session was interrupted due a network malfunction, or the session was interrupted manually from Admin Control Center" ));
	errorMap.insert(StatusMap::value_type(HASP_VS_DETECTED, "The license does not allow installing the application on a virtual machine" ));
	errorMap.insert(StatusMap::value_type(HASP_IDENTITY_REQUIRED, "A client identity is required to run this application" ));
	errorMap.insert(StatusMap::value_type(HASP_IDENTITY_UNAUTHENTICATED, "The client identity is not authenticated" ));
	errorMap.insert(StatusMap::value_type(HASP_IDENTITY_DISABLED, "The client identity is disabled" ));
	errorMap.insert(StatusMap::value_type(HASP_IDENTITY_DENIED, "The client identity does not have the required permissions" ));
	errorMap.insert(StatusMap::value_type(HASP_IDENTITY_SHARING_VIOLATION, "Your license is in use on a different machine" ));
	errorMap.insert(StatusMap::value_type(HASP_IDENTITY_TOO_MANY_MACHINES, "The maximum number of machines usable by the client identity was reached" ));
    errorMap.insert(StatusMap::value_type(HASP_IDENTITY_SERVER_NOT_READY, "The server is not ready to authenticate"));
    errorMap.insert(StatusMap::value_type(HASP_UPDATE_OUT_OF_SYNC, "Trying to install a V2C file with an update counter that is out of sync with the update counter in the Sentinel protection key"));
    errorMap.insert(StatusMap::value_type(HASP_REMOTE_SHARING_VIOLATION, "There were multiple attempts to access the protection key from a remote machine using a proxy"));
    errorMap.insert(StatusMap::value_type(HASP_CLOUD_SESSION_OCCUPIED_REMOTELY, "A cloud licensing session was released because the client requested the seat from a different location"));
    errorMap.insert(StatusMap::value_type(HASP_CLOUD_MISSING_AUTHORIZATION, "Cloud licensing authorization is required to use this license"));
    errorMap.insert(StatusMap::value_type(HASP_INV_NETWORK_SEATS, "Invalid seat value in network detach. The seat count cannot be decreased when modifying a detach"));
    errorMap.insert(StatusMap::value_type(HASP_NETWORK_DETACH_DISABLED, "Network detach of seats with concurrency is disabled on a Product with only unlimited-concurrency Features"));
    errorMap.insert(StatusMap::value_type(HASP_CLOUD_NOT_SUPP, "The required functionality is not supported for cloud licenses"));
    errorMap.insert(StatusMap::value_type(HASP_CLOUD_NOT_TRUSTED, "Only trusted licenses can be installed in the trusted license storage"));
    errorMap.insert(StatusMap::value_type(HASP_CLOUD_STORAGE_COMM_ERR, "A communication error ocurred with the license storage"));
    errorMap.insert(StatusMap::value_type(HASP_IDENTITY_EXPIRED, "Your client identity has expired"));
    errorMap.insert(StatusMap::value_type(HASP_INV_OPTION, "The option value specified for the API function is not valid"));
    errorMap.insert(StatusMap::value_type(HASP_CLOUD_STORAGE_BUSY, "The license server is overloaded. Retry the operation in a few seconds"));
    errorMap.insert(StatusMap::value_type(HASP_MACHINE_DENIED, "This machine cannot be used - the fingeprint is invalid or not accessible"));
    errorMap.insert(StatusMap::value_type(HASP_MACHINE_DISABLED, "The application license is not accessible because this machine is disabled"));
    errorMap.insert(StatusMap::value_type(HASP_IDENTITY_RATE_LIMIT_EXCEEDED, "The rate at which identity requests are received exceeded the contracted limit. Try again later"));
    errorMap.insert(StatusMap::value_type(HASP_FEATURE_START_DATE_NOT_REACHED, "The start date for the Feature has not yet arrived"));
    errorMap.insert(StatusMap::value_type(HASP_IDENTITY_TEMPORARILY_NOT_ACCESSIBLE, "The client identity is temporarily not accessible. Try again in a few seconds"));
    errorMap.insert(StatusMap::value_type(HASP_CONFLICTING_AUTHENTICATION_METHODS, "You cannot use both an identity string and a JWT for the same server address"));
    errorMap.insert(StatusMap::value_type(HASP_ACCESS_TOKEN_IS_INVALID, "The JWT or LM access token is invalid. Restart the operation"));
    errorMap.insert(StatusMap::value_type(HASP_ACCESS_TOKEN_EXPIRED, "The JWT or LM access token has expired. Restart the operation"));
    errorMap.insert(StatusMap::value_type(HASP_NO_API_DYLIB, "Unable to locate the dynamic library for this vendor code" ));
    errorMap.insert(StatusMap::value_type(HASP_INV_API_DYLIB, "The dynamic library for this vendor code cannot be loaded, possibly due to corruption" ));
    errorMap.insert(StatusMap::value_type(HASP_INCOMPLETE_API_DYLIB, "The dynamic library for this vendor code is too old and a requested function was not found"));
    errorMap.insert(StatusMap::value_type(HASP_INVALID_OBJECT, "Object was incorrectly initialized" ));
    errorMap.insert(StatusMap::value_type(HASP_INVALID_PARAMETER, "An invalid function parameter was specified" ));
    errorMap.insert(StatusMap::value_type(HASP_ALREADY_LOGGED_IN, "Attempting to log in twice to the same object" ));
    errorMap.insert(StatusMap::value_type(HASP_ALREADY_LOGGED_OUT, "Attempting to log out twice from the same object" ));
    errorMap.insert(StatusMap::value_type(HASP_OPERATION_FAILED, "Incorrect use of system or platform"));
    errorMap.insert(StatusMap::value_type(HASP_NO_EXTBLOCK, "An internal error occurred: No classic memory extension block is available" ));
	
	errorMap.insert(StatusMap::value_type(HASP_INV_PORT_TYPE, "An internal error occurred: Invalid port type" ));
	errorMap.insert(StatusMap::value_type(HASP_INV_PORT, "An internal error occurred: Invalid port value" ));
    errorMap.insert(StatusMap::value_type(HASP_NET_DLL_BROKEN, "The .NET DLL appears to be broken"));
    errorMap.insert(StatusMap::value_type(HASP_NOT_IMPL, "The requested functionality is not supported" ));
	
    errorMap.insert(StatusMap::value_type(HASP_INT_ERR, "An internal error ocurred in the API" ));
	
    errorMap.insert(StatusMap::value_type(HASP_FIRST_HELPER, "Reserved for Sentinel helper libraries" ));
	
    errorMap.insert(StatusMap::value_type(HASP_FIRST_HASP_ACT, "Reserved for Sentinel Activation API" ));
}

void ErrorPrinter::printError(haspStatus status)
{
    StatusMap::const_iterator error = errorMap.find(status);
    if(error == errorMap.end())
        cout<<"unknown error: "<<status<<endl;
    else
        cout<<error->second<<endl;
}

const char* ErrorPrinter::getError(haspStatus status)
{
    StatusMap::const_iterator error = errorMap.find(status);
    if(error == errorMap.end())
        return "Unknown error";
    else
        return error->second;
}
