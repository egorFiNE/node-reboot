# node-reboot

Immediately reboot Linux/macOS with no systemd calling or fork()ing of `/sbin/shutdown`.

This module supports node v24+ (or maybe older) and bun 1.3+.

## Why?

I'm running a cluster of Linux servers which boot readonly and perform a memory-intensive computations.

node-reboot is a part of a watchdog application that has to reboot the server immediately in case a certain condition is detected. This condition prevents the operating system from shutting down gracefully and hard restart is needed.

## Install

```bash
npm install reboot
```

or

```bash
bun add reboot
```

## Synopsis

To `sync()` filesystems and then reboot:

```javascript
import { reboot } from 'reboot';
reboot();
```

Reboot without `sync()`ing filesystems:

```javascript
import { rebootImmediately } from 'reboot';
rebootImmediately();
```

The function should never return. If it does, it means node has insufficient permissions.

For a good measure this module also exports `halt()` and `haltImmediately()`.

## Permissions (Linux only)

If you are to run node/bun process under non-superuser, be sure to give node/bun permissions to reboot the system:

```
sudo setcap CAP_SYS_BOOT=+ep $(which node) # or bun
```

See `man capabilities` for details.


## Installation

```
npm install reboot
```
