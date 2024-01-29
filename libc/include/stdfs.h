#ifndef _STDFS_H
#define _STDFS_H 1
 
#include <sys/cdefs.h>
#include <stdint.h>
#include <stddef.h>

#define EOF (-1)
 
#ifdef __cplusplus
extern "C" {
#endif

/*
============== UStar Filesystem ==============
The UStar filesystem has a file descriptor that looks like this:
=======|======|=============
Offset | Size | Description
=======|======|=============
0      | 100  | File name
100	   | 8    | File mode
108    | 8    | Owner's numeric user ID
116    | 8    | Group's numeric user ID
124    | 12   | File size in bytes (octal base)
136    | 12   | Last modification time in numeric Unix time format (octal)
148    | 8    | Checksum for header record
156    | 1    | Type flag
157    | 100  | Name of linked file
257    | 6    | UStar indicator "ustar" then NUL
263    | 2    | UStar version "00"
265    | 32   | Owner user name
297    | 32   | Owner group name
329    | 8    | Device major number
337    | 8    | Device minor number
345    | 155  | Filename prefix
=======|======|=============

The type flag, on offset 156, tells the "file" type
==========|============
Type flag | Meaning
==========|============
'0'       | Normal file
'1'	      | Hard link
'2'	      | Symbolic link
'3'	      | Character device
'4'	      | Block device
'5'	      | Directory
'6'	      | Named pipe (FIFO)
==========|============
*/

enum protection {
    PROT_NONE = 0x00,
    PROT_READ = 0x01,
    PROT_WRTE = 0x02,
    PROT_EXEC = 0x04 // Using 4 so we can distinguish from PROT_READ | PROT_WRTE
};

enum fileMode {
    TSUID = 04000, // Set user ID on execution
    TSGID = 02000, // Set group ID on execution
    TSVTX = 01000, // Reserved?

    TUREAD  = 00400, // Owner - read
    TUWRITE = 00200, // Owner - write
    TUEXEC  = 00100, // Owner - execute

    TGREAD  = 00040, // Group - read
    TGWRITE = 00020, // Group - write
    TGEXEC  = 00010, // Group - execute

    TOREAD  = 00004, // Others - read
    TOWRITE = 00002, // Others - write
    TOEXEC  = 00001, // Others - execute

    ALL = 07777, // All permissions, addded together
};

enum fileType {
    REGTYPE = 00, // Regular file
    LNKTYPE = 01, // Link
    SYMTYPE = 02, // Reserved
    CHRTYPE = 03, // Character special?
    BLKTYPE = 04, // Block special?
    DIRTYPE = 05, // Phew, something I understand. Directory
    FIFITYPE = 06, // FIFO special?
    CONTTYPE = 07, // Reserved
};

struct tart {
    uint8_t begin; // Starting address of file

    char name[100]; // File name

    int mode; // File mode

    uint32_t owner_id; // Owner ID - Checksum
    uint32_t group_id; // Group ID - Checksum
    uint8_t size; // File size (bytes)
    uint8_t last_modify; // Last modification date (Unix, octal)
    uint32_t checksum; // Checksum for header
    int file_type; // Type
    char linked_file[100]; // Name of linked file
    char ustar[6]; // Just holds "ustar"
    char ustar_v[2]; // UStar version
    char owner_name[32];
    char group_name[32];
    char device_major[8];
    char device_minor[8];
    char prefix[155];
    char block[512]; // Holds the actual data
    struct tart* next; // Pointer to next metadata, making a linked list
};

struct tart_fd {
    struct tart** tar;
    int fd;
};

void tar_free(struct tart*);
struct tart_fd tar_create(char*, size_t);
void tar_close(int);

#ifdef __cplusplus
}
#endif

#endif