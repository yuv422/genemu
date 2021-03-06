
#include <stdint.h>

#if 0
#define VDP_MASTER_FREQ       53693175   // NTSC
#define VDP_MASTER_FREQ       53203424   // PAL
#endif

#define VDP_CYCLES_PER_LINE   3420
#define YM2612_FREQ           53267

#define M68K_FREQ_DIVISOR     7
#define Z80_FREQ_DIVISOR      14

class VDP
{
    friend class GFX;
    friend bool loadstate(const char *fn);
    friend void savestate(const char *fn);

private:
    uint8_t VRAM[0x10000];
    uint16_t CRAM[0x40];
    uint16_t VSRAM[0x40];  // only 40 words are really used
    uint8_t SAT_CACHE[0x400]; // internal copy of SAT
    uint8_t regs[0x20];
    uint16_t fifo[4];
    uint16_t address_reg;
    uint8_t code_reg;
    uint16_t status_reg;
    bool hint_pending;
    int _vcounter;
    int line_counter_interrupt;
    bool command_word_pending;
    bool dma_fill_pending;
    bool hvcounter_latched;
    uint16_t hvcounter_latch;
    int sprite_overflow;
    bool sprite_collision;
    int mode_h40;
    int mode_pal;

    void VRAM_W(uint16_t address, uint8_t value);

private:
    void register_w(int reg, uint8_t value);
    int vcounter();
    int hcounter();
    bool vblank();
    void dma_trigger();
    void dma_fill(uint16_t value);
    void dma_copy();
    void dma_m68k();
    void push_fifo(uint16_t value);

    int get_nametable_A();
    int get_nametable_B();
    int get_nametable_W();

public:
    void scanline(uint8_t *screen);
    void reset();
    unsigned int num_scanlines();

public:
    uint16_t status_register_r();
    void control_port_w(uint16_t value);
    void data_port_w16(uint16_t value);
    uint16_t data_port_r16(void);
    uint16_t hvcounter_r16(void);

    int irq_acked(int level);
};

extern class VDP VDP;

void vdp_init(void);
void vdp_scanline(uint8_t *screen);

void vdp_mem_w8(unsigned int address, unsigned int value);
void vdp_mem_w16(unsigned int address, unsigned int value);

unsigned int vdp_mem_r8(unsigned int address);
unsigned int vdp_mem_r16(unsigned int address);
