/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   copyright            : (C) 2002 by Zhang Yong                         *
 *   email                : z-yong163@163.com                              *
 ***************************************************************************/

#ifndef _FILE_SESSION_H
#define _FILE_SESSION_H

#include "tcpsessionbase.h"
#include "icqlinkbase.h"

class FileSessionListener {
public:
	virtual const char *getPathName(const char *name, uint32 size) = 0;
	virtual void onFileReceive() = 0;
	virtual void onFileProgress(uint32 bytes) = 0;
	virtual void onFileFinished() = 0;
};

class FileSession : public TcpSessionListener {
public:
	FileSession(TcpSessionBase *s);
	~FileSession();

	IcqLinkBase *getLink() {
		return tcp->getLink();
	}
	uint32 getUIN() {
		return tcp->getRemoteUIN();
	}
	void setListener(FileSessionListener *l) {
		listener = l;
	}
	void sendFileInfo(const char *path, const char *name, uint32 size);

	bool isSend;

private:
	virtual bool onPacketReceived(InPacket &);
	virtual void onSend();
	virtual void onClose();

	void onFileInfo(InPacket &in);
	void onFileReceive(InPacket &in);
	void onFileData(InPacket &in);

	TcpSessionBase *tcp;
	FileSessionListener *listener;
	FILE *file;
	uint32 fileSize;
	uint32 bytesSent;
};

#endif

