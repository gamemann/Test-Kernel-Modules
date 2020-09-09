# Kernel Test Modules
## Description
A repository I'm using to release test kernel modules I make. I am getting into kernel module development due to interest in the Linux kernel in general and also because [Bifrost](https://github.com/BifrostTeam), an upcoming firewall my friend and I are working on, will be releasing a kernel module for packet processing.

## Testing
To load a module, simply use `make` to build the modules and then the following command:

```
insmod $NAME
```

Where `$NAME` is the kernel's name you want loaded (e.g. `kern.ko`). Similarly, you can unload the module with the following command:

```
rmmod $NAME
```

From here, you may check if the module is loaded by doing:

```
lsmod | grep "$NAME"
```

Make sure to remove the file extension at the end of `$NAME` when using `lsmod`.