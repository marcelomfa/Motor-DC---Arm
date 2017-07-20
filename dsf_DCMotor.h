 /*!
 *  @brief  Cabe�alho que define a biblioteca dsf_DCMotor.h.
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

#include "dsf_PWM_ocp.h"
#include "dsf_GPIO.h"

#ifndef SOURCES_DSF_DCMOTOR_H_
#define SOURCES_DSF_DCMOTOR_H_

/*!
 *  @class  dsf_DCMotor
 *
 *  @brief  Defini��o da classe com os m�todos para uso da classe dsf_DCMotor
 *  		que � classe filha da classe dsf_PWM_Ocp, detalhes dos m�todos no
 *  		arquivo .cpp.
 *
 *  @details  Essa classe � usada para configurar o perif�rico deo moator DC.
 *
 *  @section  Example Usage
 *
 *            Uso dos m�todos para setup:
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
  * M�todo construtor de inicializa��o dos atributos.
  */
  dsf_DCMotor();

  /*!
  * M�todo que seleciona o timer TMP do perif�rico.
  */
  bool bindTpmPeripheral(TPM_MemMapPtr tpm, uint16_t channel);

  /*!
  * M�todo que seleciona o gpio do perif�rico
  */
  bool setupPeripheral(GPIO_MemMapPtr gpio, uint8_t pin);

  /*!
  * M�todo que seleciona a base do perif�rico.
  */
  bool setBase(uint8_t port1, uint8_t pin1, uint8_t port2, uint8_t pin2);

  /*!
  * M�todo que define a velocidade do motor.
  */
  void setSpeed(uint16_t dutyCicle);

  /*!
  * M�todo que define rota��o hor�ria do motor.
  */
  void setClockWise();

  /*!
  * M�todo que define rota��o anti-hor�rio do motor.
  */
  void setAntiClockWise();

  /*!
  * M�todo que habilita a rota��o do motor.
  */
  void rotateMotor();

  /*!
  * M�todo que desabilita a rota��o do motor.
  */
  void stopMotor();
};

#endif /* SOURCES_DSF_DCMOTOR_H_ */
