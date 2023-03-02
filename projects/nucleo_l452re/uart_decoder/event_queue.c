







#if 0

void usart_receiver_init(
        struct usart_receiver *receiver,
        uint8_t *buffer,
        uint32_t buffer_size);
{
  receiver->usart           = usart;
  receiver->buffer          = buffer;
  receiver->buffer_size     = buffer_size;
  receiver->buffer_count    = 0;
  receiver->last_rx_time    = clock_read();
  receiver->intermcu_active = false;

}


void read_buffer_add(int received_data, uint32_t timstamp)
{
  if ((received_data == NO_DATA) || (received_data == TIMEOUT))
  {
    // recalculate in software whether we have timed out
    // because not all UARTs support hardware timeout

    uint32_t elapsed = (timstamp - receiver->last_rx_time);

    received_data = ((elapsed > CLOCK_TIMEOUT) ? TIMEOUT : NO_DATA);
  }

  if (received_data >= 0)
  {
    buffer[buffer_count] = received_data;
    buffer_count++;
  }

  bool full = (buffer_count == buffer_size);





}




void poll_receiver(struct usart_receiver *receiver)
{
  uint32_t now = time_now();

  if (!(receiver->usart->SR & USART_SR_RXNE))
  {
    if ((now - receiver->last_rx_time) > BYTE_TIMEOUT)
    {
      if (receiver->intermcu_active)
      {
        print_incomplete_intermcu(receiver->buffer, receiver->count);
      }
      else
      {
        print_non_intermcu(receiver->buffer, receiver->count);
      }

      receiver->count = 0;
    }

    return;
  }

  receiver->buffer[receiver->count++] = receiver->usart->RDR;

  receiver->last_rx_time = now;

  if (intermcu_message_complete(receiver->buffer, receiver->count))
  {
    intermcu_output_message(receiver->buffer, receiver->count);
    receiver->count = 0;
  }
}


uint buffer_full(buffer, count);

enum event {
  new data,
  timeout,

#endif
