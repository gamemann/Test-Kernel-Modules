# Simple Kernel Module For Netfilter
## Description
A simple kernel module for dropping UDP packets with the destination port `8888`. It will print a line to `/var/log/kern.log` when a packet is dropped.

Here's an example of its output:

```
Sep 16 22:21:10 test02 kernel: [105174.925559] Dropping UDP packet from 10.50.0.4 on port 8888.
Sep 16 22:21:10 test02 kernel: [105174.925566] Dropping UDP packet from 10.50.0.4 on port 8888.
Sep 16 22:21:10 test02 kernel: [105174.925571] Dropping UDP packet from 10.50.0.4 on port 8888.
Sep 16 22:21:10 test02 kernel: [105174.933436] Dropping UDP packet from 10.50.0.4 on port 8888.
Sep 16 22:21:10 test02 kernel: [105174.933438] Dropping UDP packet from 10.50.0.4 on port 8888.
Sep 16 22:21:10 test02 kernel: [105174.933440] Dropping UDP packet from 10.50.0.4 on port 8888.
Sep 16 22:21:10 test02 kernel: [105174.933441] Dropping UDP packet from 10.50.0.4 on port 8888.
Sep 16 22:21:10 test02 kernel: [105174.933442] Dropping UDP packet from 10.50.0.4 on port 8888.
Sep 16 22:21:10 test02 kernel: [105174.933443] Dropping UDP packet from 10.50.0.4 on port 8888.
Sep 16 22:21:10 test02 kernel: [105174.933444] Dropping UDP packet from 10.50.0.4 on port 8888.
Sep 16 22:21:10 test02 kernel: [105174.933445] Dropping UDP packet from 10.50.0.4 on port 8888.
```

I used my [Packet Flooding](https://github.com/gamemann/Packet-Flooder) tool to test this.