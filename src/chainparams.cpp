// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector <CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count) {
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7 * 24 * 60 * 60;
    for (unsigned int i = 0; i < count; i++) {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x69;
        pchMessageStart[1] = 0x5e;
        pchMessageStart[2] = 0xf2;
        pchMessageStart[3] = 0xa9;
        vAlertPubKey = ParseHex(
                "04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f");
        nDefaultPort = 34250;
        nRPCPort = 34251;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);

        const char *pszTimestamp = "4 March 2018 Pennsylvania Election: Regional Race Could Offer Clues";
        std::vector <CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char *) pszTimestamp,
                                                                                  (const unsigned char *) pszTimestamp +
                                                                                  strlen(pszTimestamp));
        std::vector <CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1520185570, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime = 1520185570;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 304353;

        hashGenesisBlock = genesis.GetHash();

        //printf("mainnet hashGenesisBlock = %s\n", genesis.GetHash().ToString().c_str());
        //printf("mainnet genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());

        assert(hashGenesisBlock == uint256("0x7590f1dfff3842ece0e6b65ae2a64b6db4cd2d663e1f32aeab125a3a2082e4ec"));
        assert(genesis.hashMerkleRoot == uint256("0x3ea0f01fc5816a0277ae53b58752470376a4627ac37030c2fb4d9b8d228bb1cd"));

        vSeeds.push_back(CDNSSeedData("seed1", "seed1.donationscoin.org"));
        vSeeds.push_back(CDNSSeedData("seed2", "seed2.donationscoin.org"));
        vSeeds.push_back(CDNSSeedData("seed3", "seed3.donationscoin.org"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 40);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 100);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 153);
        base58Prefixes[EXT_PUBLIC_KEY] =
                boost::assign::list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container < std::vector < unsigned char > >
                ();
        base58Prefixes[EXT_SECRET_KEY] =
                boost::assign::list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container < std::vector < unsigned char > >
                ();

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 5000000;
    }

    virtual const CBlock &GenesisBlock() const { return genesis; }

    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector <CAddress> &FixedSeeds() const {
        return vFixedSeeds;
    }

protected:
    CBlock genesis;
    vector <CAddress> vFixedSeeds;
};

static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xaf;
        pchMessageStart[1] = 0x24;
        pchMessageStart[2] = 0xbc;
        pchMessageStart[3] = 0x61;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex(
                "04a47288212ebbfa087a1d29f1efa8824730381f17bdbda3255aa23873b4961d914f9a73f1b79ac3e014aa5d1d585bbaa42cdafafb752216bea19ea48410890a55");
        nDefaultPort = 34350;
        nRPCPort = 34351;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();

        //printf("testnet hashGenesisBlock = %s\n", genesis.GetHash().ToString().c_str());
        //printf("testnet genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());

        assert(hashGenesisBlock == uint256("0x6a474fb15759fcba9b8493450fd8574cd6870661c3d7bc3817d68f6f09c61807"));
// 4f066b46971e2e791c6277c2059e3a272c77f9a0ea0a5daef7ba9869d48b839a
        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 40);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 100);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 153);
        base58Prefixes[EXT_PUBLIC_KEY] =
                boost::assign::list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container < std::vector < unsigned char > >
                ();
        base58Prefixes[EXT_SECRET_KEY] =
                boost::assign::list_of(0x04)(0x35)(0x83)(0x94).convert_to_container < std::vector < unsigned char > >
                ();

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }

    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};

static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0xc8;
        pchMessageStart[2] = 0x2d;
        pchMessageStart[3] = 0xf9;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1520185571;
        genesis.nBits = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 2;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 34355;
        strDataDir = "regtest";

        //printf("regtest hashGenesisBlock = %s\n", genesis.GetHash().ToString().c_str());
        //printf("regtest genesis.hashMerkleRoot = %s\n", genesis.hashMerkleRoot.ToString().c_str());

        assert(hashGenesisBlock == uint256("0x9cfaef6d57ed1ec4d3e5a4ce326fadd8cf6128ecaa40614a2f5e96c9958454f4"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }

    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};

static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}