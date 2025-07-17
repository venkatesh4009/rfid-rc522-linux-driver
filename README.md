# 💾 RFID RC522 Linux Driver for A5D2X

This repository contains a Linux kernel driver and integration steps for the **RC522 RFID module** on the **A5D2X (Rugged Board)** using the SPI interface. It includes both the driver source code and instructions to patch, compile, and test it on a target board.

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
├── Integration_rfid-rc522.pdf # Driver integration guide
├── rfid-rc522_Generating_patch.pdf # Patch generation guide


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
- 🧰 Cross-compilation environment (e.g., `poky-tiny`)

---

## 🚀 Driver Integration (Kernel Static Build)

### 📁 Step 1: Copy Driver Files

Copy the driver source files into the kernel:

Place into: /drivers/misc/rfid_rc522/
├── rc522.c
├── rc522_api.c
├── rc522_api.h
├── Kconfig
└── Makefile



---

### 🛠️ Step 2: Modify Kernel `Kconfig` & `Makefile`

Edit `drivers/misc/Kconfig`:

```c
source "drivers/misc/rfid_rc522/Kconfig"
Edit drivers/misc/Makefile:


obj-y += rfid_rc522/
🌲 Step 3: Update the Device Tree
Modify the following file:


arch/arm/boot/dts/a5d2x-rugged_board_common.dtsi
Add the SPI node and pinctrl for RC522. Refer to 0001-Rb-a5d2x.dtsi.patch for details.

🏗️ Step 4: Recompile Kernel

source /opt/poky-tiny/2.5.2/environment-setup-cortexa5hf-neon-poky-linux-musleabi

make distclean
make rb_a5d2x_defconfig
make menuconfig     # Enable RFID_RC522 driver
make

💾 Step 5: Copy Artifacts to SD Card
Copy the generated files to your board’s boot partition:

zImage

*.dtb

🧪 Driver Testing Steps
🔍 1. Boot the Board & Verify

ls /dev/rfid_rc522_dev
You should see /dev/rfid_rc522_dev if the driver loaded successfully.

🧰 2. Compile & Send Test Application
On host:


${CC} rfid_rc522_dev.c -o rfid_rc522_dev
scp rfid_rc522_dev root@<board-ip>:/home/root
▶️ 3. Run Test App on Board

chmod +x rfid_rc522_dev
./rfid_rc522_dev
🧵 Patch Generation (Optional)
To create patch:

git add drivers/misc/rfid_rc522/
git commit -m "Add RC522 RFID driver"
git format-patch -p1 -o patches/
To apply patch:


git am 0001-rfid-rc522_driver.patch
📄 Documentation
📘 Integration_rfid-rc522.pdf — Full hardware & software integration guide

📘 rfid-rc522_Generating_patch.pdf — Patch creation steps

👨‍💻 Developed By
Venkatesh M
📧 venkatesh.muninagaraju@essae.com
🛠️ Embedded Systems Engineer

