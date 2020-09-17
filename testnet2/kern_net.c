#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/net.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/in.h>
#include <linux/skbuff.h>

#include <linux/if_ether.h>
#include <linux/ip.h>
#include <linux/udp.h>

#include <net/ip.h>
#include <net/udp.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Deacon");
MODULE_DESCRIPTION("A more complex Linux kernel module using netfilter.");
MODULE_VERSION("0.1");

static unsigned int process_packet(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    // Ethernet header.
    struct ethhdr *eth = (struct ethhdr *)skb_mac_header(skb);

    // IP header.
    struct iphdr *iph = (struct iphdr *)skb_network_header(skb);

    // UDP header.
    struct udphdr *udph;

    // Other.
    unsigned int oldAddr;
    unsigned short oldPort;
    unsigned int udplen;

    // Check if UDP.
    if (iph->protocol == IPPROTO_UDP)
    {
        // Initialize UDP header.
        udph = (struct udphdr *)skb_transport_header(skb);

        // Check if destination port is 8888 and drop if so.
        if (udph->dest == htons(8888))
        {
            printk(KERN_INFO "Detected UDP packet from %pI4 on port 8888. Sending packet back where it came from!\n", &iph->saddr);

            // Swap the source and destination MACs of the Ethernet header.
            memcpy(eth->h_dest, eth->h_source, ETH_ALEN);
            memcpy(eth->h_source, skb->dev->dev_addr, ETH_ALEN);
        
            // Add ethernet header to SKB buffer.
            skb->data = (unsigned char *)eth;
            skb->len += sizeof(struct ethhdr);

            // Swap the source and destination addresses on the IP header.
            oldAddr = iph->saddr;
            
            iph->saddr = iph->daddr;
            iph->daddr = oldAddr;

            // Recalculate IP header checksum.
            iph->check = 0;
            ip_send_check(iph);

            // Swap the source and destination ports on the UDP header.
            oldPort = udph->source;

            udph->source = udph->dest;
            udph->dest = oldPort;

            // Recalculate UDP header checksum.
            udplen = ntohs(iph->tot_len) - (iph->ihl * 4);

            udph->check = 0;
            udph->check = udp_v4_check(udplen, iph->saddr, iph->daddr, csum_partial((char *)udph, udplen, 0));

            printk(KERN_INFO "Sending packet back to %pI4 from %pI4. Dst port => %d. Source port => %d. Source starting MAC byte => %x, source ending MAC byte => %x. Destination starting MAC byte => %x. Destination ending MAC byte => %x. UDP length => %d.\n", &iph->daddr, &iph->saddr, ntohs(udph->dest), ntohs(udph->source), eth->h_source[0], eth->h_source[5], eth->h_dest[0], eth->h_dest[5], udplen);

            // Set packet type to outgoing.
            skb->pkt_type = PACKET_OUTGOING;

            // Send packet back out.
            if (dev_queue_xmit(skb) == NET_XMIT_SUCCESS)
            {
                return NF_STOLEN;
            }
            else
            {
                return NF_DROP;
            }
        }
    }

    return NF_ACCEPT;
}

static struct nf_hook_ops netfilter_hook =
{
    .hook = process_packet,
    .hooknum = NF_INET_LOCAL_IN,
    .pf = NFPROTO_IPV4,
    .priority = NF_IP_PRI_FIRST
};


static int __init test_init(void)
{
    printk(KERN_INFO "The module has been initiated!");
    
    return nf_register_net_hook(&init_net, &netfilter_hook);
}

static void __exit test_exit(void)
{

    nf_unregister_net_hook(&init_net, &netfilter_hook);

    printk(KERN_INFO "The module has exited!");
}

module_init(test_init);
module_exit(test_exit);