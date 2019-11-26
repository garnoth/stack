// This is a test structure called a gbuf
// right now it's just a range of bytes equal to the device MTU
// i need to test the ARP/IP/ICMP layers but I'll need to reconsider
// If I'm going to use sk_buff, mbuf or something of my own design like a 
// mbuf/sk_buff lite
//

struct gbuf {
size_t buf_len;
unsigned char * data;
};
