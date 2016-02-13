### Qos ###

<<<<<<< HEAD
This is a Linux bash script that will set up tc to limit the outgoing bandwidth for connections to the Dogecoin network. It limits outbound TCP traffic with a source or destination port of 8333, but not if the destination IP is within a LAN (defined as 192.168.x.x).
=======
This is a Linux bash script that will set up tc to limit the outgoing bandwidth for connections to the Dogecoin network. It limits outbound TCP traffic with a source or destination port of 22556, but not if the destination IP is within a LAN (defined as 192.168.x.x).
>>>>>>> f568462ca04b73485d7e41266a2005155ff69707

This means one can have an always-on dogecoind instance running, and another local dogecoind/dogecoin-qt instance which connects to this node and receives blocks from it.
