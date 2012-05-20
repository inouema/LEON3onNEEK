/*
 * getstat.c implements showCANStat(fd) 
 *
 * Copyright (c) 2004 port GmbH Halle (Saale)
 *------------------------------------------------------------------
 * $Header: /z2/cvsroot/library/co_lib/drivers/shar_src/can_can4linux.c,v 2.4 2004/04/23 12:52:25 oe Exp $
 *
 *------------------------------------------------------------------
 *
 * modification history
 * --------------------
 * $Log: can_can4linux.c,v $
 *
 *
 *------------------------------------------------------------------
 */

void		showCANStat(int fd);

/*******************************************************************/
/**
*++ \brief showCANStat - show CAN status values using printf()
*-- \brief showCANStat - zeigt CAN Status Werte mit printf()
*
* \retval
*++ nothing
*-- nichts
*
*/
void showCANStat(int fd)
{
CanStatusPar_t status;
char *m;

    ioctl(fd, STATUS, &status);
    switch(status.type) {
        case  CAN_TYPE_SJA1000:
            m = "sja1000";
            break;
        case  CAN_TYPE_FlexCAN:
            m = "FlexCan";
            break;
        case  CAN_TYPE_TouCAN:
            m = "TouCAN";
            break;
        case  CAN_TYPE_82527:
            m = "I82527";
            break;
        case  CAN_TYPE_TwinCAN:
            m = "TwinCAN";
            break;
    case CAN_TYPE_UNSPEC:
    default:
            m = "sja1000";
            break;
    }

    printf(":: %s %4d %2d %2d %2d %2d %2d tx:%3d/%3d: rx:%3d/%3d:\n",
        m,
        status.baud,
        status.status,
        status.error_warning_limit,
        status.rx_errors,
        status.tx_errors,
        status.error_code,
        /* */
        status.tx_buffer_size,
        status.tx_buffer_used,
        status.rx_buffer_size,
        status.rx_buffer_used
        );
}
