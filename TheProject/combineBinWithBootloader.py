# extra_script.py
import shutil
import os

def create_firmware_with_bootloader(source, target, env):
    build_dir = env.subst("$BUILD_DIR")
    firmware_bin = os.path.join(build_dir, "firmware.bin")
    bootloader_bin = os.path.join(build_dir, "bootloader.bin")
    combined_bin = os.path.join(build_dir, "firmwareWithBoot.bin")

    if not os.path.exists(firmware_bin):
        print("Error: firmware.bin not found!")
        return
    if not os.path.exists(bootloader_bin):
        print("Error: bootloader.bin not found!")
        return

    with open(combined_bin, "wb") as wfd:
        for f in [bootloader_bin, firmware_bin]:
            with open(f, "rb") as fd:
                shutil.copyfileobj(fd, wfd)

    print("Created firmwareWithBoot.bin:", combined_bin)

Import("env")
env.AddPostAction("$BUILD_DIR/firmware.bin", create_firmware_with_bootloader)
