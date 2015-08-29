/*
 * NROS's error code. Return `-E*' on failures.
 *
 * Copyright (C) Junyu Wu, shibuyanorailgun@foxmail, 2015.
 */

#ifndef __NROS_ERRNO_H
#define __NROS_ERRNO_H

enum {
	EOK,
	E2BIG,
	EACCES,
	EADDRINUSE,
	EADDRNOTAVAIL,
	EAGAIN,
	EALREADY,

	EBADE,
	EBADF,
	EBADFD,
	EBADMSG,
	EBADR,
	EBADRQC,
	EBADSLT,

	EBUSY,
	ECANCELED,
	ECHILD,
	ECHRNG,
	ECOMM,
	EDEADLOCK,

	EINTR,
	EINVAL,
	EIO,

	ENOMEDIUM,
	ENOMEM,
	ENOMSG,
	ENONET,

	EMAXN,
};

#endif /* end of include guard: __NROS_ERRNO_H */
