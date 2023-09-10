### Notes on Userspace Program - Receiving Side 📝

---

#### Overview 🌐
- The lecture continues from the previous one focusing on the **receiving side** of the userspace program.
- The flowchart in the earlier lecture outlined the process. After binding the netlink socket, a receiving thread is initiated.

#### Key Takeaways 📌

1. **File Details**:
   - The file in question is `userspace.c`.
   - Right after binding the netlink socket, the code initiates a new thread before entering an infinite loop.

2. **Thread Arguments**:
   - Introduced a new data structure: `thread_argument`.
   - Contains a single int member - `socket file descriptor`.
   - This descriptor is assigned the same value as the one for the Netlink socket file descriptor.

3. **Receiver Thread**:
   - A new receiver thread is initiated with the function `start kernel data receiver thread`.
   - This function creates a new thread and starts it.
   - The actual logic of data reception from the kernel space is inside the function `start kernel receiver thread`.

4. **Buffer Creation**:
   - To receive data from kernel space, memory allocation is required.
   - A buffer, pointed by `netlink header receive pointer`, is allocated.
   - Size of the buffer is `Netlink message header LAN` + `max payload`.
   - `max payload` is a constant value, typically 2048 bytes.

5. **Receiving Process**:
   - The receiving loop is infinite (`do while` loop).
   - Memory is initialized and wrapped inside a vector data structure.
   - The `outer message header` is also initialized and given the vector pointer.
   - Since the message is being received, the `message name` is null.
   - `receive message` system call is invoked, blocking the userspace program until a message is received from the kernel.
   - On receipt, the netlink message header and the payload are accessed, and the received message is printed.
   - The loop continues, waiting for the next message.

6. **Compiling**:
   - After implementation, the code should be compiled to ensure messages can be sent to the kernel space and replies can be received from it.

---

#### Interview Questions ❓ (with Answers ✅)

**Q1**: What is the primary function of the `thread_argument` data structure in the userspace program?
> **A1**: The `thread_argument` data structure is used to hold the `socket file descriptor`, which is vital for communication with the kernel space via the netlink socket.

**Q2**: How does the userspace program handle incoming messages from the kernel space?
> **A2**: The program uses a separate receiver thread that continually runs in an infinite loop. This thread initializes a buffer and sets up the necessary message headers, then blocks on the `receive message` system call, waiting for a message from the kernel space. Upon receiving a message, it processes and prints it, then continues to await the next message.

**Q3**: What is the purpose of the `receive message` system call, and how does the userspace program behave when it's invoked?
> **A3**: The `receive message` system call is used to wait for and retrieve a message from the kernel space. It's a blocking call, which means the userspace program (or the specific thread invoking it) will halt its execution and wait until a message is received. Once a message is received, the function unblocks and proceeds with its subsequent operations.

**Q4**: How is the buffer sized, and why is it designed that way?
> **A4**: The buffer's size is determined by the sum of the `Netlink message header LAN` and a constant `max payload`. This design ensures that the buffer can accommodate both the message header and the maximum expected payload, ensuring that messages from the kernel space can be fully received and processed without truncation.

**Q5**: What happens if the userspace program receives a message while already processing another message?
> **A5**: The design of the infinite loop in the receiver thread ensures that after processing and printing a received message, it reinitializes and blocks on the `receive message` system call again. So, even if a message is being processed, the next message will be queued up and processed as soon as the current one is finished, ensuring smooth and sequential processing of incoming messages.

---

I hope this detailed revision note helps in your interview preparation! 🌟
