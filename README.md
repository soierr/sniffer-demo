# sniffer-demo

This is a linux demo application which allows capturing tcp packets and reveals short statistics with data persistency support. 

Functionality list is below:

1. Gathering source IP and packets count, saving it in key-value data structure based on implemented reb-black tree
   <br/>Packet capturing performed with help of pcap library

2. Saving data structure to file
   <br/>Data structure serialized/deserialized with help of protobuf protocol, particularly protobuf-c

3. Packets capturing from proper source IP

4. Short statistics: max, min packet count IP, total element in data structure, etc

sudo rights needed to launch the application

In order to be able to build the application and launch it the following libraries needs to installed:


- pcap                  (tested on v0.8)
- protobuf, protobuf-c  (tested on v3.4.0 v1.3.0)
- ncurses               (tested on v5.0)
- git


- sudo apt-get install libpcap-dev
- for protobuf, protobuf-c see proper readme on github
- sudo apt-get install libncurses-dev

After installation, make the following steps:

- git clone https://github.com/soierr/sniffer-demo.git
- cd sniffer-demo
- make

Once it's done, look for a file sniffer-demo.exe which is our target application

sudo ./sniffer-demo.exe

If there are any problem with library resolving try start "ldconfig"

