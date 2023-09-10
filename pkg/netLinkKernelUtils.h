/* 
 * Header file for common definitions and utility functions used 
 * both by the kernel module and user-space applications.
 */

#ifndef __NL_COMMON__  // Header guard to prevent multiple inclusions
#define __NL_COMMON__

#include <linux/netlink.h>  // Necessary for netlink socket definitions

/* 
 * Maximum payload size (in bytes) for messages exchanged 
 * between the kernel and user space.
 */
#define MAX_PAYLOAD 1024

/* 
 * User-defined netlink message types.
 * Any custom message type should be greater than 16 as per netlink protocol definitions.
 */
#define NLMSG_GREET     20

/* 
 * Custom protocol ID for netlink communication.
 * It should match the protocol type used when creating the netlink socket in the kernel.
 * 
 * Note: Choose an ID that's not in use. For this example, 31 is used.
 */
#define NETLINK_TEST_PROTOCOL   31

/**
 * Function to return string representation of netlink message types.
 * 
 * @param nlmsg_type Message type identifier.
 * @return Corresponding string representation.
 */
static inline char *
netlink_get_msg_type(__u16 nlmsg_type){
    switch(nlmsg_type){
        case NLMSG_NOOP:
            return "NLMSG_NOOP";
        case NLMSG_ERROR:
            return "NLMSG_ERROR";
        case NLMSG_DONE:
            return "NLMSG_DONE";
        case NLMSG_OVERRUN:
            return "NLMSG_OVERRUN";
        case NLMSG_GREET:
            return "NLMSG_GREET";
        default:
            return "NLMSG_UNKNOWN";
    }
}

/**
 * Utility function to dump details of a netlink message header.
 * 
 * This function checks if it's being compiled for kernel space (__KERNEL__)
 * or user space and accordingly uses the correct print functions.
 *
 * @param nlh Pointer to the netlink message header to be dumped.
 */
static inline void
nlmsg_dump(struct nlmsghdr *nlh){
#ifdef __KERNEL__  // Check if compiling for kernel space
    printk(KERN_INFO "Dumping Netlink Msgs Hdr");
    printk(KERN_INFO "  Netlink Msg Type = %s", netlink_get_msg_type(nlh->nlmsg_type));
    printk(KERN_INFO "  Netlink Msg len  = %d", nlh->nlmsg_len);
    printk(KERN_INFO "  Netlink Msg flags  = %d", nlh->nlmsg_flags);
    printk(KERN_INFO "  Netlink Msg Seq#  = %d", nlh->nlmsg_seq);
    printk(KERN_INFO "  Netlink Msg Pid#  = %d", nlh->nlmsg_pid);
#else  // User space
    printf("Dumping Netlink Msgs Hdr");
    printf("  Netlink Msg Type = %s", netlink_get_msg_type(nlh->nlmsg_type));
    printf("  Netlink Msg len  = %d", nlh->nlmsg_len);
    printf("  Netlink Msg flags  = %d", nlh->nlmsg_flags);
    printf("  Netlink Msg Seq#  = %d", nlh->nlmsg_seq);
    printf("  Netlink Msg Pid#  = %d", nlh->nlmsg_pid);
#endif
}

#endif /* __NL_COMMON__ */
