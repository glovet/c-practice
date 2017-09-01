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

#ifndef _TCP_SESSION_H
#define _TCP_SESSION_H

#include "icqsession.h"
#include "tcpsessionbase.h"

#define TCP_PACKET_SIZE	4096
#define TCP_HELLO		1

enum {
	TCP_STATUS_NOT_CONN,
	TCP_STATUS_SOCKS_METHOD,
	TCP_STATUS_SOCKS_AUTH,
	TCP_STATUS_SOCKS_CONNECT,
	TCP_STATUS_HELLO_WAIT,
	TCP_STATUS_ESTABLISHED,
};

class TcpInPacket;

class TcpSession : public IcqSession, public TcpSessionBase {
public:
	TcpSession(IcqLink *link, const char *name, uint32 uin);
	virtual ~TcpSession();

	virtual IcqLinkBase *getLink() {
		return icqLink;
	}
	virtual int getSocket() {
		return sock;
	}
	virtual uint32 getRemoteUIN() {
		return uin;
	}
	virtual void setListener(TcpSessionListener *l) {
		listener = l;
	}
	virtual void destroy();
	virtual void shutdown();
	virtual bool isSendSession() {
		return isSend;
	}
	virtual void enableWrite();
	virtual OutPacket *createPacket(uint16 cmd);
	virtual bool sendPacket(OutPacket *out);

	virtual void onConnect(bool success);
	virtual bool onReceive();
	virtual void onSend();
	virtual void onClose();

	bool connect(uint32 ip, uint16 port, bool isSend);

	int sock;
	int status;

private:
	bool onPacketReceived(TcpInPacket &);

	void createPlugin();
	int sendDirect(OutPacket *out);
	bool recvPacket();
	bool onTcpEstablished();

	TcpSessionListener *listener;
	bool isSend;
	uint32 destIP;
	uint16 destPort;
	uint32 realIP;

	char buf[TCP_PACKET_SIZE];
	int bufSize;
};

#endif
