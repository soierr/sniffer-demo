# sniffer-demo

This is a linux demo application which allows capturing tcp packets and reveals short statistics with data persistency support. 

Functionality list is below:

1. Gathering source IPs and packets count, saving it in key-value data structure based on reb-black tree.
   Packet capturing performed with help of pcap library.

2. Saving gathered data. 
   Data serialized/deserialized with help of protobuf protocol, particularly protobuf-c

3. Track packets from proper source IP

4. Get short statistics max, min packet count IP, total element in data structure, etc


