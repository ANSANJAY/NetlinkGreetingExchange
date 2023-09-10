# Userspace Program Design Notes 📒

Welcome back to our userspace-kernel communication topic! Let's dive into our recent progress and future steps. ✨

## 1. Background 🌐

- Until now, a standalone API has been created to **send messages from userspace to kernel space**.
- The next target is to develop a **full-fledged userspace program**.

## 2. Design/Thread Model Discussion 🧵

- The **execution starts from the Main function**.
- The immediate action is the **creation of a netlink socket**.
  - The **protocol number** remains the same as before, which is `31`.
- The socket will then be **bound**. More on binding during code discussion.

## 3. Need for Multi-Threading 🔄

- To facilitate simultaneous message sending and receiving, a **separate thread will be initiated**.
  - The **main thread** is responsible for sending messages to kernel space.
  - The **separate receiver thread** deals with incoming messages from the kernel.

## 4. Main Thread Workflow 🧠

1. Enter the **main menu**.
2. More options will be added as the program evolves.
3. The first option, **"Greet Kernel"**:
   - Sends a text message to the kernel.
   - Invokes the previously created API to send the netlink message.
4. After sending, it returns to the **main menu**.
5. This **loop continues indefinitely**.

## 5. Receiver Thread Workflow 🔊

- This thread is continuously active and listens for messages.
- Uses the **blocking 'receive message' system call**.
  - Will remain inactive until a message is detected.
- Once a message is received:
  - The program resumes execution.
  - The message is processed.
  - Returns to the 'receive message' state, waiting for the next message.
  
## 6. Final Picture 🎨

- The user space application operates with **two threads**.
- The main thread keeps sending messages.
- The receiver thread awaits and processes incoming messages.

---

# Interview Questions ❓

**Q1:** What is the purpose of the standalone API developed earlier?  
**A1:** The standalone API was developed to **send messages from userspace to kernel space**.

**Q2:** Why is the protocol number `31` significant in this context?  
**A2:** The protocol number `31` is the reserved number used when creating the **netlink socket** both in the user space and kernel space.

**Q3:** What is the primary role of the separate receiver thread?  
**A3:** The separate receiver thread's primary role is to **continuously listen and process messages coming from the kernel space**.

**Q4:** Describe the behavior of the 'receive message' system call in the receiver thread.  
**A4:** The 'receive message' system call is a **blocking call**. The receiver thread will stay blocked on this call until it receives some data on the netlink socket.

**Q5:** How does the main thread function in relation to the main menu?  
**A5:** The main thread enters the **main menu** where it offers options to interact with the kernel. After performing an action, such as sending a message, it returns to the main menu, and this continues in an **infinite loop**.

--- 

Good luck with your interviews! 🍀
