# CMPE 283 - Virtualization Technologies - Assignment 2 - Instrumentation via hypercall

To modify the CPUID emulation code in KVM to report back additional information
when special CPUID leaf nodes are requested.
* For CPUID leaf node %eax=0x4FFFFFFC:<br/>
  Return the total number of exits (all types) in %eax
* For CPUID leaf node %eax=0x4FFFFFFD:<br/>
  Return the high 32 bits of the total time spent processing all exits in %ebx<br/>
  Return the low 32 bits of the total time spent processing all exits in %ecx
  %ebx and %ecx return values are measured in processor cycles, across all VCPUs

### Professor's Name: Michael Larkin <br/>
### Submitted By: Darshini Venkatesha Murthy Nag <br/>
### Student ID: 016668951 <br/>
### Linux kernel Source code Working tree: <br/> Please refer https://github.com/darshcloud/linux.git for the complete working tree

## Steps used to complete the assignment
### Steps to build kernel:
* Fork the linux kernel source repository https://github.com/torvalds/linux.git and clone it
* Install the dependencies using the below command <br/>
`sudo apt-get install fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison`
* Copy the existing configuration using the command<br/>
`cp -v /boot/config-$(uname -r) .config`
* Run the below command to compile and build the kernel<br/>
`make -j $nproc` <br/>
if you encounter error "No rule to make target 'debian/canonical-certs.pem"
then disable securities certificate by using<br/>
`scripts/config --disable SYSTEM_TRUSTED_KEYS` and `scripts/config --disable SYSTEM_REVOCATION_KEYS`
* Run the below command to install the required modules<br/>
`sudo make INSTALL_MOD_STRIP=1 modules_install`
* Run the below command to install the kernel<br/>
`sudo make install`
* Reboot and verify the kernel version by running the below command<br/>
`uname -mrs`

### Code Modification in Kernel source code
* Added assignment functionality for building the leaf functions 0x4ffffffc and 0x4ffffffd
* Added 2 Global variables total_cycles_in_exits and total_no_of_exits
* In vmx.c, Implemented the changes for calculating the number of exits
  and total time spent processing all exits in the vmx_handle_exit function
* In cpuid.c, created 2 new cpuid leaf in kvm_emulate_cpuid function which reads the
  total_no_of_exits into % eax when eax = 0x4ffffffc and moves the high 32 bits of total_cycles_in_exits into %ebx and low 32 bits
  of total_cycles_in_exits into %ecx when % eax = 0x4ffffffd
* Compile the code using <br/>
  `make -j $nproc modules`
* To install the built modules run <br/>
  `sudo make INSTALL_MOD_STRIP=1 modules_install && make install`
* Run the below commands to reload the KVM module <br/>
`sudo rmmod kvm_intel ` <br/>
`sudo rmmod kvm` <br/>
`sudo modprobe kvm_intel` <br/>

### Inner VM Setup
* Before installing the KVM first check whether CPU virtualization feature is enabled in the system BIOS or not by running the below command <br/>
`egrep -c '(vmx|svm)' /proc/cpuinfo`
* Install the QEMU/KVM and Libvirt using the below command <br/>
`sudo apt install qemu-kvm libvirt-clients libvirt-daemon-system bridge-utils virtinst libvirt-daemon`
* Start and enable KVM service <br/>
`sudo systemctl enable --now libvirtd`
* Install Virt-Manager GUI for KVM using the below command <br/>
`sudo apt install virt-manager -y`
* Download the ubuntu iso image
* Run the KVM Virt-Manager and create a VM
* Complete the installation process and configure the inner VM
* Build the test code inside the inner VM to test the changes made in the Outer VM kvm module.

### Output
The screenshot below shows the total number of exits and the total time spent processing all exits

![Screenshot from 2022-12-01 01-16-44](https://user-images.githubusercontent.com/111547793/205148877-1d8fd36c-6777-41aa-97a1-01b85e068fae.png)

