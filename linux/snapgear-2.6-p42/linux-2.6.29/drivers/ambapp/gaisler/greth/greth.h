#define GRETH_REG_BASE  ETH_BASE_ADD 

#define GRETH_RESET 0x40
#define GRETH_MII_BUSY 0x8
#define GRETH_MII_NVALID 0x10

#define GRETH_CTRL_FD        0x10
#define GRETH_CTRL_PR        0x20
#define GRETH_CTRL_PSTATIEN  0x400
#define GRETH_CTRL_MCEN      0x800
#define GRETH_STATUS_PHYSTAT 0x100

/* PHY vendor IDs */
#define MARVELL_88EE1111_reg2   0x0141
#define MARVELL_88EE1111_reg3   0x0CC0        
#define INTEL_LXT971A_reg2      0x0013
#define INTEL_LXT971A_reg3      0x78E0
#define NS_DP83848_reg2         0x2000
#define NS_DP83848_reg3         0x5C90
#define NS_DP83865_reg2         0x2000 
#define NS_DP83865_reg3         0x5C70
#define VSC_8641_reg2           0x0007
#define VSC_8641_reg3           0x0430

#define GRETH_BD_EN 0x800
#define GRETH_BD_WR 0x1000
#define GRETH_BD_IE 0x2000
#define GRETH_BD_LEN 0x7FF

#define GRETH_TXEN 0x1
#define GRETH_INT_TX 0x8
#define GRETH_TXI 0x4
#define GRETH_TXBD_STATUS 0x0001C000
#define GRETH_TXBD_MORE 0x20000
#define GRETH_TXBD_IPCS 0x40000
#define GRETH_TXBD_TCPCS 0x80000
#define GRETH_TXBD_UDPCS 0x100000
#define GRETH_TXBD_ERR_LC 0x10000
#define GRETH_TXBD_ERR_UE 0x4000
#define GRETH_TXBD_ERR_AL 0x8000
#define GRETH_TXBD_NUM 128
#define GRETH_TXBD_NUM_MASK (GRETH_TXBD_NUM-1)
#define GRETH_TX_BUF_SIZE 2048

#define GRETH_INT_RX         0x4
#define GRETH_RXEN           0x2
#define GRETH_RXI            0x8
#define GRETH_RXBD_STATUS    0xFFFFC000
#define GRETH_RXBD_ERR_AE    0x4000
#define GRETH_RXBD_ERR_FT    0x8000
#define GRETH_RXBD_ERR_CRC   0x10000
#define GRETH_RXBD_ERR_OE    0x20000
#define GRETH_RXBD_ERR_LE    0x40000
#define GRETH_RXBD_IP_DEC    0x80000
#define GRETH_RXBD_IP_CSERR  0x100000
#define GRETH_RXBD_UDP_DEC   0x200000
#define GRETH_RXBD_UDP_CSERR 0x400000
#define GRETH_RXBD_TCP_DEC   0x800000
#define GRETH_RXBD_TCP_CSERR 0x1000000
#define GRETH_RXBD_IP_FRAG   0x2000000
#define GRETH_RXBD_MCAST     0x4000000

#define GRETH_RXBD_NUM 128
#define GRETH_RXBD_NUM_MASK (GRETH_RXBD_NUM-1)
#define GRETH_RX_BUF_SIZE 2048

/* Ethernet configuration registers */
typedef struct _greth_regs {
   volatile int    control;        
   volatile int    status;        
   volatile int    esa_msb;        
   volatile int    esa_lsb;        
   volatile int    mdio;        
   volatile int    tx_desc_p;        
   volatile int    rx_desc_p;
   volatile int    edclip;
   volatile int    hash_msb;
   volatile int    hash_lsb;
} greth_regs;

/* Ethernet buffer descriptor */
typedef struct _greth_bd {
  int    stat;
  int    addr;           /* Buffer address */
} greth_bd;








