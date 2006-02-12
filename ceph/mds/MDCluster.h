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

#ifndef __MDCLUSTER_H
#define __MDCLUSTER_H

#include "include/types.h"

#include <string>
#include <vector>
using namespace std;

class CDir;
class MDS;

class MDCluster {
 protected:
  int          num_mds;

  int          num_osd;
  int          osd_meta_begin;  // 0
  int          osd_meta_end;    // 10
  int          osd_log_begin;   
  int          osd_log_end;   
  
  set<int> mds_set;

  void map_osds();

 public:
  MDCluster(int num_mds, int num_osd);
  
  int get_num_mds() { return num_mds; }
  
  //int get_size() { return mds.size(); }
  //int add_mds(MDS *m);

  int hash_dentry( inodeno_t dirino, const string& dn );  

  int get_meta_osd(inodeno_t ino);
  object_t get_meta_oid(inodeno_t ino);
  
  int get_hashdir_meta_osd(inodeno_t ino, int mds);
  object_t get_hashdir_meta_oid(inodeno_t ino, int mds);

  int get_log_osd(int mds);
  object_t get_log_oid(int mds);

  set<int>& get_mds_set() {
	if (mds_set.empty())
	  for (int i=0; i<num_mds; i++)
		mds_set.insert(i);
	return mds_set;
  }

};

#endif
