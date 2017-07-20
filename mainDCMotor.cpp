/*!
 *  @brief     Programa principal que controla o funcionamento do Motor DC
 *
 *  @file      mainDCMotor.cpp
 *  @version   1.0
 *  @date      23 June 2017
 *
 *  @section  HARDWARE & SOFTWARE
 *            +board      FRDM-KL25Z da NXP
 *            +processor  MKL25Z128VLK4 - ARM Cortex-M0+
 *            +compile    Kinetis design Studio IDE.
 *            +manual     L25P80M48SF0RM, Rev.3, September 2012.
 *
 *  @section  AUTHORS & DEVELOPMENT
 *            +institution  Universidade Federal do Amazonas
 *            +course       Engenharia da Computação / Engenharia Elétrica
 *            +professor    Miguel Grimm <miguelgrimm@gmail.com>
 *            +students     Versão inicial:
 *              ++ Luiz Henrique Sena <coelho.luiz.sena@gmail.com>
 *              ++ Marcelo Ferreira   <marcelofdeaquino@gmail.com>
 *              ++ Micael Pimentel    <micaelpimentel1@gmail.com>
 *              ++ Osmar Kabashima    <kabashimajr@gmail.com>
 *
 * @copyright   GNU General Public License (GNU GPL)
 *
 * @section     LICENSE
 *              Este programa é um software livre; Você pode redistribuí-lo
 *              e/ou modificá-lo de acordo com os termos do "GNU General Public
 *              License" como publicado pela Free Software Foundation; Seja a
 *              versão 3 da licença, ou qualquer versão posterior.
 *
 *              Este programa é distribuído na esperança de que seja útil,
 *              mas SEM QUALQUER GARANTIA; Sem a garantia implícita de
 *              COMERCIALIZAÇÃO OU USO PARA UM DETERMINADO PROPÓSITO.
 *              Veja o site da "GNU General Public License" para mais detalhes.
 *
 * @htmlonly    http://www.gnu.org/copyleft/gpl.html
 */

#include "dsf_DCMotor.h"
#include "dsf_GPIO.h"
#include "MKL25Z4.h"

#define DUTY_MIN 1 /*! Define o duty cicle mínimo do dsf_PWM_ocp. */
#define DUTY_MAX 100 /*! Define o duty cicle máximo do dsf_PWM_ocp. */

 /*!
  * Variáveis contadoras dos laços de repetição.
  */
uint16_t i = 0;
uint16_t x = 0;

int main(void) {
  /*!
   *  Seta o contador do laço com o valor máximo do duty cicle.
   */
  x = DUTY_MAX;

  /*!
   *  Instanciação de um objeto da classe dsf_RGBLed.
   */
  dsf_DCMotor mdc;

  /*!
   *  Chamada das função do objeto pwm_led_verde
   */
  mdc.bindTpmPeripheral(TPM1_BASE_PTR, 0);
  mdc.setBase(PORT_C, 1, PORT_C, 2);
  mdc.setupPeripheral(GPIOB, 0);
  mdc.setSpeed(30);
  mdc.setClockWise();
  mdc.rotateMotor();

  /*!
   *  Loop onde ocorre a variação do duty cicle.
   */
  for ( ; ; ) {
    for (i = 0; i < 10000; i++) {
    }
    /*!
    *  Set valor Duty Cycle
    */
    mdc.setSpeed(x);

    /*!
    *  Incrementa o valor de x
    */
    x++;
    if (x >= DUTY_MAX) {
      x = DUTY_MIN;
    }
  }
  return 0;
}
