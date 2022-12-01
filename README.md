# CMPE 283 - Virtualization Technologies - Assignment 2 - Instrumentation via hypercall

To modify the CPUID emulation code in KVM to report back additional information
when special CPUID leaf nodes are requested.
* For CPUID leaf node %eax=0x4FFFFFFC:<br/>
  Return the total number of exits (all types) in %eax
* For CPUID leaf node %eax=0x4FFFFFFD:<br/>
  Return the high 32 bits of the total time spent processing all exits in %ebx
  Return the low 32 bits of the total time spent processing all exits in %ecx
  %ebx and %ecx return values are measured in processor cycles, across all VCPUs

### Professor's Name: Michael Larkin <br/>
### Submitted By: Darshini Venkatesha Murthy Nag <br/>
### Student ID: 016668951 <br/>
### Linux kernel Source code Working tree: 
Please refer https://github.com/darshcloud/linux.git

## Steps used to complete the assignment
### Steps to build kernel:
* Fork the linux kernel source repository https://github.com/torvalds/linux.git and clone it
* Install the dependencies using the below command <br/>
`sudo apt-get install fakeroot build-essential ncurses-dev xz-utils libssl-dev bc flex libelf-dev bison`
* Copy the existing configuration using the command<br/>
`cp -v /boot/config-$(uname -r) .config`
* run the below command to compile and build the kernel<br/>
`make -j $nproc` <br/>
if you encounter error "No rule to make target 'debian/canonical-certs.pem"
then disable securities certificate by using<br/>
`scripts/config --disable SYSTEM_TRUSTED_KEYS` and `scripts/config --disable SYSTEM_REVOCATION_KEYS`
* Run the below command to install the required modules<br/>
`sudo make INSTALL_MOD_STRIP=1 modules_install`
* Run the below command to install the kernel<br/>
`sudo make install`
* Reboot and verify the kernel version by running the command<br/>
`uname -mrs`
