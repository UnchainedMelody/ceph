// -*- mode:C++; tab-width:4; c-basic-offset:2; indent-tabs-mode:t -*- 
/*
 * Ceph - scalable distributed file system
 *
 * Copyright (C) 2004-2006 Sage Weil <sage@newdream.net>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __MNSCONNECTACK_H
#define __MNSCONNECTACK_H

#include "msg/Message.h"
#include "msg/TCPMessenger.h"

class MNSConnectAck : public Message {
  int rank;

 public:
  MNSConnectAck() {}
  MNSConnectAck(int r) : 
	Message(MSG_NS_CONNECTACK) { 
	rank = r;
  }
  
  char *get_type_name() { return "NSConA"; }

  int get_rank() { return rank; }

  void encode_payload() {
	payload.append((char*)&rank, sizeof(rank));
  }
  void decode_payload() {
	payload.copy(0, sizeof(rank), (char*)&rank);
  }
};


#endif

