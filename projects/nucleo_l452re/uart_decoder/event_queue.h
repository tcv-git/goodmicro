


#if 0
#define MASK_EVENT    0xF000
#define MASK_CHANNEL  0x0F00
#define MASK_DATA     0x00FF

enum event_type
{
  EVENT_NO_DATA, // events of this type aren't put in the queue but are returned if the queue is empty
  EVENT_TIMEOUT,
  EVENT_DATA,
  EVENT_OVERRUN,
  EVENT_NOISE_ERROR,
  EVENT_FRAMING_ERROR,
  EVENT_PARITY_ERROR,
};

struct event_queue
{
  uint16_t *buffer;
  uint32_t buffer_length;
  uint32_t next_write;
  uint32_t next_read;
};

void event_queue_init(struct event_queue *q, uint16_t *buffer, uint32_t buffer_length);
void event_queue_put(struct event_queue *q, enum event_type event, uint8_t channel, uint8_t data);
uint16_t event_queue_get(struct event_queue *q);

enum event_type event_get_type(uint16_t packed_event);
unsigned int event_get_channel(uint16_t packed_event);
uint8_t event_get_data(uint16_t packed_event);
#endif



#if 0

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

#endif
