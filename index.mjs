import { createRequire } from 'node:module';
import { dirname } from 'node:path';
import { fileURLToPath } from 'node:url';

const require = createRequire(import.meta.url);
const addon = require('node-gyp-build')(dirname(fileURLToPath(import.meta.url)));
export const reboot = addon.reboot;
export const rebootImmediately = addon.rebootImmediately;
export const halt = addon.halt;
export const haltImmediately = addon.haltImmediately;
export default addon;
