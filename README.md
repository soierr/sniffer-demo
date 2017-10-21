# sniffer-demo

This is a linux demo application which allows capturing tcp packets and reveals short statistics with data persistency support. 

Functionality list is below:

1. Gathering source IP and packets count, saving it in key-value data structure based on reb-black tree
   <br/>Packet capturing performed with help of pcap library

2. Saving gathered data to file
   <br/>Data serialized/deserialized with help of protobuf protocol, particularly protobuf-c

3. Packets capturing from proper source IP

4. Short statistics: max, min packet count IP, total element in data structure, etc

sudo rights needed to launch the application


