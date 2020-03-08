Name of Author: Sharar Mahmood 
Course: CIS 3110 - Operating Systems
Date of Submission: 12 March 2020
Namof Assignment: Developing Virtual Memory Manager

Description:

(Description prepared according to W20 CIS 3110 A3)

Translating Logical address to physical addresses. the programr program will read from a file containing logical addresses 
and, using a TLB as well as a page table, will translate each 
logical address to its corresponding physical address 
and output the value of the byte stored at the translated physical address. 
The goal behind it is to simulate the steps involved in translating logical to physical addresses.
Program reads the file containing several 32-bit integer numbers that represent 
logical addresses. 

However, the program need only be concerned with 16-bit addresses, 
so the program must mask the rightmost 16 bits of each logical address.
These 16 bits are divided into 
(1) an 8-bit page number and 
(2) 8-bit page offset.
Hence, the addresses are structured as shown in Figure 1.

First, the page number is extracted from the logical address, 
and the TLB is consulted. 
In the case of a TLB-hit, the frame number is obtained from the TLB. 
In the case of a TLB-miss, the page table must be consulted. 
In the latter case, either the frame number is obtained from the page table 
or a page fault occurs.

The backing store is represented by the file BACKING_STORE.bin, a binary file 
of size 65,536 bytes. 
When a page fault occurs, the program will read in a 256-byte page from the file BACKING_STORE.bin 
and store it in an available page frame in physical memory.
For example, if a logical address with page number 15 resulted in a page fault, the programr program would read in page 15 from BACKING_STORE (remember that pages begin at 0 and are 256 bytes in size) and store it in a page frame in physical memory. Once this frame is stored (and the page table and TLB are updated), subsequent accesses to page 15 will be resolved by either the TLB or the page table.
the program will need to treat BACKING_STORE.bin as a random-access file so that the program can randomly seek to certain positions of the file for reading. We suggest using the standard C library functions 
for performing I/O, including fopen(), fread(), fseek(), and fclose().
The size of physical memory is the same as the size of the virtual address space — 65,536 bytes — 
so  do not need to be concerned about page replacements during a page fault.

Inputs:

1 command line argument : File Name

Outputs:

The output format is shown below
Page Fault Rate=< page-fault rate>
TLB Hit Rate=<TLB-hit rate>
Please be advised that the programr results will be accurate to three decimal places.

For example,
Page Fault Rate=0.331
TLB Hit Rate=0.058

Since the logical addresses in addresses.txt were generated randomly and 
do not reflect any memory access locality,
 do not expect to have a high TLB hit rate.

the program program is to output the following values the standard output device (stdout):
1. The logical address being translated (the integer value being read from addresses.txt).
2. The corresponding physical address (what the programr program translates the logical address to).
3. The signed byte value stored at the translated physical address.

Virtual address: <logical address> Physical address: <physical address> Value: <byte value>
where output fields are separated by a single whitespace.
For example,
Virtual address: 31260 Physical address: 23324 Value: 0
which means that the corresponding physical address for the logical address 31260 is 23324. 
The value stored at physical memory unit of an address 23324 is 0.


Running:

The program will read in the file addresses.txt, 
which contains 1,000 logical addresses ranging from 0 to 65535. 
program is to translate each logical address to a physical address 
and determine the contents of the signed byte stored 
at the correct physical address.