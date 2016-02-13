<<<<<<< HEAD
// Copyright (c) 2012 The Bitcoin developers
// Copyright (c) 2014 The Inutoshi developers
// Distributed under the MIT/X11 software license, see the accompanying
=======
// Copyright (c) 2012-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_VERSION_H
#define BITCOIN_VERSION_H

/**
 * network protocol versioning
 */

static const int PROTOCOL_VERSION = 70004;

<<<<<<< HEAD
//
// network protocol versioning
//

static const int PROTOCOL_VERSION = 70003;

// intial proto version, to be increased after version/verack negotiation
static const int INIT_PROTO_VERSION = 209;

// disconnect from peers older than this proto version
=======
//! initial proto version, to be increased after version/verack negotiation
static const int INIT_PROTO_VERSION = 209;

//! In this version, 'getheaders' was introduced.
static const int GETHEADERS_VERSION = 31800;

//! disconnect from peers older than this proto version
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
static const int MIN_PEER_PROTO_VERSION = 70003;

//! nTime field added to CAddress, starting with this version;
//! if possible, avoid requesting addresses nodes older than this
static const int CADDR_TIME_VERSION = 31402;

<<<<<<< HEAD
// only request blocks from nodes outside this range of versions
static const int NOBLKS_VERSION_START = 60000;
static const int NOBLKS_VERSION_END = 60002;
=======
//! only request blocks from nodes outside this range of versions
static const int NOBLKS_VERSION_START = 32000;
static const int NOBLKS_VERSION_END = 32400;
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707

//! BIP 0031, pong message, is enabled for all versions AFTER this one
static const int BIP0031_VERSION = 60000;

//! "mempool" command, enhanced "getdata" behavior starts with this version
static const int MEMPOOL_GD_VERSION = 60002;

#endif // BITCOIN_VERSION_H
