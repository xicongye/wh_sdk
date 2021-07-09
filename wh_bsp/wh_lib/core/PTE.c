/*********************************************************************************
*
*   PROJECT:    SDJ2102
*
*   FILENAME:   PTE.c
*
*   FUNCTION:   implement the interface of sv32
*
*   AUTHOR:     liaoll
*
*   DATE:       2019/07/15
*
*   ISFINISH:   NO
*
*   STATUS: 
************************************************************************************/

/* Includes --------------------------------------------------------*/
#include "platform.h"

/* Private define --------------------------------------------------*/
/* Private macro ---------------------------------------------------*/
/* Private variables -----------------------------------------------*/
/* Extern variables ------------------------------------------------*/
int super_page_sv32[1024] __attribute__((aligned(4096)));
int leaf_page_sv32[1024][1024] __attribute__((aligned(4096)));

/* Private function prototypes -------------------------------------*/
/* Private functions -----------------------------------------------*/

/********************************************************************
* Function Name :   sv32_init
* Description   :   reset super_page_sv32 & leaf_page_sv32
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void sv32_init(void)
{
  unsigned int idx_x, idx_y;

  for(idx_x = 0; idx_x < 1024; idx_x++)
  {
    super_page_sv32[idx_x] = 0;
    for(idx_y = 0; idx_y < 1024; idx_y++)
       leaf_page_sv32[idx_x][idx_y] = 0;
  }
}


/********************************************************************
* Function Name :   sv32_enable
* Description   :   enable sv32
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void sv32_enable(void) 
{
#if __riscv_xlen == 32
  int satp_ppn,satp_mode;
  int satp ;

  //Flush the TLB 
  asm("SFENCE.VMA" : : : "memory");
  satp_ppn = ((int)super_page_sv32) >> PADDR_PPN0_BIT;
  satp_mode = 1;
  satp = (satp_mode << SATP_MODE_BIT) | satp_ppn;
  write_csr(satp,satp);
#endif
}


/********************************************************************
* Function Name :   sv32_disable
* Description   :   disable sv32
* Input         :   none
* Output        :   none
* Return        :   none
********************************************************************/
void sv32_disable(void)
{
  write_csr(satp, 0);
}



/********************************************************************
* Function Name :   sv32_addr_map
* Description   :   translate physical address to virtual address
* Input         :   - Level - 1: use 1-level PTE, 2: use 2-level PTE
*               :   - Paddr - physical address
*               :   - Exe - executable
*               :   - Write - writable
*               :   - Read - readable
*               :   - User - 1: indicates whether the page is accessible to user mode
*               :   - Global - 1: indicates a global mapping
* Output        :   none
* Return        :   none
********************************************************************/
void * sv32_addr_map(int Level, void *Paddr, unsigned int Exe, unsigned int Write, unsigned int Read, unsigned int User, unsigned int Global)
{
#if __riscv_xlen == 32
  unsigned int idx_x , idx_y;
  unsigned int pte_priv;
  unsigned int super_priv; 
  unsigned int paddr_ppn1;
  unsigned int paddr_ppn0;
  unsigned int paddr_offset;
  unsigned int super_page_entry;
  unsigned int super_page_idx_addr_ppn1;
  unsigned int super_page_idx_addr_ppn0;
  unsigned int super_page_idx_addr_vpn ;
  unsigned int second_page_entry ;
  unsigned int second_page_idx_addr_ppn1;
  unsigned int second_page_idx_addr_ppn0;
  unsigned int second_page_idx_addr_vpn ;
  unsigned int pte_set_value;

  paddr_ppn1 = ((unsigned int) Paddr >> PADDR_PPN1_BIT ) & PADDR_PPN1_MASK ;
  paddr_ppn0 = ((unsigned int) Paddr >> PADDR_PPN0_BIT ) & PADDR_PPN0_MASK ;
  paddr_offset = (unsigned int) Paddr & PAGE_OFFSET_MASK ;

  pte_priv =    ((Global & PTE_GLOBAL_MASK)      << PTE_GLOABL_BIT)      | \
                ((User   & PTE_USER_MASK)        << PTE_USER_BIT)        | \
                ((Read   & PTE_READABLE_MASK)    << PTE_READABLE_BIT)    | \
                ((Write  & PTE_WRITEABLE_MASK)   << PTE_WRITEABLE_BIT)   | \
                ((Exe    & PTE_EXECUTEABLE_MASK) << PTE_EXECUTEABLE_BIT) | \
                ((1  & PTE_ACCESS_MASK)          << PTE_ACCESS_BIT)      | \
                ((1  & PTE_DIRTY_MASK )          << PTE_DIRTY_BIT )      | \
                ((1  & PTE_VALID_MASK)           << PTE_VALID_BIT)       ;

  super_priv =  ((Global & PTE_GLOBAL_MASK)      << PTE_GLOABL_BIT)      | \
                ((User   & PTE_USER_MASK)        << PTE_USER_BIT)        | \
                ((1  & PTE_ACCESS_MASK)          << PTE_ACCESS_BIT)      | \
                ((1  & PTE_DIRTY_MASK )          << PTE_DIRTY_BIT )      | \
                ((1  & PTE_VALID_MASK)           << PTE_VALID_BIT)       ;
 
  for(idx_x = 0 ; idx_x < 1024 ; idx_x ++ )
  {
    super_page_entry = super_page_sv32[idx_x];
    unsigned int super_addr_offset = (unsigned int) super_page_sv32 + idx_x * 4;

    super_page_idx_addr_ppn1 =  (super_addr_offset >> INDEX_ADDR_PPN1_BIT) & INDEX_ADDR_PPN1_MASK ;
    super_page_idx_addr_ppn0 =  (super_addr_offset >> INDEX_ADDR_PPN0_BIT) & INDEX_ADDR_PPN0_MASK ;
    super_page_idx_addr_vpn  =  (super_addr_offset >> INDEX_ADDR_VPN_BIT)  & INDEX_ADDR_VPN_MASK ;

    if(IsPTEValid(super_page_entry))
    {
      if(IsPointerToNext(super_page_entry))
      {
        if(Level == 2)
        {
          for(idx_y = 0 ; idx_y < 1024 ; idx_y++)
          {
            second_page_entry = leaf_page_sv32[idx_x][idx_y];
            unsigned int leaf_addr_offset = (unsigned int) leaf_page_sv32 + (idx_x * 1024 * 4) + (idx_y * 4 );
            second_page_idx_addr_ppn1 = (leaf_addr_offset >> INDEX_ADDR_PPN1_BIT) & INDEX_ADDR_PPN1_MASK ;
            second_page_idx_addr_ppn0 = (leaf_addr_offset >> INDEX_ADDR_PPN0_BIT) & INDEX_ADDR_PPN0_MASK ;
            second_page_idx_addr_vpn  = (leaf_addr_offset >> INDEX_ADDR_VPN_BIT)  & INDEX_ADDR_VPN_MASK ;
            pte_set_value = (paddr_ppn1 << PTE_PPN1_BIT) |   \
                            (paddr_ppn0 << PTE_PPN0_BIT) |   \
                            pte_priv ;
            if(!IsPTEValid(second_page_entry))
            {
              leaf_page_sv32[idx_x][idx_y] = pte_set_value ;
              return  (void *) (((super_page_idx_addr_vpn & VADDR_VPN1_MASK ) << VADDR_VPN1_BIT) | \
                                ((second_page_idx_addr_vpn & VADDR_VPN0_MASK) << VADDR_VPN0_BIT) | \
                                 (paddr_offset &  PAGE_OFFSET_MASK));
            }
            else 
            {
              if((pte_set_value >> PTE_PPN0_BIT) == (second_page_entry >> PTE_PPN0_BIT))
              {
                leaf_page_sv32[idx_x][idx_y] = pte_set_value ;
                return (void*) (((super_page_idx_addr_vpn & VADDR_VPN1_MASK ) << VADDR_VPN1_BIT) | \
                                ((second_page_idx_addr_vpn & VADDR_VPN0_MASK) << VADDR_VPN0_BIT) | \
                                (paddr_offset &  PAGE_OFFSET_MASK));
              }
            }  
          }    
        }
      }
    }
    else
    {
      if(Level == 1)
      {
        super_page_sv32[idx_x] = paddr_ppn1 << PTE_PPN1_BIT | \
                                          0 << PTE_PPN0_BIT | \
                                          pte_priv ;
        return (void *) (((super_page_idx_addr_vpn & VADDR_VPN1_MASK) << VADDR_VPN1_BIT ) | \
                         ((paddr_ppn0 & VADDR_VPN0_MASK) << VADDR_VPN0_BIT) | \
                          (paddr_offset & PAGE_OFFSET_MASK) );
      }
      else if(Level == 2)
      {
        unsigned int leaf_addr_offset = (unsigned int)leaf_page_sv32 + idx_x * 1024 * 4;
        second_page_idx_addr_ppn1 = (leaf_addr_offset >> INDEX_ADDR_PPN1_BIT) & INDEX_ADDR_PPN1_MASK ;
        second_page_idx_addr_ppn0 = (leaf_addr_offset >> INDEX_ADDR_PPN0_BIT) & INDEX_ADDR_PPN0_MASK ;
        second_page_idx_addr_vpn  = (leaf_addr_offset >> INDEX_ADDR_VPN_BIT) & INDEX_ADDR_VPN_MASK;
        super_page_sv32[idx_x] = (second_page_idx_addr_ppn1 << PTE_PPN1_BIT ) | \
                                 (second_page_idx_addr_ppn0 << PTE_PPN0_BIT ) | \
                                  super_priv ;
        leaf_page_sv32[idx_x][0] = (paddr_ppn1 << PTE_PPN1_BIT) |   \
                                   (paddr_ppn0 << PTE_PPN0_BIT) |   \
                                    pte_priv ;

        return (void *) (((super_page_idx_addr_vpn & VADDR_VPN1_MASK ) << VADDR_VPN1_BIT) | \
                         ((second_page_idx_addr_vpn & VADDR_VPN0_MASK) << VADDR_VPN0_BIT) | \
                          (paddr_offset &  PAGE_OFFSET_MASK)) ;
      }
    }
  }
#endif
  return NULL ; // Error 
}

