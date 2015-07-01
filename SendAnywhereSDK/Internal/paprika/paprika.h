#ifndef PAPRIKA_TRANSFER_H_
#define PAPRIKA_TRANSFER_H_

#include <stdbool.h>
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PAPRIKA_EXTERN

typedef void (*paprika_char_debuglog_function)(int, const char*);
typedef void (*paprika_wchar_debuglog_function)(int, const wchar_t*);

PAPRIKA_EXTERN void paprika_set_debuglog_callback(
        paprika_char_debuglog_function charCallback,
        paprika_wchar_debuglog_function wcharCallback);

typedef void (*paprika_analytics_function)(
        const char*,    // category
        const char*,    // action
        const char*,    // label
        long            // value
        );

PAPRIKA_EXTERN void paprika_set_analytics_callback(paprika_analytics_function callback);

typedef struct {
    const char* key;
    const char* value;
} AnalyticsParam;

typedef void (*paprika_fl_analytics_function)(
        const char*,        // event
        AnalyticsParam*,    // params
        size_t              // param number
        );

PAPRIKA_EXTERN void paprika_set_fl_analytics_callback(paprika_fl_analytics_function callback);

PAPRIKA_EXTERN void paprika_set_apikey(const char* key);

// auth function
typedef void* PaprikaAuthToken;

PAPRIKA_EXTERN PaprikaAuthToken paprika_auth_create();
PAPRIKA_EXTERN PaprikaAuthToken paprika_auth_create_with_deviceid(
                                    const char* id, const char* password);
PAPRIKA_EXTERN void paprika_auth_close(PaprikaAuthToken auth);

PAPRIKA_EXTERN const char* paprika_auth_get_device_id(PaprikaAuthToken auth);
PAPRIKA_EXTERN const char* paprika_auth_get_device_password(PaprikaAuthToken auth);
PAPRIKA_EXTERN const char* paprika_auth_get_user_id(PaprikaAuthToken auth);
PAPRIKA_EXTERN const char* paprika_auth_get_token(PaprikaAuthToken auth);

// option function
typedef enum {
    PAPRIKA_OPTION_API_SERVER = 0,
    PAPRIKA_OPTION_SERVER_REGION,
    PAPRIKA_OPTION_PUSH_ID,
    PAPRIKA_OPTION_PROFILE_NAME,
    PAPRIKA_OPTION_SHARED_PATH,
    PAPRIKA_OPTION_PUSH_SERVER,
    PAPRIKA_OPTION_UPLOAD_TIMEOUT,
} PaprikaOptionKey;

typedef void* PaprikaOption;

PAPRIKA_EXTERN PaprikaOption paprika_option_create();
PAPRIKA_EXTERN void paprika_option_close(PaprikaOption option);

PAPRIKA_EXTERN void paprika_option_set_value(PaprikaOption option,
                        PaprikaOptionKey key, const void* value);

// localinfo
PAPRIKA_EXTERN void paprika_local_set_osinfo(
                const char* osVersion, const char* osLanguage);
PAPRIKA_EXTERN void paprika_local_set_appinfo(
                const char* appName, const char* appVersion);
PAPRIKA_EXTERN void paprika_local_set_location(
                double latitude, double longitude);
PAPRIKA_EXTERN void paprika_local_set_device(
                const char* modelNumber, const char* carrierName, const char* networkCountry);
PAPRIKA_EXTERN void paprika_local_set_network(
                const char* deviceIp, const char* bssid, const char* networkState);

// task function

typedef enum {
    PAPRIKA_STATE_UNKNOWN = 0,

    // all task
    PAPRIKA_STATE_FINISHED,
    PAPRIKA_STATE_ERROR,
    PAPRIKA_STATE_PREPARING,

    // trasnfer task
    PAPRIKA_STATE_TRANSFERRING,

    // Push Listener
    PAPRIKA_STATE_NOTIFICATION,
} PaprikaState;

typedef enum {
    PAPRIKA_DETAILED_STATE_UNKNOWN = 0,

    // all task
    PAPRIKA_DETAILED_STATE_FINISHED_SUCCESS,
    PAPRIKA_DETAILED_STATE_FINISHED_CANCEL,
    PAPRIKA_DETAILED_STATE_FINISHED_ERROR,

    PAPRIKA_DETAILED_STATE_ERROR_WRONG_API_KEY,
    PAPRIKA_DETAILED_STATE_ERROR_SERVER_WRONG_PROTOCOL,
    PAPRIKA_DETAILED_STATE_ERROR_SERVER_NETWORK,
    PAPRIKA_DETAILED_STATE_ERROR_REQUIRED_LOGIN,
    PAPRIKA_DETAILED_STATE_ERROR_SERVER_AUTHENTICATAION,

    PAPRIKA_DETAILED_STATE_PREPARING_UPDATED_DEVICE_ID,
    PAPRIKA_DETAILED_STATE_PREPARING_UPDATED_AUTH_TOKEN,

    // transfer task
    /* PAPRIKA_TASK_UPLOAD, PAPRIKA_TASK_UPLOAD_REQ, PAPRIKA_TASK_UPLOAD_RES,
       PAPRIKA_TASK_DOWNLOAD, PAPRIKA_TASK_DOWNLOAD_REQ, PAPRIKA_TASK_DOWNLOAD_RES */
    PAPRIKA_DETAILED_STATE_PREPARING_REQUEST_KEY,
    PAPRIKA_DETAILED_STATE_PREPARING_UPDATED_KEY,
    PAPRIKA_DETAILED_STATE_PREPARING_REQUEST_MODE,
    PAPRIKA_DETAILED_STATE_PREPARING_UPDATED_MODE,
    PAPRIKA_DETAILED_STATE_PREPARING_UPDATED_FILE_LIST,
    PAPRIKA_DETAILED_STATE_PREPARING_WAIT_NETWORK,

    PAPRIKA_DETAILED_STATE_TRANSFERRING_ACTIVE,
    PAPRIKA_DETAILED_STATE_TRANSFERRING_PASSIVE,
    PAPRIKA_DETAILED_STATE_TRANSFERRING_SERVER,
    PAPRIKA_DETAILED_STATE_TRANSFERRING_START_NEW_FILE,
    PAPRIKA_DETAILED_STATE_TRANSFERRING_END_FILE,
    PAPRIKA_DETAILED_STATE_TRANSFERRING_RESUME,
    PAPRIKA_DETAILED_STATE_TRANSFERRING_PAUSE,

    PAPRIKA_DETAILED_STATE_ERROR_FILE_NETWORK,
    PAPRIKA_DETAILED_STATE_ERROR_FILE_WRONG_PROTOCOL,

    // PAPRIKA_TASK_UPLOAD
    PAPRIKA_DETAILED_STATE_ERROR_NO_REQUEST,
    PAPRIKA_DETAILED_STATE_ERROR_NO_EXIST_FILE,

    // PAPRIKA_TASK_DOWNLOAD
    PAPRIKA_DETAILED_STATE_ERROR_FILE_NO_DOWNLOAD_PATH,
    PAPRIKA_DETAILED_STATE_ERROR_FILE_NO_DISK_SPACE,

    // PAPRIKA_TASK_DOWNLOAD, PAPRIKA_TASK_DELETE_KEY, PAPRIKA_TASK_QUERY_KEY
    PAPRIKA_DETAILED_STATE_ERROR_NO_EXIST_KEY,

    // PAPRIKA_TASK_REGISTER_USER
    PAPRIKA_DETAILED_STATE_ERROR_EXIST_USER_ID,
    PAPRIKA_DETAILED_STATE_ERROR_EXIST_USER_EMAIL,
    PAPRIKA_DETAILED_STATE_ERROR_INVALID_USER_ID,
    PAPRIKA_DETAILED_STATE_ERROR_INVALID_USER_PASSWORD,

    // PAPRIKA_TASK_UPDATE_DEVICE
    PAPRIKA_DETAILED_STATE_ERROR_NEED_UPDATE,

    // PAPRIKA_TASK_PUSH_KEY
    PAPRIKA_DETAILED_STATE_ERROR_SEND_KEY_FAILED,

    // PAPRIKA_TASK_GET_FILE_LIST
    PAPRIKA_DETAILED_STATE_ERROR_WRONG_FILE_LIST,

    // Push Listener
    PAPRIKA_DETAILED_STATE_NOTIFICATION_RECEIVE_KEY,
    PAPRIKA_DETAILED_STATE_NOTIFICATION_REQUEST_UPLOAD,
    PAPRIKA_DETAILED_STATE_NOTIFICATION_REQUESTD_DOWNLOAD,

} PaprikaDetailedState;

typedef enum {
    /* PAPRIKA_TASK_UPLOAD, PAPRIKA_TASK_UPLOAD_REQ, PAPRIKA_TASK_UPLOAD_RES,
       PAPRIKA_TASK_DOWNLOAD, PAPRIKA_TASK_DOWNLOAD_REQ, PAPRIKA_TASK_DOWNLOAD_RES */
    PAPRIKA_VALUE_TRANSFER_KEY = 0,
    PAPRIKA_VALUE_TRANSFER_FILE_STATE,
    PAPRIKA_VALUE_TRANSFER_PEER_DEVICE_ID,

    // PAPRIKA_TASK_UPLOAD, PAPRIKA_TASK_UPLOAD_REQ, PAPRIKA_TASK_UPLOAD_RES,
    PAPRIKA_VALUE_UPLOAD_LINK_URL,
    PAPRIKA_VALUE_UPLOAD_EXPIRES_TIME,

    // PAPRIKA_TASK_UPLOAD_RES, PAPRIKA_TASK_DOWNLOAD_RES
    PAPRIKA_VALUE_TRANSFER_PEER_DEVICE_NAME,

    // PAPRIKA_TASK_SEARCH_NEARBY
    PAPRIKA_VALUE_DETECTED_DEVICES,

    // PAPRIKA_TASK_QUERY_FRIEND
    PAPRIKA_VALUE_DEVICE_LIST,

    // PAPRIKA_TASK_PUSH_KEY
    PAPRIKA_VALUE_PUSHKEY_IS_ACCEPT,

    // PAPRIKA_TASK_QUERY_PUSHKEY
    PAPRIKA_VALUE_PUSHKEY_INFO,

    // PAPRIKA_TASK_GET_DEVICE_LIST
    PAPRIKA_VALUE_SHARE_DEVICE_INFO,

    // PAPRIKA_TASK_GET_FILE_LIST
    PAPRIKA_VALUE_PATH_TYPE,
    PAPRIKA_VALUE_FILE_INFO,
} PaprikaValue;

typedef void* PaprikaTask;

typedef void (*paprika_listener_function)(
                    PaprikaState state,
                    PaprikaDetailedState detailedState,
                    const void* param,
                    void* userptr);

typedef struct {
    const wchar_t* name;
    const wchar_t* fullPath;
    unsigned long long size;
    unsigned long long sent;
} PaprikaTransferFileState;

typedef struct {
    unsigned int number;
    PaprikaTransferFileState* fileState;
} PaprikaAllTransferFileState;

typedef size_t (*paprika_upload_read_function)(
                char* buf, unsigned long long start, size_t n,
                void* userptr);
typedef struct {
    const wchar_t* name;
    const wchar_t* path;
    unsigned long long size;
    int time;
    paprika_upload_read_function readFunc;
    void* userData;
} PaprikaUploadFileInfo;


typedef struct {
    const wchar_t* profileName;
    const char* deviceName;
    const char* deviceId;
    const char* osType;
    bool hasPushId;
    bool isShared;
    bool isOnline;
} PaprikaDeviceInfo;

typedef struct {
    unsigned int number;
    PaprikaDeviceInfo* deviceInfo;
} PaprikaAllDeviceInfo;

typedef struct {
    const wchar_t* key;
    int expiresTime;

    int fileNumber;
    unsigned long long fileSize;
    const wchar_t* comment;
    const unsigned char* thumbnail;
    unsigned long thumbnailSize;

    const char* deviceId;
    const char* deviceName;
    const wchar_t* profileName;
    const char* osType;
} PaprikaPushKeyInfo;

typedef enum {
    PAPRIKA_FILE_TYPE_ROOT,
    PAPRIKA_FILE_TYPE_DIR,
    PAPRIKA_FILE_TYPE_FILE
} PaprikaFileType;

typedef struct {
    const wchar_t* path;
    unsigned long long size;
    int time;
    PaprikaFileType type;
    const unsigned char* thumbnail;
    unsigned long thumbnailSize;
} PaprikaFileInfo;

typedef struct {
    unsigned int number;
    PaprikaFileInfo* fileInfo;
} PaprikaAllFileInfo;

typedef enum {
    PAPRIKA_PUSH_RET_ACCEPT,
    PAPRIKA_PUSH_RET_REJECT,
    PAPRIKA_PUSH_RET_NO_RESPONSE
} PaprikaPushResult;

// send/recv function
PAPRIKA_EXTERN PaprikaTask paprika_create_update_device();
PAPRIKA_EXTERN PaprikaTask paprika_create_upload(
        const wchar_t* files[], unsigned int fileNumber,
        const wchar_t* wishKey, bool async, bool secureKey);
PAPRIKA_EXTERN PaprikaTask paprika_create_upload_stream(
        const wchar_t* files[], unsigned int fileNumber,
        const PaprikaUploadFileInfo streams[], unsigned int streamNumber,
        const wchar_t* wishKey, bool async, bool secureKey);

PAPRIKA_EXTERN PaprikaTask paprika_create_download(
        const wchar_t* key, const wchar_t* destDirPath);

PAPRIKA_EXTERN PaprikaTask paprika_create_delete_key(const wchar_t* key);

// nearby function
PAPRIKA_EXTERN PaprikaTask paprika_create_nearby_publish();
PAPRIKA_EXTERN PaprikaTask paprika_create_nearby_close();
PAPRIKA_EXTERN PaprikaTask paprika_create_nearby_search();

PAPRIKA_EXTERN PaprikaTask paprika_create_push_key(
                            const wchar_t* key, const char* deviceId,
                            const wchar_t* comment,
                            const unsigned char* thumbnail, size_t thumbnailSize);
PAPRIKA_EXTERN PaprikaTask paprika_create_query_pushkey(
                            const wchar_t* key);
PAPRIKA_EXTERN PaprikaTask paprika_create_reply_pushkey(
                            const wchar_t* key, bool isAccept);

PAPRIKA_EXTERN PaprikaTask paprika_create_query_friend(
                            const char* deviceIds[], unsigned int idNumber);

// My device function
PAPRIKA_EXTERN PaprikaTask paprika_create_register_user(
                            const char* userId,
                            const char* userPassword);
PAPRIKA_EXTERN PaprikaTask paprika_create_login_user(
                            const char* userId,
                            const char* userPassword);
PAPRIKA_EXTERN PaprikaTask paprika_create_change_user(const char* userPassword);
PAPRIKA_EXTERN PaprikaTask paprika_create_logout_user();

PAPRIKA_EXTERN PaprikaTask paprika_create_get_device_list();
PAPRIKA_EXTERN PaprikaTask paprika_create_get_file_list(
                            const char* deviceId, const wchar_t* path,
                            int thumbnailSizeX, int thumbnailSizeY, const char* thumbnailType,
                            bool isCacheOff);

PAPRIKA_EXTERN PaprikaTask paprika_create_download_req(const char* deviceId,
                            const wchar_t* files[], unsigned int fileNumber,
                            const wchar_t* destDirPath);
PAPRIKA_EXTERN PaprikaTask paprika_create_download_res(const wchar_t* key);

PAPRIKA_EXTERN PaprikaTask paprika_create_upload_req(const char* deviceId,
                            const wchar_t* files[], unsigned int fileNumber,
                            const wchar_t* destDir);
PAPRIKA_EXTERN PaprikaTask paprika_create_upload_stream_req(const char* deviceId,
                            const wchar_t* files[], unsigned int fileNumber,
                            const PaprikaUploadFileInfo streams[], unsigned int streamNumber,
                            const wchar_t* destDir);
PAPRIKA_EXTERN PaprikaTask paprika_create_upload_res(const wchar_t* key);

PAPRIKA_EXTERN PaprikaTask paprika_create_push_listener();

// general function for task
PAPRIKA_EXTERN void paprika_close(PaprikaTask task);

PAPRIKA_EXTERN void paprika_start(PaprikaTask task);
PAPRIKA_EXTERN void paprika_wait(PaprikaTask task);
PAPRIKA_EXTERN void paprika_cancel(PaprikaTask task);
PAPRIKA_EXTERN bool paprika_is_running(PaprikaTask task);

PAPRIKA_EXTERN void paprika_set_auth(PaprikaTask task, PaprikaAuthToken auth);
PAPRIKA_EXTERN void paprika_set_option(PaprikaTask task, PaprikaOption option);
PAPRIKA_EXTERN void paprika_set_listner(PaprikaTask task,
                        paprika_listener_function func, void* userptr);

PAPRIKA_EXTERN bool paprika_get_value(PaprikaTask task,
                        PaprikaValue value, void* param);

PAPRIKA_EXTERN const char* paprika_state_to_string(PaprikaState state);
PAPRIKA_EXTERN const char* paprika_detailedstate_to_string(PaprikaDetailedState state);

#ifdef __cplusplus
}
#endif

#endif // PAPRIKA_TRANSFER_H_
