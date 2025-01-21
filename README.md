# operating_system

The operating system kernel will be a hybrid design, moving much of the code outside of supervisor mode. Only the scheduler, memory manager, and IO port and MMIO access will be in the kernel. The VFS, init system, and device drivers will be implemented as servers or modules that run in user mode.

All parts of the kernel will be preemptible except the scheduler. The scheduler will have a priority queue to keep track of processes. Each process will get a chance to execute in each cycle, but some processes will get multiple chances each cycle. A process will give up its time when it accesses a system call. If a process uses up its time it will be preempted and another process will get time.

The virtual file system will be based on disks, which will be numbered 0-255. Disk 0 is the boot disk and the one that the system is mounted on. Special virtual files are mounted on disk 0. For example, the standard input and output are 0:/devices/stdin and 0:/devices/stdout. The disk devices are accessible as raw files with 0:/devices/d0 to 0:/devices/d255.

In the bootup sequence, the UEFI loads BOOTX64.EFI, which is the kernel binary. This then loads a file called INIT.CFG, which is a text config file listing the startup disk and startup options. The kernel then loads important kernel services, like the VFS module, from the startup disk. These files should be in 0:/system. One of these, 0:/system/init.sys, is the init system. The init system loads the userspace and runs config scripts located in 0:/system/initcfg. For example, the system shell is loaded.