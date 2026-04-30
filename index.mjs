import { createRequire } from 'node:module';
const require = createRequire(import.meta.url);
const addon = require('./build/Release/reboot.node');
export const reboot = addon.reboot;
export const halt = addon.halt;
export default addon;
