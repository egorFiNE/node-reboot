## Prebuild on Intel macOS

Intel node should be first in path, otherwise npx will pick up the default node, which is arm64 one:

```bash
arch -x86_64 /bin/bash
export PATH=~/Downloads/node-v24.15.0-darwin-x64/bin/:$PATH
cd /some/where/node-reboot
npx prebuildify --napi --strip
```

## Make prebuilds

Run github action, download two prebuilt files. Then:

```bash
cd /some/where/node-reboot
unzip ~/Downloads/prebuilds-linux-x64.zip
unzip ~/Downloads/prebuilds-linux-arm64.zip
tar xvf prebuilds-linux-x64.tgz
tar xvf prebuilds-linux-arm64.tgz
```

## Pack

```bash
npm pack --pack-destination dist
```
