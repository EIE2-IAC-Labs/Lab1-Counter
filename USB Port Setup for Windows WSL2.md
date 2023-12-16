# USB Port Setup for Windows WSL 2
### Step 1:
Firstly, check if the WSL version you are running is version 2. Open up Windows PowerShell or Command Prompt and type 
	
	wsl --list --verbose

It should show the distro you are running and the version of it. If it is running version 1, type the following to convert to version 2:
`wsl --set-version <Distro> 2`, replacing `<Distro>` with your actual distro name, such as `Ubuntu`.

### Step 2:
Download usbipd-win. First check your kernel version. Open up WSL and run `uname -a` and check if it reports a kernel version of 5.10.60.1 or later.
	On Ubuntu 20.04 LTS, run:

	sudo apt install linux-tools-virtual hwdata

followed by:

	sudo update-alternatives --install /usr/local/bin/usbip usbip `ls /usr/lib/linux-tools/*/usbip | tail -n1` 20

Also on Windows, download the latest version's `.msi` file from https://github.com/dorssel/usbipd-win/releases and install it.

### Step 3:
Run Windows PowerShell as an Administrator. 

To list all the devices connected to your machine, run:

	usbipd list
	
Note down the `BUS-ID` for the device you want to connect.

Run 

	usbipd --wsl attach --busid={BUS-ID}

e.g. `usbipd --wsl attach --busid=4-3`

Verify that the device is being used by WSL. Under "STATE", it should show: `Attached`
	
	usbipd list

### Step 4:
On WSL, cd to your lab workspace folder.

Type `lsusb` and the device should now show other than two other Linux Foundation root hubs.

To verify the port, run 
	
	dmesg | grep tty

It should provide a verification message ending with "... now attached to ttyUSB*", with * representing the number of the port. Usually it is 0.

Open VSCode with

	code .

In the `vbuddy.cfg`, type `/dev/ttyUSB*`  then press ENTER to open a new line.

When connecting to the Vbuddy via running `./doit.sh` , it should show `** Connected to Vbuddy via: /dev/ttyUSB*` .

References: 
https://blog.golioth.io/program-mcu-from-wsl2-with-usb-support/
https://github.com/dorssel/usbipd-win/wiki/WSL-support

https://github.com/MicrosoftDocs/WSL/issues/1868#issuecomment-1850904397
(issue is that `wsl` is no longer a subcommand of usbipd-win, but `usbipd --wsl` is)
## IMPORTANT NOTE

Some students had difficulties running Vbuddy in Windows WSL in spite of following the instructions above.  A common mistake is that you clone your github lab repo under the Windows operating systems instead of within WSL, while all the tools for this module are installed under WSL, not Windows.  Therefore, always do everything in WSL, not in Windows. 

Why?  Because in the real world, software tools for software developers are mostly written to run in Linux, not in Windows.  WSL is effectively Linux run inside Windows.
