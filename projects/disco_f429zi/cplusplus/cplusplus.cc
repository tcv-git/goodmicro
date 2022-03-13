// cplusplus.cc PUBLIC DOMAIN 2020

#include "debug_printf.h"
#include "cplusplus.h"

class cplusplus
{
  public:
    cplusplus & operator=(const cplusplus &) = delete;
    cplusplus(const cplusplus &) = delete;
    cplusplus() = delete;

    cplusplus(int argument);
    ~cplusplus();

    int getmember();

  private:
    int member;
};

cplusplus::cplusplus(int argument)
  : member(argument)
{
  debug_printf("constructor %08X\n", (unsigned int)this);
}

cplusplus::~cplusplus()
{
  debug_printf("destructor  %08X\n", (unsigned int)this);
}

int cplusplus::getmember()
{
  return member;
}

cplusplus static_instance(42);

int get_member_of_static(void)
{
  return static_instance.getmember();
}

int get_member_of_stack(void)
{
  cplusplus stack_instance(50);

  return stack_instance.getmember();
}

class base
{
  public:
    virtual void virt() = 0;
};

class derrived : public base
{
  public:
    void virt();
};

void derrived::virt()
{
  debug_printf("poly\n");
}

derrived poly_instance;

void call_virt(void)
{
  base * base_pointer = &poly_instance;

  base_pointer->virt();
}
