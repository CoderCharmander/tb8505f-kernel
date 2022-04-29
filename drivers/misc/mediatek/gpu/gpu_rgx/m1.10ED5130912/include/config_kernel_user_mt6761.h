#define SUPPORT_VDM_CONTEXT_STORE_BUFFER_AB 
#define SUPPORT_PERCONTEXT_FREELIST 
#define SUPPORT_GPUTRACE_EVENTS 
#define GPUVIRT_VALIDATION_NUM_OS 8
#define GPUVIRT_VALIDATION_NUM_REGIONS 2
#define PVRSRV_APPHINT_OSIDREGION0MIN  "0x00000000 0x04000000 0x10000000 0x18000000 0x20000000 0x28000000 0x30000000 0x38000000"
#define PVRSRV_APPHINT_OSIDREGION0MAX  "0x3FFFFFFF 0x0FFFFFFF 0x17FFFFFF 0x1FFFFFFF 0x27FFFFFF 0x2FFFFFFF 0x37FFFFFF 0x3FFFFFFF"
#define PVRSRV_APPHINT_OSIDREGION1MIN  "0x3F000000 0x3F000000 0x3F000000 0x3F000000 0x3F000000 0x3F000000 0x3F000000 0x3F000000"
#define PVRSRV_APPHINT_OSIDREGION1MAX  "0x3FFFFFFF 0x3FFFFFFF 0x3FFFFFFF 0x3FFFFFFF 0x3FFFFFFF 0x3FFFFFFF 0x3FFFFFFF 0x3FFFFFFF"
#define RGX_FW_FILENAME "rgx.fw"
#define LINUX 
#define PVR_BUILD_DIR "mtk_android"
#define PVR_BUILD_TYPE "release"
#define PVRSRV_MODNAME "pvrsrvkm"
#define PVRSYNC_MODNAME "pvr_sync"
#define SUPPORT_RGX 1
#define RELEASE 
#define RGX_BVNC_CORE_KM_HEADER "cores/rgxcore_km_22.68.54.30.h"
#define RGX_BNC_CONFIG_KM_HEADER "configs/rgxconfig_km_22.V.54.30.h"
#define SUPPORT_MULTIBVNC_RUNTIME_BVNC_ACQUISITION 
#define SUPPORT_DBGDRV_EVENT_OBJECTS 
#define PDUMP_STREAMBUF_MAX_SIZE_MB 16
#define PVRSRV_NEED_PVR_DPF 
#define PVRSRV_POISON_ON_ALLOC_VALUE 0xd9
#define PVRSRV_POISON_ON_FREE_VALUE 0x63
#define PVRSRV_VZ_NUM_OSID 
#define PVRSRV_APPHINT_DRIVERMODE 0x7FFFFFFF
#define RGX_FW_HEAP_SHIFT 25
#define PVR_POWER_ACTOR 
#define SUPPORT_LINUX_X86_WRITECOMBINE 
#define SUPPORT_LINUX_X86_PAT 
#define PVR_LDM_DRIVER_REGISTRATION_NAME "pvrsrvkm"
#define PVRSRV_FULL_SYNC_TRACKING_HISTORY_LEN 256
#define PVRSRV_ENABLE_FULL_CCB_DUMP
#define SUPPORT_ALT_REGBASE
#define SUPPORT_MMU_PENDING_FAULT_PROTECTION 
#define CACHEFLUSH_NO_KMRBF_USING_UMVA 
#define HWR_DEFAULT_ENABLED 
#define PVRSRV_APPHINT_HWRDEBUGDUMPLIMIT APPHNT_BLDVAR_DBGDUMPLIMIT
#define PVRSRV_APPHINT_ENABLETRUSTEDDEVICEACECONFIG IMG_FALSE
#define PVRSRV_APPHINT_HTBUFFERSIZE 64
#define PVRSRV_APPHINT_GENERAL_NON4K_HEAP_PAGE_SIZE 0x4000
#define PVRSRV_APPHINT_HWPERFCLIENTBUFFERSIZE 786432
#define PVRSRV_APPHINT_ENABLESIGNATURECHECKS APPHNT_BLDVAR_ENABLESIGNATURECHECKS
#define PVRSRV_APPHINT_SIGNATURECHECKSBUFSIZE RGXFW_SIG_BUFFER_SIZE_MIN
#define PVRSRV_APPHINT_BIFTILINGMODE 4
#define PVRSRV_APPHINT_DISABLECLOCKGATING 0
#define PVRSRV_APPHINT_DISABLEDMOVERLAP 0
#define PVRSRV_APPHINT_ENABLECDMKILLINGRANDMODE 0
#define PVRSRV_APPHINT_ENABLEFWCONTEXTSWITCH RGXFWIF_INICFG_CTXSWITCH_DM_ALL
#define PVRSRV_APPHINT_VDMCONTEXTSWITCHMODE RGXFWIF_INICFG_VDM_CTX_STORE_MODE_INDEX
#define PVRSRV_APPHINT_ENABLERDPOWERISLAND RGX_RD_POWER_ISLAND_DEFAULT
#define PVRSRV_APPHINT_FIRMWAREPERF FW_PERF_CONF_NONE
#define PVRSRV_APPHINT_FWCONTEXTSWITCHPROFILE RGXFWIF_CTXSWITCH_PROFILE_MEDIUM_EN
#define PVRSRV_APPHINT_HWPERFDISABLECUSTOMCOUNTERFILTER 0
#define PVRSRV_APPHINT_HWPERFFWBUFSIZEINKB 2048
#define PVRSRV_APPHINT_HWPERFHOSTBUFSIZEINKB 2048
#define PVRSRV_APPHINT_JONESDISABLEMASK 0
#define PVRSRV_APPHINT_NEWFILTERINGMODE 1
#define PVRSRV_APPHINT_TRUNCATEMODE 2
#define PVRSRV_APPHINT_USEMETAT1 RGX_META_T1_OFF
#define PVRSRV_APPHINT_EMUMAXFREQ 0
#define PVRSRV_APPHINT_GPIOVALIDATIONMODE 0
#define PVRSRV_APPHINT_RGXBVNC ""
#define PVRSRV_APPHINT_ENABLETRUSTEDDEVICEACECONFIG IMG_FALSE
#define PVRSRV_APPHINT_CLEANUPTHREADPRIORITY 0
#define PVRSRV_APPHINT_CLEANUPTHREADWEIGHT 0
#define PVRSRV_APPHINT_WATCHDOGTHREADPRIORITY 0
#define PVRSRV_APPHINT_WATCHDOGTHREADWEIGHT 0
#define PVRSRV_APPHINT_ASSERTONHWRTRIGGER IMG_FALSE
#define PVRSRV_APPHINT_ASSERTOUTOFMEMORY IMG_FALSE
#define PVRSRV_APPHINT_CHECKMLIST APPHNT_BLDVAR_DEBUG
#define PVRSRV_APPHINT_DISABLEFEDLOGGING IMG_FALSE
#define PVRSRV_APPHINT_ENABLEAPM RGX_ACTIVEPM_DEFAULT
#define PVRSRV_APPHINT_ENABLEHTBLOGGROUP 0
#define PVRSRV_APPHINT_ENABLELOGGROUP RGXFWIF_LOG_TYPE_NONE
#define PVRSRV_APPHINT_FIRMWARELOGTYPE 0
#define PVRSRV_APPHINT_HTBOPERATIONMODE HTB_OPMODE_DROPLATEST
#define PVRSRV_APPHINT_ENABLEFTRACEGPU IMG_FALSE
#define PVRSRV_APPHINT_HWPERFFWFILTER 0
#define PVRSRV_APPHINT_HWPERFHOSTFILTER 0
#define PVRSRV_APPHINT_HWPERFCLIENTFILTER_SERVICES 0
#define PVRSRV_APPHINT_HWPERFCLIENTFILTER_EGL 0
#define PVRSRV_APPHINT_HWPERFCLIENTFILTER_OPENGLES 0
#define PVRSRV_APPHINT_HWPERFCLIENTFILTER_OPENCL 0
#define PVRSRV_APPHINT_HWPERFCLIENTFILTER_OPENRL 0
#define PVRSRV_APPHINT_HWPERFCLIENTFILTER_VULKAN 0
#define PVRSRV_APPHINT_TIMECORRCLOCK 0
#define PVRSRV_APPHINT_ENABLEFWPOISONONFREE IMG_FALSE
#define PVRSRV_APPHINT_FWPOISONONFREEVALUE 0xBD
#define PVRSRV_APPHINT_ZEROFREELIST IMG_FALSE
#define PVRSRV_APPHINT_DUSTREQUESTINJECT IMG_FALSE
#define PVRSRV_APPHINT_DISABLEPDUMPPANIC IMG_FALSE
#define PVRSRV_APPHINT_CACHEOPCONFIG 0
#define PVRSRV_APPHINT_CACHEOPGFTHRESHOLDSIZE 0
#define SOC_TIMER_FREQ 20
#define PDVFS_COM_HOST 1
#define PDVFS_COM_AP 2
#define PDVFS_COM_PMC 3
#define PDVFS_COM PDVFS_COM_HOST
#define PVR_GPIO_MODE_GENERAL 1
#define PVR_GPIO_MODE_POWMON_PIN 2
#define PVR_GPIO_MODE_POWMON_WO_PIN 3
#define PVR_GPIO_MODE PVR_GPIO_MODE_GENERAL
#define PVRSRV_ENABLE_PROCESS_STATS 
#define SUPPORT_DEVICEMEMHISTORY_BRIDGE 
#define SUPPORT_PAGE_FAULT_DEBUG 
#define PVR_ANNOTATION_MAX_LEN 40
#define PVRSRV_ENABLE_CCCB_UTILISATION_INFO 
#define PVRSRV_ENABLE_CCCB_UTILISATION_INFO_THRESHOLD 90
#define PVRSRV_ENABLE_MEMTRACK_STATS_FILE 
#define PVR_LINUX_PHYSMEM_MAX_POOL_PAGES 10240
#define PVR_LINUX_PHYSMEM_MAX_EXCESS_POOL_PAGES 20480
#define PVR_LINUX_PHYSMEM_ZERO_ALL_PAGES 
#define PVR_PMR_TRANSLATE_UMA_ADDRESSES 
#define SUPPORT_DEVICE_PA0_AS_VALID
#define PVR_LINUX_PHYSMEM_USE_HIGHMEM_ONLY 
#define PVR_DIRTY_BYTES_FLUSH_THRESHOLD 524288
#define PVR_LINUX_HIGHORDER_ALLOCATION_THRESHOLD 256
#define PVR_LINUX_PHYSMEM_MAX_ALLOC_ORDER_NUM  2

#ifdef CONFIG_MTK_GMO_RAM_OPTIMIZE
#define PVR_LINUX_KMALLOC_ALLOCATION_THRESHOLD  8192
#else
#define PVR_LINUX_KMALLOC_ALLOCATION_THRESHOLD  16384
#endif

#define SUPPORT_NATIVE_FENCE_SYNC 
#define PVR_USE_FENCE_SYNC_MODEL 1
#define PVRSRV_SYNC_SEPARATE_TIMELINES
#define PVR_DRM_NAME "pvr"
#define DEVICE_MEMSETCPY_ALIGN_IN_BYTES 8
#define PVRSRV_RGX_LOG2_CLIENT_CCB_SIZE_TQ3D 14
#define PVRSRV_RGX_LOG2_CLIENT_CCB_SIZE_TQ2D 14
#define PVRSRV_RGX_LOG2_CLIENT_CCB_SIZE_CDM 13
#define PVRSRV_RGX_LOG2_CLIENT_CCB_SIZE_TA 15
#define PVRSRV_RGX_LOG2_CLIENT_CCB_SIZE_3D 16
#define PVRSRV_RGX_LOG2_CLIENT_CCB_SIZE_KICKSYNC 13
#define PVRSRV_RGX_LOG2_CLIENT_CCB_SIZE_RTU 15
#define ANDROID 
#define SUPPORT_ION 
#define PVR_ANDROID_ION_HEADER "../drivers/staging/android/ion/ion.h"
#define PVR_ANDROID_ION_PRIV_HEADER "../drivers/staging/android/ion/ion_priv.h"
#define PVR_ANDROID_ION_USE_SG_LENGTH 
#define PVR_ANDROID_SYNC_HEADER "linux/sync.h"
#define MTK_USE_HW_APM 
#define MTK_DEBUG_PROC_PRINT 
#define MTK_CONFIG_OF 
#define ENABLE_COMMON_DVFS 
