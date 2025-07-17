🛠️ RFID RC522 Linux Driver for A5D2X
This repository contains a Linux kernel driver and integration steps for the RC522 RFID module on the A5D2X (Rugged Board) using the SPI interface. It includes both the driver source code and the instructions to patch, compile, and test it on a target board.

📂 Project Structure
bash
Copy
Edit
rfid-rc522-linux-driver/
├── rfid_rc522/                  # Kernel driver source folder
│   ├── rc522.c
│   ├── rc522_api.c
│   ├── rc522_api.h
│   ├── Makefile
│   └── Kconfig
├── rfid_rc522_dev.c            # User-space test application
├── driver-readme               # Developer notes
├── *.patch                     # Kernel patch files
├── Integration_rfid-rc522.pdf  # Driver integration guide
├── rfid-rc522_Generating_patch.pdf # Patch generation guide
⚙️ Hardware Requirements
RC522 RFID Module (SPI)

RB-A5D2X (Rugged Board)

SPI-connected via mikroBUS (VCC, MISO, MOSI, SCK, CS, RST, GND)

RFID Tags

🔧 Software Requirements
Linux kernel source for RB-A5D2X

Yocto or similar toolchain setup

Git, GCC, Device Tree tools

Cross-compilation environment (e.g., poky-tiny)

🚀 Driver Integration (Kernel Static Build)
Copy driver files into kernel:

swift
Copy
Edit
/drivers/misc/rfid_rc522/
    ├── rc522.c
    ├── rc522_api.c
    ├── rc522_api.h
    ├── Kconfig
    └── Makefile
Modify kernel Kconfig & Makefile:

In drivers/misc/Kconfig, add:

c
Copy
Edit
source "drivers/misc/rfid_rc522/Kconfig"
In drivers/misc/Makefile, add:

make
Copy
Edit
obj-y += rfid_rc522/
Update device tree:
Edit arch/arm/boot/dts/a5d2x-rugged_board_common.dtsi
Add SPI node for RC522 with pinctrl settings.

Recompile kernel:

bash
Copy
Edit
source /opt/poky-tiny/2.5.2/environment-setup-cortexa5hf-neon-poky-linux-musleabi
make distclean && make rb_a5d2x_defconfig
make menuconfig  # Enable RFID_RC522 driver
make
Copy zImage and .dtb files to SD card’s boot partition.

🧪 Testing the Driver
Boot the board.

Check if device exists:

bash
Copy
Edit
ls /dev/rfid_rc522_dev
Build and copy test app:

bash
Copy
Edit
${CC} rfid_rc522_dev.c -o rfid_rc522_dev
scp rfid_rc522_dev root@<board-ip>:/home/root
On the board:

bash
Copy
Edit
chmod +x rfid_rc522_dev
./rfid_rc522_dev
🧵 Patch Generation (Optional)
If you're integrating into an upstream kernel:

bash
Copy
Edit
git add drivers/misc/rfid_rc522/
git commit -m "Add RC522 RFID driver"
git format-patch -p1 -o patches/
Apply the patch later using:

bash
Copy
Edit
git am 0001-rfid-rc522_driver.patch
📄 Documentation
Integration_rfid-rc522.pdf — Integration and wiring guide

rfid-rc522_Generating_patch.pdf — Patch creation and management

👨‍💻 Developed By
Venkatesh M
📧 venkatesh.muninagaraju@essae.com
👨‍💼 Embedded Systems Engineer

