/*
 * Copyright (C) 2003 Yasuhiro Ohara
 *
 * This file is part of GNU Zebra.
 *
 * GNU Zebra is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * GNU Zebra is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Zebra; see the file COPYING.  If not, write to the 
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330, 
 * Boston, MA 02111-1307, USA.  
 */

#ifndef OSPF_AREA_H
#define OSPF_AREA_H

#include "ospf6_top.h"

struct ospf6_area
{
  /* Reference to Top data structure */
  struct ospf6 *ospf6;

  /* Area-ID */
  u_int32_t area_id;

  /* Area-ID string */
  char name[16];

  /* flag */
  u_char flag;

  /* OSPF Option */
  u_char options[3];

  /* TransitCapability */
  int transit_capability;

  /* Summary routes to be originated (includes Configured Address Ranges) */
  struct ospf6_route_table *summary_table;

  /* OSPF interface list */
  list if_list;

  struct ospf6_lsdb        *lsdb;
  struct ospf6_route_table *spf_table;
  struct ospf6_route_table *route_table;

  struct thread  *thread_spf_calculation;
  struct thread  *thread_route_calculation;

  struct thread *thread_router_lsa;
  struct thread *thread_intra_prefix_lsa;
  u_int32_t router_lsa_size_limit;
};

#define OSPF6_AREA_DISABLE 0x01
#define OSPF6_AREA_STUB    0x02

/* prototypes */
int ospf6_area_cmp (void *va, void *vb);
int ospf6_area_is_stub (struct ospf6_area *o6a);
struct ospf6_area *ospf6_area_create (u_int32_t, struct ospf6 *);
void ospf6_area_delete (struct ospf6_area *);
struct ospf6_area *ospf6_area_lookup (u_int32_t, struct ospf6 *);

void ospf6_area_enable (struct ospf6_area *);
void ospf6_area_disable (struct ospf6_area *);

void ospf6_area_show (struct vty *, struct ospf6_area *);
void ospf6_area_init ();

#endif /* OSPF_AREA_H */

