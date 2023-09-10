### 📖 **Understanding API and Netlink Message Implementation to Kernel**

---

#### 📂 **File In Focus**

- **userspace.c**: Represents the userspace program.

---

#### 📌 **Header Files**

- Necessary headers are `#include`d.
- `socket.h` is essential because we're creating a netlink socket.
- `linux/netlink.h` is needed to use the netlink message header and associated data structures.

---

#### 🛠 **Implementation Steps**

1. **Setting the Destination Address**
    - Address: Kernel space.
    - Semantics: Netlink semantics.
    - Data Structure: `socket_netlink` - Used to determine the source or destination address over the netlink socket.
    - Address Family: `AF_NETLINK` (a constant).
    - Destination Process (Kernel) Port ID: 0 (a constant).
  
2. **Creating the Netlink Message Header (appended by payload)**
    - Necessary memory space is reserved using macros (seen for the first time).
        - `Netlink message header LAN`: Macro expanding to the size of the Netlink message header.
        - Always use Linux API macros, like `Netlink message align`, for alignment.
            - The alignment is usually to a multiple of four (e.g., 18 -> 20, 23 -> 24).
    - Message size: Specified in the third argument.
    - Populate netlink header fields:
        - `Netlink message header LAN`: Total length of the message from userspace to kernel.
        - Port ID: Use `getpid()`.
        - Flags: Copy from the fifth argument.
        - Message type: Copy from the fourth argument.
        - Sequence number: Set to 0 for now.

3. **Fill the Payload Data**
    - Use `MCP` or `strcpy` for copying the message.
    - `Netlink message data` macro returns the address of the payload data behind the netlink header.
  
4. **Wrapping the Netlink Message Data Inside the Vector Data Structure**
    - Use a vector variable.
    - `base` field: Address of the netlink header.
    - Specify the total length of the message being sent to the kernel.
  
5. **Second Round of Wrapping Using `struct message header` Data Structure**
    - Initialize the data structure.
    - Fill fields:
        - `message name`: Address of the destination.
        - `message name length`: Size of the destination address.
        - Address of the I/O vector (which contains the message).
        - Number of units of this vector: Set to 1.

6. **Sending the Data to Kernel Space**
    - Use the `sendmsg` API.
    - If the return value is negative, `sendmsg` failed.
        - Check the `error number` global variable for failure reasons.
  
---

#### 🌐 **Additional Notes**

- **Kernel Code Alignment**: There's alignment in the kernel code. Always use macros from Linux APIs for accurate values.
- **Always Use Linux Kernel API Macros**: For instance, when manipulating the Netlink header.
- **Linux/netlink.h**: File where all the macros can be found.
  
---

#### 🔜 **What's Next?**

- Designing a user space application.
    - A two-threaded application is in development.
    - For now, ensure `userspace.c` compiles without errors.

---

#### 💡 **Interview Questions (with Answers)**

1. **Q:** How is the destination address specified in terms of netlink semantics?
    **A:** Using the `socket_netlink` data structure, and specifically setting the address family to `AF_NETLINK` and the port ID to 0 for the kernel space.
   
2. **Q:** What's the significance of the `Netlink message align` macro?
    **A:** It aligns any integral number to the next bigger multiple of four.
    
3. **Q:** How is the payload data filled behind the Netlink header?
    **A:** Using the `MCP` or `strcpy` functions and making use of the `Netlink message data` macro to get the start of the payload data.
    
4. **Q:** How is the message from user space sent to kernel space?
    **A:** By using the `sendmsg` API, which returns the number of bytes sent to the kernel space. If it returns a negative value, it indicates a failure.
    

---
