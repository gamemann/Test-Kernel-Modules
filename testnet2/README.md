# More Advanced Netfilter Kernel Module
## Description
A more complex netfilter kernel module. In this module, any incoming UDP packets with the destination port `8888` will be sent back to the host it came from. Thing is basically a ping-pong effect.

Two lines will be outputted every time an incoming packet matches the above and is sent back. Output will be located in `/var/log/kern.log` and here is an output example:

```
Sep 17 00:25:22 test02 kernel: [112626.489512] Detected UDP packet from 10.50.0.4 on port 8888. Sending packet back where it came from!
Sep 17 00:25:22 test02 kernel: [112626.489548] Sending packet back to 10.50.0.4 from 10.50.0.3. Dst port => 58618. Source port => 8888. Source starting MAC byte => 1a, source ending MAC byte => a6. Destination starting MAC byte => ae. Destination ending MAC byte => 6d. UDP length => 88.
Sep 17 00:25:22 test02 kernel: [112626.489586] Detected UDP packet from 10.50.0.4 on port 8888. Sending packet back where it came from!
Sep 17 00:25:22 test02 kernel: [112626.489594] Sending packet back to 10.50.0.4 from 10.50.0.3. Dst port => 18305. Source port => 8888. Source starting MAC byte => 1a, source ending MAC byte => a6. Destination starting MAC byte => ae. Destination ending MAC byte => 6d. UDP length => 88.
Sep 17 00:25:22 test02 kernel: [112626.489603] Detected UDP packet from 10.50.0.4 on port 8888. Sending packet back where it came from!
Sep 17 00:25:22 test02 kernel: [112626.489610] Sending packet back to 10.50.0.4 from 10.50.0.3. Dst port => 39306. Source port => 8888. Source starting MAC byte => 1a, source ending MAC byte => a6. Destination starting MAC byte => ae. Destination ending MAC byte => 6d. UDP length => 88.
Sep 17 00:25:22 test02 kernel: [112626.489618] Detected UDP packet from 10.50.0.4 on port 8888. Sending packet back where it came from!
Sep 17 00:25:22 test02 kernel: [112626.489626] Sending packet back to 10.50.0.4 from 10.50.0.3. Dst port => 39306. Source port => 8888. Source starting MAC byte => 1a, source ending MAC byte => a6. Destination starting MAC byte => ae. Destination ending MAC byte => 6d. UDP length => 88.
Sep 17 00:25:22 test02 kernel: [112626.489634] Detected UDP packet from 10.50.0.4 on port 8888. Sending packet back where it came from!
Sep 17 00:25:22 test02 kernel: [112626.489641] Sending packet back to 10.50.0.4 from 10.50.0.3. Dst port => 44534. Source port => 8888. Source starting MAC byte => 1a, source ending MAC byte => a6. Destination starting MAC byte => ae. Destination ending MAC byte => 6d. UDP length => 88.
Sep 17 00:25:22 test02 kernel: [112626.489649] Detected UDP packet from 10.50.0.4 on port 8888. Sending packet back where it came from!
Sep 17 00:25:22 test02 kernel: [112626.489656] Sending packet back to 10.50.0.4 from 10.50.0.3. Dst port => 18305. Source port => 8888. Source starting MAC byte => 1a, source ending MAC byte => a6. Destination starting MAC byte => ae. Destination ending MAC byte => 6d. UDP length => 88.
```

I used my [Packet Flooding](https://github.com/gamemann/Packet-Flooder) tool to test this.