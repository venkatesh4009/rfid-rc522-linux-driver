# 💾 RFID RC522 Linux Driver for A5D2X

This repository contains a Linux kernel driver and integration guide for the **RC522 RFID module** on the **A5D2X (Rugged Board)** using SPI interface. It includes kernel driver source, device tree patching, and testing procedures.

---

## 📁 Project Structure

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
├── 0002-rfid-rc522_driver.patch # Kernel driver patch
├── Integration_rfid-rc522.pdf # Driver integration guide
├── rfid-rc522_Generating_patch.pdf # Patch generation guide

yaml
Copy
Edit

---

## ⚙️ Hardware Requirements

- 📟 RC522 RFID Module (SPI interface)
- 💻 RB-A5D2X (Rugged Board)
- 🔌 mikroBUS SPI interface (VCC, MISO, MOSI, SCK, CS, RST, GND)
- 🏷️ RFID Tags

---

## 🔧 Software Requirements

- 🐧 Linux kernel source for RB-A5D2X
- 🛠️ Yocto build environment
- 📦 GCC, Git, Device Tree tools
- 🧰 Cross-compiler toolchain (`poky-tiny`, etc.)

---

## 🚀 Integration Steps (Static Kernel Driver)

### ✅ Step 1: Copy Driver Files

Place the following files into your kernel source:

Destination: drivers/misc/rfid_rc522/
├── rc522.c
├── rc522_api.c
├── rc522_api.h
├── Kconfig
└── Makefile

yaml
Copy
Edit

---

### 🛠️ Step 2: Modify Kernel Build Files

Edit the following:

- `drivers/misc/Kconfig`  
  Add:
  ```c
  source "drivers/misc/rfid_rc522/Kconfig"
drivers/misc/Makefile
Add:

make
Copy
Edit
obj-y += rfid_rc522/
🌲 Step 3: Update Device Tree
Edit:
arch/arm/boot/dts/a5d2x-rugged_board_common.dtsi

Add the SPI node and pin configuration for the RC522.

➡️ Reference: 0001-Rb-a5d2x.dtsi.patch

🏗️ Step 4: Recompile the Kernel
bash
Copy
Edit
# Setup Yocto environment
source /opt/poky-tiny/2.5.2/environment-setup-cortexa5hf-neon-poky-linux-musleabi

# Clean and configure kernel
make distclean
make rb_a5d2x_defconfig
make menuconfig      # Enable "RFID_RC522" driver
make
💾 Step 5: Deploy to Target Board
Copy kernel artifacts to SD card:

zImage

<board>.dtb

Place these into the /boot partition on the target device.

🧪 Testing the Driver
🔍 1. Boot and Verify Device
bash
Copy
Edit
ls /dev/rfid_rc522_dev
If the driver loads, the device node will be created.

🧰 2. Build and Deploy Test Application
Compile on host:

bash
Copy
Edit
${CC} rfid_rc522_dev.c -o rfid_rc522_dev
Transfer to board:

bash
Copy
Edit
scp rfid_rc522_dev root@<board-ip>:/home/root
▶️ 3. Run Test Application
bash
Copy
Edit
chmod +x rfid_rc522_dev
./rfid_rc522_dev
🧵 Generating Kernel Patch (Optional)
To create a patch:


git add drivers/misc/rfid_rc522/
git commit -m "Add RC522 RFID driver"
git format-patch -p1 -o patches/
To apply the patch later:


git am 0001-rfid-rc522_driver.patch
📄 Documentation
📘 Integration_rfid-rc522.pdf – Complete driver integration steps

📘 rfid-rc522_Generating_patch.pdf – Patch creation guide

👨‍💻 Developed By
Venkatesh M
📧 venkatesh.m@phytecembadded.com
 Embedded Systems Engineer
