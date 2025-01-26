# Subnetter

## About
Subnetter is a IPv4 subnet calculator command line tool. It reports network addresses, usable host addresses, IP class, IP type, and more

## Dependencies
- [CMake](https://cmake.org)

### Windows Dependencies 
- Visual Studio Community 2022
- [Desktop development with C++](https://imgur.com/a/visual-studio-community-2019-installer-c-options-7zs51IT) in Visual Studio installer

## Installation
Subnetter uses cmake for it's build system so you will need it to create the build scripts. You can go [here](https://cmake.org/download/) to download cmake or if you are using a package manager you can also install it using that. For example

```
sudo apt install cmake
```

Once you have cmake execute the following commands
```
git clone https://github.com/BeastieNate5/Subnetter  
cd Subnetter
mkdir build
cmake .. 
```

That will create the build scripts for your platform to compile the source code

### Windows Details
By default a Visual Studio Solution should have been generated. Open up `Developer Command Prompt for VS 2022` by searching that in the start menu. Then run the followin commands
```
cd Subnetter\build
msbuild subnetter.sln /p:Configuration=Release
```
*Ignore the warnings*

This will create the final executale in the `release/` directory

### Linux Details
By default a Makefile should have been generated to compile execute the following command
```
make
```
That will create the final executable in the current directory

## Usage
The command syntax is the following
```
subnetter <IP> <CIDR Prefix>
```
The following is a example 
```
subnetter 192.168.10.43 24
```
output
```
IP Address: 192.168.10.43
Network Address: 192.168.10.0
Subnetmask: 255.255.255.0
Host IP Range: 192.168.10.1 - 192.168.10.254
Broadcast Address: 192.168.10.255
Next Subnet: 192.168.11.0
Host amount: 254
IP Class: C
IP Type: Private
Binary Network Address: 11000000.10101000.00001010.00000000
Binary Subnetmask: 11111111.11111111.11111111.00000000
```