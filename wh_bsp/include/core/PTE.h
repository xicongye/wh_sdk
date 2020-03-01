//-----------UC TECH IP------------------
//FileName:	PTE.h
//Function:	define the page table of sv32,sv39 & sv48 and its interface 
//Author: 	liaoll
//Date :	2019-07-15

#ifndef WH_PROCESSOR_PTE
#define WH_PROCESSOR_PTE

//pte_sv32[i][0] is the first level of page table entry 
extern int super_page_sv32 [1024];
extern int leaf_page_sv32[1024][1024];

void pageTableEnable_sv32();
void pageTableDisable_sv32();


void  pageTableInit_sv32();

void * addrMap_sv32(int Level ,void *Paddr,unsigned int Exe,unsigned int Write,unsigned int Read,unsigned int User,unsigned int Global);

//Physical Address Format 
//   33      22 21     12 11      0
//   ------------------------------
//  |    PPN1  |  PPN0   |  offset |
//   ------------------------------
#define PADDR_PPN1_BIT 22
#define PADDR_PPN1_MASK  0xFFF
#define PADDR_PPN0_BIT 12
#define PADDR_PPN0_MASK  0x3FF

//Virtual Address Format 
//    31       22 21     12 11      0
//    ------------------------------- 
//   |    VPN1   |  VPN0   |  offset |
//    -------------------------------
#define VADDR_VPN1_BIT 22
#define VADDR_VPN1_MASK 0x3FF
#define VADDR_VPN0_BIT 12
#define VADDR_VPN0_MASK 0x3FF

//PageTableEntry Format 
//    31       20 19        10 9    8 7 6 5 4 3 2 1 0 
//    ------------------------------------------------
//   |   PPN1    |    PPN0    |  RSW |D|A|G|U|X|W|R|V |
//    ------------------------------------------------
// D: indicates the virtual page has been written since the last time the D bit was cleared 
// A: indicates the virtual page has been read, written, or fetched from since the last time the A bit was cleared
// G: designates a global mapping 
// U: indicates whether the page is accessible to user mode
// X: executable
// W: writeable
// R: readable
// V: indicates the PTE is valid 

#define PTE_PPN1_BIT 20
#define PTE_PPN1_MASK 0xFFF

#define PTE_PPN0_BIT 10
#define PTE_PPN0_MASK 0x3FF

#define PTE_DIRTY_BIT 7
#define PTE_DIRTY_MASK 0x1

#define PTE_ACCESS_BIT 6
#define PTE_ACCESS_MASK 0x1

#define PTE_GLOABL_BIT 5
#define PTE_GLOBAL_MASK 0x1

#define PTE_USER_BIT 4
#define PTE_USER_MASK 0x1

#define PTE_EXECUTEABLE_BIT 3
#define PTE_EXECUTEABLE_MASK 0x1

#define PTE_WRITEABLE_BIT 2
#define PTE_WRITEABLE_MASK 0x1

#define PTE_READABLE_BIT 1
#define PTE_READABLE_MASK 0x1


#define PTE_VALID_BIT 0
#define PTE_VALID_MASK 0x1 

//is pointer to next level of page table 
#define IsPointerToNext(pte) \
	!( (pte >> PTE_READABLE_BIT) & PTE_READABLE_MASK ||  \
	   (pte >> PTE_WRITEABLE_BIT) & PTE_WRITEABLE_MASK || \
           (pte >> PTE_EXECUTEABLE_BIT) & PTE_EXECUTEABLE_MASK \
         )
#define IsPTEValid(pte)  \
        (pte >> PTE_VALID_BIT) & PTE_VALID_MASK

#define HasBeenAccessed(pte) \
	(pte >> PTE_ACCESS_BIT) & PTE_ACCESS_MASK 

#define HasBeenWrited(pte) \
	(pte >> PTE_DIRTY_BIT) & PTE_DIRTY_MASK 



#define PAGE_OFFSET_MASK 0xFFF


//SATP Register 
//      31    30                22 21                0
//   -------------------------------------------------
//  |  MODE  |        ASID        |       PPN         |
//   -------------------------------------------------

#define SATP_MODE_BIT 31
#define SATP_MODE_MASK 0x1

#define SATP_ASID_BIT  22
#define SATP_ASID_MASK  0x1FF

#define SATP_PPN_BIT 0
#define SATP_PPN_MASK 0x3FFFFF

//Index Address Format
//  33       22 21      12 11     2 1  0
//  ------------------------------------
// |   PPN1    |   PPN0   |   VPN  |2'b0|
//  ------------------------------------

#define INDEX_ADDR_PPN1_BIT 22
#define INDEX_ADDR_PPN1_MASK 0xFFF

#define INDEX_ADDR_PPN0_BIT 12
#define INDEX_ADDR_PPN0_MASK 0x3FF

#define INDEX_ADDR_VPN_BIT 2
#define INDEX_ADDR_VPN_MASK 0x3FF 

#endif 
