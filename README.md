# 🛠️ RFID RC522 Linux Driver for A5D2X

This repository contains a Linux kernel driver and integration steps for the **RC522 RFID module** on the **A5D2X (Rugged Board)** using the SPI interface. It includes the driver source code and instructions to patch, compile, and test on a target board.

---

## 📂 Project Structure

rfid-rc522-linux-driver/
├── rfid_rc522/ # Kernel driver source folder
│ ├── rc522.c
│ ├── rc522_api.c
│ ├── rc522_api.h
│ ├── Makefile
│ └── Kconfig
├── rfid_rc522_dev.c # User-space test application
├── driver-readme # Developer notes
├── 0001-*.patch # Kernel patch files
├── Integration_rfid-rc522.pdf # Driver integration guide
├── rfid-rc522_Generating_patch.pdf # Patch generation guide

yaml
Copy
Edit

---

## ⚙️ Hardware Requirements

- RC522 RFID Module (SPI)
- RB-A5D2X (Rugged Board)
- SPI via mikroBUS (VCC, MISO, MOSI, SCK, CS, RST, GND)
- RFID Tags

---

## 🔧 Software Requirements

- Linux kernel source for RB-A5D2X
- Yocto or similar toolchain
- Git, GCC, Device Tree tools
- Cross-compilation environment (e.g., poky-tiny)

---

## 🚀 Driver Integration (Static Kernel Build)

### 1. Copy files to kernel:

/drivers/misc/rfid_rc522/
├── rc522.c
├── rc522_api.c
├── rc522_api.h
├── Kconfig
└── Makefile

bash
Copy
Edit

### 2. Modify Kconfig and Makefile

**Edit `drivers/misc/Kconfig`:**

```c
source "drivers/misc/rfid_rc522/Kconfig"
Edit drivers/misc/Makefile:

make
Copy
Edit
obj-y += rfid_rc522/
3. Device Tree Edit
Modify: arch/arm/boot/dts/a5d2x-rugged_board_common.dtsi
Add RC522 SPI node with correct pinctrl.

4. Kernel Build Steps
bash
Copy
Edit
source /opt/poky-tiny/2.5.2/environment-setup-cortexa5hf-neon-poky-linux-musleabi
make distclean
make rb_a5d2x_defconfig
make menuconfig   # Enable RFID_RC522
make
Copy zImage and .dtb files to SD card boot partition.

🧪 Testing the Driver
Boot the board

Check if device exists:

bash
Copy
Edit
ls /dev/rfid_rc522_dev
Build user app:

bash
Copy
Edit
${CC} rfid_rc522_dev.c -o rfid_rc522_dev
Copy to board:

bash
Copy
Edit
scp rfid_rc522_dev root@<BOARD_IP>:/home/root
On board:

bash
Copy
Edit
chmod +x rfid_rc522_dev
./rfid_rc522_dev
🧵 Patch Generation (Optional)
bash
Copy
Edit
git add drivers/misc/rfid_rc522/
git commit -m "Add RC522 driver"
git format-patch -p1 -o patches/
Apply patch:

bash
Copy
Edit
git am 0001-rfid-rc522_driver.patch
📄 Documentation
📘 Integration_rfid-rc522.pdf – Full driver integration guide

🧾 rfid-rc522_Generating_patch.pdf – Patch generation steps

👨‍💻 Developed By
Venkatesh M
📧 venkatesh.muninagaraju@essae.com
👨‍💼 Embedded System Engineer
