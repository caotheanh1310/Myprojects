#include <stdbool.h>
#include "nrf.h"
#include "nrf_drv_gpiote.h"
#include "app_error.h"
#include "boards.h"
#include "stdint.h"
#include "nrfx.h"

#define BUTTON 27
#define LED_1 11
#define LED_2 7

int a=0;
void in_pin_handler(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action)
{
  a++;
}

static void gpio_init(void)
{
    ret_code_t err_code;
    err_code = nrf_drv_gpiote_init();
    APP_ERROR_CHECK(err_code);
    nrf_gpio_cfg_output(LED_1);
    nrf_gpio_cfg_output(LED_2);
    nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_HITOLO(true);
    in_config.pull = NRF_GPIO_PIN_PULLUP;
    err_code = nrf_drv_gpiote_in_init(BUTTON,&in_config,&in_pin_handler);
    APP_ERROR_CHECK(err_code);
    nrf_drv_gpiote_in_event_enable(BUTTON,true);
}

int main(void)
{
  gpio_init();
  int b=a;
  int c=0;
  while (true)
  {
    if(b !=a){
      for(int i=1000000; i>0;i--){
      }
      b=a;
      c++;
      if (c==3) c=0;
      if (c == 0){
        nrf_gpio_pin_set(LED_2);
      }
      if (c==1){
        while(b == a){
          nrf_gpio_pin_toggle(LED_1);
          NRFX_DELAY_US(50000);
        }
      }
      if (c==2){
        nrf_gpio_pin_clear(LED_1);
        while(b == a){
          nrf_gpio_pin_toggle(LED_2);
          NRFX_DELAY_US(50000);
        }
      }
    }
  }
}

