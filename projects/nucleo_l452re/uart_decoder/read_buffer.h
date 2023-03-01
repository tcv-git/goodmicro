
struct usart_receiver
{
  uint8_t *buffer;
  uint32_t buffer_size;
  uint32_t buffer_count;
  uint32_t last_rx_time;
};

void usart_receiver_init(struct usart_receiver *receiver, uint8_t *buffer, uint32_t buffer_size);
void usart_receiver_poll(struct usart_receiver *receiver);

void read_buffer_add(int received_data, uint32_t timstamp);


