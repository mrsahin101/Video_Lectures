# Debian or Yocto Project? Which is the best for your Embedded Linux project ?
- **Off-the-peg** : Use a Debian based distro(or another distro of your choice)
- **Bespoke** : Build everything from scratch using a build system like Yocto(or Buildroot)

## Debian
- Debian is a full distro with tens of thousands of packages
- Stable, long term support
- Binary, so no need to cross-compile

### Developing on Debian
- The overall procedure would be
    1. Take an existing "off-the-peg" image
    2. Strip out thing you dont want
    3. Add the things you do want
    4. Compile natively(on the target) custom programs and libraries
    5. Add any other tweaks you need
    6. Resulting in **Golder Master** image
- Once development is done to take copy of the file system. Clone it to all units shipped

- What can go wrong.
    1. A Golder Master can become a millstone
    2. Steps to create it are almost certainly not documented
        1. So changes have to incremental
        2. Major changes, new distro release are very difficult
    3. Probably contains a firger print of the person who created it    
        1. User accounts and passwords
        2. $Home/.bash_history
        3. Old system log files

### Developing on Debian 2
- You need a **robust**, **reproducible** build process
    1. Build a base system image using Rootstock, debootstrap, or similiar
    2. Install only the packages you need
    3. Import your own software and configuration

### Software Update on Debian
- Updates to Debian systems would seem to be easy
    1. Just use <code>apt update</code>
- But, updates via apt are not **atomic**. If power lost during update system is corrupted.
- You will probably end up doing a full image update

### Downside of Debian
- Large image size(compared to equivalent Yocto system)
- More software means more attack vectors, therefore less secure system
- Many not be compiled optimally for your platform(may not be using some features of the your CPU.)
- Not optimized for flash memory. (Many disk writes wear it out)
- Compiling natively on a low powered device is slow
- You still have to build the bootloader, kernel and kernel modules

## Yocto Project/OpenEmbedded
- With OpenEmbedded/Yocto Project you can create a distribution to your own specification
- Build from up-stream **source** code
    1. Control every stage of compiling and building the target
- Industry-wide support
    1. Chip vendors of ARM, MIPS, PowerPC, and x86 architectures
    2. Board and System on Module vendors
    3. Commercial embedded Linux software vendors, such as ENEA, Mentor Graphics, Montavista, Timesys

- Building a rootfs with Yocto project
    1. From upstream source code, and metadata(which contains board specific recipes) with bitbake, creates rootfilesystem. 
- Metadata is : 
    1. **Distro** : How i want to put my system together recipes
    2. **Machine** : The board I want to build for
    3. **Image** : The selection of packages I want

### Downsides of Yocto Projects
- Steep learning curve
- Community support window is only 12 months
    1. After that you are responsible for monitoring and updating key packages
    2. Or outsource to a third party
- Building the rootfs from source requires powerfull hardware

## Debian is best for : 
- Proof of Concept and prototypes
- One-off projects
- Using commodity hardware such as Raspberry pi

## Yocto is best for :
- If you have custom hardware(no distro available)
- Reduced surface attack(Because less software means more secure system)
- Optimized for minimal memory and storage
- Full report of packages and their licenses(Needed license compliance)
