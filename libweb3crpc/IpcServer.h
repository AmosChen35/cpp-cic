#ifndef LIBWEB3CRPC_IPCSERVER_H
#define LIBWEB3CRPC_IPCSERVER_H

#if _WIN32
#include "WinPipeServer.h"
#else
#include <sys/un.h>
#include <sys/socket.h>
#include "UnixSocketServer.h"
#endif

// "Mac OS X does not support the flag MSG_NOSIGNAL but we have an equivalent."
// See http://lists.apple.com/archives/macnetworkprog/2002/Dec/msg00091.html
#if defined(__APPLE__)
	#if !defined(MSG_NOSIGNAL)
		#define MSG_NOSIGNAL SO_NOSIGPIPE
	#endif
#endif

#if _WIN32
using IpcServer = WindowsPipeServer;
#else
using IpcServer = UnixDomainSocketServer;
#endif

#endif //LIBWEB3CRPC_IPCSERVER_H
