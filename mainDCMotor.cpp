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
 *            +course       Engenharia da Computa��o / Engenharia El�trica
 *            +professor    Miguel Grimm <miguelgrimm@gmail.com>
 *            +students     Vers�o inicial:
 *              ++ Luiz Henrique Sena <coelho.luiz.sena@gmail.com>
 *              ++ Marcelo Ferreira   <marcelofdeaquino@gmail.com>
 *              ++ Micael Pimentel    <micaelpimentel1@gmail.com>
 *              ++ Osmar Kabashima    <kabashimajr@gmail.com>
 *
 * @copyright   GNU General Public License (GNU GPL)
 *
 * @section     LICENSE
 *              Este programa � um software livre; Voc� pode redistribu�-lo
 *              e/ou modific�-lo de acordo com os termos do "GNU General Public
 *              License" como publicado pela Free Software Foundation; Seja a
 *              vers�o 3 da licen�a, ou qualquer vers�o posterior.
 *
 *              Este programa � distribu�do na esperan�a de que seja �til,
 *              mas SEM QUALQUER GARANTIA; Sem a garantia impl�cita de
 *              COMERCIALIZA��O OU USO PARA UM DETERMINADO PROP�SITO.
 *              Veja o site da "GNU General Public License" para mais detalhes.
 *
 * @htmlonly    http://www.gnu.org/copyleft/gpl.html
 */

#include "dsf_DCMotor.h"
#include "dsf_GPIO.h"
#include "MKL25Z4.h"

#define DUTY_MIN 1 /*! Define o duty cicle m�nimo do dsf_PWM_ocp. */
#define DUTY_MAX 100 /*! Define o duty cicle m�ximo do dsf_PWM_ocp. */

 /*!
  * Vari�veis contadoras dos la�os de repeti��o.
  */
uint16_t i = 0;
uint16_t x = 0;

int main(void) {
  /*!
   *  Seta o contador do la�o com o valor m�ximo do duty cicle.
   */
  x = DUTY_MAX;

  /*!
   *  Instancia��o de um objeto da classe dsf_RGBLed.
   */
  dsf_DCMotor mdc;

  /*!
   *  Chamada das fun��o do objeto pwm_led_verde
   */
  mdc.bindTpmPeripheral(TPM1_BASE_PTR, 0);
  mdc.setBase(PORT_C, 1, PORT_C, 2);
  mdc.setupPeripheral(GPIOB, 0);
  mdc.setSpeed(30);
  mdc.setClockWise();
  mdc.rotateMotor();

  /*!
   *  Loop onde ocorre a varia��o do duty cicle.
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
