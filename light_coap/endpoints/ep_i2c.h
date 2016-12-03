#ifndef __EP_I2C_H
#define __EP_I2C_H

extern const scoap_endpoint_path_t path_i2c_read;
extern const scoap_endpoint_path_t path_i2c_write;
extern const scoap_endpoint_path_t path_i2c_start;
extern const scoap_endpoint_path_t path_i2c_restart;
extern const scoap_endpoint_path_t path_i2c_stop;
extern const scoap_endpoint_path_t path_i2c_speed;

extern int ep_i2c_read(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_i2c_write(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_i2c_start(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_i2c_restart(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_i2c_stop(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_i2c_speed(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);

#endif
