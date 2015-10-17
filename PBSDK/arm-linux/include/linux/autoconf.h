/*
 * Automatically generated C config: don't edit
 */
#define AUTOCONF_INCLUDED
#define CONFIG_ARM 1
#define CONFIG_MMU 1
#define CONFIG_UID16 1
#define CONFIG_RWSEM_GENERIC_SPINLOCK 1

/*
 * Code maturity level options
 */
#define CONFIG_EXPERIMENTAL 1
#define CONFIG_CLEAN_COMPILE 1
#define CONFIG_STANDALONE 1
#define CONFIG_BROKEN_ON_SMP 1

/*
 * General setup
 */
#define CONFIG_SWAP 1
#define CONFIG_SYSVIPC 1
#undef CONFIG_POSIX_MQUEUE
#undef CONFIG_BSD_PROCESS_ACCT
#define CONFIG_SYSCTL 1
#undef CONFIG_AUDIT
#define CONFIG_LOG_BUF_SHIFT 14
#undef CONFIG_HOTPLUG
#undef CONFIG_IKCONFIG
#undef CONFIG_EMBEDDED
#define CONFIG_KALLSYMS 1
#define CONFIG_FUTEX 1
#define CONFIG_EPOLL 1
#define CONFIG_IOSCHED_NOOP 1
#define CONFIG_IOSCHED_AS 1
#define CONFIG_IOSCHED_DEADLINE 1
#define CONFIG_IOSCHED_CFQ 1
#define CONFIG_CC_OPTIMIZE_FOR_SIZE 1

/*
 * Loadable module support
 */
#undef CONFIG_MODULES

/*
 * System Type
 */
#undef CONFIG_ARCH_ADIFCC
#undef CONFIG_ARCH_CLPS7500
#undef CONFIG_ARCH_CLPS711X
#undef CONFIG_ARCH_CO285
#undef CONFIG_ARCH_EBSA110
#undef CONFIG_ARCH_CAMELOT
#undef CONFIG_ARCH_FOOTBRIDGE
#undef CONFIG_ARCH_INTEGRATOR
#undef CONFIG_ARCH_IOP3XX
#undef CONFIG_ARCH_IXP4XX
#undef CONFIG_ARCH_L7200
#define CONFIG_ARCH_PXA 1
#undef CONFIG_ARCH_RPC
#undef CONFIG_ARCH_SA1100
#undef CONFIG_ARCH_S3C2410
#undef CONFIG_ARCH_SHARK
#undef CONFIG_ARCH_LH7A40X
#undef CONFIG_ARCH_OMAP
#undef CONFIG_ARCH_VERSATILE_PB

/*
 * Intel PXA2xx Implementations
 */
#define CONFIG_ARCH_LUBBOCK 1
#undef CONFIG_MACH_MAINSTONE
#undef CONFIG_ARCH_PXA_IDP
#define CONFIG_PXA25x 1
#define CONFIG_SA1111 1
#define CONFIG_FORCE_MAX_ZONEORDER 9
#define CONFIG_DMABOUNCE 1

/*
 * Processor Type
 */
#define CONFIG_CPU_32 1
#define CONFIG_CPU_XSCALE 1
#define CONFIG_CPU_32v5 1
#define CONFIG_CPU_ABRT_EV5T 1
#define CONFIG_CPU_TLB_V4WBI 1
#define CONFIG_CPU_MINICACHE 1

/*
 * Processor Features
 */
#define CONFIG_ARM_THUMB 1
#define CONFIG_XSCALE_PMU 1

/*
 * General setup
 */
#undef CONFIG_ZBOOT_ROM
#define CONFIG_ZBOOT_ROM_TEXT 0x0
#define CONFIG_ZBOOT_ROM_BSS 0x0

/*
 * At least one math emulation must be selected
 */
#undef CONFIG_FPE_NWFPE
#undef CONFIG_FPE_FASTFPE
#define CONFIG_BINFMT_ELF 1
#define CONFIG_BINFMT_AOUT 1
#undef CONFIG_BINFMT_MISC

/*
 * Generic Driver Options
 */
#undef CONFIG_PM
#undef CONFIG_PREEMPT
#undef CONFIG_ARTHUR
#define CONFIG_CMDLINE ""
#define CONFIG_LEDS 1
#define CONFIG_LEDS_TIMER 1
#define CONFIG_LEDS_CPU 1
#define CONFIG_ALIGNMENT_TRAP 1

/*
 * Parallel port support
 */
#undef CONFIG_PARPORT

/*
 * Memory Technology Devices (MTD)
 */
#define CONFIG_MTD 1
#undef CONFIG_MTD_DEBUG
#undef CONFIG_MTD_PARTITIONS
#undef CONFIG_MTD_CONCAT

/*
 * User Modules And Translation Layers
 */
#define CONFIG_MTD_CHAR 1
#define CONFIG_MTD_BLOCK 1
#undef CONFIG_FTL
#undef CONFIG_NFTL
#undef CONFIG_INFTL

/*
 * RAM/ROM/Flash chip drivers
 */
#define CONFIG_MTD_CFI 1
#undef CONFIG_MTD_JEDECPROBE
#define CONFIG_MTD_GEN_PROBE 1
#undef CONFIG_MTD_CFI_ADV_OPTIONS
#define CONFIG_MTD_CFI_INTELEXT 1
#undef CONFIG_MTD_CFI_AMDSTD
#undef CONFIG_MTD_CFI_STAA
#undef CONFIG_MTD_RAM
#undef CONFIG_MTD_ROM
#undef CONFIG_MTD_ABSENT
#undef CONFIG_MTD_OBSOLETE_CHIPS

/*
 * Mapping drivers for chip access
 */
#undef CONFIG_MTD_COMPLEX_MAPPINGS
#undef CONFIG_MTD_PHYSMAP
#undef CONFIG_MTD_ARM_INTEGRATOR
#undef CONFIG_MTD_EDB7312

/*
 * Self-contained MTD device drivers
 */
#undef CONFIG_MTD_SLRAM
#undef CONFIG_MTD_MTDRAM
#undef CONFIG_MTD_BLKMTD

/*
 * Disk-On-Chip Device Drivers
 */
#undef CONFIG_MTD_DOC2000
#undef CONFIG_MTD_DOC2001
#undef CONFIG_MTD_DOC2001PLUS

/*
 * NAND Flash Device Drivers
 */
#undef CONFIG_MTD_NAND

/*
 * Plug and Play support
 */

/*
 * Block devices
 */
#undef CONFIG_BLK_DEV_FD
#undef CONFIG_BLK_DEV_LOOP
#undef CONFIG_BLK_DEV_NBD
#define CONFIG_BLK_DEV_RAM 1
#define CONFIG_BLK_DEV_RAM_SIZE 4096
#undef CONFIG_BLK_DEV_INITRD

/*
 * Multi-device support (RAID and LVM)
 */
#undef CONFIG_MD

/*
 * Networking support
 */
#define CONFIG_NET 1

/*
 * Networking options
 */
#undef CONFIG_PACKET
#undef CONFIG_NETLINK_DEV
#define CONFIG_UNIX 1
#undef CONFIG_NET_KEY
#define CONFIG_INET 1
#undef CONFIG_IP_MULTICAST
#undef CONFIG_IP_ADVANCED_ROUTER
#define CONFIG_IP_PNP 1
#undef CONFIG_IP_PNP_DHCP
#define CONFIG_IP_PNP_BOOTP 1
#undef CONFIG_IP_PNP_RARP
#undef CONFIG_NET_IPIP
#undef CONFIG_NET_IPGRE
#undef CONFIG_ARPD
#undef CONFIG_SYN_COOKIES
#undef CONFIG_INET_AH
#undef CONFIG_INET_ESP
#undef CONFIG_INET_IPCOMP
#undef CONFIG_IPV6
#undef CONFIG_NETFILTER

/*
 * SCTP Configuration (EXPERIMENTAL)
 */
#undef CONFIG_IP_SCTP
#undef CONFIG_ATM
#undef CONFIG_BRIDGE
#undef CONFIG_VLAN_8021Q
#undef CONFIG_DECNET
#undef CONFIG_LLC2
#undef CONFIG_IPX
#undef CONFIG_ATALK
#undef CONFIG_X25
#undef CONFIG_LAPB
#undef CONFIG_NET_DIVERT
#undef CONFIG_ECONET
#undef CONFIG_WAN_ROUTER
#undef CONFIG_NET_FASTROUTE
#undef CONFIG_NET_HW_FLOWCONTROL

/*
 * QoS and/or fair queueing
 */
#undef CONFIG_NET_SCHED

/*
 * Network testing
 */
#undef CONFIG_NET_PKTGEN
#undef CONFIG_NETPOLL
#undef CONFIG_NET_POLL_CONTROLLER
#undef CONFIG_HAMRADIO
#undef CONFIG_IRDA
#undef CONFIG_BT
#define CONFIG_NETDEVICES 1
#undef CONFIG_DUMMY
#undef CONFIG_BONDING
#undef CONFIG_EQUALIZER
#undef CONFIG_TUN

/*
 * Ethernet (10 or 100Mbit)
 */
#define CONFIG_NET_ETHERNET 1
#undef CONFIG_MII

/*
 * Ethernet (1000 Mbit)
 */

/*
 * Ethernet (10000 Mbit)
 */

/*
 * Token Ring devices
 */

/*
 * Wireless LAN (non-hamradio)
 */
#undef CONFIG_NET_RADIO

/*
 * Wan interfaces
 */
#undef CONFIG_WAN
#undef CONFIG_PPP
#undef CONFIG_SLIP
#undef CONFIG_SHAPER
#undef CONFIG_NETCONSOLE

/*
 * ATA/ATAPI/MFM/RLL support
 */
#undef CONFIG_IDE

/*
 * SCSI device support
 */
#undef CONFIG_SCSI

/*
 * Fusion MPT device support
 */

/*
 * IEEE 1394 (FireWire) support
 */
#undef CONFIG_IEEE1394

/*
 * I2O device support
 */

/*
 * ISDN subsystem
 */
#undef CONFIG_ISDN

/*
 * Input device support
 */
#define CONFIG_INPUT 1

/*
 * Userland interfaces
 */
#define CONFIG_INPUT_MOUSEDEV 1
#define CONFIG_INPUT_MOUSEDEV_PSAUX 1
#define CONFIG_INPUT_MOUSEDEV_SCREEN_X 1024
#define CONFIG_INPUT_MOUSEDEV_SCREEN_Y 768
#undef CONFIG_INPUT_JOYDEV
#undef CONFIG_INPUT_TSDEV
#undef CONFIG_INPUT_EVDEV
#undef CONFIG_INPUT_EVBUG

/*
 * Input I/O drivers
 */
#undef CONFIG_GAMEPORT
#define CONFIG_SOUND_GAMEPORT 1
#define CONFIG_SERIO 1
#define CONFIG_SERIO_I8042 1
#define CONFIG_SERIO_SERPORT 1
#undef CONFIG_SERIO_CT82C710
#undef CONFIG_SERIO_SA1111

/*
 * Input Device Drivers
 */
#define CONFIG_INPUT_KEYBOARD 1
#define CONFIG_KEYBOARD_ATKBD 1
#undef CONFIG_KEYBOARD_SUNKBD
#undef CONFIG_KEYBOARD_LKKBD
#undef CONFIG_KEYBOARD_XTKBD
#undef CONFIG_KEYBOARD_NEWTON
#define CONFIG_INPUT_MOUSE 1
#define CONFIG_MOUSE_PS2 1
#undef CONFIG_MOUSE_SERIAL
#undef CONFIG_MOUSE_VSXXXAA
#undef CONFIG_INPUT_JOYSTICK
#undef CONFIG_INPUT_TOUCHSCREEN
#undef CONFIG_INPUT_MISC

/*
 * Character devices
 */
#define CONFIG_VT 1
#define CONFIG_VT_CONSOLE 1
#define CONFIG_HW_CONSOLE 1
#undef CONFIG_SERIAL_NONSTANDARD

/*
 * Serial drivers
 */
#undef CONFIG_SERIAL_8250

/*
 * Non-8250 serial port support
 */
#undef CONFIG_SERIAL_PXA
#define CONFIG_UNIX98_PTYS 1
#define CONFIG_LEGACY_PTYS 1
#define CONFIG_LEGACY_PTY_COUNT 256
#undef CONFIG_QIC02_TAPE

/*
 * IPMI
 */
#undef CONFIG_IPMI_HANDLER

/*
 * Watchdog Cards
 */
#undef CONFIG_WATCHDOG
#undef CONFIG_NVRAM
#undef CONFIG_RTC
#undef CONFIG_GEN_RTC
#undef CONFIG_DTLK
#undef CONFIG_R3964
#undef CONFIG_APPLICOM

/*
 * Ftape, the floppy tape device driver
 */
#undef CONFIG_FTAPE
#undef CONFIG_AGP
#undef CONFIG_DRM
#undef CONFIG_RAW_DRIVER

/*
 * I2C support
 */
#undef CONFIG_I2C

/*
 * Multimedia devices
 */
#undef CONFIG_VIDEO_DEV

/*
 * Digital Video Broadcasting Devices
 */
#undef CONFIG_DVB

/*
 * File systems
 */
#define CONFIG_EXT2_FS 1
#undef CONFIG_EXT2_FS_XATTR
#undef CONFIG_EXT3_FS
#undef CONFIG_JBD
#undef CONFIG_REISERFS_FS
#undef CONFIG_JFS_FS
#undef CONFIG_XFS_FS
#undef CONFIG_MINIX_FS
#define CONFIG_ROMFS_FS 1
#undef CONFIG_QUOTA
#undef CONFIG_AUTOFS_FS
#undef CONFIG_AUTOFS4_FS

/*
 * CD-ROM/DVD Filesystems
 */
#undef CONFIG_ISO9660_FS
#undef CONFIG_UDF_FS

/*
 * DOS/FAT/NT Filesystems
 */
#undef CONFIG_FAT_FS
#undef CONFIG_NTFS_FS

/*
 * Pseudo filesystems
 */
#define CONFIG_PROC_FS 1
#define CONFIG_SYSFS 1
#undef CONFIG_DEVFS_FS
#undef CONFIG_DEVPTS_FS_XATTR
#undef CONFIG_TMPFS
#undef CONFIG_HUGETLB_PAGE
#define CONFIG_RAMFS 1

/*
 * Miscellaneous filesystems
 */
#undef CONFIG_ADFS_FS
#undef CONFIG_AFFS_FS
#undef CONFIG_HFS_FS
#undef CONFIG_HFSPLUS_FS
#undef CONFIG_BEFS_FS
#undef CONFIG_BFS_FS
#undef CONFIG_EFS_FS
#undef CONFIG_JFFS_FS
#undef CONFIG_JFFS2_FS
#undef CONFIG_CRAMFS
#undef CONFIG_VXFS_FS
#undef CONFIG_HPFS_FS
#undef CONFIG_QNX4FS_FS
#undef CONFIG_SYSV_FS
#undef CONFIG_UFS_FS

/*
 * Network File Systems
 */
#define CONFIG_NFS_FS 1
#undef CONFIG_NFS_V3
#undef CONFIG_NFS_V4
#undef CONFIG_NFS_DIRECTIO
#undef CONFIG_NFSD
#define CONFIG_ROOT_NFS 1
#define CONFIG_LOCKD 1
#undef CONFIG_EXPORTFS
#define CONFIG_SUNRPC 1
#undef CONFIG_RPCSEC_GSS_KRB5
#undef CONFIG_SMB_FS
#undef CONFIG_CIFS
#undef CONFIG_NCP_FS
#undef CONFIG_CODA_FS
#undef CONFIG_AFS_FS

/*
 * Partition Types
 */
#define CONFIG_PARTITION_ADVANCED 1
#undef CONFIG_ACORN_PARTITION
#undef CONFIG_OSF_PARTITION
#undef CONFIG_AMIGA_PARTITION
#undef CONFIG_ATARI_PARTITION
#undef CONFIG_MAC_PARTITION
#undef CONFIG_MSDOS_PARTITION
#undef CONFIG_LDM_PARTITION
#undef CONFIG_NEC98_PARTITION
#undef CONFIG_SGI_PARTITION
#undef CONFIG_ULTRIX_PARTITION
#undef CONFIG_SUN_PARTITION
#undef CONFIG_EFI_PARTITION

/*
 * Native Language Support
 */
#undef CONFIG_NLS

/*
 * Profiling support
 */
#undef CONFIG_PROFILING

/*
 * Graphics support
 */
#undef CONFIG_FB

/*
 * Console display driver support
 */
#define CONFIG_VGA_CONSOLE 1
#undef CONFIG_MDA_CONSOLE
#define CONFIG_DUMMY_CONSOLE 1

/*
 * Sound
 */
#undef CONFIG_SOUND

/*
 * Misc devices
 */

/*
 * USB support
 */
#undef CONFIG_USB

/*
 * USB Gadget Support
 */
#undef CONFIG_USB_GADGET

/*
 * Kernel hacking
 */
#define CONFIG_FRAME_POINTER 1
#define CONFIG_DEBUG_USER 1
#undef CONFIG_DEBUG_INFO
#undef CONFIG_DEBUG_KERNEL

/*
 * Security options
 */
#undef CONFIG_SECURITY

/*
 * Cryptographic options
 */
#undef CONFIG_CRYPTO

/*
 * Library routines
 */
#undef CONFIG_CRC32
#undef CONFIG_LIBCRC32C
