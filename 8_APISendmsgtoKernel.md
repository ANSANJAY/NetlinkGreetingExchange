**📝  Unified API for Sending Messages via Netlink Socket** 🚀



### **1. Introduction:** 🌐

To facilitate seamless communication from the userspace program to the kernel space through the netlink socket, we're introducing a consolidated API - `send_netlink_message_to_kernel`.

---

### **2. API Overview:** 👩‍💻

**API Name:** `send_netlink_message_to_kernel`

**Arguments:**
1. **File Descriptor** of the netlink socket: Initialized when the userspace program begins.
2. **Payload**: Data that the userspace program wants to send to the kernel.
3. **Payload Size**: The total size of the above payload.
4. **Netlink Message Type**: Indicates the kind of netlink message being sent from the userspace to kernel space.
   - For our context, this field aligns with an enumeration titled `greet`.
5. **Flags**: Directions for the kernel space regarding message processing.

---

### **3. API Implementation Steps:** 🛠

1. **Message Preparation**: Craft a message comprising of:
   - **Netlink Message Header**
   - **Payload**

   The exchange between userspace and kernel space always uses this format.

2. **Using the IOV (Input Output Vector) Data Structure**:
   - A minimalistic data structure featuring:
     - `iov_base` (void pointer type): Stores the netlink message header's address.
     - `iov_len` (sys_tty type): Total length of the message, starting from the header to the payload's end.

   By doing this, we indirectly enclose the netlink message to send to kernel space inside the IOV data structure.

3. **Embedding IOV within another structure - `struct message_header`**:
   - **Destination Address**: Specifies the recipient's address. The method to designate this will be elucidated in the code.
   - **Size of Destination Address**: Further details to be shared during the code walkthrough.
   - **Address of the IOV**: As set up in step 2.
   - **Count of IOV Structures**: As we've incorporated only one IOV, this value is 1.

   For the **Destination Address**, we utilize a data type known as `struct sockaddr_channel`, a socket address structure designed for netlink sockets. Herein, we only adjust two fields:
   - **Netlink Family**: Always set to `AF_NETLINK`.
   - **Port ID**: Set to 0 for kernel space communication.

4. **Sending the User Space Message to Kernel Space via Netlink Socket**:
   - **1st Argument**: File descriptor of the previously created socket.
   - **2nd Argument**: Address of the outer message header.
   - **3rd Argument**: Generally set to 0.

---

### **4. Conclusion and Utility of the API**: 💡

- **Versatility**: This API is engineered to be a generic tool. It can transmit various types of messages or payloads from the userspace to kernel space.

---

**🤓 Interview Questions:** 📜

1. **Q:** What is the primary purpose of the `send_netlink_message_to_kernel` API?

   **A:** The API's main role is to simplify and standardize the sending of any type of message from the userspace program to the kernel space via a netlink socket.

2. **Q:** What is the significance of the IOV (Input Output Vector) data structure in the API's implementation?

   **A:** IOV acts as an intermediate structure to encapsulate the netlink message, thereby enabling efficient message transmission to the kernel space.

3. **Q:** Why do we need an additional wrapping layer (`struct message_header`) after encapsulating the netlink message inside the IOV?

   **A:** The `struct message_header` acts as an outer message header, providing a comprehensive framework to embed destination details, size, and other critical metadata to ensure seamless message communication.

4. **Q:** In the context of netlink communication, what value do we typically set for the destination's Port ID and why?

   **A:** For communication targeting kernel space, the Port ID is usually set to 0. This is because the kernel space's designated Port ID is always zero.

---

📘 **Resources**:

1. [Netlink Socket Overview](https://man7.org/linux/man-pages/man7/netlink.7.html)
2. [Working with IOV (Input Output Vector)](https://en.wikipedia.org/wiki/Vectored_I/O)

---

