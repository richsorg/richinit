#pragma once

#include "debug.h"

#define MOUNT_DIR(type, device, dir, opts) \
	INFO("Mounting %s\n", dir);			   \
	util_system("mount -t %s %s %s -o %s", type, device, dir, opts)

#define REMOUNT(dir)					   \
	INFO("Remounting %s\n", dir);		   \
	util_system("mount -o remount %s", dir)

#define MOUNT_FS() 						\
	INFO("Mounting file system\n");		\
	util_system("mount -a -t no nfs no nfs4 no smbfs no cifs no codafs no ncpfs no shfs no fuse no fuseblk no glusterfs no davfs no fuse.glusterfs -O no_netdev")
