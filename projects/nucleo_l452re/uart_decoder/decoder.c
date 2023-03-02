
/*
>WELCOME_CHALLENGE(seqno) 12 AB 12 AB 12 AB
<ACK(WELCOME_CHALLENGE,seqno)
<WELCOME_RESPONSE 23 23 12 56 67 23
<23 12 45 56 87 65 23
^56 23 23 34 87
<"er df fg d \r\n"
<MUX OVERFLOW
<FRAMING ERROR
<PARITY ERROR
*/

#if 0
void decoder_init(struct decoder *dec, char prefix, uint8_t color, uint8_t bold_color, uint8_t super_color, uint8_t *line_buffer, uint32_t line_buffer_size);
void decoder_event(struct decoder *dec, enum event);
void decoder_data(struct decoder *dec, uint8_t byte);
void decoder_poll(struct decoder *dec);
#endif
