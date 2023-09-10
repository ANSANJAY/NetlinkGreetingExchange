# 📝 Netlink Protocol and Linux Kernel Module Revision Notes

## 🌐 Concept of Netlink Protocol
- Netlink allows communication between userspace applications and the Linux kernel.
- To specify which kernel subsystem the application wants to communicate with, a unique ID, called the Netlink protocol number, is used.
- Pre-existing Linux subsystems have reserved netlink protocol numbers.
- The routing infrastructure and TCP IP stack in the kernel have a Netlink protocol number of zero, known as Netlink route.
- To see what netlink protocol numbers are being used, check the file: `Linux/netlink.h`.
- In the project described, the unused netlink protocol number 31 is used for a new kernel subsystem.

## 📁 Greet Netlink LCMC File Creation
- Inside the directory named "Greetings", a file named `greet Netlink lcmc` is created to represent the Linux kernel module.

## 🚀 Steps for Linux Kernel Module Creation
1. **Initialization and Cleanup Functions**
   - Every Linux kernel module starts with an initialization function and ends with a cleanup function.
   - A message is printed during initialization to indicate successful insertion of the module. A return value of 0 means success.
   - During cleanup, a message is printed to indicate the module's successful removal.

2. **Receiving Data from User Space**
   - A variable of type `netlink_kernel_cfg` is defined. This data structure is provided by the Linux kernel.
   - Within this structure, there's an 'input' member, which is a pointer to a function meant to receive data from user space.
   - When data is received from user space, this function is invoked in kernel space.
   - The prototype of this function matches the datatype of the 'input' pointer in the `netlink_kernel_cfg` structure.

3. **Creating a Netlink Socket**
   - Upon inserting the Linux kernel module, it should create a netlink socket that defines the type of data it will receive from user space.
   - The socket is created using the `netlink_kernel_create` API.
   - The first argument is a global variable `init_net`, representing the complete networking subsystem in the kernel.
   - The second argument is the netlink protocol number, which for this project is defined as 31.
   - The third argument is the configuration parameter (`netlink_kernel_cfg`).

4. **Releasing Kernel Resources**
   - To prevent kernel resource leaks, any resources created by the kernel module must be released upon its removal.
   - For this module, the only resource is the netlink socket, which is released using the `netlink_kernel_release` API.

5. **Header Files Inclusion**
   - Always include `Linux/module.h` when writing a Linux kernel module.
   - For netlink related functionalities, include `Linux/netlink.h` and `net/socket.h`.
   - For string handling APIs in kernel space, include `linux/string.h`.

## 📖 Next Steps
- The subsequent steps involve having the Linux kernel module receive messages from user space, process them, and reply back.

## 🎤 Interview Questions

1. **What is the main purpose of the Netlink protocol in the Linux kernel?**
   - Answer: 📌 Netlink allows communication between userspace applications and the Linux kernel, and each kernel subsystem is identified using a unique Netlink protocol number.

2. **What is the significance of the `netlink_kernel_cfg` structure in relation to the Netlink protocol?**
   - Answer: 📌 The `netlink_kernel_cfg` data structure allows us to define various parameters of our netlink communication in kernel space. The 'input' member within this structure points to a function meant to receive data from user space.

3. **Why is it crucial to release resources when a kernel module is removed, and how is it done for a netlink socket?**
   - Answer: 📌 Releasing resources prevents kernel resource leaks. If not released, resources continue to exist in kernel space without any code using them. For a netlink socket, the `netlink_kernel_release` API is used.

4. **Which header file must always be included when writing any Linux kernel module?**
   - Answer: 📌 The `Linux/module.h` header file must always be included when writing any Linux kernel module.

5. **Describe the process of creating a netlink socket in the Linux kernel module.**
   - Answer: 📌 To create a netlink socket, the `netlink_kernel_create` API is used. It takes three arguments: the global variable `init_net` (representing the complete networking subsystem in the kernel), the netlink protocol number, and the configuration parameter (`netlink_kernel_cfg`).

I hope these detailed notes and interview questions help you in your revision for interviews! 🚀
