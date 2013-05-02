# node-reboot

Reboot Linux kernel immediately from node without calling `/sbin/shutdown` or going thru initscripts. 

## Why? 

I'm running a cluster of Linux servers which boot readonly and perform a memory-intensive computations. node-reboot is a part of a watchdog application, which in case of emergencies much reboot the server immediately without `fork()`ing another process or going thru upstart/initscripts.

## Synopsis

Call `sync()` and then reboot: 

```javascript
require('reboot').reboot();
```

Reboot without `sync()`ing: 

```javascript
require('reboot').rebootImmediately();
```

The function should never return. If it does, it means node has insufficient permissions. 

## Permissions

If you are to run node process under non-superuser, be sure to give node permissions to reboot the system: 

```
sudo setcap CAP_SYS_BOOT=+ep /usr/local/bin/node
```

See `man capabilities` for details.


## Installation

```
npm install reboot
```

or

```
npm install .
```


## License

See LICENSE file. Basically, it's a kind of "do-whatever-you-want-for-free" license.


