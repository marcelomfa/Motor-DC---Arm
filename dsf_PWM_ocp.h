 /*!
 *  @brief  Cabeçalho que define a biblioteca dsf_PWM_ocp.h.
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

#include "stdbool.h"
#include "MKL25Z4.h"

#ifndef SOURCES_DSF_PWM_OCP_H_
#define SOURCES_DSF_PWM_OCP_H_


/*
 * TPM clock source select
 * Seleção do relógio de clock para usar no contador do TPM
 * TPM_CLK_DIS     	0	// Clock disabled
 * TPM_PLLFLL 		1	// MCGFLLCLK clock or MCGPLLCLK/2 clock
 * TPM_OSCERCLK 	2	// OSCERCLK clock
 * PM_MCGIRCLK		3	// MCGIRCLK clock
*/

typedef enum{TPM_CLK_DIS=0, TPM_PLLFLL, TPM_OSCERCLK, PM_MCGIRCLK} Clock_t;

/*
 * Modo de incremento do contador do relógio
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
 *  @brief  Definição da classe com os métodos para uso do módulo PWM, detalhes
 *          dos métodos no arquivo .cpp.
 *
 *  @details  Essa classe é usada para configurar o módulo PWM e selecionar a gpio,
 *  		  o canal e o timer (TMP) do módulo.
 *
 *  @section  Example Usage
 *
 *            Uso dos métodos para setup:
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
	   * Método construtor de inicialização dos atributos.
	   */
	dsf_PWM_ocp();

	  /*!
	   * Método que seleciona o periférico TPM do módulo PWM.
	   */
	bool bindPeripheral(TPM_MemMapPtr tpm);

	  /*!
	   * Método que define a frequência do sinal PWM.
	   */
	bool setFrequence(uint16_t freq);

	  /*!
	   * Método que seleciona o canal.
	   */
	bool bindChannel(uint16_t channel);

	  /*!
	   * Método que seleciona a porta do sinal PWM.
	   */
	bool bindPort(GPIO_MemMapPtr gpio, uint8_t pin);

	  /*!
	   * Método que seleciona o duty cicle do sinal PWM.
	   */
	void setDutyCycle(uint16_t dutyCicle);

	  /*!
	   * Método que habilita o periférico.
	   */
	void enableOperation();

	  /*!
	   * Método que desqabilita o periférico.
	   */
	void disableOperation();
};

#endif /* SOURCES_DSF_PWM_OCP_H_ */
