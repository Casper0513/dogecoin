<<<<<<< HEAD
#!/usr/bin/env python
# Copyright (c) 2014 The Bitcoin Core developers
# Distributed under the MIT/X11 software license, see the accompanying
=======
#!/usr/bin/env python2
# Copyright (c) 2014 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

# Exercise the listtransactions API

from test_framework.test_framework import BitcoinTestFramework
from test_framework.util import *


def check_array_result(object_array, to_match, expected):
    """
    Pass in array of JSON objects, a dictionary with key/value pairs
    to match against, and another dictionary with expected key/value
    pairs.
    """
    num_matched = 0
    for item in object_array:
        all_match = True
        for key,value in to_match.items():
            if item[key] != value:
                all_match = False
        if not all_match:
            continue
        for key,value in expected.items():
            if item[key] != value:
                raise AssertionError("%s : expected %s=%s"%(str(item), str(key), str(value)))
            num_matched = num_matched+1
    if num_matched == 0:
        raise AssertionError("No objects matched %s"%(str(to_match)))

<<<<<<< HEAD
def run_test(nodes):
    # Simple send, 0 to 1:
    txid = nodes[0].sendtoaddress(nodes[1].getnewaddress(), 0.1)
    sync_mempools(nodes)
    check_array_result(nodes[0].listtransactions(),
                       {"txid":txid},
                       {"category":"send","account":"","amount":Decimal("-0.1"),"confirmations":0})
    check_array_result(nodes[1].listtransactions(),
                       {"txid":txid},
                       {"category":"receive","account":"","amount":Decimal("0.1"),"confirmations":0})
    # mine a block, confirmations should change:
    nodes[0].setgenerate(True, 1)
    sync_blocks(nodes)
    check_array_result(nodes[0].listtransactions(),
                       {"txid":txid},
                       {"category":"send","account":"","amount":Decimal("-0.1"),"confirmations":1})
    check_array_result(nodes[1].listtransactions(),
                       {"txid":txid},
                       {"category":"receive","account":"","amount":Decimal("0.1"),"confirmations":1})

    # send-to-self:
    txid = nodes[0].sendtoaddress(nodes[0].getnewaddress(), 0.2)
    check_array_result(nodes[0].listtransactions(),
                       {"txid":txid, "category":"send"},
                       {"amount":Decimal("-0.2")})
    check_array_result(nodes[0].listtransactions(),
                       {"txid":txid, "category":"receive"},
                       {"amount":Decimal("0.2")})

    # sendmany from node1: twice to self, twice to node2:
    send_to = { nodes[0].getnewaddress() : 0.11, nodes[1].getnewaddress() : 0.22,
                nodes[0].getaccountaddress("from1") : 0.33, nodes[1].getaccountaddress("toself") : 0.44 }
    txid = nodes[1].sendmany("", send_to)
    sync_mempools(nodes)
    check_array_result(nodes[1].listtransactions(),
                       {"category":"send","amount":Decimal("-0.11")},
                       {"txid":txid} )
    check_array_result(nodes[0].listtransactions(),
                       {"category":"receive","amount":Decimal("0.11")},
                       {"txid":txid} )
    check_array_result(nodes[1].listtransactions(),
                       {"category":"send","amount":Decimal("-0.22")},
                       {"txid":txid} )
    check_array_result(nodes[1].listtransactions(),
                       {"category":"receive","amount":Decimal("0.22")},
                       {"txid":txid} )
    check_array_result(nodes[1].listtransactions(),
                       {"category":"send","amount":Decimal("-0.33")},
                       {"txid":txid} )
    check_array_result(nodes[0].listtransactions(),
                       {"category":"receive","amount":Decimal("0.33")},
                       {"txid":txid, "account" : "from1"} )
    check_array_result(nodes[1].listtransactions(),
                       {"category":"send","amount":Decimal("-0.44")},
                       {"txid":txid, "account" : ""} )
    check_array_result(nodes[1].listtransactions(),
                       {"category":"receive","amount":Decimal("0.44")},
                       {"txid":txid, "account" : "toself"} )
    

def main():
    import optparse

    parser = optparse.OptionParser(usage="%prog [options]")
    parser.add_option("--nocleanup", dest="nocleanup", default=False, action="store_true",
                      help="Leave bitcoinds and test.* datadir on exit or error")
    parser.add_option("--srcdir", dest="srcdir", default="../../src",
                      help="Source directory containing bitcoind/bitcoin-cli (default: %default%)")
    parser.add_option("--tmpdir", dest="tmpdir", default=tempfile.mkdtemp(prefix="test"),
                      help="Root directory for datadirs")
    (options, args) = parser.parse_args()

    os.environ['PATH'] = options.srcdir+":"+os.environ['PATH']

    check_json_precision()

    success = False
    nodes = []
    try:
        print("Initializing test directory "+options.tmpdir)
        if not os.path.isdir(options.tmpdir):
            os.makedirs(options.tmpdir)
        initialize_chain(options.tmpdir)

        nodes = start_nodes(2, options.tmpdir)
        connect_nodes(nodes[1], 0)
        sync_blocks(nodes)

        run_test(nodes)

        success = True

    except AssertionError as e:
        print("Assertion failed: "+e.message)
    except Exception as e:
        print("Unexpected exception caught during testing: "+str(e))
        traceback.print_tb(sys.exc_info()[2])

    if not options.nocleanup:
        print("Cleaning up")
        stop_nodes(nodes)
        wait_bitcoinds()
        shutil.rmtree(options.tmpdir)

    if success:
        print("Tests successful")
        sys.exit(0)
    else:
        print("Failed")
        sys.exit(1)
=======
class ListTransactionsTest(BitcoinTestFramework):

    def run_test(self):
        # Simple send, 0 to 1:
        txid = self.nodes[0].sendtoaddress(self.nodes[1].getnewaddress(), 100)
        self.sync_all()
        check_array_result(self.nodes[0].listtransactions(),
                           {"txid":txid},
                           {"category":"send","account":"","amount":-100,"confirmations":0})
        check_array_result(self.nodes[1].listtransactions(),
                           {"txid":txid},
                           {"category":"receive","account":"","amount":100,"confirmations":0})
        # mine a block, confirmations should change:
        self.nodes[0].generate(1)
        self.sync_all()
        check_array_result(self.nodes[0].listtransactions(),
                           {"txid":txid},
                           {"category":"send","account":"","amount":-100,"confirmations":1})
        check_array_result(self.nodes[1].listtransactions(),
                           {"txid":txid},
                           {"category":"receive","account":"","amount":100,"confirmations":1})

        # send-to-self:
        txid = self.nodes[0].sendtoaddress(self.nodes[0].getnewaddress(), 200)
        check_array_result(self.nodes[0].listtransactions(),
                           {"txid":txid, "category":"send"},
                           {"amount":-200})
        check_array_result(self.nodes[0].listtransactions(),
                           {"txid":txid, "category":"receive"},
                           {"amount":200})

        # sendmany from node1: twice to self, twice to node2:
        send_to = { self.nodes[0].getnewaddress() : 110,
                    self.nodes[1].getnewaddress() : 220,
                    self.nodes[0].getaccountaddress("from1") : 330,
                    self.nodes[1].getaccountaddress("toself") : 440 }
        txid = self.nodes[1].sendmany("", send_to)
        self.sync_all()
        check_array_result(self.nodes[1].listtransactions(),
                           {"category":"send","amount":-110},
                           {"txid":txid} )
        check_array_result(self.nodes[0].listtransactions(),
                           {"category":"receive","amount":110},
                           {"txid":txid} )
        check_array_result(self.nodes[1].listtransactions(),
                           {"category":"send","amount":-220},
                           {"txid":txid} )
        check_array_result(self.nodes[1].listtransactions(),
                           {"category":"receive","amount":220},
                           {"txid":txid} )
        check_array_result(self.nodes[1].listtransactions(),
                           {"category":"send","amount":-330},
                           {"txid":txid} )
        check_array_result(self.nodes[0].listtransactions(),
                           {"category":"receive","amount":330},
                           {"txid":txid, "account" : "from1"} )
        check_array_result(self.nodes[1].listtransactions(),
                           {"category":"send","amount":-440},
                           {"txid":txid, "account" : ""} )
        check_array_result(self.nodes[1].listtransactions(),
                           {"category":"receive","amount":440},
                           {"txid":txid, "account" : "toself"} )
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707

if __name__ == '__main__':
    ListTransactionsTest().main()

