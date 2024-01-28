#ifndef _STDFS_H
#define _STDFS_H 1
 
#include <sys/cdefs.h>
 
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

// Such a cute name
typedef struct tart {
    unsigned int begin; // Starting address of file
    union {
        char name[100]; // File name

        enum {
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
        } mode; // File mode

        int owner_id; // Owner ID - Checksum
        int group_id; // Group ID - Checksum
        int size; // File size (bytes)
        int last_modify; // Last modification date (Unix, octal)
        int checksum; // Checksum for header
        enum {
            REGTYPE = 00, // Regular file
            LNKTYPE = 01, // Link
            SYMTYPE = 02, // Reserved
            CHRTYPE = 03, // Character special?
            BLKTYPE = 04, // Block special?
            DIRTYPE = 05, // Phew, something I understand. Directory
            FIFITYPE = 06, // FIFO special?
            CONTTYPE = 07, // Reserved
        } file_type; // Type
        char linked_file[100]; // Name of linked file
        char ustar[6]; // Just holds "ustar"
        char ustar_v[2]; // UStar version
        char owner_name[32];
        char group_name[32];
        char device_major[8];
        char device_minor[8];
        char prefix[155];
    };
    char block[512]; // Holds the actual data
    struct tart* next; // Pointer to next metadata, making a linked list
};

void tar_free(struct tart*);
struct tart** tar_create(char* name);

#ifdef __cplusplus
}
#endif

#endif