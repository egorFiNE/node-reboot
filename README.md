# node-reboot

Immediately reboot or halt Linux/macOS from Node.js or Bun.

This package calls the operating-system reboot APIs directly. It does not call
systemd, shell out, or fork `/sbin/shutdown`.

## Runtimes supported

- Node.js v24+.
- Bun 1.3+.
- Linux and macOS.

Older Node.js versions may work as well.

## Why?

`node-reboot` is intended for watchdog-style applications that need to force an
immediate machine restart when graceful shutdown is not an option anymore.

For example, this package was built for a cluster of Linux servers that boot
read-only and run memory-intensive workloads. When a bad runtime condition is
detected, the watchdog needs to reboot the server immediately instead of asking
around nicely.

## Install

```bash
npm install reboot
```

or:

```bash
bun add reboot
```

## Usage

Sync filesystems, then reboot:

```javascript
import { reboot } from 'reboot';

reboot();
```

Reboot immediately without syncing filesystems:

```javascript
import { rebootImmediately } from 'reboot';

rebootImmediately(); // Hasta la vista baby
```

The function should not return. If it does return, the process probably does
not have permission to reboot the system.

The package also exports halt helpers:

```javascript
import { halt, haltImmediately } from 'reboot';

halt();
// or
haltImmediately();
```

## Permissions

On Linux, a non-root Node.js or Bun process needs the `CAP_SYS_BOOT` capability
to reboot the system:

```bash
sudo setcap CAP_SYS_BOOT=+ep "$(which node)" # or bun
```

See `man capabilities` for details.
