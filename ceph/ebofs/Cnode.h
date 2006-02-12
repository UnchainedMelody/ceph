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

#ifndef __EBOFS_CNODE_H
#define __EBOFS_CNODE_H

#include "Onode.h"

/*
 * collection node
 *
 * holds attribute metadata for collections.
 * colletion membership is stored in b+tree tables, independent of tte cnode.
 */

class Cnode : public LRUObject
{
 private:
  int ref;
  bool dirty;

 public:
  coll_t coll_id;
  Extent cnode_loc;

  map<string,AttrVal> attr;

 public:
  Cnode(coll_t cid) : ref(0), dirty(false), coll_id(cid) {
	cnode_loc.length = 0;
  }
  ~Cnode() {
  }

  block_t get_cnode_id() { return cnode_loc.start; }
  int get_cnode_len() { return cnode_loc.length; }

  void get() {
	if (ref == 0) lru_pin();
	ref++;
  }
  void put() {
	ref--;
	if (ref == 0) lru_unpin();
  }

  void mark_dirty() {
	if (!dirty) {
	  dirty = true;
	  get();
	}
  }
  void mark_clean() {
	if (dirty) {
	  dirty = false;
	  put();
	}
  }
  bool is_dirty() { return dirty; }


  int get_attr_bytes() {
	int s = 0;
	for (map<string, AttrVal >::iterator i = attr.begin();
		 i != attr.end();
		 i++) {
	  s += i->first.length() + 1;
	  s += i->second.len + sizeof(int);
	}
	return s;
  }
  
  //
  //???void clear();

  
};

inline ostream& operator<<(ostream& out, Cnode& cn)
{
  out << "cnode(" << hex << cn.coll_id << dec;
  if (cn.is_dirty()) out << " dirty";
  //out << " " << &cn;
  out << ")";
  return out;
}

#endif
