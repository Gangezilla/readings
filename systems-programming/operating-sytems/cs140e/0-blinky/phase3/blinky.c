#define GPIO_BASE (0x3F000000 + 0x200000)

volatile unsigned *GPIO_FSEL1 = (volatile unsigned *)(GPIO_BASE + 0x04);
volatile unsigned *GPIO_SET0  = (volatile unsigned *)(GPIO_BASE + 0x1C);
volatile unsigned *GPIO_CLR0  = (volatile unsigned *)(GPIO_BASE + 0x28);

static void spin_sleep_us(unsigned int us) {
  for (unsigned int i = 0; i < us * 6; i++) {
    asm volatile("nop");
  }
}

static void spin_sleep_ms(unsigned int ms) {
  spin_sleep_us(ms * 1000);
}

int main(void) {
  const unsigned int gpio_16 = 16;
  // Set GPIO Pin 16 as output.
  // To set GPIO16 we need to set bits 20-18 to 001
  // 0b0000'0000'0000'0000'0100'0000'0000'0000'0000' = 0x40000
  //      └32  └28  └24  └20  └16  └12  └8   └ 4  └ 0
  *GPIO_FSEL1 += 0b001 << 18;
  // we left shift 1 18 spots from 0 to 17 to set the correct value
  
  // STEP 2: Continuously set and clear GPIO 16.
  while (1) {
    *GPIO_SET0 = 0b1 << gpio_16;
    spin_sleep_ms(0.1 * 1000);

    *GPIO_CLR0 = 0b1 << gpio_16;
    spin_sleep_ms(0.1 * 1000);
  }

  return 0;
}
