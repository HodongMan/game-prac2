#include "pch.h"
#include "SocketUtil.h"

bool SocketUtil::staticInit( void ) noexcept
{
	return false;
}

void SocketUtil::cleanUp(void) noexcept
{
}

void SocketUtil::reportError(const char * inOperationDesc) noexcept
{
}

int SocketUtil::getLastError(void) noexcept
{
	return 0;
}

int SocketUtil::select(const vector<TCPSocketPtr>* inReadSet, vector<TCPSocketPtr>* outReadSet, const vector<TCPSocketPtr>* inWriteSet, vector<TCPSocketPtr>* outWriteSet, const vector<TCPSocketPtr>* inExceptSet, vector<TCPSocketPtr>* outExceptSet) noexcept
{
	return 0;
}

UDPSocketPtr SocketUtil::createUDPSocket(SocketAddressFamily family) noexcept
{
	return UDPSocketPtr();
}

TCPSocketPtr SocketUtil::createTCPSocket(SocketAddressFamily family) noexcept
{
	return TCPSocketPtr();
}

inline fd_set * SocketUtil::fillSetFromVector(fd_set & outSet, const vector<TCPSocketPtr>* inSockets, int & ioNaxNfds) noexcept
{
	return nullptr;
}

inline void SocketUtil::fillVectorFromSet(vector<TCPSocketPtr>* outSockets, const vector<TCPSocketPtr>* inSockets, const fd_set & inSet) noexcept
{
}
