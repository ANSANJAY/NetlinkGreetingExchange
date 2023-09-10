# Notes on Kernel to User Space Communication via Netlink Sockets 🐧

## Kernel Replying to User Space 🔄

1. **Acknowledgement Flag**: 
   - The kernel should only send data back to the user space when the user space specifies the acknowledgment flag in the Netlink message header flags.
   - By setting the acknowledgement flag, the user space informs the kernel that it expects a reply after the message has been received.

2. **Memory Allocation for Reply Message**: 
   - A character array of size 256 bytes is initialized to store the kernel's reply.
   - The array is then populated using the `snprintf` function to create a formatted message indicating that the message from the user space (identified by the process port ID) has been processed by the kernel.

3. **Socket Buffers for Data Exchange**:
   - Data is exchanged between user and kernel space using socket buffers.
   - A socket buffer, `skb_out`, is initialized.
   - `netlink_msg_new` API: Creates a new socket buffer of the desired size (256 bytes in this case).

4. **Message Preparation**:
   - The message consists of a Netlink message header followed by a payload.
   - `netlink_msg_put` API: This function is used to populate the Netlink message header fields. Important fields include:
     - `port ID`: Always zero for kernel as the sender.
     - `sequence number`: Same as the one from the incoming message from user space.
     - `netlink message type`: Typically set as `NETLINK_MSG_DONE`.

5. **Sending the Message**:
   - `netlink_msg_unicast` API: Sends the data from the kernel to the user space.
   - Requires the netlink socket, socket buffer pointer, and the user space application's process ID.
   - If this API fails (returns a negative value), any dynamic memory (like socket buffers) allocated must be freed. This is done using the `free_skb` API.

6. **Testing & Debugging**:
   - It's crucial to write a user space application to send data to the kernel space to fully test the kernel module.
   - Without a user space application, the kernel's code cannot be properly observed in action.
   - Upcoming lectures will cover writing such user space applications.

## Interview Questions 🤔

1. **Q**: Why is the acknowledgement flag important in the Netlink message header flags?
   - **A**: The acknowledgment flag indicates to the kernel that the user space expects a reply once its message has been received.

2. **Q**: How is data exchanged between the user and kernel space?
   - **A**: Data is exchanged using socket buffers.

3. **Q**: What does the `netlink_msg_put` API function do?
   - **A**: The `netlink_msg_put` function populates the fields of the Netlink message header inside a socket buffer.

4. **Q**: How can you handle the failure of the `netlink_msg_unicast` API?
   - **A**: If `netlink_msg_unicast` returns a negative value, indicating failure, any dynamically allocated memory such as socket buffers must be freed using APIs like `free_skb`.

5. **Q**: Why is it necessary to have a user space application to test the kernel module fully?
   - **A**: Without a user space application sending data to the kernel module, we cannot observe the kernel's code in action or ensure that data exchange is functioning as expected.
