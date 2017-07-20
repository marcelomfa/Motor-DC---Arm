 /*!
 *  @brief  Cabe�alho que define a biblioteca dsf_PWM_ocp.h.
 *
 *  @file      dsf_PWM_ocp.h
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

#include "stdbool.h"
#include "MKL25Z4.h"

#ifndef SOURCES_DSF_PWM_OCP_H_
#define SOURCES_DSF_PWM_OCP_H_


/*
 * TPM clock source select
 * Sele��o do rel�gio de clock para usar no contador do TPM
 * TPM_CLK_DIS     	0	// Clock disabled
 * TPM_PLLFLL 		1	// MCGFLLCLK clock or MCGPLLCLK/2 clock
 * TPM_OSCERCLK 	2	// OSCERCLK clock
 * PM_MCGIRCLK		3	// MCGIRCLK clock
*/

typedef enum{TPM_CLK_DIS=0, TPM_PLLFLL, TPM_OSCERCLK, PM_MCGIRCLK} Clock_t;

/*
 * Modo de incremento do contador do rel�gio
 *
 * TPM_CNT_DIS		0	// counter is disable
 * TPM_CLK			1	// counter increments on every LPTPM counter clock
 * TPM_EXT_CLK		2	// counter increments on rising edge of LPTPM_EXTCLK synchronized to the LPTPM counter clock
 *
 */

typedef enum{TPM_CNT_DIS=0, TPM_CLK, TPM_EXT_CLK} Tpm_mode;

/*
 * Valor do fator de Freescale
 *
 * PS_1			0
 * PS_2			1
 * PS_4			2
 * PS_8			3
 * PS_16		4
 * PS_32		5
 * PS_64		6
 * PS_128		7
 *
 */

typedef enum{PS_1, PS_2, PS_4, PS_8, PS_16, PS_32, PS_64, PS_128} Tpm_ps;

//typedef enum{dsf_TPM0=0x40038000u, dsf_TPM1=0x40039000u, dsf_TPM2=0x4003A000u} dsf_TPMx_t;

#define TPM_OC_TOGGLE	TPM_CnSC_MSA_MASK|TPM_CnSC_ELSA_MASK
#define TPM_OC_CLR		TPM_CnSC_MSA_MASK|TPM_CnSC_ELSB_MASK
#define TPM_OC_SET		TPM_CnSC_MSA_MASK|TPM_CnSC_ELSA_MASK|TPM_CnSC_ELSB_MASK
#define TPM_OC_OUTL		TPM_CnSC_MSB_MASK|TPM_CnSC_MSA_MASK|TPM_CnSC_ELSB_MASK
#define TPM_OC_OUTH		TPM_CnSC_MSB_MASK|TPM_CnSC_MSA_MASK|TPM_CnSC_ELSA_MASK
#define TPM_PWM_H 		TPM_CnSC_MSB_MASK|TPM_CnSC_ELSB_MASK
#define TPM_PWM_L		TPM_CnSC_MSB_MASK|TPM_CnSC_ELSA_MASK
#define EDGE_PWM		0
#define CENTER_PWM		1
/* */

/*!
 *  @class  dsf_PWM_ocp
 *
 *  @brief  Defini��o da classe com os m�todos para uso do m�dulo PWM, detalhes
 *          dos m�todos no arquivo .cpp.
 *
 *  @details  Essa classe � usada para configurar o m�dulo PWM e selecionar a gpio,
 *  		  o canal e o timer (TMP) do m�dulo.
 *
 *  @section  Example Usage
 *
 *            Uso dos m�todos para setup:
 *            +fn bindPeripheral(TPM2_BASE_PTR);
 *            +fn bindChannel(1);
 *            +fn setFrequence(100);
 *
 */
class dsf_PWM_ocp {
private:
	TPM_MemMapPtr tpm;
	uint16_t channel;
	GPIO_MemMapPtr gpio;
	uint8_t pin;
public:

	  /*!
	   * M�todo construtor de inicializa��o dos atributos.
	   */
	dsf_PWM_ocp();

	  /*!
	   * M�todo que seleciona o perif�rico TPM do m�dulo PWM.
	   */
	bool bindPeripheral(TPM_MemMapPtr tpm);

	  /*!
	   * M�todo que define a frequ�ncia do sinal PWM.
	   */
	bool setFrequence(uint16_t freq);

	  /*!
	   * M�todo que seleciona o canal.
	   */
	bool bindChannel(uint16_t channel);

	  /*!
	   * M�todo que seleciona a porta do sinal PWM.
	   */
	bool bindPort(GPIO_MemMapPtr gpio, uint8_t pin);

	  /*!
	   * M�todo que seleciona o duty cicle do sinal PWM.
	   */
	void setDutyCycle(uint16_t dutyCicle);

	  /*!
	   * M�todo que habilita o perif�rico.
	   */
	void enableOperation();

	  /*!
	   * M�todo que desqabilita o perif�rico.
	   */
	void disableOperation();
};

#endif /* SOURCES_DSF_PWM_OCP_H_ */
