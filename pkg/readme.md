# Greetings Netlink Kernel Module 🚀

This project consists of a Linux kernel module, `greetNetlinkLKM.c`, which interacts with a user-space application, `userspace.c`, via the Netlink socket. Netlink socket provides a communication mechanism between the kernel and user-space processes.

## Table of Contents 📚

- [Installation](#installation)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)
- [Contributing](#contributing)
- [License](#license)

## Installation 📦

1. **Prerequisites**: Ensure you have kernel headers installed for your running kernel. On Fedora:

   ```bash
   sudo dnf install kernel-devel
   ```

2. **Compile the Kernel Module**:

   Navigate to the project directory and run:

   ```bash
   make
   ```

   This will compile the kernel module using the provided `Makefile`.

3. **Compile the User-space Application**:

```bash
gcc userspace.c -o userspace -lpthread
```

## Usage 🚀

1. **Insert the Kernel Module**:

   ```bash
   sudo insmod greetNetlinkLKM.ko
   ```

2. **Run the User-space Application**:

   ```bash
   ./userspace
   ```

   If everything is set up correctly, you should see the communication between the kernel module and the user-space application.

3. **Remove the Kernel Module**:

   Once done, you can remove the kernel module using:

   ```bash
   sudo rmmod greetNetlinkLKM
   ```

## Troubleshooting 🔧

If you encounter the error `Netlink socket creation failed: error = 93`, it may indicate a problem with the Netlink configuration or an issue in the kernel/user-space interaction. 

- Ensure the Netlink configuration in both `greetNetlinkLKM.c` and `userspace.c` matches.
- Check kernel logs for more details. On Fedora:

```bash

 journalctl -k -f

```

## Contributing 🤝

Feel free to fork, create a feature branch, and submit a pull request if you wish to contribute to this project!

## License ⚖️

This project is open-source.
