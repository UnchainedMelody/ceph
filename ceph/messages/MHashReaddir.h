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

#ifndef __MHASHREADDIR_H
#define __MHASHREADDIR_H

#include "include/types.h"
#include "msg/Message.h"

class MHashReaddir : public Message {
  inodeno_t ino;

 public:
  MHashReaddir() { }
  MHashReaddir(inodeno_t ino) :
	Message(MSG_MDS_HASHREADDIR) {
	this->ino = ino;
  }

  inodeno_t get_ino() { return ino; }

  virtual char *get_type_name() { return "Hls"; }

  virtual void decode_payload() {
	payload.copy(0, sizeof(ino), (char*)&ino);
  }
  virtual void encode_payload() {
	payload.append((char*)&ino, sizeof(ino));
  }

};

#endif
