#ifndef ETHMAC
#define ETHMAC
typedef struct eth_reg
{
    int eth_moder;
    int eth_int_source;
    int eth_int_mask;
    int eth_ipgt;
    int eth_ipgr1;
    int eth_ipgr2;
    int eth_packet_len;
    int eth_collconf;
    int eth_rx_bd_num;
    int eth_ctrlmoder;
    int eth_mii_moder;
    int eth_mii_command;
    int eth_mii_address;
    int eth_mii_tx_data;
    int eth_mii_rx_data;
    int eth_mii_status;
    int eth_mac_addr0;
    int eth_mac_addr1;
    int eth_hash0_adr;
    int eth_hash1_adr;
}ETH_REG_T,*ETH_REG_P;

#endif
