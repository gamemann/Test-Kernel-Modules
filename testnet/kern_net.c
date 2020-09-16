#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/net.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/in.h>
#include <linux/skbuff.h>

#include <linux/ip.h>
#include <linux/udp.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Christian Deacon");
MODULE_DESCRIPTION("My first netfilter kernel module.");
MODULE_VERSION("0.1");

static unsigned int process_packet(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
    // IP header.
    struct iphdr *iph = (struct iphdr *)skb_network_header(skb);

    // Check if UDP.
    if (iph->protocol == IPPROTO_UDP)
    {
        // Initialize UDP header.
        struct udphdr *udph = (struct udphdr *)skb_transport_header(skb);

        // Check if destination port is 8888 and drop if so.
        if (udph->dest == htons(8888))
        {
            printk(KERN_INFO "Dropping UDP packet from %pI4 on port 8888.\n", &iph->saddr);

            return NF_DROP;
        }
    }

    return NF_ACCEPT;
}

static struct nf_hook_ops netfilter_hook =
{
    .hook = process_packet,
    .hooknum = NF_INET_LOCAL_IN,
    .pf = PF_INET,
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