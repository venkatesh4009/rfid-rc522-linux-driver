# 🛠️ RFID RC522 Linux Driver for A5D2X

This repository contains a Linux kernel driver and integration steps for the **RC522 RFID module** on the **A5D2X (Rugged Board)** using the SPI interface. It includes the driver source code and instructions to patch, compile, and test on the target board.

---

## 📂 Project Structure

rfid-rc522-linux-driver/
├── rfid_rc522/ # Kernel driver source
│ ├── rc522.c
│ ├── rc522_api.c
│ ├── rc522_api.h
│ ├── Makefile
│ └── Kconfig
├── rfid_rc522_dev.c # User-space test application
├── driver-readme # Developer notes
├── 0001-Rb-a5d2x.dtsi.patch # Device tree patch
├── 0002-rfid-rc522_driver.patch # Driver source patch
├── Integration_rfid-rc522.pdf # Integration guide (PDF)
├── rfid-rc522_Generating_patch.pdf # Patch generation (PDF)

yaml
Copy
Edit

---

## ⚙️ Hardware Requirements

- RC522 RFID Module (SPI interface)
- RB-A5D2X Rugged Board
- SPI connection via mikroBUS (VCC, MISO, MOSI, SCK, CS, RST, GND)
- RFID Tags

---

## 🔧 Software Requirements

- Linux kernel source tree (RB-A5D2X)
- Yocto or similar cross-compilation environment
- Tools: `git`, `gcc`, `device tree compiler`, etc.
- Poky toolchain (e.g. `poky-tiny`)

---

## 🚀 Driver Integration (Static Kernel Build)

### 1. Copy driver files to kernel source

Copy to:  
`drivers/misc/rfid_rc522/`

rc522.c
rc522_api.c
rc522_api.h
Kconfig
Makefile

bash
Copy
Edit

### 2. Modify Kconfig and Makefile

Edit `drivers/misc/Kconfig`:

```c
source "drivers/misc/rfid_rc522/Kconfig"
Edit drivers/misc/Makefile:

make
Copy
Edit
obj-y += rfid_rc522/
3. Device Tree Changes
Edit: arch/arm/boot/dts/a5d2x-rugged_board_common.dtsi
Add SPI node for RC522 with pinctrl and GPIO config.

🏗️ Kernel Build
bash
Copy
Edit
source /opt/poky-tiny/2.5.2/environment-setup-cortexa5hf-neon-poky-linux-musleabi
make distclean
make rb_a5d2x_defconfig
make menuconfig      # Enable RFID_RC522
make
Copy zImage and *.dtb files to SD card boot partition.

🧪 Driver Testing
Boot the board

Confirm device:

bash
Copy
Edit
ls /dev/rfid_rc522_dev
Build and copy user-space app:

bash
Copy
Edit
${CC} rfid_rc522_dev.c -o rfid_rc522_dev
scp rfid_rc522_dev root@<BOARD_IP>:/home/root
Run on board:

bash
Copy
Edit
chmod +x rfid_rc522_dev
./rfid_rc522_dev
🧵 Patch Generation (Optional)
Generate patch from kernel:

bash
Copy
Edit
git add drivers/misc/rfid_rc522/
git commit -m "Add RC522 driver"
git format-patch -p1 -o patches/
Apply patch later using:

bash
Copy
Edit
git am 0001-rfid-rc522_driver.patch
📄 Documentation
📘 Integration Guide: Integration_rfid-rc522.pdf

🧾 Patch Generation: rfid-rc522_Generating_patch.pdf

👨‍💻 Developed By
Venkatesh M
📧 venkatesh.muninagaraju@essae.com
👨‍💼 Embedded Systems Engineer, Essae-Teraoka

