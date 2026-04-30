declare const addon: {
  reboot(): void;
  rebootImmediately(): void;
  halt(): void;
  haltImmediately(): void;
};

export const reboot: typeof addon.reboot;
export const rebootImmediately: typeof addon.rebootImmediately;
export const halt: typeof addon.halt;
export const haltImmediately: typeof addon.haltImmediately;

export default addon;
