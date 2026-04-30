import { createRequire } from 'node:module';
import { dirname } from 'node:path';
import { fileURLToPath } from 'node:url';

const require = createRequire(import.meta.url);
const addon = require('node-gyp-build')(dirname(fileURLToPath(import.meta.url)));

export const reboot = addon.reboot;
export const halt = addon.halt;

// Legacy signature from 0.1.0
export const rebootImmediately = () => addon.reboot(true);

export default {
  reboot,
  halt,
  rebootImmediately
};
