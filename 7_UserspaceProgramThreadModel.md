**📝  Netlink Userspace Program Development** 🚀

### **1. Introduction:** 🌐

In this part of the course, the focus is on creating a **Netlink userspace program**.

---

### **2. Steps in the Userspace Program:** 👩‍💻

1. **Creating a Netlink Userspace Socket:**
   - The foremost step is to generate a socket specifically for the userspace.

2. **Establishing a Separate Thread for Netlink Message Reception:**
   - Within the main thread, initiate a secondary thread dubbed the `netlink message receiver thread`.
   - This thread solely dedicates itself to accept incoming messages from kernel space.

     ```mermaid
     graph TD;
       A[Main Thread (Yellow)] -->|Create| B[Receiver Thread (Blue)];
       A -->|Send Messages| C[Kernel Space];
       B -->|Receive Messages| C[Kernel Space];
     ```

3. **Main Thread Responsibilities:** 
   - Acts as a conveyor, transmitting messages to the kernel space.
   - Can be envisioned as a menu-driven program:
     - Presents users with multiple choices for dispatching varied data types to the kernel space.
     - Asks users to input a greeting message for the kernel.
     - Sends user's chosen message to the kernel space receiver thread.

4. **Receiver Thread Responsibilities:**
   - Exclusively tasked with acknowledging messages from kernel space.
   - In our scenario, the thread awaits a `greet reply`.

---

### **3. Summarized Design:** 🎨

The userspace application's architecture is straightforward:

- It's a **dual-threaded application**.
- One thread (`main thread`) handles sending messages to the kernel space.
- The other (`receiver thread`) manages the receipt of messages from the kernel space.

---

**🤓 Interview Questions:** 📜

1. **Q:** What is the initial step in creating a Netlink userspace program?
   
   **A:** The first step is to create a Netlink socket specifically for the userspace.

2. **Q:** Why do we introduce a separate thread (receiver thread) in the userspace program?

   **A:** The separate `receiver thread` is established to solely receive messages from the kernel space, ensuring that message sending and receiving functionalities are isolated and can operate simultaneously.

3. **Q:** How can you differentiate between the main thread and the receiver thread in terms of responsibilities in the userspace program?

   **A:** The `main thread` is responsible for sending messages to the kernel space, often based on user input or choices. In contrast, the `receiver thread` exclusively handles the receipt of messages from the kernel space.

4. **Q:** In the described userspace program, what kind of reply does the receiver thread anticipate from the kernel?

   **A:** The receiver thread anticipates a `greet reply` from the kernel space.

---

📘 **Resources**:

1. [Netlink Socket Overview](https://man7.org/linux/man-pages/man7/netlink.7.html)
2. [Multi-threading in C](https://www.geeksforgeeks.org/multithreading-c-2/)

---
