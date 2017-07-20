 /*!
 *  @brief  Define todas as m�todos para funcionamento da classe do
 *  		motor DC para chip FRDM-K64F.
 *
 *  @file      dsf_DCMotor.cpp
 *  @version   1.0
 *  @date      13 July 2017
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
 *            	++ Luiz Henrique Sena	<coelho.luiz.sena@gmail.com>
 *              ++ Marcelo Ferreira  	<marcelofdeaquino@gmail.com>
 *              ++ Micael Pimentel		<micaelpimentel1@gmail.com>
 *              ++ Osmar Kabashima		<kabashimajr@gmail.com>
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

#include <dsf_DCMotor.h>

  /*!
  * M�todo construtor de inicializa��o dos atributos.
  */
dsf_DCMotor::dsf_DCMotor() {
  /*!
  * TODO Auto-generated constructor stub
  */
}

  /*!
  * M�todo que seleciona o timer TMP do perif�rico.
  */
bool dsf_DCMotor::bindTpmPeripheral(TPM_MemMapPtr tpm, uint16_t channel) {
  this->bindPeripheral(tpm);
  this->bindChannel(channel);
  this->setFrequence(100);
  return true;
}

  /*!
  * M�todo que seleciona o gpio do perif�rico
  */
bool dsf_DCMotor::setupPeripheral(GPIO_MemMapPtr gpio, uint8_t pin) {
  this->bindPort(gpio, pin);
  return true;
}

  /*!
  * M�todo que define a velocidade do motor.
  */
void dsf_DCMotor::setSpeed(uint16_t dutyCicle) {
  this->setDutyCycle(dutyCicle);
}

  /*!
  * M�todo que habilita a rota��o do motor.
  */
void dsf_DCMotor::rotateMotor() {
  this->enableOperation();
}

  /*!
  * M�todo que desabilita a rota��o do motor.
  */
void dsf_DCMotor::stopMotor() {
  this->disableOperation();
}

  /*!
  * M�todo que seleciona a base do perif�rico.
  */
bool dsf_DCMotor::setBase(uint8_t port1, uint8_t pin1, uint8_t port2,
uint8_t pin2) {
  this->port1 = port1;
  this->port2 = port2;
  this->pin1 = pin1;
  this->pin2 = pin2;
  this->base1.gpio_direction(port1, pin1, OUTPUT, NO_PULL_RESISTOR);
  this->base2.gpio_direction(port2, pin2, OUTPUT, NO_PULL_RESISTOR);
  return true;
}

  /*!
  * M�todo que define rota��o hor�ria do motor.
  */
void dsf_DCMotor::setClockWise() {
  this->base1.gpio_set(this->port1, this->pin1, HIGH);
  this->base2.gpio_set(this->port2, this->pin2, LOW);
}

  /*!
  * M�todo que define rota��o anti-hor�rio do motor.
  */
void dsf_DCMotor::setAntiClockWise() {
  this->base1.gpio_set(this->port1, this->pin1, LOW);
  this->base2.gpio_set(this->port2, this->pin2, HIGH);
}
