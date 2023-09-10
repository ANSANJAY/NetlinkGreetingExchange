
# Netlink Sockets Userspace Application: Revision Guide 📘

## Overview 🌐
Netlink socket is a special IPC used for communication between kernel and userspace applications. The provided code represents a userspace program that communicates with the Linux kernel using Netlink sockets.

## Main Features 🔍
- **Socket Creation**: Establishes a communication channel via a Netlink socket.
- **Message Sending**: Sends messages to the Linux kernel.
- **Message Receiving**: Asynchronously receives messages from the kernel using a dedicated thread.
- **User Interaction**: A menu-driven approach to interact with the kernel.

## Detailed Breakdown 📝

### 1. Socket Creation & Management 🛠️
- Uses the `socket(PF_NETLINK, SOCK_RAW, protocol_number)` system call.
- Binds the created socket using the `bind()` function to specify the address and protocol.
- When done, the socket is closed using the `close()` function.

### 2. Message Formation & Transmission 📤
- The `send_netlink_msg_to_kernel()` function is used for sending messages.
    - Creates a `sockaddr_nl` structure for the destination (Linux kernel).
    - Allocates memory for the Netlink message header (`nlmsghdr`) and its payload.
    - Fills up the header with information (e.g., message type, flags).
    - Copies the application data to the payload.
    - Uses `sendmsg()` to send the message to the kernel.

### 3. Asynchronous Message Reception 📥
- `start_kernel_data_receiver_thread()` function initializes a thread that listens for kernel messages.
- `_start_kernel_data_receiver_thread()` is the core function that does the actual message reception.
    - It waits for kernel messages using `recvmsg()`.
    - Upon message reception, it prints the received message.

### 4. User Interaction 👥
- The `main()` function offers a menu to the user with two options:
    1. Send a greeting to the kernel.
    2. Exit the program.

---

## Code workflow

```
Main:
    Create a Netlink socket.
    - If socket creation failed, terminate the program.

    Bind the socket.
    - If binding failed, terminate the program.

    Start the kernel data receiver thread.

    Display Main Menu loop:
        1. Greet Kernel
        2. Exit

        - If 1:
            Read user message from stdin.
            Send the message to the kernel.
        
        - If 2:
            Close the socket.
            Exit the program.

Functions:
    create_netlink_socket() : 
        Creates a netlink socket using socket() system call.

    send_netlink_msg_to_kernel() : 
        Sends a netlink message to the kernel. Constructs the netlink header, wraps the message in iovec, and sends the message using sendmsg().

    greet_kernel() : 
        Invokes send_netlink_msg_to_kernel() to send a greeting message to the kernel.

    exit_userspace() :
        Closes the socket.

    new_seq_no() :
        Generates a new sequence number.

    start_kernel_data_receiver_thread() :
        Initiates a thread to receive data from the kernel.

    _start_kernel_data_receiver_thread() :
        Infinite loop that waits for and receives messages from the kernel. 
        Once a message is received, it prints it.
```
---


## Interview Questions (with Answers) 🤔💬

### Q1: What is the role of Netlink sockets in Linux?
**Answer**: Netlink sockets provide a communication mechanism between the kernel and userspace applications. It's primarily used for transferring information between kernel and user space, or between different user-space processes.

### Q2: How is a Netlink message sent to the kernel from a user-space application?
**Answer**: A Netlink message is sent using the `sendmsg()` function. Before sending, the message is constructed with a proper Netlink header (`nlmsghdr`) and payload. The `send_netlink_msg_to_kernel()` function in the provided code demonstrates this process.

### Q3: How does the userspace application asynchronously receive messages from the kernel?
**Answer**: The application initializes a dedicated thread using the `start_kernel_data_receiver_thread()` function. This thread continuously waits for messages from the kernel using the `recvmsg()` function.

### Q4: Why is the `bind()` function used in this code, and what's its significance in the context of Netlink sockets?
**Answer**: The `bind()` function is used to bind a socket to a specific address and protocol. In the context of Netlink sockets, binding informs the kernel about the application's interest in receiving messages for a specific Netlink protocol. It's a way of registering the application's intent to communicate over a particular Netlink protocol.

### Q5: What is the significance of the `nl_pid` field in the `sockaddr_nl` structure?
**Answer**: The `nl_pid` field represents the process ID (PID) of the sending or receiving process in the context of Netlink sockets. For messages intended for the kernel, this field is set to 0. When a userspace application sets its `nl_pid` to its own PID, it's informing the kernel about its identity.

### Q1: In the `send_netlink_msg_to_kernel()` function, what are the specific roles of the `NLMSG_SPACE` and `NLMSG_DATA` macros?
**Answer**: 
- `NLMSG_SPACE`: This macro calculates the total size required for a Netlink message based on the payload size. It includes the size of the message header (`nlmsghdr`) and any padding needed to align the message to the boundary.
  
- `NLMSG_DATA`: Given a pointer to a Netlink message header (`nlmsghdr`), this macro returns a pointer to the actual payload/data of the message. It's essentially a way to skip past the header and access the data directly.

### Q2: How does the program handle potential errors during socket creation or message sending?
**Answer**: The code contains multiple error-checking routines. For instance, after trying to create a socket, the returned socket descriptor is checked against `-1` to see if there were any errors. Similarly, the result of the `sendmsg()` function call is checked to ensure the message was sent successfully. If errors occur, appropriate error messages are printed.

### Q3: How can the program ensure that the message received is actually the expected type and not some other kind of Netlink message?
**Answer**: By examining the `nlmsg_type` field in the received message's header (`nlmsghdr`). This field indicates the type of the received message. The application can validate this type against the expected value to confirm it's processing the correct message.

### Q4: What modifications would be required in the code if we wanted to add another option in the main menu, for instance, to send a different type of message to the kernel?
**Answer**: 
1. Update the `main()` function to include an additional option in the printed menu.
2. Add another conditional branch (`if` or `switch` case) to handle the user's input for the new option.
3. Implement a new function similar to `send_netlink_msg_to_kernel()` that forms and sends the new message type.
4. Adjust any necessary error checks or handling mechanisms related to this new message.

### Q5: In the context of the code, how does the program differentiate between messages from different userspace processes when receiving them in the kernel space?
**Answer**: The differentiation is achieved using the `nl_pid` field in the `sockaddr_nl` structure. When binding a Netlink socket, userspace processes specify their own process ID (PID) in the `nl_pid` field. This allows the kernel to uniquely identify and communicate with specific userspace processes based on their PIDs.

### Q6: Why is it beneficial to have a separate thread for receiving kernel messages, as implemented in the provided code?
**Answer**: Having a separate thread for receiving kernel messages ensures asynchronous communication. This way, the main thread can continue handling user interactions or performing other tasks without being blocked by the message reception process. This design allows for a more responsive and efficient application, especially when waiting for messages from the kernel that might not arrive on a predictable schedule.

---

# Socket & Thread API Revision 🚀

## Table of Contents
- [Socket APIs](#socket-apis)
- [Thread APIs](#thread-apis)
- [Interview Questions](#interview-questions)

## Socket APIs 🧦

### 1. `socket()`
- **Purpose**: Create a new socket.
  - **`domain`**: Communication domain (e.g., `AF_NETLINK` for Netlink sockets).
  - **`type`**: Socket type (e.g., `SOCK_RAW` for raw network protocol access).
  - **`protocol`**: Specific protocol (e.g., `NETLINK_USERSOCK` for user-kernel communication).

### 2. `bind()`
- **Purpose**: Bind a socket to a specific address.
  - **`sockfd`**: Socket file descriptor.
  - **`addr`**: Pointer to address structure (e.g., `struct sockaddr_nl`).
  - **`addrlen`**: Size of the address structure.

### 3. `sendmsg()`
- **Purpose**: Send a message on a socket.
  - **`sockfd`**: Socket file descriptor.
  - **`msg`**: Pointer to message structure (`msghdr`).
  - **`flags`**: Flags for sending (typically 0).

### 4. `recvmsg()`
- **Purpose**: Receive a message from a socket.
  - **`sockfd`**: Socket file descriptor.
  - **`msg`**: Pointer to a message structure where the received message details will be stored.
  - **`flags`**: Flags for receiving (typically 0).

### 5. `close()`
- **Purpose**: Close a file descriptor.
  - **`fd`**: File descriptor.

## Thread APIs 🧵

### 1. `pthread_create()`
- **Purpose**: Create a new thread.
  - **`thread`**: Pointer to variable for thread ID.
  - **`attr`**: Thread attributes (or NULL).
  - **`start_routine`**: Function pointer for thread execution.
  - **`arg`**: Argument pointer for the function.

### 2. `pthread_join()`
- **Purpose**: Wait for the thread to terminate.
  - **`thread`**: Thread ID.
  - **`retval`**: Pointer for exit status of the thread.

### 3. `pthread_exit()`
- **Purpose**: Exit from a thread.
  - **`retval`**: Return value pointer.

## Interview Questions ❓

**Q1**: What is the primary use of the `NETLINK_USERSOCK` protocol in the socket API?  
**A1**: The `NETLINK_USERSOCK` protocol is used to allow user-space applications to communicate with the kernel via Netlink sockets.

**Q2**: Why would one use `SOCK_RAW` in the socket creation?  
**A2**: `SOCK_RAW` provides raw network protocol access. This means the application is responsible for providing the transport protocol header, allowing more control over the data being sent.

**Q3**: How can you ensure a thread has completed its execution?  
**A3**: We use `pthread_join()`. It waits for the specified thread to terminate, ensuring the thread has completed its execution.

**Q4**: What would be a potential reason to bind a socket to a specific address using `bind()`?  
**A4**: Binding a socket to a specific address ensures that the socket receives data intended for that address. It's essential for servers that need to listen on specific ports or addresses.

**Q5**: What’s the difference between `pthread_exit()` and simply returning from the thread's start routine?  
**A5**: `pthread_exit()` immediately terminates the thread, and the return value can be collected by another thread using `pthread_join()`. Returning from the start routine also terminates the thread but can potentially deallocate some resources before the `pthread_join()` is called.
---

## Custom API Logic Explanation 🛠

### `call_netlink()`

#### Purpose:
This function serves to communicate with the kernel space using Netlink sockets from the user space.

#### Logic Breakdown:

1. **Socket Creation**:
    - `socket(AF_NETLINK, SOCK_RAW, NETLINK_USERSOCK)`:
      - **`AF_NETLINK`**: Address family for Netlink sockets.
      - **`SOCK_RAW`**: Socket type providing raw network protocol access.
      - **`NETLINK_USERSOCK`**: Protocol for user-kernel communication.

    After socket creation, the program checks if the socket descriptor is valid.

2. **Binding**:
    - `bind(sock_fd, (struct sockaddr*)&src_addr, sizeof(src_addr))`:
      This binds the socket to the source address specified.

3. **Message Initialization**:
    - The program constructs the Netlink message using a header (`nlh`) and the provided message (`hello_str`). The header includes metadata about the message like its length, type, flags, etc.
    - The `iov` structure (scatter/gather array) is used to store the address and size of the message. This structure is useful for sending multiple non-contiguous blocks of data in one `sendmsg()` call.
    - The `msg` structure is filled with details about the message to be sent, including its destination address and the `iov`.

4. **Sending Message**:
    - The `sendmsg()` API is used to send the message to the kernel.
    - The program checks if the sending was successful.

5. **Receiving Message**:
    - The `recvmsg()` API waits for a message from the kernel. The received message's data will populate the `iov` and `msg` structures.
    - The program then extracts and prints the received message.

6. **Cleanup**:
    - The Netlink header memory is freed using `free(nlh)`.
    - The socket is closed using the `close()` function.

This function essentially establishes a Netlink socket, binds to it, sends a message to the kernel, waits for a reply, and then cleans up resources.

---
## Custom API Logic Explanation 🛠

### `send_netlink_msg_to_kernel()`

#### Purpose:
This function sends a message to the kernel over the Netlink protocol.

#### Logic:
1. **Destination Address Initialization**: This API constructs a `sockaddr_nl` structure named `dest_addr` representing the address for the Linux kernel. Since the kernel's process ID is always zero, `nl_pid` is set to `0`.
2. **Netlink Message Header Initialization**: It dynamically allocates memory to construct a Netlink message. This message consists of a header (`nlh`) and the actual payload (`msg`).
3. **Filling the Header**: The header fields are filled with metadata like message length, the process ID (PID) of the sender, message type, flags, and a sequence number.
4. **Filling the Payload**: The actual message content (`msg`) is copied to the payload space of the Netlink message.
5. **Wrapping Data Inside iovec**: An `iovec` structure (`iov`) wraps the Netlink message. This allows a scatter/gather array approach for sending possibly non-contiguous blocks of data.
6. **Message Sending**: A `msghdr` structure (`outermsghdr`) wraps the `iovec` and is filled with details about the message, such as the destination address and the iovec itself. The `sendmsg()` function is then used to send this message.
7. **Error Checking**: The function checks if the message was successfully sent.

### `create_netlink_socket()`

#### Purpose:
Creates a socket to communicate over the Netlink protocol.

#### Logic:
1. **Socket Creation**: Uses the `socket()` function to create a socket that operates using the Netlink protocol. The socket type used is `SOCK_RAW`.

### `_start_kernel_data_receiver_thread()`

#### Purpose:
This function acts as a thread handler. It continuously receives messages from the kernel using Netlink sockets.

#### Logic:
1. **Initialization**: Memory is allocated to hold incoming Netlink messages.
2. **Reception Loop**: 
    - The loop continuously waits for a message from the kernel using the `recvmsg()` function.
    - Once a message is received, it's parsed and the payload (message from the kernel) is printed.

### `start_kernel_data_receiver_thread()`

#### Purpose:
Starts a new thread that listens for incoming messages from the kernel.

#### Logic:
1. **Thread Initialization**: Initializes thread attributes and sets it to a detached state.
2. **Thread Creation**: The `_start_kernel_data_receiver_thread` function is set as the thread handler. The `pthread_create` function is used to start this new thread.

### `greet_kernel()`

#### Purpose:
Sends a greeting message to the kernel.

#### Logic:
1. **Message Sending**: Uses the `send_netlink_msg_to_kernel()` function with a specific message type (`NLMSG_GREET`) to send the greeting message.

### `exit_userspace()`

#### Purpose:
Cleans up resources before exiting the user-space application.

#### Logic:
1. **Socket Closure**: The Netlink socket descriptor is closed.

### `new_seq_no()`

#### Purpose:
Generates a new sequence number for Netlink messages.

#### Logic:
1. **Sequence Generation**: Uses a static variable (`seq_no`) that gets incremented with every call.

---
# Netlink Sockets: User Space Application Guide 🚀

Netlink socket is a special IPC (Inter-Process Communication) used for communication between the kernel and user-space processes or between different user-space processes. The provided code demonstrates how a user-space application communicates with a kernel module using Netlink sockets.

## Key Concepts 💡

### 1. Creating a Netlink Socket

```c
int sock_fd = socket(PF_NETLINK, SOCK_RAW, protocol_number);
```
Here:
- `PF_NETLINK` specifies the protocol family for Netlink.
- `SOCK_RAW` denotes raw communication between the application and the kernel.
- `protocol_number` is a unique identifier for your communication purpose.

🔍 **Interview Question**: Why would you use `SOCK_RAW` and not `SOCK_DGRAM` for Netlink communication?
**Answer**: When `SOCK_RAW` is used, the application has to prepare the `msghdr` structure and send the message using `sendmsg()`. In contrast, when `SOCK_DGRAM` is used, the socket layer will handle the `msghdr` for you, and you'd use `sendto()`. In this demonstration, we're showcasing the more detailed `SOCK_RAW` approach.

### 2. Sending Messages to Kernel

This involves constructing a Netlink message with a header (`nlmsghdr`) followed by the actual message payload. The message is then sent to the kernel using `sendmsg()`.

### 3. Receiving Messages from Kernel

The code employs a separate thread to listen for incoming messages from the kernel. `recvmsg()` is used, which is a blocking system call, suspending the application until a message is received.

## Breakdown of Functions 🛠

### 1. `send_netlink_msg_to_kernel(...)`

This function sends a message to the kernel via Netlink. It involves:
- Constructing the destination address.
- Preparing the Netlink message header and payload.
- Sending the message using `sendmsg()`.

### 2. `create_netlink_socket(...)`

Creates and returns a Netlink socket descriptor.

### 3. `_start_kernel_data_receiver_thread(...)`

This function represents a separate thread that waits for and receives messages from the kernel.

### 4. `start_kernel_data_receiver_thread(...)`

Spawns the thread responsible for receiving messages from the kernel.

### 5. `greet_kernel(...)`

A simple function to send a greeting message to the kernel.

### 6. `exit_userspace(...)`

Cleans up by closing the Netlink socket.

## Main Workflow 🔄

1. Create the Netlink socket.
2. Bind the socket.
3. Start the kernel data receiver thread.
4. Present a menu to the user allowing them to send greetings to the kernel or exit the program.

🔍 **Interview Question**: How is the sequence number (`nlmsg_seq`) managed in this code when sending messages?
**Answer**: The code uses a static function `new_seq_no()` that keeps a static counter (`seq_no`). Each time a new sequence number is required, this counter is incremented and returned.

🔍 **Interview Question**: Why do we use a separate thread for receiving messages from the kernel?
**Answer**: By using a separate thread, the main program can continue its normal operation (like displaying the menu to the user) without being blocked. The receiving thread will independently handle messages as they arrive from the kernel.

---




