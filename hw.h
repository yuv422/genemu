#ifndef __HW_H__
#define __HW_H__

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const uint8_t *keystate;
extern uint8_t keypressed[256];
extern uint8_t keyreleased[256];

void hw_init(void);
int hw_poll(void);

void hw_beginframe(uint8_t **screen, int *pitch);
void hw_endframe();

#define HW_AUDIO_FREQ         53267
#define HW_AUDIO_NUMSAMPLES   (HW_AUDIO_FREQ / 50)

void hw_beginaudio(int16_t **buf);
void hw_endaudio(void);

#ifdef __cplusplus
}
#endif

#endif

