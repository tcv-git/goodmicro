// struct_queue.c
// PUBLIC DOMAIN
// https://www.purposeful.co.uk/goodmicro/

/*
  I, Tom Vajzovic, am the author of this software and its documentation.
  I permanently abandon all copyright and other intellectual property rights
  in them.

  I am fairly certain that the software does what the documentation says it
  does, but I do not guarantee that it does, or that it does what you think it
  should.  I do not guarantee that it will not have undesirable side effects.

  If you use, modify or distribute this software then you do so at your own
  risk.  If you do not pass on this warning then you may be responsible for any
  problems encountered by those who obtain the software through you.
*/

#include <stddef.h>
#include <stdint.h>
#include "atomic_test_and_set.h"
#include "struct_queue.h"


void queue_write(struct queued_item * volatile * head_ptr, struct queued_item *new_item)
{
    for (;;)
    {
        struct queued_item *old_head = *head_ptr;

        new_item->next = old_head;

        if (atomic_change_u32_from_to((volatile uint32_t*)head_ptr, (uint32_t)old_head, (uint32_t)new_item) == 0)
        {
            return;
        }
    }
}

struct queued_item *queue_read(struct queued_item * volatile * head_ptr)
{
    for (;;)
    {
        struct queued_item *head = *head_ptr;

        if (head == NULL)
        {
            return NULL;
        }

        if (head->next == NULL)
        {
            if (atomic_change_u32_from_to((volatile uint32_t*)head_ptr, (uint32_t)head, (uint32_t)NULL) == 0)
            {
                return head;
            }
            else
            {
                // restart at head
                continue;
            }
        }
        else
        {
            struct queued_item *previous = head;

            for (;;)
            {
                struct queued_item *current = previous->next;

                if (current->next == NULL)
                {
                    previous->next = NULL;
                    return current;
                }
                else
                {
                    previous = current;
                }
            }
        }
    }
}
