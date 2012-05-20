#define GRETH_REG_BASE  ETH_BASE_ADD 

#define GRETH_FD 0x10
#define GRETH_RESET 0x40
#define PHY_ADDR 0
#define GRETH_MII_BUSY 0x8
#define GRETH_MII_NVALID 0x10

#define GRETH_BD_EN 0x800
#define GRETH_BD_WR 0x1000
#define GRETH_BD_IE 0x2000
#define GRETH_BD_LEN 0x7FF

#define GRETH_INT_TXERR 0x2
#define GRETH_INT_TX 0x8
#define GRETH_TXEN 0x1
#define GRETH_TXI 0x4
#define GRETH_TXBD_STATUS 0xFFFFC000
#define GRETH_TXBD_ERR_UE 0x4000
#define GRETH_TXBD_ERR_AL 0x8000
#define GRETH_TXBD_NUM 32
#define GRETH_TXBD_NUM_MASK GRETH_TXBD_NUM-1
#define GRETH_TX_BUF_SIZE 2048

#define GRETH_INT_RXERR 0x1
#define GRETH_INT_RX 0x4
#define GRETH_RXEN 0x2
#define GRETH_RXI 0x8
#define GRETH_RXBD_STATUS 0xFFFFC000
#define GRETH_RXBD_ERR_AE 0x4000
#define GRETH_RXBD_ERR_FT 0x8000
#define GRETH_RXBD_ERR_CRC 0x10000
#define GRETH_RXBD_ERR_OE 0x20000
#define GRETH_RXBD_NUM 32
#define GRETH_RXBD_NUM_MASK GRETH_RXBD_NUM-1
#define GRETH_RX_BUF_SIZE 2048

#define GRETH_INTMASK (GRETH_INT_TXERR|GRETH_INT_TX|GRETH_INT_RXERR|GRETH_INT_RX)

/* Ethernet configuration registers */
typedef struct _greth_regs {
  volatile int    control;        
  volatile int    status;        
  volatile int    esa_msb;        
  volatile int    esa_lsb;        
  volatile int    mdio;        
  volatile int    tx_desc_p;        
  volatile int    rx_desc_p;        
} greth_regs;

/* Ethernet buffer descriptor */
typedef struct _greth_bd {
  int    stat;
  int    addr;           /* Buffer address */
} greth_bd;








