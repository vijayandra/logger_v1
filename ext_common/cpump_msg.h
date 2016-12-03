#ifndef _CPUMB_MSG_H
#define _CPUMB_MSG_H

enum
{
    en_sig_tab=0,
    en_sco_tab,
    en_plg_tab
};

enum
{
    en_set_freq=0,
    en_set_points,
    en_set_start,
    en_set_stop,
    en_set_tmr1,
    en_set_tmr2
};

enum
{
    en_uart_1,
    en_uart_2,
    en_uart_3
};

enum
{
    en_uart_speed,
    en_uart_parity,
    en_uart_stop_bit,
    en_uart_baud,
    en_uart_databit,
    en_uart_start,
    en_uart_stop,
};

enum
{
    en_i2c_speed,
    en_i2c_write,
    en_i2c_read,
    en_i2c_start,
    en_i2c_stop,
    en_i2c_restart,
};

enum
{
    en_adc_start,
    en_adc_stop,
    en_adc_chnls,
    en_adc_dtpnts,
    en_adc_timer,
};

enum
{
    en_dac_start,
    en_dac_stop,
    en_dac_chnls,
    en_dac_dtpnts,
    en_dac_timer,
};

enum
{
    en_open_file,
    en_open_rd_file,
    en_open_wr_file,
    en_close_file,
    en_append_file,
    en_size_file,
    en_get_index
};

enum
{
    enUSART_WORDLENGTH_8B=0,
    enUSART_WORDLENGTH_9B,
    enUSART_STOPBITS_1,
    enUSART_STOPBITS_0_5,
    enUSART_STOPBITS_2,
    enUSART_STOPBITS_1_5,
    enUSART_PARITY_NONE,
    enUSART_PARITY_EVEN,
    enUSART_PARITY_ODD
};



















#endif
