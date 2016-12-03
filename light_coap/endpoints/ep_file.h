#ifndef __EP_FILE_H
#define __EP_FILE_H

extern const char *uriFileOpArrStr[20];

#define FILE_OPEN_URI  "<file-open>"
#define FILE_CLOSE_URI "<file-close>"
#define FILE_WRITE_URI "<file-write>"
#define FILE_READ_URI  "<file-read>"
#define FILE_POS_URI   "<file-pos>"
#define FILE_POS_URI   "<file-pos>"
#define FILE_FATSD_DONE  "<fatsd-done>"
#define FILE_FORMAT_URI "<sdformat>"

extern const scoap_endpoint_path_t path_open_file;
extern const scoap_endpoint_path_t path_close_file;
extern const scoap_endpoint_path_t path_write_file;
extern const scoap_endpoint_path_t path_read_file;
extern const scoap_endpoint_path_t path_ptr_file;
extern const scoap_endpoint_path_t path_sd_format;

extern int ep_format_sd(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);

extern int ep_open_file_get(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_open_file_put(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_close_file_get(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_close_file_put(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_write_file(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_read_file(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_put_ptr_file(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);
extern int ep_get_ptr_file(scoap_rw_buffer_t *scratch, const scoap_packet_t *inpkt, scoap_packet_t *outpkt, uint8_t id_hi, uint8_t id_lo);


#endif
