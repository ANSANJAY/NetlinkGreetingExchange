## Userspace Program Implementation and Netlink Communication 🚀

### **Overview** 📄

In this section, we dive deep into the design and implementation of a userspace program, focusing primarily on its capability to send and receive messages using Netlink sockets to communicate with the kernel space.

```sql
Userspace Program Flowchart

+--------------------------------------------------------+
|                        Start                           |
+--------------------------------------------------------+
                                 |
                                 V
+--------------------------------------------------------+
|                  Execution from Main                    |
+--------------------------------------------------------+
                                 |
                                 V
+--------------------------------------------------------+
|                Create Netlink Socket (31)               |
+--------------------------------------------------------+
                                 |
                                 V
+--------------------------------------------------------+
|                     Bind the Socket                     |
+--------------------------------------------------------+
                                 |
                                 V
+--------------------------------------------------------+
|                   Start Separate Thread                 |
+--------------------------------------------------------+
              |                                       |
          Main Thread                            Receiver Thread
              |                                       |
              V                                       V
+--------------------------------------------------------+       +--------------------------------------------------------+
|                       Main Menu:                       |       |          Call `receive message` system call             |
|    - Greet Kernel (Send netlink message to kernel)     |       +--------------------------------------------------------+
+--------------------------------------------------------+                             |
              |                                       |                             V
              |                                       |       +--------------------------------------------------------+
              |                                       |       |             Process received message from                |
              V                                       |       |                      the kernel space                    |
+--------------------------------------------------------+       +--------------------------------------------------------+
|                       Loop back to                    |                             |
|                       Main Menu                       |                             V
+--------------------------------------------------------+       +--------------------------------------------------------+
                                                               | Loop back to `receive message` system call             |
                                                               +--------------------------------------------------------+


```



### **Design Flow of the Userspace Program** 📐

1. **Start Execution from Main**: Our journey in the userspace program begins here.
2. **Create a Netlink Socket**:
    - Use the same protocol number as used for the kernel space socket.
    - The reserved protocol number is `31`.
3. **Bind the Netlink Socket**: 
    - Essential to define what our socket binds against.
    - Details will be expanded upon in the code discussion.
4. **Launch a Separate Thread**:
    - **Reason**: Allow userspace program to independently receive messages from kernel space, while main thread sends messages.
5. **Main Menu in Main Thread**:
    - Will provide options to interact with the kernel. 
    - First option: `Greet Kernel`
        - Sends a text message to the kernel space/module.
        - Invokes the API: `Send netlink message to kernel`.
    - The main menu runs continuously in an infinite loop.

### **Receiver Thread Flow** 📡

1. **Call the `receive message` system call**:
    - **Blocking Call**: The thread will stay blocked until data is received on the Netlink socket.
2. **Process the Received Message**: After receiving the message, it will be processed.
3. **Loop back to the `receive message` system call**:
    - The receiver thread continues to loop, waiting for new messages from the kernel space.

### **Big Picture View** 🖼

- **Two-threaded application**: 
    1. Main Thread: Sends messages via main menu in a loop.
    2. Receiver Thread: Waits and processes messages from the kernel in a loop.

### **Next Steps** 🚶‍♂️

In the following lessons, this flowchart will be transformed into executable code, giving life to the userspace program.

### **Challenge** 🧗‍♀️

Feel free to try implementing this flowchart on your own and see if you can skip the subsequent lessons!

---

## Interview Questions 🤔

**Q1**: Explain the purpose of creating a separate receiver thread in the userspace program design.

**A1**: The separate receiver thread allows the userspace program to independently receive messages from the kernel space, without hindering the main thread's ability to send messages.

---

**Q2**: What is the significance of the `receive message` system call in the receiver thread flow?

**A2**: The `receive message` system call is a blocking call in the receiver thread flow. This means the thread stays blocked (waits) on this system call until it receives some data on the Netlink socket. Once a message is received, it gets processed, and then the thread goes back to blocking on the `receive message` system call.

---

**Q3**: Why do we need to bind the Netlink socket in the userspace program?

**A3**: Binding the Netlink socket in the userspace program is crucial to define what our socket binds against and to set up a communication endpoint. It ensures that messages are sent and received correctly between the userspace and kernel space.

---

**Q4**: What does the main menu in the main thread provide?

**A4**: The main menu in the main thread provides options for the user to interact with the kernel. For instance, the first option, "Greet Kernel," allows users to send a text message to the kernel space/module.

---

**Q5**: How does the userspace program handle sending and receiving messages concurrently?

**A5**: The userspace program is designed as a two-threaded application. The main thread is responsible for sending messages to the kernel space continuously through a main menu that runs in an infinite loop. Simultaneously, the receiver thread runs in a loop, staying blocked on the `receive message` system call until it receives a message from the kernel space. Once received, it processes the message and then goes back to waiting for new messages. This design ensures concurrent handling of sending and receiving messages.



