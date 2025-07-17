# 💾 RFID RC522 Linux Driver for A5D2X

This repository contains a Linux kernel driver and integration steps for the RC522 RFID module on the A5D2X (Rugged Board) using the SPI interface. It includes both the driver source code and the instructions to patch, compile, and test it on a target board.

---

## 📦 Project Structure

rfid-rc522-linux-driver/
├── rfid_rc522/ # Kernel driver source folder
│ ├── rc522.c
│ ├── rc522_api.c
│ ├── rc522_api.h
│ ├── Makefile
│ └── Kconfig
├── rfid_rc522_dev.c # User-space test application
├── driver-readme # Developer notes
├── 0001-Rb-a5d2x.dtsi.patch # Device tree patch
├── 0002-rfid-rc522_driver.patch # Driver patch
├── Integration_rfid-rc522.pdf # Driver integration guide
├── rfid-rc522_Generating_patch.pdf # Patch generation guide

yaml
Copy
Edit

---

## ⚙️ Hardware Requirements

- 📟 RC522 RFID Module (SPI)
- 💻 RB-A5D2X (Rugged Board)
- 🔌 SPI-connected via mikroBUS (VCC, MISO, MOSI, SCK, CS, RST, GND)
- 🏷️ RFID Tags

---

## 🔧 Software Requirements

- 🐧 Linux kernel source for RB-A5D2X
- 🛠️ Yocto or similar toolchain setup
- 📦 Git, GCC, Device Tree tools
- 🧰 Cross-compilation environment (e.g. poky-tiny)

---

## 🚀 Driver Integration (Kernel Static Build)

### 📁 1. Copy driver files into kernel

Place files into `/drivers/misc/rfid_rc522/`:

├── rc522.c
├── rc522_api.c
├── rc522_api.h
├── Kconfig
└── Makefile

yaml
Copy
Edit

---

### 🛠️ 2. Modify kernel Kconfig & Makefile

In `drivers/misc/Kconfig`:

```c
source "drivers/misc/rfid_rc522/Kconfig"
In drivers/misc/Makefile:

make
Copy
Edit
obj-y += rfid_rc522/
🌲 3. Update device tree
Edit a5d2x-rugged_board_common.dtsi to include SPI node and pinctrl for RC522.

🏗️ 4. Recompile kernel
bash
Copy
Edit
source /opt/poky-tiny/2.5.2/environment-setup-cortexa5hf-neon-poky-linux-musleabi
make distclean
make rb_a5d2x_defconfig
make menuconfig   # Enable RFID_RC522
make
💾 5. Copy artifacts to SD card
Replace zImage and .dtb files in the boot partition with the newly built versions.

🧪 Testing the Driver
🔍 1. Boot the board and check for device
bash
Copy
Edit
ls /dev/rfid_rc522_dev
🧰 2. Compile & send test app
bash
Copy
Edit
${CC} rfid_rc522_dev.c -o rfid_rc522_dev
scp rfid_rc522_dev root@<board-ip>:/home/root
▶️ 3. Run on board
bash
Copy
Edit
chmod +x rfid_rc522_dev
./rfid_rc522_dev
🧵 Patch Generation (Optional)
To create patches:

bash
Copy
Edit
git add drivers/misc/rfid_rc522/
git commit -m "Add RC522 RFID driver"
git format-patch -p1 -o patches/
To apply patch later:

bash
Copy
Edit
git am 0001-rfid-rc522_driver.patch
📄 Documentation
📘 Integration_rfid-rc522.pdf — Full hardware & software integration guide

📘 rfid-rc522_Generating_patch.pdf — Kernel patch generation steps

👨‍💻 Developed By
Venkatesh M
📧 venkatesh.muninagaraju@essae.com
👨‍💼 Embedded Systems Engineer

yaml
Copy
Edit
