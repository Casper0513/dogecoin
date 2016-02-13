<<<<<<< HEAD
// Copyright (c) 2011 Vince Durham
// Distributed under the MIT/X11 software license, see the accompanying
// file license.txt or http://www.opensource.org/licenses/mit-license.php.
#include "script.h"
#include "auxpow.h"
#include "init.h"

using namespace std;
using namespace boost;

unsigned char pchMergedMiningHeader[] = { 0xfa, 0xbe, 'm', 'm' } ;

void RemoveMergedMiningHeader(vector<unsigned char>& vchAux)
{
    if (vchAux.begin() != std::search(vchAux.begin(), vchAux.end(), UBEGIN(pchMergedMiningHeader), UEND(pchMergedMiningHeader)))
        throw runtime_error("merged mining aux too short");
    vchAux.erase(vchAux.begin(), vchAux.begin() + sizeof(pchMergedMiningHeader));
}

bool CAuxPow::Check(uint256 hashAuxBlock, int nChainID)
=======
// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2011 Vince Durham
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2014-2015 Daniel Kraft
// Copyright (c) 2014-2015 The Dogecoin Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file license.txt or http://www.opensource.org/licenses/mit-license.php.

#include "auxpow.h"

#include "chainparams.h"
#include "consensus/validation.h"
#include "main.h"
#include "script/script.h"
#include "util.h"

#include <algorithm>

/* Moved from wallet.cpp.  CMerkleTx is necessary for auxpow, independent
   of an enabled (or disabled) wallet.  Always include the code.  */

int CMerkleTx::SetMerkleBranch(const CBlock& block)
{
    AssertLockHeld(cs_main);
    CBlock blockTmp;

    // Update the tx's hashBlock
    hashBlock = block.GetHash();

    // Locate the transaction
    for (nIndex = 0; nIndex < (int)block.vtx.size(); nIndex++)
        if (block.vtx[nIndex] == *(CTransaction*)this)
            break;
    if (nIndex == (int)block.vtx.size()) {
        vMerkleBranch.clear();
        nIndex = -1;
        LogPrintf("ERROR: SetMerkleBranch(): couldn't find tx in block\n");
        return 0;
    }

    // Fill in merkle branch
    vMerkleBranch = block.GetMerkleBranch(nIndex);

    // Is the tx in a block that's in the main chain
    BlockMap::iterator mi = mapBlockIndex.find(hashBlock);
    if (mi == mapBlockIndex.end())
        return 0;
    const CBlockIndex* pindex = (*mi).second;
    if (!pindex || !chainActive.Contains(pindex))
        return 0;

    return chainActive.Height() - pindex->nHeight + 1;
}

int CMerkleTx::GetDepthInMainChainINTERNAL(const CBlockIndex*& pindexRet) const
{
    if (hashBlock.IsNull() || nIndex == -1)
        return 0;
    AssertLockHeld(cs_main);

    // Find the block it claims to be in
    BlockMap::iterator mi = mapBlockIndex.find(hashBlock);
    if (mi == mapBlockIndex.end())
        return 0;
    CBlockIndex* pindex = (*mi).second;
    if (!pindex || !chainActive.Contains(pindex))
        return 0;

    // Make sure the merkle branch connects to this block
    if (!fMerkleVerified) {
        if (CBlock::CheckMerkleBranch(GetHash(), vMerkleBranch, nIndex) != pindex->hashMerkleRoot)
            return 0;
        fMerkleVerified = true;
    }

    pindexRet = pindex;
    return chainActive.Height() - pindex->nHeight + 1;
}

int CMerkleTx::GetDepthInMainChain(const CBlockIndex*& pindexRet) const
{
    AssertLockHeld(cs_main);
    int nResult = GetDepthInMainChainINTERNAL(pindexRet);
    if (nResult == 0 && !mempool.exists(GetHash()))
        return -1; // Not in chain, not in mempool

    return nResult;
}

int CMerkleTx::GetBlocksToMaturity() const
{
    if (!IsCoinBase())
        return 0;
    int nCoinbaseMaturity = Params().GetConsensus(chainActive.Height()).nCoinbaseMaturity;
    return std::max(0, (nCoinbaseMaturity + 1) - GetDepthInMainChain());
}


bool CMerkleTx::AcceptToMemoryPool(bool fLimitFree, bool fRejectAbsurdFee)
{
    CValidationState state;
    return ::AcceptToMemoryPool(mempool, state, *this, fLimitFree, NULL, fRejectAbsurdFee);
}

/* ************************************************************************** */

bool
CAuxPow::check(const uint256& hashAuxBlock, int nChainId, const Consensus::Params& params) const
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
{
    if (nIndex != 0)
        return error("AuxPow is not a generate");

<<<<<<< HEAD
    if (!TestNet() && parentBlockHeader.GetChainID() == nChainID)
=======
    if (params.fStrictChainId && parentBlock.nVersion.GetChainId() == nChainId)
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
        return error("Aux POW parent has our chain ID");

    if (vChainMerkleBranch.size() > 30)
        return error("Aux POW chain merkle branch too long");

    // Check that the chain merkle root is in the coinbase
<<<<<<< HEAD
    uint256 nRootHash = CBlock::CheckMerkleBranch(hashAuxBlock, vChainMerkleBranch, nChainIndex);
    vector<unsigned char> vchRootHash(nRootHash.begin(), nRootHash.end());
    std::reverse(vchRootHash.begin(), vchRootHash.end()); // correct endian

    // Check that we are in the parent block merkle tree
    if (CBlock::CheckMerkleBranch(GetHash(), vMerkleBranch, nIndex) != parentBlockHeader.hashMerkleRoot)
=======
    const uint256 nRootHash = CBlock::CheckMerkleBranch(hashAuxBlock, vChainMerkleBranch, nChainIndex);
    std::vector<unsigned char> vchRootHash(nRootHash.begin(), nRootHash.end());
    std::reverse(vchRootHash.begin(), vchRootHash.end()); // correct endian

    // Check that we are in the parent block merkle tree
    if (CBlock::CheckMerkleBranch(GetHash(), vMerkleBranch, nIndex) != parentBlock.hashMerkleRoot)
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
        return error("Aux POW merkle root incorrect");

    const CScript script = vin[0].scriptSig;

    // Check that the same work is not submitted twice to our chain.
    //

    CScript::const_iterator pcHead =
        std::search(script.begin(), script.end(), UBEGIN(pchMergedMiningHeader), UEND(pchMergedMiningHeader));

    CScript::const_iterator pc =
        std::search(script.begin(), script.end(), vchRootHash.begin(), vchRootHash.end());

<<<<<<< HEAD
    if (pcHead == script.end())
        return error("MergedMiningHeader missing from parent coinbase");

    if (pc == script.end())
        return error("Aux POW missing chain merkle root in parent coinbase");

    // Enforce only one chain merkle root by checking that a single instance of the merged
    // mining header exists just before.
    if (script.end() != std::search(pcHead + 1, script.end(), UBEGIN(pchMergedMiningHeader), UEND(pchMergedMiningHeader)))
        return error("Multiple merged mining headers in coinbase");
    if (pcHead + sizeof(pchMergedMiningHeader) != pc)
        return error("Merged mining header is not just before chain merkle root");
=======
    if (pc == script.end())
        return error("Aux POW missing chain merkle root in parent coinbase");

    if (pcHead != script.end()) {
        // Enforce only one chain merkle root by checking that a single instance of the merged
        // mining header exists just before.
        if (script.end() != std::search(pcHead + 1, script.end(), UBEGIN(pchMergedMiningHeader), UEND(pchMergedMiningHeader)))
            return error("Multiple merged mining headers in coinbase");
        if (pcHead + sizeof(pchMergedMiningHeader) != pc)
            return error("Merged mining header is not just before chain merkle root");
    } else {
        // For backward compatibility.
        // Enforce only one chain merkle root by checking that it starts early in the coinbase.
        // 8-12 bytes are enough to encode extraNonce and nBits.
        if (pc - script.begin() > 20)
            return error("Aux POW chain merkle root must start in the first 20 bytes of the parent coinbase");
    }

>>>>>>> f568462ca04b73485d7e41266a2005155ff69707

    // Ensure we are at a deterministic point in the merkle leaves by hashing
    // a nonce and our chain ID and comparing to the index.
    pc += vchRootHash.size();
    if (script.end() - pc < 8)
        return error("Aux POW missing chain merkle tree size and nonce in parent coinbase");

    int nSize;
    memcpy(&nSize, &pc[0], 4);
<<<<<<< HEAD
    if (nSize != (1 << vChainMerkleBranch.size()))
=======
    const unsigned merkleHeight = vChainMerkleBranch.size();
    if (nSize != (1 << merkleHeight))
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
        return error("Aux POW merkle branch size does not match parent coinbase");

    int nNonce;
    memcpy(&nNonce, &pc[4], 4);

<<<<<<< HEAD
=======
    if (nChainIndex != getExpectedIndex(nNonce, nChainId, merkleHeight))
        return error("Aux POW wrong index");

    return true;
}

int
CAuxPow::getExpectedIndex(int nNonce, int nChainId, unsigned h)
{
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
    // Choose a pseudo-random slot in the chain merkle tree
    // but have it be fixed for a size/nonce/chain combination.
    //
    // This prevents the same work from being used twice for the
    // same chain while reducing the chance that two chains clash
    // for the same slot.
<<<<<<< HEAD
    unsigned int rand = nNonce;
    rand = rand * 1103515245 + 12345;
    rand += nChainID;
    rand = rand * 1103515245 + 12345;

    if (nChainIndex != (rand % nSize))
        return error("Aux POW wrong index");

    return true;
}

CScript MakeCoinbaseWithAux(unsigned int nHeight, unsigned int nExtraNonce, vector<unsigned char>& vchAux)
{
    vector<unsigned char> vchAuxWithHeader(UBEGIN(pchMergedMiningHeader), UEND(pchMergedMiningHeader));
    vchAuxWithHeader.insert(vchAuxWithHeader.end(), vchAux.begin(), vchAux.end());

    CScript script = (CScript() << nHeight << CScriptNum(nExtraNonce)) + COINBASE_FLAGS;
    
    // Push OP_2 just in case we want versioning later
    script = script << OP_2 << vchAuxWithHeader;
    
    return script;
}


void IncrementExtraNonceWithAux(CBlock* pblock, CBlockIndex* pindexPrev, unsigned int& nExtraNonce, vector<unsigned char>& vchAux)
{
    // Update nExtraNonce
    static uint256 hashPrevBlock;
    if (hashPrevBlock != pblock->hashPrevBlock)
    {
        nExtraNonce = 0;
        hashPrevBlock = pblock->hashPrevBlock;
    }
    ++nExtraNonce;

    unsigned int nHeight = pindexPrev->nHeight+1; // Height first in coinbase required for block.version=2
    pblock->vtx[0].vin[0].scriptSig = MakeCoinbaseWithAux(nHeight, nExtraNonce, vchAux);
    pblock->hashMerkleRoot = pblock->BuildMerkleTree();
}


=======

    unsigned rand = nNonce;
    rand = rand * 1103515245 + 12345;
    rand += nChainId;
    rand = rand * 1103515245 + 12345;

    return rand % (1 << h);
}
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
