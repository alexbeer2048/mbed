#include "mbed.h"

#if defined(TARGET_LPC1768)
#define UART_TX             p9
#define UART_RX             p10
#define FLOW_CONTROL_RTS    p30
#define FLOW_CONTROL_CTS    p29
#define RTS_CHECK_PIN       p8

#elif defined(TARGET_SAMR21G18A)
#define UART_TX             PA04
#define UART_RX             PA05
#define FLOW_CONTROL_RTS    PA06
#define FLOW_CONTROL_CTS    PA07
#define RTS_CHECK_PIN       PB03

#else
#error This test is not supported on this target
#endif

Serial pc(UART_TX, UART_RX);

#ifdef RTS_CHECK_PIN
InterruptIn in(RTS_CHECK_PIN);
DigitalOut led(LED1);
static void checker(void) {
  led = !led;
}
#endif

int main() {
    char buf[256];

    pc.set_flow_control(Serial::RTSCTS, FLOW_CONTROL_RTS, FLOW_CONTROL_CTS);
#ifdef RTS_CHECK_PIN
    in.fall(checker);
#endif
    while (1) {
        pc.gets(buf, 256);
        pc.printf("%s", buf);
    }
}
