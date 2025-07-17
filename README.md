# 💾 RFID RC522 Linux Driver for A5D2X

This repository contains a Linux kernel driver and integration steps for the **RC522 RFID module** on the **A5D2X (Rugged Board)** using the SPI interface. It includes both the driver source code and the instructions to patch, compile, and test it on a target board.

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
├── *.patch # Kernel patch files
├── Integration_rfid-rc522.pdf
├── rfid-rc522_Generating_patch.pdf
└── README.md # This documentation

yaml
Copy
Edit

---

## ⚙️ Hardware Requirements

- 📟 RC522 RFID Module (SPI)
- 💻 RB-A5D2X (Rugged Board)
- 🔌 Connected via mikroBUS (VCC, MISO, MOSI, SCK, CS, RST, GND)
- 🏷️ RFID Tags

---

## 🔧 Software Requirements

- 🐧 Linux kernel source for RB-A5D2X
- 🛠️ Yocto or similar toolchain setup
- 📦 Git, GCC, Device Tree tools
- 🧰 Cross-compilation environment (e.g. `poky-tiny`)

---

## 🚀 Driver Integration (Static Kernel Build)

### 📁 1. Copy Driver Files

Place files into `/drivers/misc/rfid_rc522/`:

├── rc522.c
├── rc522_api.c
├── rc522_api.h
├── Kconfig
└── Makefile

---

### 🛠️ 2. Modify Kernel `Kconfig` & `Makefile`

Edit `drivers/misc/Kconfig`:

```c
source "drivers/misc/rfid_rc522/Kconfig"
Edit drivers/misc/Makefile:


obj-y += rfid_rc522/
🌲 3. Update Device Tree
Modify a5d2x-rugged_board_common.dtsi to include SPI node and pinctrl.

🏗️ 4. Recompile Kernel

source /opt/poky-tiny/2.5.2/environment-setup-cortexa5hf-neon-poky-linux-musleabi
make distclean
make rb_a5d2x_defconfig
make menuconfig   # Enable RFID_RC522
make
💾 5. Copy to SD Card
Replace zImage and .dtb files in the boot partition.

🧪 Driver Testing
🔍 Check Device Node

ls /dev/rfid_rc522_dev
🧰 Build & Send Test App

${CC} rfid_rc522_dev.c -o rfid_rc522_dev
scp rfid_rc522_dev root@<board-ip>:/home/root
▶️ Run on Target

chmod +x rfid_rc522_dev
./rfid_rc522_dev
🧵 Patch Generation (Optional)
To create a patch:

git add drivers/misc/rfid_rc522/
git commit -m "Add RC522 RFID driver"
git format-patch -p1 -o patches/
To apply the patch:


git am 0001-rfid-rc522_driver.patch
📄 Documentation
📘 Integration_rfid-rc522.pdf – Full hardware & software integration guide

📘 rfid-rc522_Generating_patch.pdf – Patch generation steps

👨‍💻 Developed By
Venkatesh M
📧 venkatesh.muninagaraju@essae.com
👨‍💼 Embedded Systems Engineer


