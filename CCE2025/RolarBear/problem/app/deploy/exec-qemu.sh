#!/bin/bash

# 4MB
dd if=/dev/zero of=disk.img bs=512 count=8192 > /dev/null 2>&1

exec ./qemu-system-riscv64 \
    -L . \
    -machine virt \
    -m 2G \
    -nographic \
    -serial stdio \
    -monitor none \
    -bios default \
    -kernel prob \
    -drive if=none,format=raw,file=disk.img,id=disk0 \
    -global virtio-mmio.force-legacy=false \
    -device virtio-rng-device \
    -device virtio-blk-device,drive=disk0
