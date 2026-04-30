declare const addon: {
  reboot(skipSync: boolean): void;
  halt(skipSync: boolean): void;
};

export const reboot: typeof addon.reboot;
export const halt: typeof addon.halt;

export default addon;

// `rebootImmediately()` is not declared here because it is a remnant of v0.1.0
