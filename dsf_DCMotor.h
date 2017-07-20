 /*!
 *  @brief  Cabeçalho que define a biblioteca dsf_DCMotor.h.
 *
 *  @file      dsf_DCMotor.h
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
 *            +course       Engenharia da Computação / Engenharia Elétrica
 *            +professor    Miguel Grimm <miguelgrimm@gmail.com>
 *            +students     Versão inicial:
 *            	++ Luiz Henrique Sena	<coelho.luiz.sena@gmail.com>
 *              ++ Marcelo Ferreira  	<marcelofdeaquino@gmail.com>
 *              ++ Micael Pimentel		<micaelpimentel1@gmail.com>
 *              ++ Osmar Kabashima		<kabashimajr@gmail.com>
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

#include "dsf_PWM_ocp.h"
#include "dsf_GPIO.h"

#ifndef SOURCES_DSF_DCMOTOR_H_
#define SOURCES_DSF_DCMOTOR_H_

/*!
 *  @class  dsf_DCMotor
 *
 *  @brief  Definição da classe com os métodos para uso da classe dsf_DCMotor
 *  		que é classe filha da classe dsf_PWM_Ocp, detalhes dos métodos no
 *  		arquivo .cpp.
 *
 *  @details  Essa classe é usada para configurar o periférico deo moator DC.
 *
 *  @section  Example Usage
 *
 *            Uso dos métodos para setup:
 *            +fn bindTpmPeripheral(TPM1_BASE_PTR,0);
 *            +fn setBase(PORT_C,1,PORT_C,2);
 *            +fn setSpeed(30);
 *
 */
class dsf_DCMotor : public dsf_PWM_ocp{
 private:
  dsf_GPIO base1, base2;
  uint8_t port1, port2;
  uint8_t pin1, pin2;

 public:
  /*!
  * Método construtor de inicialização dos atributos.
  */
  dsf_DCMotor();

  /*!
  * Método que seleciona o timer TMP do periférico.
  */
  bool bindTpmPeripheral(TPM_MemMapPtr tpm, uint16_t channel);

  /*!
  * Método que seleciona o gpio do periférico
  */
  bool setupPeripheral(GPIO_MemMapPtr gpio, uint8_t pin);

  /*!
  * Método que seleciona a base do periférico.
  */
  bool setBase(uint8_t port1, uint8_t pin1, uint8_t port2, uint8_t pin2);

  /*!
  * Método que define a velocidade do motor.
  */
  void setSpeed(uint16_t dutyCicle);

  /*!
  * Método que define rotação horária do motor.
  */
  void setClockWise();

  /*!
  * Método que define rotação anti-horário do motor.
  */
  void setAntiClockWise();

  /*!
  * Método que habilita a rotação do motor.
  */
  void rotateMotor();

  /*!
  * Método que desabilita a rotação do motor.
  */
  void stopMotor();
};

#endif /* SOURCES_DSF_DCMOTOR_H_ */
