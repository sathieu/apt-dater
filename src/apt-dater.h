/* apt-dater - terminal-based remote package update manager
 *
 * $Id$
 *
 * Authors:
 *   Andre Ellguth <ellguth@ibh.de>
 *   Thomas Liske <liske@ibh.de>
 *
 * Copyright Holder:
 *   2008-2009 (C) IBH IT-Service GmbH [http://www.ibh.de/apt-dater/]
 *
 * License:
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this package; if not, write to the Free Software
 *   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef _APT_DATER_H
#define _APT_DATER_H

#define _GNU_SOURCE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <glib-2.0/glib.h>

#define STATS_MAX_LINE_LEN 1000
#define INPUT_MAX 4096
#define BUF_MAX_LEN 256
#define PROG_NAME PACKAGE
#define CFGFILENAME "apt-dater.conf"

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifndef NDEBUG
typedef enum {
    T_CFGFILE=1,
    T_UPDATE=2,
    T_SESSION=3,
    T_HOSTNODE=4,
    T_MAPPING=5,
    T_VERSION=6,
    T_DISTRI=7,
} etype;
#endif

typedef struct _cfgfile {
#ifndef NDEBUG
 etype _type;
#endif
 gchar *hostsfile;
 gchar *screenrcfile;
 gchar *screentitle;
 gchar *statsdir;
 gchar *ssh_cmd;
 gchar *sftp_cmd;
 gchar *ssh_optflags;
 gchar *ssh_defuser;
 gint  ssh_defport;
 gchar *cmd_refresh;
 gchar *cmd_upgrade;
 gchar *cmd_install;
 gboolean use_screen;
 gboolean dump_screen;
 gboolean query_maintainer;
 gboolean beep;
 gboolean flash;
 gchar **colors;
#ifdef FEAT_TCLFILTER
 gchar *filterexp;
 gchar *filterfile;
#endif
#ifdef FEAT_AUTOREF
 gboolean auto_refresh;
#endif
} CfgFile;

typedef struct _update {
#ifndef NDEBUG
 etype _type;
#endif
 gchar *package;
 gchar *version;
 gint flag;
 gchar *data;
} PkgNode;

typedef struct _session {
#ifndef NDEBUG
 etype _type;
#endif
  gint pid;
  struct stat st;
} SessNode;

typedef enum {
 C_UPDATES_PENDING = 0,
 C_UP_TO_DATE = 1,
 C_BROKEN_PKGS = 2,
 C_REFRESH_REQUIRED = 3,
 C_REFRESH = 4,
 C_SESSIONS = 5,
#ifdef FEAT_TCLFILTER
 C_FILTERED = 6,
 C_UNKNOWN = 7,
#else
 C_UNKNOWN = 6,
#endif
} Category;

#define HOST_STATUS_PKGUPDATE         1
#define HOST_STATUS_PKGKEPTBACK       2
#define HOST_STATUS_PKGEXTRA          4
#define HOST_STATUS_PKGBROKEN         8
#define HOST_STATUS_KERNELNOTMATCH   16
#define HOST_STATUS_KERNELSELFBUILD  32
#define HOST_STATUS_VIRTUALIZED      64
#define HOST_STATUS_LOCKED          128

#define HOST_FORBID_REFRESH           1
#define HOST_FORBID_UPGRADE           2
#define HOST_FORBID_INSTALL           4

#define HOST_FORBID_MASK     (HOST_FORBID_REFRESH | HOST_FORBID_UPGRADE | HOST_FORBID_INSTALL)

typedef struct _hostnode {
#ifndef NDEBUG
 etype _type;
#endif
 gchar     *hostname;
 gchar     *group;
 gchar     *ssh_user;
 gint      ssh_port;
#ifdef FEAT_AUTOREF
 time_t    last_upd;
#endif
 guint     status;
 gboolean  keptback;
#ifdef FEAT_TCLFILTER
 gboolean  filtered;
#endif
 Category  category;
 GList     *packages;
 gint      nupdates;
 gint      nholds;
 gint      nextras;
 gint      nbrokens;
 GList     *screens;
 gint      fdlock;
 FILE      *fpstat;
 gchar     *lsb_distributor;
 gchar     *lsb_release;
 gchar     *lsb_codename;
 gchar     *kernelrel;
 gchar     *virt;
 gchar     *identity_file;
 gint      forbid;
} HostNode;

struct mapping_t {
 gchar *name;
 gint value;
};

#include "extern.h"

#endif /* _APT_DATER_H */
