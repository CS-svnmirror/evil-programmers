enum {
  mName,
  mNameDisk,
  mRootName,
  mExtMain,
  mExtError,
  mExtWarning,
  mExtInformation,
  mExtAuditSuccess,
  mExtAuditFailure,
  mExtNameError,
  mFileDate,
  mFileTime,
  mFileUser,
  mFileComputer,
  mFileEventID,
  mFileSource,
  mFileType,
  mFileCategory,
  mFileDescription,
  mFileData,
  mFileErr1,
  mFileErr2,
  mTypeError,
  mTypeWarning,
  mTypeInformation,
  mTypeSuccessAudit,
  mTypeFailureAudit,
  mTypeUnknown,
  mTitleTime,
  mTitleSource,
  mTitleCategory,
  mTitleEvent,
  mTitleUser,
  mTitleComputer,
  mCpyDlgCopyTitle,
  mCpyDlgMoveTitle,
  mCpyDlgCopyOk,
  mCpyDlgMoveOk,
  mCpyDlgCancel,
  mCpyDlgCopyTox1,
  mCpyDlgCopyTo234,
  mCpyDlgCopyToN,
  mCpyDlgMoveTox1,
  mCpyDlgMoveTo234,
  mCpyDlgMoveToN,
  mClearLog,
  mConfigAddToDisksMenu,
  mConfigDisksMenuDigit,
  mConfigAddToPluginMenu,
  mConfigBrowseEvtFiles,
  mConfigStripExtension,
  mConfigRestore,
  mConfigScan1,
  mConfigScan2,
  mConfigShowHeader,
  mConfigShowDescription,
  mConfigShowData,
  mConfigPrefix,
  mConfigSave,
  mConfigCancel,
  mSelCompTitle,
  mSelCompLabel,
  mSelCompFootnote,
  mExistSource,
  mExistDestination,
  mExistDestAlreadyExists,
  mExistAcceptChoice,
  mExistOverwrite,
  mExistSkip,
  mExistAppend,
  mExistCancel,
  mRetryError,
  mRetryFrom,
  mRetryTo,
  mRetryRetry,
  mRetrySkip,
  mRetryCancel,
  mClearCancel,
  mClearClear,
  mClearSkip,
  mOtherConnecting,
  mOtherScanning,
  mError,
  mErr1,
  mErr2,
  mKeyBackup,
  mKeyMove,
  mKeyClear,
  mKeyRemote,
  mKeyLocal,
  mKeyViewData,
  mKeyEditData,
  mOk,
  mPanelTypeDir0,
  mPanelSizeDir0,
  mColonTypeDir0,
  mColonSizeDir0,
  mPanelFullDir0,
  mPanelTypeDir1,
  mPanelSizeDir1,
  mColonTypeDir1,
  mColonSizeDir1,
  mPanelFullDir1,
  mPanelTypeDir2,
  mPanelSizeDir2,
  mColonTypeDir2,
  mColonSizeDir2,
  mPanelFullDir2,
  mPanelTypeDir3,
  mPanelSizeDir3,
  mColonTypeDir3,
  mColonSizeDir3,
  mPanelFullDir3,
  mPanelTypeDir4,
  mPanelSizeDir4,
  mColonTypeDir4,
  mColonSizeDir4,
  mPanelFullDir4,
  mPanelTypeDir5,
  mPanelSizeDir5,
  mColonTypeDir5,
  mColonSizeDir5,
  mPanelFullDir5,
  mPanelTypeDir6,
  mPanelSizeDir6,
  mColonTypeDir6,
  mColonSizeDir6,
  mPanelFullDir6,
  mPanelTypeDir7,
  mPanelSizeDir7,
  mColonTypeDir7,
  mColonSizeDir7,
  mPanelFullDir7,
  mPanelTypeDir8,
  mPanelSizeDir8,
  mColonTypeDir8,
  mColonSizeDir8,
  mPanelFullDir8,
  mPanelTypeDir9,
  mPanelSizeDir9,
  mColonTypeDir9,
  mColonSizeDir9,
  mPanelFullDir9,
  mPanelTypeFile0,
  mPanelSizeFile0,
  mColonTypeFile0,
  mColonSizeFile0,
  mPanelFullFile0,
  mPanelTypeFile1,
  mPanelSizeFile1,
  mColonTypeFile1,
  mColonSizeFile1,
  mPanelFullFile1,
  mPanelTypeFile2,
  mPanelSizeFile2,
  mColonTypeFile2,
  mColonSizeFile2,
  mPanelFullFile2,
  mPanelTypeFile3,
  mPanelSizeFile3,
  mColonTypeFile3,
  mColonSizeFile3,
  mPanelFullFile3,
  mPanelTypeFile4,
  mPanelSizeFile4,
  mColonTypeFile4,
  mColonSizeFile4,
  mPanelFullFile4,
  mPanelTypeFile5,
  mPanelSizeFile5,
  mColonTypeFile5,
  mColonSizeFile5,
  mPanelFullFile5,
  mPanelTypeFile6,
  mPanelSizeFile6,
  mColonTypeFile6,
  mColonSizeFile6,
  mPanelFullFile6,
  mPanelTypeFile7,
  mPanelSizeFile7,
  mColonTypeFile7,
  mColonSizeFile7,
  mPanelFullFile7,
  mPanelTypeFile8,
  mPanelSizeFile8,
  mColonTypeFile8,
  mColonSizeFile8,
  mPanelFullFile8,
  mPanelTypeFile9,
  mPanelSizeFile9,
  mColonTypeFile9,
  mColonSizeFile9,
  mPanelFullFile9,
};

enum {
  atNone,
  atOverwrite,
  atSkip,
  atAppend,
};

enum {
  rRetry,
  rSkip,
  rCancel,
};

#define FAR165_INFO_SIZE 336
#define EVENT_START_TIME 116444736000000000ULL
#define EVENTLOG_KEY "SYSTEM\\CurrentControlSet\\Services\\EventLog"
#define SMALL_BUFFER 16*1024
#define BIG_BUFFER  128*1024
#define CUSTOM_COLUMN_COUNT 6

struct EventViewer
{
  char path[MAX_PATH];
  char computer[MAX_PATH];
  char computer_oem[MAX_PATH];
  char *computer_ptr;
  int level;
  int redraw;
};

struct MsgPath
{
  char path[MAX_PATH];
};

extern void free_sid_cache(void);
extern char *GetUserName(char *computer,EVENTLOGRECORD *rec);

extern void free_category_cache(void);
extern char *GetCategory(EVENTLOGRECORD *rec);
