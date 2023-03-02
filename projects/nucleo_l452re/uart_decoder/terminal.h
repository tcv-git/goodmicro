#if 0
void terminal_init(uint8_t default_color);
void terminal_set_color(uint8_t color);
void terminal_write(const uint8_t *data, uint32_t count);
void terminal_write_line(uint64_t timestamp, uint8_t color, struct linebuffer *lb);
void terminal_restore(void);
#endif
